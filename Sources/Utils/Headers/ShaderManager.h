//
// Created by fangl on 2023/7/28.
//

#ifndef MY_SHADERMANAGER_H
#define MY_SHADERMANAGER_H

#include <QDebug>
#include <QString>

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class ShaderManager
{
    friend class ResourceManager;
public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    void compile(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource = nullptr);

    ShaderManager& use(){
        shaderProgram->bind();
        return *this;
    }

    void setFloat(const QString& name, const GLfloat& value) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setInteger(const QString& name, const GLint& value) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setVector2f(const QString& name, const GLfloat& x, const GLfloat& y) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, QVector2D(x, y));
    }

    void setVector2f(const QString& name, const QVector2D& value) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setVector3f(const QString& name, const GLfloat& x, const GLfloat& y, const GLfloat& z) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, QVector3D(x, y, z));
    }

    void setVector3f(const QString& name, const QVector3D& value) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setVector4f(const QString& name, const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, QVector4D(x, y, z, w));
    }

    void setVector4f(const QString& name, const QVector4D& value) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setMatrix4f(const QString& name, const QMatrix4x4& value) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setBool(const QString& name, const GLboolean& value) const {
        GLint loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

private:
    QOpenGLShaderProgram *shaderProgram;
};

#endif //MY_SHADERMANAGER_H
