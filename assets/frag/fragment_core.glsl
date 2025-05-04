#version 330 core
precision mediump float;

uniform vec4 ourColor;
uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

void main() {
  vec2 uv = inUV;
  uv.x *= iResolution.x / iResolution.y;
  // uv = fract(uv) -.5;

  vec2 uv0 = uv;
  float distance = length(uv / .2);
  distance += iTime; 
  distance = fract(distance);
  distance = length(uv) * sin(distance) -.8;
  distance = abs(distance);
  
  FragColor = vec4(distance, 0.0f, 0.5f, 1.0);
}

