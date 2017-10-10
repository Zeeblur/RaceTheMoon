#version 330 core

// Model view projection matrix
uniform mat4 MVP;

in vec3 position;
in vec4 in_colour;

out vec4 frag_colour;

void main()
{
	// Calculate screen position of vertex
	gl_Position = MVP * vec4(position, 1.0);
	// Output colour to the fragment shader
	frag_colour = in_colour;
}
