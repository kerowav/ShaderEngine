#version 330 core
precision mediump float;

uniform float iTime;
uniform vec2 iResolution;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;

    vec2 uv0 = uv;
    float distance = length(uv / .2);
    distance += iTime; 
    distance = fract(distance);
    distance = length(uv) * sin(distance) -.8;
    distance = abs(distance);

    gl_FragColor = vec4(distance, 0.0f, 0.5f, 1.0);
}

