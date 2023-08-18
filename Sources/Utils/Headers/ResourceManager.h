//
// Created by fangl on 2023/7/28.
//

#ifndef MY_RESOURCEMANAGER_H
#define MY_RESOURCEMANAGER_H

#include <map>
#include <QString>

#include "ShaderManager.h"
#include "TextureManager.h"


class ResourceManager
{
public:
    static std::map<QString, ShaderManager> map_Shaders;
    static std::map<QString, TextureManager> map_Textures;

    static ShaderManager loadShader(const QString& name, const QString& vShaderFile, const QString& fShaderFile, const QString& gShaderfile = NULL);
    static ShaderManager getShader(const QString&  name);
    static TextureManager loadTexture(const QString&  name, const QString& file, GLboolean alpha = false);
    static TextureManager getTexture(const QString&  name);
    static void clear();
    static void clearTextures();

private:
    ResourceManager() {}
};


#endif //MY_RESOURCEMANAGER_H
