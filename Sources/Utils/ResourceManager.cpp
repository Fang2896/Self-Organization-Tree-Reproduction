//
// Created by fangl on 2023/7/28.
//

#include "ResourceManager.h"

// Global variables to store Shaders and Textures
std::map<QString, ShaderManager> ResourceManager::map_Shaders;
std::map<QString, TextureManager> ResourceManager::map_Textures;

ShaderManager ResourceManager::loadShader(const QString& name,
                                          const QString& vShaderFile,
                                          const QString& fShaderFile,
                                          const QString& gShaderfile) {
    ShaderManager shaderManager{};
    shaderManager.compile(vShaderFile,
                          fShaderFile,
                          gShaderfile == nullptr ? nullptr : gShaderfile);
    map_Shaders[name] = shaderManager;
    return map_Shaders[name];
}

ShaderManager ResourceManager::getShader(const QString& name){
    return map_Shaders[name];
}

TextureManager ResourceManager::loadTexture(const QString& name, const QString& file, GLboolean alpha){
    TextureManager texture;

    if(alpha){
        texture.internal_format = QOpenGLTexture::RGBAFormat;
        texture.wrap_s = QOpenGLTexture::ClampToBorder;
        texture.wrap_t = QOpenGLTexture::ClampToBorder;
    }

    texture.generate(file);
    map_Textures[name] = texture;
    return texture;
}

TextureManager ResourceManager::getTexture(const QString& name){
    return map_Textures[name];
}

void ResourceManager::clear(){
    for (auto & map_Shader : map_Shaders)
        delete map_Shader.second.shaderProgram;
    for (auto & map_Texture : map_Textures)
        delete map_Texture.second.texture;

    map_Shaders.clear();
    map_Textures.clear();
}

void ResourceManager::clearTextures() {
    for (auto & map_Texture : map_Textures)
        delete map_Texture.second.texture;
    map_Textures.clear();
}
