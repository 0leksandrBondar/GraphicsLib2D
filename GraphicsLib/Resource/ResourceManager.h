#pragma once

#include "GraphicsLib/BaseTypes/Singleton.h"
#include "GraphicsLib/RawGraphics/Shader.h"

#include <unordered_map>

namespace gfx2d
{
    class ResourceManager final : public Singleton<ResourceManager>
    {
    public:
        ResourceManager() = default;

        void loadShader(const std::string& shaderName, const std::filesystem::path& vertexPath,
                        const std::filesystem::path& fragmentPath);

        ShaderPtr getShader(const std::string& shaderName);

    private:
        std::unordered_map<std::string, ShaderPtr> _shaders;
    };
} // namespace gfx2d