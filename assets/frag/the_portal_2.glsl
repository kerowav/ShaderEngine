
/* phreax/jiagual 2025 - https://www.shadertoy.com/view/W3jSRV */
#version 330 core
precision mediump float;

mat2 rot(float x) {return mat2(cos(x), -sin(x), sin(x), cos(x));}
vec3 pal(float x) {return .5+.5*cos(6.28*x-vec3(0,2,4));}

uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

void main() {
    vec2 uv = inUV;
    uv.x *= iResolution.x / iResolution.y;


    vec3 col = vec3(0);
    vec3 rd = vec3(uv, 1);
    vec3 p = vec3(0);
    float t = 0.;
    float tt = iTime*.5;
    
    for(float i=0.; i<1e2; i++) {
        vec3 p = t*rd + rd;
        p.z += tt;
        p = abs(p)-.3;
        p.xy *= rot(p.z);
        p = abs(p)-.3;
        for(float j=0.; j < 3.; j++) {     
            float  a= exp(j)/exp2(j);
            p += cos(4.*p.yzx*a + tt - length(p.xy)*5.)/a; 
        }
        float d = 0.01 + abs((p-vec3(0,1,0)).y-1.)/10.;
        
        col += pal(t*.7)*1e-3/d;       
        t += d/4.;
    }
   
    col *= tanh(col*.1);
    col = pow(col, vec3(.45));

    FragColor = vec4(col,1.0);;
}