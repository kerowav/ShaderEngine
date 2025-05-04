#version 330 core
precision mediump float;

uniform vec4 ourColor;
uniform vec2 iResolution;
out vec4 FragColor;
in vec2 inUV;
in float iTime;

float circleShape(float radius, vec2 position) {
  float pxToCenter = distance(position, vec2(sin(iTime), cos(iTime)));
  return step(radius, pxToCenter);
}

void main() {
  vec2 uv = inUV;
  uv.x *= iResolution.x / iResolution.y;
//   uv = fract(uv) -.5;

  float circleWidth = 0.2;
  float circle = circleShape(circleWidth, uv);
  
  float circle2 = circleShape(circleWidth-0.1, uv);

  FragColor = vec4(circle, 0.0, 0.0f, 1.0);
}

