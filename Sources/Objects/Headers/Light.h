//
// Created by fangl on 2023/7/28.
//

#ifndef MY_LIGHT_H
#define MY_LIGHT_H

#include <QOpenGLFunctions_4_3_Core>


class Light
{
public:
    Light();
    ~Light();
    void init();
    void drawLight();
private:
    QOpenGLFunctions_4_3_Core *core;
    GLuint lightVAO;
    GLuint lightVBO;
};


#endif //MY_LIGHT_H
