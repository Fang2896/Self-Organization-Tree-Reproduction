//
// Created by fangl on 2023/7/28.
//

#include "TextureManager.h"


TextureManager::TextureManager()
    : texture(nullptr), internal_format(QOpenGLTexture::RGBFormat),
    wrap_s(QOpenGLTexture::Repeat), wrap_t(QOpenGLTexture::Repeat),
    filter_min(QOpenGLTexture::Linear), filter_max(QOpenGLTexture::Linear)
{ }

TextureManager::~TextureManager() = default;

void TextureManager::generate(const QString &file) {
    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setFormat(internal_format);
    texture->setData(QImage(file).mirrored(), QOpenGLTexture::GenerateMipMaps);

    texture->setWrapMode(QOpenGLTexture::DirectionS, wrap_s);
    texture->setWrapMode(QOpenGLTexture::DirectionT, wrap_t);

    texture->setMinificationFilter(filter_min);
    texture->setMagnificationFilter(filter_max);
}

void TextureManager::bind() const {
    texture->bind();
}

