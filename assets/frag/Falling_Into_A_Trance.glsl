#version 330 core
precision mediump float;

uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

void main() {
    vec2 uv = inUV;
    uv.x *= iResolution.x / iResolution.y;
    vec2 uv0 = uv;

    uv = fract(uv / .5) - 0.5;

    uv = uv / .5;

    uv0 = uv0 / abs(sin(iTime / 2.));
    float wave = fract((length(uv) - length(uv0)) + iTime); 
    float blue = smoothstep(0.2, 0.05, wave);

    float red =  1.0 - fract(1.0 - wave) / (length(uv0) * .5);

    blue = fract(1.0 - blue);

    FragColor = vec4(red - .5, red - .7, blue, 1.0);
}