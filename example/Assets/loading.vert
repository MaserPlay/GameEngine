#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform float time;
out vec2 TexCoord;
out vec4 Color;

void main(){
    float x = position.x + (gl_InstanceID - 1.5) * sin(time) / 2;
    gl_Position = projection * (vec4(x, position.y, position.z, 1));
    TexCoord = texCoord;
    Color = color;
}