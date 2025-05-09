#version 330 core
precision mediump float;

#define RADIUS 100.0

uniform vec2 iResolution;
uniform float iTime;
uniform vec2 iMouse;

void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;

	vec4 color = vec4(1.);
    vec2 center = vec2( 200.0, 200.0);
    
    center = iMouse;


    if(length(gl_FragCoord.xy - center) < (RADIUS * (sin(iTime) + 1.0) / 2.0)) {
		color = vec4(1.0);
	} else {
		color = vec4(0.0);
	}
    
    gl_FragColor = vec4(color);
}
