//
// Created by fangl on 2023/7/31.
//

#ifndef MY_BASICGEOMETRY_H
#define MY_BASICGEOMETRY_H

#include "ResourceManager.h"
#include <QOpenGLFunctions_4_3_Core>

enum class Data_Type {
    ONLY_POSITION,
    POS_TEX_NOR
};

enum class Draw_Mode {
    POINTS,
    LINES,
    LINE_STRIP,
    LINE_LOOP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN
};

class BasicGeometry {
public:
    GLuint numVertex;
    std::string shaderName;

    BasicGeometry();
    ~BasicGeometry();
    // TODO: 把后面两个参数改成成员变量
    void init(const QVector<float>& data, Data_Type dataType, Draw_Mode mode);   // position, texture, normal
    void updateVertexData(const QVector<float>& data, Data_Type dataType);
    void draw();

    void changeDrawMode(Draw_Mode mode) {
        this->drawMode = mode;
    }

private:
    QOpenGLFunctions_4_3_Core *core;
    GLuint VAO;
    GLuint VBO;

    Draw_Mode drawMode;
};


// Geometry Data:
class GeometryData {
public:
    // 1. Cube
    static const QVector<float>& getCubeVertices() {
        static QVector<float> cubeVertices =
        {
                // positions        // textures        // normals
                //Back Face
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f, //bottom-left
                0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f, //top-right
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,

                //Front Face
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

                //Left Face
                -0.5f,  0.5f,  0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,

                //Right Face
                0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,

                //Bottom Face
                -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,

                //Top Face
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        };
        return cubeVertices;
    }

    // 2. Plane
    static const QVector<float>& getPlaneVertices() {
        static QVector<float> planeVertices =
        {
                // positions        // textures        // normals
                -0.5f,  0.0f, -0.5f,   0.0f,  10.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.0f, -0.5f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.0f,  0.5f,  10.0f,   0.0f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.0f,  0.5f,  10.0f,   0.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.0f,  0.5f,   0.0f,   0.0f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.0f, -0.5f,   0.0f,  10.0f,  0.0f,  1.0f,  0.0f,
        };
        return planeVertices;
    }

    // 3. Coordinate
    static const QVector<float>& getCoordinateVertices() {
        static QVector<float> coordinateVertices =
        {
                // positions
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,

                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,

                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f
        };
        return coordinateVertices;
    }

    // 4. Light
    static const QVector<float>& getLightVertices() {
        static QVector<float> lightVertices =
        {
                // positions                        // normals           // texture coords
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,

                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,

                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,

                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f
        };
        return lightVertices;
    }

    // 禁止创建此类的实例
    GeometryData() = delete;
};

#endif //MY_BASICGEOMETRY_H
