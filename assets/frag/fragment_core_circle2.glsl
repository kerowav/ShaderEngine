#version 330 core
precision mediump float;

uniform float iTime;
uniform vec2 iResolution;

float circleShape(float radius, vec2 position, vec2 modifier) {
    float pxToCenter = distance(position, vec2(sin(iTime * modifier.x), cos(iTime * modifier.y)));
    return step(radius, pxToCenter);
}

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;
	uv = uv / .5;
	vec2 uv0 = -uv;
	uv = uv / .5;
    float circleWidth = 0.2;
    float circle = circleShape(circleWidth, uv, vec2(0.5, 0.5));

    float circle2 = circleShape(circleWidth, uv0, vec2(2.0, 2.0));
	
    float circle3 = circleShape(circleWidth, uv0, vec2(.75, 1.5));
	
	circle += fract(length(uv));
	//circle3 += 1. - step(0.2, fract(length(uv)));

	vec4 bg = vec4(0.05, 0.061, 0.15, 1.0);
	bg.r = 1 - circle;
	bg.g = 1 - circle2;
	bg.b = 1 - circle3;
    gl_FragColor = vec4(bg.r, bg.g, bg.b, 1.0);
}



