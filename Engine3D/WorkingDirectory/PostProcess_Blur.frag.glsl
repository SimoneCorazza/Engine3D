#version 330 core

uniform sampler2D renderedTex;
uniform sampler2D depthTex;

uniform vec2 resolution;

in vec2 UV;
out vec4 fragmentFinal;

// Version not in GLSL
// http://blog.ivank.net/fastest-gaussian-blur.html

// https://github.com/Jam3/glsl-fast-gaussian-blur
vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction)
{
	vec4 color = vec4(0.0);
	vec2 off1 = vec2(1.411764705882353) * direction;
	vec2 off2 = vec2(3.2941176470588234) * direction;
	vec2 off3 = vec2(5.176470588235294) * direction;
	color += texture2D(image, uv) * 0.1964825501511404;
	color += texture2D(image, uv + (off1 / resolution)) * 0.2969069646728344;
	color += texture2D(image, uv - (off1 / resolution)) * 0.2969069646728344;
	color += texture2D(image, uv + (off2 / resolution)) * 0.09447039785044732;
	color += texture2D(image, uv - (off2 / resolution)) * 0.09447039785044732;
	color += texture2D(image, uv + (off3 / resolution)) * 0.010381362401148057;
	color += texture2D(image, uv - (off3 / resolution)) * 0.010381362401148057;

	return color;
}

float minD = 0.1f;
float maxD = 1000.f;
float desiredDistance = 500.0f;

void main()
{
/*
	if(texture2D(depthTex, UV).r < 0.1)
		fragmentFinal = vec4(1, 0, 0, 1); 	// fragmentFinal = texture2D (renderedTex, UV);
	else
		fragmentFinal = blur13(renderedTex, UV, resolution, vec2(1, 1));*/
	fragmentFinal = blur13(renderedTex, UV, resolution, vec2(1, 1));
}