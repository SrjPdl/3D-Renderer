#version 440 core

layout(location = 0) in vec4 iPosition;
layout(location = 1) in vec3 iNormal;
layout(location = 2) in vec2 iTexCoord;

out vec3 normal;
out vec2 texCoord;
out vec3 fragmentCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


void main()
{
    gl_Position = projection * view * model * iPosition;

    normal = transpose(inverse(mat3(view * model))) * iNormal;

    texCoord = iTexCoord;
    fragmentCoord = (model * iPosition).xyz; 
}