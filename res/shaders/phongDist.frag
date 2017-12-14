#version 330 core


// Incoming texture coordinate
in vec2 tex_coord;

in vec3 vertex_pos;
in vec4 viewSpace;
smooth in vec3 trans_normal;

in vec4 frag_colour;

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

uniform vec3 light_pos;

uniform directional_light dir_light; 
// Sampler used to get texture colour
uniform sampler2D tex;


//0 linear; 1 exponential; 2 exponential square

//0 plane based; 1 range based

const vec3 DiffuseLight = vec3(0.15, 0.05, 0.0);
const vec3 RimColor = vec3(0.2, 0.2, 0.2);
 
 
const vec4 fogColor = vec4(0.5, 0.5,0.5, 0.0);
const float FogDensity = 0.05;
 
void main(){
 
vec3 tex1 = texture(tex, tex_coord).rgb;
 
//get light an view directions
vec3 L = normalize( light_pos - vertex_pos);
vec3 V = normalize( eye_pos - vertex_pos);
 
//diffuse lighting
vec3 diffuse = DiffuseLight * max(0, dot(L,trans_normal));
 
//rim lighting
float rim = 1 - max(dot(V, trans_normal), 0.0);
rim = smoothstep(0.6, 1.0, rim);
vec3 finalRim = RimColor * vec3(rim, rim, rim);
//get all lights and texture
vec4 lightColor = vec4(finalRim + diffuse + tex1, 1.0);
 
vec4 finalColor = vec4(0, 0, 0, 1);
 
//distance
float dist = 0;
float fogFactor = 0;
 
//compute distance used in fog equations

int depthFog = 1;

if(depthFog == 0)//select plane based vs range based
{
  //plane based
  dist = abs(viewSpace.z);
  //dist = (gl_FragCoord.z / gl_FragCoord.w);
}
else
{
   //range based
   dist = length(viewSpace);
}

int fogSelector = 0;
 
if(fogSelector == 0)//linear fog
{
   // 20 - fog starts; 80 - fog ends
   fogFactor = (800 - dist)/(800 - 200);
   fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
   //if you inverse color in glsl mix function you have to
   //put 1.0 - fogFactor
   finalColor = mix(fogColor, lightColor, fogFactor);
}
else if( fogSelector == 1)// exponential fog
{
    fogFactor = 1.0 /exp(dist * FogDensity);
    fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
    // mix function fogColor⋅(1−fogFactor) + lightColor⋅fogFactor
    finalColor = mix(fogColor, lightColor, fogFactor);
}
else if( fogSelector == 2)
{
   fogFactor = 1.0 /exp( (dist * FogDensity)* (dist * FogDensity));
   fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
   finalColor = mix(fogColor, lightColor, fogFactor);
}
 
//show fogFactor depth(gray levels)
fogFactor = 1 - fogFactor;
out_colour = vec4( fogFactor, fogFactor, fogFactor,1.0 );
out_colour = finalColor;

}