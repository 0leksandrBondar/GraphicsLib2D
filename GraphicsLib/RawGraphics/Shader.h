#pragma once

#include "GraphicsLib/BaseTypes/NonCopyableButMovable.h"
#include "GraphicsLib/OpenGL.h"

#include <glm/mat4x4.hpp>
#include <filesystem>

namespace gfx2d
{

    using ShaderPtr = std::shared_ptr<class Shader>;

    class Shader final : public NonCopyableButMovable
    {
    public:
        static ShaderPtr create(const std::string& vertexShader, const std::string& fragmentShader);
        ~Shader();

        void use() const;

        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setBool(const std::string& name, bool value) const;
        void setVector4(const std::string& name, const glm::vec4& value) const;
        void setMatrix4(const std::string& name, const glm::mat4& matrix) const;

    private:
        Shader(const std::filesystem::path& vertexShaderPath,
               const std::filesystem::path& fragmentShaderPath);

        int getUniformLocation(const std::string& name) const;

        void validateProgramLinking(GLuint shaderID) const;
        void validateShaderCompilation(GLuint shaderID) const;
        void createProgram(GLuint vertexShader, GLuint fragmentShader);
        GLuint createShader(const std::string& source, GLenum shaderType);
        std::string getShaderProgramSourceCode(const std::filesystem::path& shaderProgramPath);

    private:
        GLuint _id{ 0 };
        mutable std::unordered_map<std::string, int> _uniformCache;
    };
} // namespace gfx2d
