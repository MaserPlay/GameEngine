#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform float time;
uniform float lifetime;
uniform float distdifference;
out vec2 TexCoord;
out vec4 Color;

void main(){//gl_InstanceID
    float m = time + gl_InstanceID / distdifference;
    float dist = (m - int(m)) * lifetime;
    vec2 circle = vec2(dist*cos(gl_InstanceID), dist*sin(gl_InstanceID));

    gl_Position = projection * (vec4(position.xy + circle, position.z, 1));
    TexCoord = texCoord;
    Color = color;
}