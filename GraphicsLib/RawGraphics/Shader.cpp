#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>

namespace gfx2d
{

    Shader::Shader(const std::filesystem::path& vertexShaderPath,
                   const std::filesystem::path& fragmentShaderPath)
    {
        const std::string vertexShaderSource = getShaderProgramSourceCode(vertexShaderPath);
        const std::string fragmentShaderSource = getShaderProgramSourceCode(fragmentShaderPath);
        const GLuint vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER);
        const GLuint fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
        createProgram(vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderPtr Shader::create(const std::string& vertexShader, const std::string& fragmentShader)
    {
        return std::shared_ptr<Shader>(new Shader(vertexShader, fragmentShader));
    }

    Shader::~Shader() { glDeleteProgram(_id); }

    void Shader::use() const { glUseProgram(_id); }

    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
    }

    void Shader::validateProgramLinking(GLuint shaderID) const
    {
        GLint success;
        glGetProgramiv(_id, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLint infoLogLength;
            glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::string infoLog(infoLogLength, ' ');
            glGetProgramInfoLog(_id, infoLogLength, nullptr, infoLog.data());
            glDeleteProgram(_id);
            spdlog::error("ShaderProgram::validateProgramLinking: {}", infoLog);
        }
    }

    void Shader::validateShaderCompilation(const GLuint shaderID) const
    {
        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint infoLogLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::string infoLog(infoLogLength, ' ');
            glGetShaderInfoLog(shaderID, infoLogLength, nullptr, infoLog.data());
            glDeleteShader(shaderID);

            spdlog::error("ShaderProgram::validateShaderCompilation: {}", infoLog);
        }
    }

    void Shader::setBool(const std::string& name, const bool value) const
    {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value ? GL_TRUE : GL_FALSE);
    }

    void Shader::setVector4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(value));
    }

    void Shader::setMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, value_ptr(matrix));
    }

    void Shader::createProgram(const GLuint vertexShader, const GLuint fragmentShader)
    {
        _id = glCreateProgram();
        if (_id == 0)
            spdlog::error("ShaderProgram::createProgram: Failed to create program!");

        glAttachShader(_id, vertexShader);
        glAttachShader(_id, fragmentShader);
        glLinkProgram(_id);

        validateProgramLinking(_id);
    }

    GLuint Shader::createShader(const std::string& source, const GLenum shaderType)
    {
        const GLuint shaderID = glCreateShader(shaderType);
        if (shaderID == 0)
            spdlog::error("ShaderProgram::createShader: Failed to create shader!");

        const char* sourcePointer = source.c_str();

        glShaderSource(shaderID, 1, &sourcePointer, nullptr);
        glCompileShader(shaderID);

        validateShaderCompilation(shaderID);

        return shaderID;
    }

    std::string Shader::getShaderProgramSourceCode(const std::filesystem::path& shaderProgramPath)
    {
        std::ifstream file(shaderProgramPath);
        file.open(shaderProgramPath, std::ios::in | std::ios::binary);
        if (!file.is_open())
            throw std::runtime_error("[Shader::getShaderProgramSourceCode] Failed to open file "
                                     + shaderProgramPath.string());

        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
} // namespace gfx2d
