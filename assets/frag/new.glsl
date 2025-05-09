#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;    
	vec2 uv0 = uv;
	float movement = (sin(iTime * 1.5) + 1.) / 3.;
	
	movement = 1.0 - movement;

	uv = uv / movement;
	uv = fract(uv) - 0.5;
	float dist = length(uv);	
	float red = dist;
	red = 1.0 - sin(red) + cos(iTime);

	red = smoothstep(0.1, 0.5, red);	
	red -= length(uv0);
	
	float a = - (red + cos(movement));
	float blue = - red;	
	
	blue = fract(blue);

    gl_FragColor = vec4(red, a , blue, 1.);
}

