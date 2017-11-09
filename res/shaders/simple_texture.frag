#version 330 core

// Incoming vertex colour
//in vec4 frag_colour;

// Incoming texture coordinate
in vec2 tex_coord;

smooth in vec3 trans_normal;
in vec3 vertex_pos;

// Outgoing pixel colour
out vec4 out_colour;

// Sampler used to get texture colour
uniform sampler2D tex;

void main()
{
	out_colour = texture(tex, tex_coord);
	//out_colour.a = 1.0f;
}