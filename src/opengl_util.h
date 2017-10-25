//
// Created by zoe on 06/10/17.
//
#pragma once

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>

#include <map>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <memory>
#include <vector>

namespace gl
{

	struct light_data
	{
		// Ambient intensity of the light
		glm::vec4 _ambient = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
		// The colour of the light
		glm::vec4 _colour = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
		// The direction the light is facing
		glm::vec3 _direction = glm::vec3(1.0f, 0.0f, 0.0f);

		// pos
		glm::vec3 _position = glm::vec3(0.0, 0.0, 0.0f);
	};


    enum BUFFER_INDEXES
    {
        // The position data
        POSITION_BUFFER = 0,
        // The colour data
        COLOUR_BUFFER = 1,
        // The surface normals
        NORMAL_BUFFER = 2,
        // The binormals for the surfaces
        BINORMAL_BUFFER = 3,
        // The tangents for the surfaces
        TANGENT_BUFFER = 4,
        // Texture coordinates 0
        TEXTURE_COORDS_0 = 10,
        // Texture coordinates 1
        TEXTURE_COORDS_1 = 11,
        // Texture coordinates 2
        TEXTURE_COORDS_2 = 12,
        // Texture coordinates 3
        TEXTURE_COORDS_3 = 13,
        // Texture coordinates 4
        TEXTURE_COORDS_4 = 14,
        // Texture coordinates 5
        TEXTURE_COORDS_5 = 15
    };

    // Mesh struct
    struct mesh_geom
    {
        std::vector<glm::vec3> positions;
        glm::vec3 min;
        glm::vec3 max;
        std::vector<glm::vec4> colours;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> tex_coords;
        std::vector<unsigned int> indices;
        void *GpuData;
    };

	// Effect struct
	struct Effect
	{
		std::string name;
		bool has_geometry;
		bool is_compute;
		void *GpuData;
		GLuint program;

		std::vector<light_data> lights;
	};

	struct render_data
	{
		bool visible;// = true;
					 // Let's pretend this is a matrix that was built.
		std::string colour;// = "Red";
		std::string shader;// = "Phong";

		glm::mat4 M;
		glm::mat3 N;
		glm::mat4 MVP;

		// Reference to structs
		std::shared_ptr<gl::Effect> effect;

		// shape is now mesh
		std::shared_ptr<gl::mesh_geom> mesh;
	};

    // store vao/vbos for obj
    struct glData
    {
        // The primitive geometry type used by the geometry
        GLenum type;
        // The OpenGL ID of the vertex array object
        GLuint vao;
        // The OpenGL IDs of the buffers used within the vertex array object
        std::map<GLuint, GLuint> buffers;
        // The OpenGL ID of the index buffer
        GLuint index_buffer;
        bool has_indices;
        // The number of vertices in the geometry
        // GLuint vertices;
        // The number of indices in the index buffer
        GLuint indice_count;
        GLuint vertex_count;
    };

    inline bool CheckGL(int line, const std::string &file);

    void createvao(glData &data);

    extern GLuint LoadShaders(char const* vertex_file_path, char const* fragment_file_path);

    std::shared_ptr<mesh_geom> load_mesh(std::string msh);

    mesh_geom* generate_plane();

	mesh_geom* generate_rect();
    mesh_geom* get_model_mesh(const std::string &file);

	void bind_light(GLuint programID, light_data light);

	void render(std::shared_ptr<render_data> rd);
}
