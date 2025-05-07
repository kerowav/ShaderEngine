#version 330 core
precision mediump float;

uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

void main() {
    vec2 uv = inUV;
    uv.x *= iResolution.x / iResolution.y;

    

    FragColor = vec4(1.);
}
