#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;
	vec2 uv_unmodified = uv;
	float zoomMovement = 1 - (sin(iTime) + 1.0) / 2.5;
	uv = uv / zoomMovement;


	

	//float movement = (sin(iTime) + 1.0) / 2.5;    
	float movement = -iTime / 2.5;
	float dist = length(uv);
	float red = 0.0;

	vec2 uv0 = fract(uv) - 0.5;
	
	float green = 1 - dist;
	green -= movement;
	green -= length(uv0);
	green = sin(fract(green));
	green = step(0.8, green);

	float blue = dist / .55;
	
	blue = fract(blue + movement);
	
	

	blue +=  length(uv) - length(uv0) - 0.1;
	blue = fract(blue) + length(uv_unmodified);
	

	float blueMovement = (cos(iTime) + 1.0) / 2.0; 
	blue += cos(movement);

	
	blue = smoothstep(0.1, .60, blue - green);
	red = step(0.2, red);
	red = length(uv0);	
	red += sin(movement * 2.);
	red = smoothstep(0.1 ,0.60, red);
	
	float nullGreen = green + movement;

	float redFinal = red - green - blue;
	float greenFinal = nullGreen;
	float blueFinal = (1- blue) - green;

	
    gl_FragColor = vec4(redFinal, greenFinal, abs(blueFinal), 1.);
}


