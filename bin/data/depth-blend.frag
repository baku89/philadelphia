#version 120

uniform vec2 resolution;

uniform sampler2DRect maskTex;
uniform sampler2DRect depthTex;

varying vec2 uv;

// maskTex
// r - depth
// g - [0-1] -> [bg-fg]

void main() {

	float bgDepth = texture2DRect(maskTex, uv).r;
	float fgDepth = texture2DRect(depthTex, uv).r;

	vec4 result = vec4(
		max(bgDepth, fgDepth),
		0.0,
		0.0,
		1.0
		);

	if (bgDepth <= fgDepth) {
		result.y = 1.0;
	}

	gl_FragColor = result;
}