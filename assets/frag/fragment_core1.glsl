#version 330 core
precision mediump float;

uniform float iTime;
uniform vec2 iResolution;

float circleShape(float radius, vec2 position) {
    float pxToCenter = distance(position, vec2(sin(iTime), cos(iTime)));
    return step(radius, pxToCenter);
}

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;

    float circleWidth = 0.2;
    float circle = circleShape(circleWidth, uv);

    float circle2 = circleShape(circleWidth-0.1, uv);

    gl_FragColor = vec4(circle, 0.0, 0.0f, 1.0);
}

