//
// Created by fangl on 2023/7/28.
//

#ifndef MY_OGLADAPTER_H
#define MY_OGLADAPTER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>

#include <QTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QElapsedTimer>

#include "Camera.h"
#include "ResourceManager.h"

#include "Light.h"
#include "BasicGeometry.h"
#include "Model.h"

#include "MarkerSet.h"
#include "Metamer.h"
#include "Tree.h"
#include "TreeSkeleton.h"


class OGLAdapter : public QOpenGLWidget
{
public:
    explicit OGLAdapter(QWidget *parent = nullptr, int width = 200, int height = 200);
    ~OGLAdapter() override;

    void handleKeyPressEvent(QKeyEvent *event);
    void handleKeyReleaseEvent(QKeyEvent *event);

    void changeObjModel(const QString& fileName) const;
    void clearLoadedModel() const;

    void performTreeGrowth();
    void resetTreeGrowth();


    // Object to Rendering
    std::unique_ptr<Model> my_model;
    std::unique_ptr<BasicGeometry> light;
    std::unique_ptr<BasicGeometry> coordinate;
    std::unique_ptr<BasicGeometry> plane;

    std::unique_ptr<Tree> my_tree;
    std::unique_ptr<TreeSkeleton> my_treeSkeleton;

    GLboolean keys[1024];
    GLboolean isOpenLighting;
    GLboolean isLineMode;
    GLfloat modelScaling;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void handleInput(GLfloat dt);
    void updateGL();

    // Tree Related Parameters:
    qint32 seedNow;
    std::unique_ptr<QRandomGenerator> randomGenerator;
    std::unique_ptr<MarkerSet> markerSet;
    std::unique_ptr<Environment> environment;

    QOpenGLFunctions_4_3_Core *core;

    // control variables
    GLboolean isFirstMouse;
    GLboolean isRightMousePress;
    GLint lastX;
    GLint lastY;

    QElapsedTimer eTimer;
    GLfloat deltaTime;
    GLfloat lastFrame;

    Camera *camera;
};


#endif //MY_OGLADAPTER_H
