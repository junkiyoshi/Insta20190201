#version 150

uniform float time;
uniform vec2 resolution;
uniform sampler2DRect tex;
uniform vec3 y_noise[720];

out vec4 outputColor;

void main() {

  float drift = 240.0;
  vec3 color = vec3(1.0);
  float r = texture(tex, vec2(gl_FragCoord.x + drift * y_noise[int(gl_FragCoord.y)].r, (resolution.y - gl_FragCoord.y))).r;
  float g = texture(tex, vec2(gl_FragCoord.x + drift * y_noise[int(gl_FragCoord.y)].g, (resolution.y - gl_FragCoord.y))).g;
  float b = texture(tex, vec2(gl_FragCoord.x + drift * y_noise[int(gl_FragCoord.y)].b, (resolution.y - gl_FragCoord.y))).b;
  outputColor = vec4(color - vec3(r, g, b), 1.0);
}