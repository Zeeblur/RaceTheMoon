#version 330 core

// Model view projection matrix
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 MV;
uniform mat3 N;


in vec3 position;

in vec4 in_colour;
in vec3 normal;

in vec2 tex_coord_in;

out vec2 tex_coord;
out vec3 vertex_pos;
out vec4 viewSpace;
smooth out vec3 trans_normal;
out vec4 frag_colour;

void main()
{
	// Calculate screen position of vertex
	gl_Position = MVP * vec4(position, 1.0);

	vertex_pos = (M * vec4(position, 1.0f)).xyz;
	trans_normal = normalize(N * normal);
	
	viewSpace = (MV* vec4(position, 1.0));
	frag_colour = in_colour;

	tex_coord = tex_coord_in;
}
