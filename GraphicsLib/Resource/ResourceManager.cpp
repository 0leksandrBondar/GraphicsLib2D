#include "ResourceManager.h"

namespace gfx2d
{

    void ResourceManager::loadShader(const std::string& shaderName,
                                     const std::filesystem::path& vertexPath,
                                     const std::filesystem::path& fragmentPath)
    {
        _shaders[shaderName] = Shader::create(vertexPath.string(), fragmentPath.string());
    }

    ShaderPtr ResourceManager::getShader(const std::string& shaderName)
    {
        if (const auto it = _shaders.find(shaderName); it != _shaders.cend())
        {
            return it->second;
        }
        return nullptr;
    }
} // namespace gfx2d