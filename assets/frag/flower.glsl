#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;
	vec2 uv0 = uv;
	
	float adjustedTime = iTime / 2.;
	float movement = abs(sin(adjustedTime));

	uv = fract(uv * 1.5) - 0.5;
	
	float dist = length(uv);
	
	float distanceModifiedMovement = abs(abs(adjustedTime) - length(uv0));
	float r = dist - distanceModifiedMovement;
	//r += movement;
	
	r = abs(sin(r - adjustedTime));
	float g = r;
	r = step(0.05, r);
	vec3 color = vec3(1.0 - r, 0.0, 0.0);
	
    gl_FragColor = vec4(color, 1.);
}