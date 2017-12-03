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
	vec3 ambient_intensity;
};
#endif

#ifndef MATERIAL
#define MATERIAL
struct material
{
	vec4 emissive;
	vec4 diffuse_reflection;
	vec4 specular_reflection;
	float shininess;
};
#endif

// Position of the camera
uniform vec3 eye_pos;

uniform material mat;

uniform directional_light dir_light; 
// Sampler used to get texture colour
uniform sampler2D tex;

void main()
{
	// calculate ambient
    vec4 ambient = mat.diffuse_reflection * vec4(dir_light.ambient_intensity, 1.0);

    float dotD = dot(trans_normal, dir_light.light_dir);
    float k = max(dotD, 0);
    vec4 diffuse = mat.diffuse_reflection * vec4(dir_light.light_colour, 1.0) * k;

    // calculate view direction & half vector
    vec3 view_dir = normalize(eye_pos - vertex_pos);
    vec3 halfV = normalize(view_dir + dir_light.light_dir);


    // specular
    float dotS = dot(halfV, trans_normal);
    float kSpec = max(dotS, 0);

    vec4 specular = mat.specular_reflection * vec4(dir_light.light_colour, 1.0) * pow(kSpec, mat.shininess);


    // sample texture
    vec4 tex_colour = texture2D(tex, tex_coord);

    vec4 primary = mat.emissive +  diffuse;

    out_colour = primary*tex_colour;// + specular;
    out_colour = vec4(k,k,k, 1.0);
	out_colour.a = 1.0f;
}