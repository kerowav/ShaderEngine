#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;
	vec2 uv0 = fract(uv) - 0.5;
	

	float movement = (sin(iTime) + 1.0) / 2.0;    

	float dist = length(uv);
	float red = 0.0;


	float green = 1 - dist;
	green -= movement;
	green = fract(green);
	green -= length(uv0);
	green = step(0.7, green);

	float blue = dist;


	
	blue += movement;

	
	blue = step(1., blue - green);

	

    gl_FragColor = vec4(red, green, (1- blue) - green, 1.);
}
