//
// Created by fangl on 2023/7/28.
//

#include "OGLAdapter.h"

#include "Light.h"
#include "BasicGeometry.h"
#include "Model.h"

#include "MarkerSet.h"
#include "Metamer.h"
#include "Tree.h"
#include "TreeSkeleton.h"


const QVector3D CAMERA_POSITION(0.0f, 0.1f, 3.0f);

const QVector3D LIGHT_POSITION(-3.0f, 2.0f, 2.0f);
const QVector3D LIGHT_COLOR(1.0f, 1.0f, 1.0f);

const QVector3D COORDINATE_COLOR(1.0f, 1.0f, 0.0f);

const QVector3D PLANE_POSITION(0.0f, -0.01f, 0.0f);
const QVector3D PLANE_COLOR(0.5f, 0.5f, 0.5f);


// objects
std::unique_ptr<BasicGeometry> light;
std::unique_ptr<BasicGeometry> coordinate;
std::unique_ptr<BasicGeometry> plane;
std::unique_ptr<Model> my_model;

std::unique_ptr<Tree> my_tree;
std::unique_ptr<TreeSkeleton> my_treeSkeleton;


OGLAdapter::OGLAdapter(QWidget *parent, int width, int height) : QOpenGLWidget(parent) {
    this->setGeometry(10, 20, width, height);
}

OGLAdapter::~OGLAdapter() {
    delete camera;
}


// OpenGL functions

