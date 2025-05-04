#version 330 core
precision mediump float;

uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

void main() {
    vec2 uv = inUV;
    uv.x *= iResolution.x / iResolution.y;

    float distance = length(uv);

    float red = 1 - distance / .5;
    float adjustedTime = fract(abs(sin(iTime)));
    
    red += adjustedTime;
    // red = sin(red);

    FragColor = vec4(red, vec2(0.), 1.);
}