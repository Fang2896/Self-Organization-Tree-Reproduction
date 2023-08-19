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

#include "../Managers/Headers/Camera.h"
#include "../Managers/Headers/ResourceManager.h"


class OGLAdapter : public QOpenGLWidget
{
public:
    explicit OGLAdapter(QWidget *parent = nullptr, int width = 200, int height = 200);
    ~OGLAdapter() override;

    void handleKeyPressEvent(QKeyEvent *event);
    void handleKeyReleaseEvent(QKeyEvent *event);

    static void changeObjModel(const QString& fileName);
    static void clearLoadedModel();

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
