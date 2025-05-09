#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

float circleShape(float radius, vec2 position) {
    float pxToCenter = distance(position, vec2(sin(iTime), cos(iTime)));
    pxToCenter = sin(fract(pxToCenter - iTime / 2.));
    float smoothPx = smoothstep(radius, radius + 0.2, abs(pxToCenter));
    float distance = length(position);
    return smoothstep(radius, radius + 0.001, smoothPx);
}

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;


    float circleWidth = 0.01;
    float circle = 1 - circleShape(circleWidth, uv);

    float distance = length(uv);

    float red = 1 - distance / .5;
    float adjustedTime = fract(abs(sin(iTime)));
    
    red += adjustedTime;
    // red = sin(red);

    gl_FragColor = vec4(red, circle, sin(circle + fract(iTime + sin(red))), 1.);
}