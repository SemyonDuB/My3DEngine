#version 430 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 VertexTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;
out vec2 TexCoord;

void main(void)
{
    gl_Position = projection * view * model * vec4(in_pos, 1.0);
    color = vec4(in_color, 1.0);
    TexCoord = VertexTexCoord;
}