void OGLAdapter::initializeGL() {
    // core
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    core->glEnable(GL_DEPTH_TEST);

    // initialize parameters
    isOpenLighting = GL_TRUE;
    isLineMode = GL_FALSE;
    modelScaling = 0.001f;

    // initialize keyboard and mouse variables
    for(unsigned char & key : keys)
        key = GL_FALSE;

    isFirstMouse = GL_TRUE;
    isRightMousePress = GL_FALSE;

    deltaTime = 0.0f;
    lastFrame = 0.0f;
    lastX = (int)((float)width() / 2.0f);
    lastY = (int)((float)height() / 2.0f);

    eTimer.start();

    // utils initialize
    camera = new Camera(CAMERA_POSITION);

    // objects initialize
    light = std::make_unique<BasicGeometry>();
    light->init(GeometryData::getLightVertices(), Data_Type::ONLY_POSITION, Draw_Mode::TRIANGLES);

    coordinate = std::make_unique<BasicGeometry>();
    coordinate->init(GeometryData::getCoordinateVertices(),
                     Data_Type::ONLY_POSITION, Draw_Mode::LINES);

    plane = std::make_unique<BasicGeometry>();
    plane->init(GeometryData::getPlaneVertices(), Data_Type::POS_TEX_NOR, Draw_Mode::TRIANGLES);

    /*********** Tree Generator *************/
    auto seedNow = static_cast<qint32>(QDateTime::currentMSecsSinceEpoch() % 2147483647);
    QRandomGenerator randomGenerator(seedNow);
    MarkerSet markerSet(randomGenerator, 2.0f, 10, 1000 * 1000);
    Environment environment(randomGenerator, markerSet);
    my_tree = std::make_unique<Tree>(environment, Point{});

    // iteration 10 times first
    for(int i = 0; i < 2; i++)
        my_tree->performGrowthIteration();

    my_tree->countMetamers();

    my_treeSkeleton = std::make_unique<TreeSkeleton>();
    my_treeSkeleton->init(my_tree);

    my_model = std::make_unique<Model>();

    // load shader
    ResourceManager::loadShader("light",
                                ":/shaders/Shaders/pureColor.vert",
                                ":/shaders/Shaders/pureColor.frag");
    ResourceManager::loadShader("coordinate",
                                ":/shaders/Shaders/pureColor.vert",
                                ":/shaders/Shaders/pureColor.frag");
    ResourceManager::loadShader("plane",
                                ":/shaders/Shaders/basicGeometry.vert",
                                ":/shaders/Shaders/basicGeometry.frag");
    ResourceManager::loadShader("my_model",
                                ":/shaders/Shaders/model.vert",
                                ":/shaders/Shaders/model.frag");

    ResourceManager::getShader("light").use().setVector3f("objectColor", LIGHT_COLOR);
    ResourceManager::getShader("coordinate").use().setVector3f("objectColor", COORDINATE_COLOR);

    ResourceManager::getShader("plane").use().setVector3f("lightPos", LIGHT_POSITION);
    ResourceManager::getShader("plane").use().setVector3f("viewPos", camera->position);
    ResourceManager::getShader("plane").use().setVector3f("lightColor", LIGHT_COLOR);
    ResourceManager::getShader("plane").use().setVector3f("objectColor", PLANE_COLOR);

    ResourceManager::getShader("my_model").use().setInteger("material.ambientMap", 0);
    ResourceManager::getShader("my_model").use().setInteger("material.diffuseMap", 1);
    ResourceManager::getShader("my_model").use().setVector3f("light.position", LIGHT_POSITION);

    // matrix configuration
    QMatrix4x4 model;
    model.translate(LIGHT_POSITION);
    model.scale(0.1f);
    ResourceManager::getShader("light").use().setMatrix4f("model", model);
    model.setToIdentity();
    model.scale(60.0f);
    ResourceManager::getShader("coordinate").use().setMatrix4f("model", model);
    model.setToIdentity();
    model.translate(PLANE_POSITION);
    model.scale(10.0f);
    ResourceManager::getShader("plane").use().setMatrix4f("model", model);

    // background setting
    core->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    core->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void OGLAdapter::resizeGL(int w, int h) {
    core->glViewport(0, 0, w, h);
}

void OGLAdapter::paintGL() {
    // time and position data
    GLfloat currentFrame = (GLfloat)eTimer.elapsed() / 100;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    this->handleInput(deltaTime);
    this->updateGL();

    // paint objects
    ResourceManager::getShader("light").use();
    light->draw();
    ResourceManager::getShader("coordinate").use();
    // coordinate->draw();
    my_treeSkeleton->draw();

    ResourceManager::getShader("plane").use();
    plane->draw();

    if(!my_model->empty) {
        ResourceManager::getShader("my_model").use();
        my_model->draw(this->isOpenLighting);
    }

}

void OGLAdapter::updateGL() {
    if(this->isLineMode)
        core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    QMatrix4x4 projection, view;
    projection.perspective(camera->zoom, (GLfloat)width() / (GLfloat)height(), 0.1f, 200.f);
    view = camera->getViewMatrix();

    ResourceManager::getShader("light").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("light").use().setMatrix4f("view", view);

    ResourceManager::getShader("coordinate").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("coordinate").use().setMatrix4f("view", view);

    ResourceManager::getShader("plane").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("plane").use().setMatrix4f("view", view);
    ResourceManager::getShader("plane").use().setVector3f("viewPos", camera->position);


    ResourceManager::getShader("my_model").use().setMatrix4f("projection", projection);
    ResourceManager::getShader("my_model").use().setMatrix4f("view", camera->getViewMatrix());
    ResourceManager::getShader("my_model").use().setVector3f("viewPos", camera->position);

    QMatrix4x4 scaling;
    scaling.scale(modelScaling * 0.1);
    ResourceManager::getShader("my_model").use().setMatrix4f("model", scaling);

}


// control functions
void OGLAdapter::changeObjModel(const QString &fileName) {
    my_model->newModel = true;
    my_model->init(fileName);
    my_model->empty = false;
}

void OGLAdapter::clearLoadedModel() {
    my_model->clearModel();

    my_model->newModel = true;
    my_model->empty = true;
}

void OGLAdapter::handleKeyPressEvent(QKeyEvent *event) {
    GLuint key = event->key();
    if(key < 1024)
        this->keys[key] = GL_TRUE;
}

void OGLAdapter::handleKeyReleaseEvent(QKeyEvent *event) {
    GLuint key = event->key();
    if(key < 1024)
        this->keys[key] = GL_FALSE;
}

// TODO: 窗口改变会导致鼠标移动很怪
void OGLAdapter::mouseMoveEvent(QMouseEvent *event) {
    GLint xPos = event->pos().x();
    GLint yPos = event->pos().y();
    if(!isRightMousePress)
        return;

    if (isFirstMouse){
        lastX = xPos;
        lastY = xPos;
        isFirstMouse = GL_FALSE;
    }

    GLint xOffset = xPos - lastX;
    GLint yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top
    lastX = xPos;
    lastY = yPos;
    camera->handleMouseMovement((GLfloat)xOffset, (GLfloat)yOffset);
}

void OGLAdapter::wheelEvent(QWheelEvent *event) {
    QPoint offset = event->angleDelta();
    camera->handleMouseScroll((float)offset.y() / 20.0f);
}

void OGLAdapter::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::RightButton)
        isRightMousePress = GL_TRUE;
}

void OGLAdapter::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::RightButton){
        isRightMousePress = GL_FALSE;
        isFirstMouse = GL_TRUE;
    }
}

void OGLAdapter::handleInput(GLfloat dt) {
    if (keys[Qt::Key_W])
        camera->handleKeyboard(CAMERA_MOVE::FORWARD, dt);
    if (keys[Qt::Key_S])
        camera->handleKeyboard(CAMERA_MOVE::BACKWARD, dt);
    if (keys[Qt::Key_A])
        camera->handleKeyboard(CAMERA_MOVE::LEFT, dt);
    if (keys[Qt::Key_D])
        camera->handleKeyboard(CAMERA_MOVE::RIGHT, dt);
    if (keys[Qt::Key_E])
        camera->handleKeyboard(CAMERA_MOVE::UP, dt);
    if (keys[Qt::Key_Q])
        camera->handleKeyboard(CAMERA_MOVE::DOWN, dt);
}

