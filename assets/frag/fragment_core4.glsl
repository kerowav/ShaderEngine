#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;

    vec2 uv0 = uv;
    float distance = length(uv * 10.0);
    distance -= iTime * 5.; 
    distance = length(uv) * sin(distance);
    distance = abs(distance);

    gl_FragColor = vec4(1.0f, 1 - distance, sin(fract(length(uv0) * 3)), 1.0);
}

