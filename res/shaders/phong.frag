#version 330 core

// Incoming vertex colour
in vec4 frag_colour;

// Incoming texture coordinate
in vec2 tex_coord;

smooth in vec3 trans_normal;
in vec3 vertex_pos;

// Outgoing pixel colour
out vec4 out_colour;

#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT
struct directional_light
{
	vec3 light_colour;
	vec3 light_dir;
	float ambient_intensity;
};
#endif



uniform directional_light dir_light; 
// Sampler used to get texture colour
uniform sampler2D tex;

void main()
{

	float diffuse = max(0.0, dot(normalize(trans_normal), -dir_light.light_dir));
	vec4 ambient = vec4(dir_light.light_colour * (dir_light.ambient_intensity + diffuse), 1.0);
ambient = ambient + frag_colour;
	out_colour = texture(tex, tex_coord);// * ambient;

	//out_colour = vec4(1.0, 0.0, 1.0, 1.0);
	out_colour.a = 1.0f;
}