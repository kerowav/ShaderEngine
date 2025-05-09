#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;    

    gl_FragColor = vec4(1.);
}
