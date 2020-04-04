#version 430 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 FragPos;

void main(void)
{
    gl_Position = projection * view * model * vec4(in_pos, 1.0);
    FragPos = vec3(model * vec4(in_pos, 1.0));
    normal = in_normal;
}
