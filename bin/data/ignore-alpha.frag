#version 120

uniform vec2 resolution;

uniform sampler2DRect maskTex;
uniform sampler2DRect bgTex;
uniform sampler2DRect fgTex;

varying vec2 uv;

void main() {

	vec4 bg = texture2DRect(bgTex, uv);
	vec4 fg = pow(texture2DRect(fgTex, uv), vec4(0.5)) * vec4(0.75, 0.95, 0.9, 1.0) + vec4(0.1, 0.0, 0.1, 0.0);
	float blend = texture2DRect(maskTex, uv).y;

	vec4 color = mix(bg, fg, blend);

	gl_FragColor = color;
}