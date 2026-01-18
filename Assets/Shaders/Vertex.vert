#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 viewMat;
uniform mat4 modelMat;
uniform mat4 projectionMat;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 0.0, 1.0);
}
