#version 330 core
in vec2 fragCoord;

uniform vec2 iResolution;
in float iTime;
in vec2 inUV;

out vec4 FragColor;

vec3 palette( float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);
    
    return a + b*cos( 6.28318*(c*t+d) );
}

void main( )
{
    vec2 uv = inUV;
    uv.x *= iResolution.x / iResolution.y;

    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0f);
    
    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;

        float d = length(uv) * exp(-length(uv0));

        vec3 col = palette(length(uv0) + i*.4 + iTime*.4);

        d = sin(d*8. + iTime)/8.;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        col *= d;

        finalColor += col * d;
    }
    
    FragColor = vec4(finalColor, 1.0);
}