#version 330 core
precision mediump float;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uvs;

uniform float iTime;

out vec4 col;

 
void main() {
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  
}