#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uvs;

uniform float inTime;

out float iTime;
out vec2 inUV;
out vec4 col;

 
void main() {
  // iTime = fract(inTime);
  iTime = inTime;

  
  gl_Position = vec4(aPos.x, aPos.yz, 1.0);
  inUV = vec2(gl_Position.xy);
  // col = ourColor;
}