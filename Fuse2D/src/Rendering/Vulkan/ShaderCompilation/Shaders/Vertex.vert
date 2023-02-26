#version 450

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 model;
    mat4 view;
    mat4 ortho;
} ubo;

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColour;

layout(location = 0) out vec3 fragColour;

void main() {
    gl_Position = ubo.ortho * ubo.view * ubo.model * vec4(inPos, 0.0f, 1.0);
    fragColour = inColour;
}