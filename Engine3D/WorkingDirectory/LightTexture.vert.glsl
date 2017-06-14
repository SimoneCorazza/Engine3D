#version 330 core

layout(location = 0) in vec4 v_coord;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec3 v_normal;

uniform mat4 m, v, p;
uniform mat3 m_3x3_inv_transp;

out vec4 position;  // position of the vertex (and fragment) in world space
out vec3 varyingNormalDirection;  // surface normal vector in world space
out vec2 uv;

void main()
{
	uv = v_uv;
	position = m * v_coord;
	varyingNormalDirection = normalize(m_3x3_inv_transp * v_normal);

	mat4 mvp = p * v * m;
	gl_Position = mvp * v_coord;
}