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
	struct Mesh
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

	std::shared_ptr<Mesh> loadModel(std::string msh);
	std::shared_ptr<Mesh> generate_rect();

	Mesh* GetMesh(const std::string &file);
}
