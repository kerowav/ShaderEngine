#version 330 core
precision mediump float;

uniform vec2 iResolution;
out vec4 FragColor;
in float iTime;

void main() {
    vec2 uv = gl_FragCoord.xy;
    uv.x *= iResolution.x / iResolution.y;

    vec3 color = vec3(0.0);
    color.r = abs(sin(color.r + iTime));
    

    FragColor = vec4(vec3(color), 1.);
}