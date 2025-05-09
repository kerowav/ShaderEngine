#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;
    vec2 uv0 = uv;

    float distance = length(uv);

    uv = fract(uv / sin(distance) + iTime)  - 0.5;
    uv = uv / .2;

    vec4 my_color = vec4(0.0);
    // my_color.r = length(my_color.r);

    float modulatedDistance = distance + iTime;
    float fractDist = fract(modulatedDistance);

    float red = sin(fractDist);
    float green = 1 - cos(fractDist / 4.);
    float blue = 1 - distance;

    blue += smoothstep(0.2, 0.3 + iTime, blue);

    float d = fract(length(uv));
    red += d;

    float a = exp(length(uv0));
    red += sin(a * .8 + iTime);

    my_color = vec4(red, green, blue, 1.0);
    my_color += abs(sin(my_color + iTime)) / 2.;


    gl_FragColor = my_color;

}