#version 460 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec4 spriteColor;
uniform bool useTexture;

void main()
{
    vec4 baseColor = spriteColor;

    if (useTexture)
    {
        vec4 texColor = texture(tex, TexCoord);

        baseColor.rgb = mix(baseColor.rgb, texColor.rgb, texColor.a);
        baseColor.a   = spriteColor.a;
    }

    FragColor = baseColor;
}

