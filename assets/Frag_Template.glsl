#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = gl_FragCoord.xy;
    uv.x *= iResolution.x / iResolution.y;

    

    gl_FragColor = vec4(1.);
}