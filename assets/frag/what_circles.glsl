#version 330 core
precision mediump float;

uniform float iTime;
uniform vec2 iResolution;

float circleShape(float radius, vec2 position, vec2 modifier) {
    float pxToCenter = distance(position, vec2(sin(iTime * modifier.x), cos(iTime * modifier.y)));
    return step(radius, pxToCenter);
}

void main() {
    vec2 uv = abs( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;
	uv = uv / .25;
	vec2 uv0 = -uv;
	uv = uv * 8.;
    float circleWidth = 0.;
    float circle = circleShape(circleWidth, uv, vec2(0.5, 0.5));
	
    float circle2 = circleShape(circleWidth, uv0, vec2(2.0, 2.0));
	
    float circle3 = circleShape(circleWidth, uv0, vec2(.75, 1.5));
	
	circle += length(uv);

	vec4 bg = vec4(0.05, 0.01, 0.5, 1.0);
	circle = 1 *  circle * .5 + sin(iTime) + sin(length(uv + iTime) + cos(circle + iTime));	
	bg.r = circle * .6 - iTime;
	bg.g = circle2;
	bg.b = circle3;
	
	bg.g -= fract(bg.r + iTime * .5);
    gl_FragColor = vec4(bg.r, bg.g, bg.b, 1.0);
}



