//
// Created by fangl on 2023/7/28.
//

#ifndef MY_TEXTUREMANAGER_H
#define MY_TEXTUREMANAGER_H

#include <QOpenGLTexture>
#include <memory>

class TextureManager
{
    friend class ResourceManager;
public:
    TextureManager();
    ~TextureManager();
    void generate(const QString& file);
    void bind() const;

    QOpenGLTexture::TextureFormat internal_format;//Format of texture object
    QOpenGLTexture::WrapMode wrap_s;
    QOpenGLTexture::WrapMode wrap_t;
    QOpenGLTexture::Filter filter_min;
    QOpenGLTexture::Filter filter_max;

private:
    QOpenGLTexture* texture;
};


#endif //MY_TEXTUREMANAGER_H
