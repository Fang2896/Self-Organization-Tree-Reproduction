//
// Created by fangl on 2023/7/30.
//

#ifndef MY_MODEL_H
#define MY_MODEL_H


#include <QOpenGLFunctions_4_3_Core>
#include "../../Managers/Headers/ResourceManager.h"
#include <QVector>

#include <QDebug>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLTexture>
#include <QMap>

class Object;
class Material;

class Model
{
public:
    Model();
    bool init(const QString& path);
    void draw(GLboolean isOpenLighting = GL_FALSE);
    void clearModel();

    GLboolean empty = true;
    GLboolean newModel = true;

private:
    bool loadOBJ(const QString& path);
    void bindBufferData();
    void enableBufferData(Object &object);

    QOpenGLFunctions_4_3_Core *core;
    QVector<Object> objects;
    QMap<QString, Material> map_materials;
};

class Object{
public:
    GLuint VAO;
    GLuint positionVBO;
    GLuint uvVBO;
    GLuint normalVBO;

    QVector<QVector3D> positions;
    QVector<QVector2D> uvs;
    QVector<QVector3D> normals;

    QString matName;
};

class Material{
public:
    QVector3D Ka;
    QVector3D Kd;
    QVector3D Ks;
    double shininess;

    QString name_map_Ka;
    QString name_map_Kd;

    // TODO: add name_map_bump
};


#endif //MY_MODEL_H
