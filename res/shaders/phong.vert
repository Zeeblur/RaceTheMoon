#version 330 core

// Model view projection matrix
uniform mat4 MVP;
uniform mat4 M;
uniform mat3 N;

in vec3 position;
in vec3 normal;
in vec4 in_colour;

out vec3 vertex_pos;
out vec3 trans_normal;
out vec4 frag_colour;

void main()
{
	// Calculate screen position of vertex
	gl_Position = MVP * vec4(position, 1.0);

	vertex_pos = vec3(M * vec4(position, 1.0f));
	trans_normal = N * normal;
	frag_colour = in_colour;
}
