#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;
	vec2 uv0 = fract(uv) - 0.5;
	

	//float movement = (sin(iTime) + 1.0) / 2.0;    
	float movement = -iTime / 2.5;
	float dist = length(uv);
	float red = 0.0;


	float green = 1 - dist;
	green -= movement;
	green -= length(uv0);
	green = sin(fract(green));
	green = step(0.8, green);

	float blue = dist / .55;
	
	blue = fract(blue + movement);
	
	blue += length(uv0) - 0.1;
	//blue += movement;

	
	blue = smoothstep(0.1, .60, blue - green);
	red = step(0.2, red);
	red = length(uv0);	
	red += sin(movement * 2.);
	red = smoothstep(0.2 ,0.5, red);
	
	

    gl_FragColor = vec4(red - green - blue, green - red, (1- blue) - green, 1.);
}
