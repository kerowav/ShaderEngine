#version 330 core
precision mediump float;

uniform vec2 iResolution;
uniform float iTime;

vec3 palette( float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);
    
    return a + b*cos( 6.28318*(c*t+d) );
}


void main() {
    vec2 uv = ( 2. * gl_FragCoord.xy - iResolution.xy ) / iResolution.y;   
	vec2 uv0 = uv;
	
	float time = iTime / 2.;

	uv = fract(uv / .2) - 0.5;
	vec2 uvFract = fract(uv / .5) - 0.5;

	float subDistance = length(uvFract);
	 	
	
    float distance = length(uv / .5);

	
    distance -= time - length(uv);
	subDistance += time + length(uvFract);
	subDistance = fract(subDistance);
    distance = fract(distance);

	float red = 1.0 - distance;
	red = step(.9, red);
	red = mix(red, length(uv) - 0.2, red);

	red -= subDistance / 2.5;

	
	float green = fract(red / 2.) - 0.5;

	green = 1.0 - green;
	green -= red;

	red += green - 0.47;
	red -= length(uv0) - iTime;

	vec3 color = palette(sin(red));

	float redFinal = (color.r) - ( 0.7 - (sin(time) - 0.3));
	float blueFinal = (color.b - (color.r)) - 0.6;
	

    gl_FragColor = vec4(redFinal, 0.0, blueFinal + 0.1, 1.);
}



