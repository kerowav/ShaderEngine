#version 330 core
precision mediump float;

uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

void main() {


    vec4 my_color = vec4(0.247059,0.000000,0.000000,3);
    my_color.r = length(my_color.r);
    FragColor = my_color;

}