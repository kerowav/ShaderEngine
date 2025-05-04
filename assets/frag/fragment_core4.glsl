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
  float distance = length(uv * 10.0);
  distance -= iTime * 5.; 
  // distance = fract(distance);
  distance = length(uv) * sin(distance);
  distance = abs(distance);
  
  FragColor = vec4(1.0f, 1 - distance, sin(fract(length(uv0) * 3)), 1.0);
}

