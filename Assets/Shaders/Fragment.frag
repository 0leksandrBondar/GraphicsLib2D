#version 460 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec4 color;
uniform bool useTexture;
uniform bool selection;

uniform vec4 outlineColor = vec4(1,1,0,1);

vec4 getOutlineColor(vec2 uv)
{
    float alpha = texture(tex, uv).a;

    if (alpha > 0.1)
    return vec4(0.0);

    vec2 texel = 1.0 / vec2(textureSize(tex, 0));

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            vec2 offset = vec2(x,y) * texel;

            if (texture(tex, uv + offset).a > 0.1)
            return outlineColor;
        }
    }

    return vec4(0.0);
}

void main()
{
    vec4 color = color;

    if (useTexture)
    {
        vec4 texColor = texture(tex, TexCoord);
        color = texColor * color;
    }

    if (selection)
    {
        vec4 outline = getOutlineColor(TexCoord);
        if (outline.a > 0.0)
        color = outline;
    }

    FragColor = color;
}