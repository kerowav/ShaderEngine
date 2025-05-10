#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y; 

	float movement = 1 - ((sin(iTime * .75) + 1) / 3.);
	uv = uv /  movement;
	uv = cos(uv / .15);
	
	uv = (uv + (movement / .15)) - 0.5;
	vec2 uv0 = fract(uv) - 0.5;
	float fractDist = length(uv0) + 0.5;
	float red = fractDist;
	float redModifier = red + fract(length(uv));
	red = mix(red, redModifier, red);
	red = fract(red - 0.5);
	
	float blue = 1.0 - (red - iTime) - 0.5;
	blue = fract(blue - iTime * .75);
	
    gl_FragColor = vec4(1 - red - 0.5, 0.0 , red - blue,1.);
}

