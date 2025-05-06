#version 330 core
precision mediump float;

uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

void main() {
    vec2 uv = inUV;
    uv.x *= iResolution.x / iResolution.y;
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
	
    FragColor = vec4(color, 1.);
}