#version 330 core

// Model view projection matrix
uniform mat4 MVP;
uniform mat4 M;

in vec3 position;
out vec3 vertex_pos;


void main()
{
	// Calculate screen position of vertex
	gl_Position = MVP * vec4(position, 1.0);

	vertex_pos = position;
}
