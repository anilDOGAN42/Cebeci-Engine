#version 430 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 aTexCoord;

layout(std430, binding = 0) buffer Transforms {
    mat4 transforms[];
};

out vec2 TexCoord;

uniform int transformCount;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    mat4 model = transforms[0];

    for (int i = 1; i < transformCount; i++) {
        model = transforms[i] * model;
        
    }
    vec4 screenNormalizedPos = vec4(Pos.x,Pos.y,Pos.z,1);
    gl_Position = projection * view *  model * screenNormalizedPos;

    TexCoord=aTexCoord;
}
