#pragma once

#include "GraphicsLib/BaseTypes/Singleton.h"
#include "GraphicsLib/RawGraphics/Shader.h"
#include "GraphicsLib/Graphics/Texture/Texture.h"

#include <unordered_map>

class ResourceManager final : public gfx2d::Singleton<ResourceManager>
{
public:
    ResourceManager() = default;

    void loadShader(const std::string& shaderName, const std::filesystem::path& vertexPath,
                    const std::filesystem::path& fragmentPath);

    void loadTexture(const std::string& textureName, const std::filesystem::path& texturePath);

    gfx2d::ShaderPtr getShader(const std::string& shaderName);
    gfx2d::TexturePtr getTexture(const std::string& textureName);

    void loadAllResources();

private:
    std::unordered_map<std::string, gfx2d::ShaderPtr> _shaders;
    std::unordered_map<std::string, gfx2d::TexturePtr> _textures;
};
