//
// Created by fangl on 2023/7/28.
//

#include "ShaderManager.h"


void ShaderManager::compile(const QString& vertexSource, const QString& fragmentSource, const QString& geometrySource) {
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    bool success = vertexShader.compileSourceFile(vertexSource);
    if(!success){
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << Qt::endl;
        qDebug() << vertexShader.log() << Qt::endl;
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    success  = fragmentShader.compileSourceFile(fragmentSource);
    if(!success){
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << Qt::endl;
        qDebug() << fragmentShader.log() << Qt::endl;
    }

    QOpenGLShader geometryShader(QOpenGLShader::Geometry);
    if(geometrySource != nullptr){
        success  = geometryShader.compileSourceFile(geometrySource);
        if(!success){
            qDebug() << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED" << Qt::endl;
            qDebug() << geometryShader.log() << Qt::endl;
        }
    }

    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShader(&vertexShader);
    shaderProgram->addShader(&fragmentShader);
    if(geometrySource != nullptr)
        shaderProgram->addShader(&geometryShader);
    success = shaderProgram->link();
    if(!success){
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << Qt::endl;
        qDebug() << shaderProgram->log() << Qt::endl;
    } else {
        qDebug() << "Successfully Load Shader." << Qt::endl;
    }
}
