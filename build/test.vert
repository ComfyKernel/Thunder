#version 330 core

in vec3 pos;

out vec2 uv;

void main() {
     gl_Position = vec4(pos, 1.0);
     uv = pos.xy;
}