#include "ResourceManager.h"

void ResourceManager::loadShader(const std::string& shaderName,
                                 const std::filesystem::path& vertexPath,
                                 const std::filesystem::path& fragmentPath)
{
    _shaders[shaderName] = gfx2d::Shader::create(vertexPath.string(), fragmentPath.string());
}

void ResourceManager::loadTexture(const std::string& textureName,
                                  const std::filesystem::path& texturePath)
{
    _textures[textureName] = gfx2d::Texture::create(texturePath.string());
}

gfx2d::ShaderPtr ResourceManager::getShader(const std::string& shaderName)
{
    if (const auto it = _shaders.find(shaderName); it != _shaders.cend())
    {
        return it->second;
    }
    return nullptr;
}

gfx2d::TexturePtr ResourceManager::getTexture(const std::string& textureName)
{
    if (const auto it = _textures.find(textureName); it != _textures.cend())
    {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::loadAllResources()
{
    loadShader("defaultShader", "Assets/Shaders/Vertex.vert", "Assets/Shaders/Fragment.frag");
    loadTexture("Skin", "Assets/Textures/1.png");
    loadTexture("Player_idle", "Assets/Textures/Player/MPlayer_idle.png");
    loadTexture("Player_walk", "Assets/Textures/Player/MPlayer_walk.png");
    loadTexture("Tiles", "Assets/Textures/Farm/Tiles.png");
}
