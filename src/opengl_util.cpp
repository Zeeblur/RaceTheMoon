//
// Created by zoe on 03/10/17.
//
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "opengl_util.h"
#include <memory>
#include <sstream>
#include <functional>
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define CHECK_GL_ERROR CheckGL(__LINE__, __FILE__)



namespace gl
{
    // macro for gl check for error and println
    inline bool CheckGL(int line, const std::string &file)
    {
        // Get the current error
        GLenum error = glGetError();

        // If there is an error display message
        if (error)
        {
            // Display error
            std::cerr << "OpenGL Error: " << error << std::endl;
            std::cerr << "At line " << line << " in file " << file << std::endl;
            return true;
        }
        return false;
    }

    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
    {
        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        if (VertexShaderStream.is_open()) {
            std::string Line = "";
            while (getline(VertexShaderStream, Line))
                VertexShaderCode += "\n" + Line;
            VertexShaderStream.close();
        }
        else {
            printf("Impossible to open %s. Are you in the right directory !\n", vertex_file_path);
            getchar();
            return 0;
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if (FragmentShaderStream.is_open()) {
            std::string Line = "";
            while (std::getline(FragmentShaderStream, Line))
                FragmentShaderCode += "\n" + Line;
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;


        // Compile Vertex Shader
        printf("Compiling shader : %s\n", vertex_file_path);
        char const * VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }



        // Compile Fragment Shader
        printf("Compiling shader : %s\n", fragment_file_path);
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }



        // Link the program
        printf("Linking program\n");
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }


        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;
    }

    void createvao(glData &data)
    {
        auto d = data;

        if (data.vao == 0)
        {
            //generate and check for errors if vao is not gen
            glGenVertexArrays(1, &data.vao);
            //assert(!CHECK_GL_ERROR && "Couldn't create VAO.");

            auto d = data;

            if (CHECK_GL_ERROR) {
                // Display error
                std::cerr << "ERROR - creating geometry" << std::endl;
                std::cerr << "Could not generate vertex array object" << std::endl;
                // Set vertex array object to 0
                data.vao = 0;
                // Throw exception
                throw std::runtime_error("Error creating vertex array object with OpenGL");
                //return false;
            }
        }
    }

    bool add_buffer(glData &data, const void *dataBuf, GLuint stride, GLuint size, GLuint index, GLenum buffer_type)
    {
        // Check that index is viable
        assert(index < 16);
        // Check that buffer is not empty
        assert(size > 0);
        // Check if geometry initialised
        if (data.vao == 0)
        {
            createvao(data);
        }

        // Now add buffer to the vertex array object.  Bind the vertex array object
        glBindVertexArray(data.vao);
        // Generate buffer with OpenGL
        GLuint id;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        // Set the buffer data
        glBufferData(GL_ARRAY_BUFFER, size, dataBuf, buffer_type);
        // Set the vertex pointer and enable
        glVertexAttribPointer(index, stride, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(index);
        // Check for OpenGL error
        if (CHECK_GL_ERROR)
        {
            std::cerr << "ERROR - adding buffer to geometry object" << std::endl;
            std::cerr << "Could not create buffer with OpenGL" << std::endl;
            return false;
        }


        // Add buffer to map
        data.buffers[index] = id;
        return true;
    }

    bool add_index_buffer(glData &data, const std::vector<GLuint> &buffer)
    {
        // Check that buffer is not empty
        assert(buffer.size() > 0);
        // Check if vertex array object is valid
        assert(data.vao != 0);
        // Set indices to buffer size
        data.indice_count = static_cast<GLuint>(buffer.size());
        // Bind vertex array object
        glBindVertexArray(data.vao);
        // Add buffer
        glGenBuffers(1, &data.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), &buffer[0], GL_STATIC_DRAW);

        // Check for error
        if (CHECK_GL_ERROR)
        {
            std::cerr << "Error - adding index buffer to geometry object" << std::endl;
            std::cerr << "Could not create buffer with OpenGL" << std::endl;
            return false;
        }

        return true;
    }

    bool add_buffer(glData &data, const std::vector<glm::vec2> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW)
    {
        return add_buffer(data, &buffer[0], 2, static_cast<GLuint>(buffer.size() * sizeof(glm::vec2)), index, buffer_type);
    }

    bool add_buffer(glData &data, const std::vector<glm::vec3> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW)
    {
        return add_buffer(data, &buffer[0], 3, static_cast<GLuint>(buffer.size() * sizeof(glm::vec3)), index, buffer_type);
    }

    bool add_buffer(glData &data, const std::vector<glm::vec4> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW)
    {
        return add_buffer(data, &buffer[0], 4, static_cast<GLuint>(buffer.size() * sizeof(glm::vec4)), index, buffer_type);
    }

    mesh_geom* get_model_mesh(const std::string &file)
    {
        std::string path = file;

        std::ifstream filepath(path, std::ios_base::in);

        if (filepath.bad())
        {
            std::cerr << "ERROR - could not find file " << path << std::endl;
            throw std::runtime_error("Error loading model file");
        }

        // Create model importer
        Assimp::Importer model_importer;
        // Read in the model data
        auto sc = model_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
            aiProcess_ValidateDataStructure | aiProcess_FindInvalidData);
        // Check that data has been read in correctly
        if (!sc) {
            // Display error
            std::cerr << "ERROR - loading geometry " << path << std::endl;
            std::cerr << model_importer.GetErrorString() << std::endl;
            // Throw exception
            throw std::runtime_error("Error reading in model file");
        }
        // TODO - read in multiple texture coordinates
        // TODO - mesh hierarchy?
        // TODO - bones
        // TODO - multiple colour values
        mesh_geom *ret = new mesh_geom();

        unsigned int vertex_begin = 0;
        // Iterate through each sub-mesh in the model
        for (unsigned int n = 0; n < sc->mNumMeshes; ++n) {
            // Get the sub-mesh
            auto mesh = sc->mMeshes[n];
            // Iterate through all the vertices in the sub-mesh
            for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                // Get position vertex
                auto pos = mesh->mVertices[i];
                // Add to positions data
                ret->positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
            }
            // If we have colour data then iterate through them
            if (mesh->HasVertexColors(0))
                // Iterate through colour data
                for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                    // Get the colour data from the mesh
                    auto col = mesh->mColors[0][i];
                    // Add to colour data vector
                    ret->colours.push_back(glm::vec4(col.r, col.g, col.b, col.a));
                }
            // Otherwise just push back grey
            else
                for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
                    ret->colours.push_back(glm::vec4(0.5, 0.5, 0.5, 1.0));
            // If we have normals, then add to normal data
            if (mesh->HasNormals())
                for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                    auto norm = mesh->mNormals[i];
                    ret->normals.push_back(glm::vec3(norm.x, norm.y, norm.z));
                }
            // ** Beej's earlier attempt to add texture **
            //// If we have texture coordinates then add to texture coordinate data
            //for (int count = 0; count < 8; ++count)
            //{
            //	if (mesh->HasTextureCoords(count))
            //	{
            //		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            //			auto tex_coord = mesh->mTextureCoords[count][i];
            //			ret->tex_coords.push_back(glm::vec2(tex_coord.x, tex_coord.y));
            //		}
            //		break;
            //	}
            //}
            // If we have face information, then add to index buffer
            if (mesh->HasFaces())
                for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
                    auto face = mesh->mFaces[f];
                    for (auto i = 0; i < 3; ++i)
                        ret->indices.push_back(vertex_begin + face.mIndices[i]);
                }
            vertex_begin += mesh->mNumVertices;
        }

        // Calculate the minimal and maximal
        ret->min = ret->positions[0];
        ret->max = ret->positions[0];
        for (auto &v : ret->positions) {
            ret->min = glm::min(ret->min, v);
            ret->max = glm::max(ret->max, v);
        }

        // Log success
        std::clog << "LOG - geometry " << path << " loaded "
            << (ret->normals.size() ? "With normals & " : "With no normals & ")
            << (ret->tex_coords.size() ? "With UVs" : "With no UVs") << std::endl;

        return ret;
    }

    mesh_geom* generate_rect()
    {
        mesh_geom *mesh = new mesh_geom();

        std::vector<glm::vec3> positions
        {
            // 1
            glm::vec3(-1.0f, 1.0f, 0.0f),
            glm::vec3(-1.0f, -1.0f, 0.0f),
            glm::vec3(1.0f, -1.0f, 0.0f),
            // 2
            glm::vec3(1.0f, -1.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 0.0f),
            glm::vec3(-1.0f, 1.0f, 0.0f)
        };
        // These are probably wrong
        std::vector<glm::vec2> tex_coords
        {
            glm::vec2(0.5, 1),
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 0),
            glm::vec2(0, 0),
            glm::vec2(0.5, 1)
        };

        // Colours
        std::vector<glm::vec4> colours
        {
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
        };

        //// Calculate the minimal and maximal
        //mesh->min = mesh->positions[0];
        //mesh->max = mesh->positions[0];
        //for (auto &v : mesh->positions) {
        //	mesh->min = glm::min(mesh->min, v);
        //	mesh->max = glm::max(mesh->max, v);
        //}

        mesh->positions = positions;
        mesh->tex_coords = tex_coords;
        mesh->colours = colours;

        return mesh;
    }

    // Currently a red 100x100 plane
    mesh_geom* generate_plane()
    {
        mesh_geom *mesh = new mesh_geom();

        std::vector<glm::vec3> positions
        {
			// 1
			glm::vec3(100.0f, 0.0f, -100.0f),
			glm::vec3(-100.0f,  0.0f, -100.0f),
			glm::vec3(-100.0f,  0.0f, 100.0f),
			// 2
			glm::vec3(-100.0f, 0.0f, 100.0f),
			glm::vec3(100.0f, 0.0f, 100.0f),
			glm::vec3(100.0f,0.0f, -100.0f)

        };
        // These are probably wrong
        std::vector<glm::vec2> tex_coords
        {
            glm::vec2(0.5, 1),
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 0),
            glm::vec2(0, 0),
            glm::vec2(0.5, 1)
        };

        // Colours
        std::vector<glm::vec4> colours
        {
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        };

        //// Calculate the minimal and maximal
        //mesh->min = mesh->positions[0];
        //mesh->max = mesh->positions[0];
        //for (auto &v : mesh->positions) {
        //	mesh->min = glm::min(mesh->min, v);
        //	mesh->max = glm::max(mesh->max, v);
        //}

        mesh->positions = positions;
        mesh->tex_coords = tex_coords;
        mesh->colours = colours;

		return mesh;
    }

	// add more generating functions 

    // Currently a blue 10x10x10 cube using triangles
    mesh_geom* generate_cube()
    {
        mesh_geom *mesh = new mesh_geom();

        std::vector<glm::vec3> positions
        {
            // Front
            glm::vec3(-0.5f, 0.5f, -2.0f),
            glm::vec3(-1.0f, 0.5f, -2.0f),
            glm::vec3(-1.0f, 0.0f, -2.0f),

            glm::vec3(-1.0f, 0.0f, -2.0f),
            glm::vec3(-0.5f, 0.0f, -2.0f),
            glm::vec3(-0.5f, 0.5f, -2.0f),
            
            // Back
            glm::vec3(-1.0f, 0.5f, -2.5f),
            glm::vec3(-0.5f, 0.5f, -2.5f),
            glm::vec3(-0.5f, 0.0f, -2.5f),

            glm::vec3(-0.5f, 0.0f, -2.5f),
            glm::vec3(-1.0f, 0.0f, -2.5f),
            glm::vec3(-1.0f, 0.5f, -2.5f),

            // Right
            glm::vec3(-0.5f, 0.5f, -2.5f),
            glm::vec3(-0.5f, 0.5f, -2.0f),
            glm::vec3(-0.5f, 0.0f, -2.0f),

            glm::vec3(-0.5f, 0.0f, -2.0f),
            glm::vec3(-0.5f, 0.0f, -2.5f),
            glm::vec3(-0.5f, 0.5f, -2.5f),

            // Left 
            glm::vec3(-1.0f, 0.5f, -2.0f),
            glm::vec3(-1.0f, 0.5f, -2.5f),
            glm::vec3(-1.0f, 0.0f, -2.5f),

            glm::vec3(-1.0f, 0.0f, -2.5f),
            glm::vec3(-1.0f, 0.0f, -2.0f),
            glm::vec3(-1.0f, 0.5f, -2.0f),

            // Top
            glm::vec3(-0.5f, 0.5f, -2.5f),
            glm::vec3(-1.0f, 0.5f, -2.5f),
            glm::vec3(-1.0f, 0.5f, -2.0f),

            glm::vec3(-1.0f, 0.5f, -2.0f),
            glm::vec3(-0.5f, 0.5f, -2.0f),
            glm::vec3(-0.5f, 0.5f, -2.5f),

            // Bottom
            glm::vec3(-1.0f, 0.0f, -2.0f),
            glm::vec3(-1.0f, 0.0f, -2.5f),
            glm::vec3(-0.5f, 0.0f, -2.5f),
 
            glm::vec3(-0.5f, 0.0f, -2.5f),
            glm::vec3(-0.5f, 0.0f, -2.0f),
            glm::vec3(-1.0f, 0.0f, -2.0f)

        };
        // These are probably wrong
        std::vector<glm::vec2> tex_coords
        {
            glm::vec2(0.5, 1),
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 0),
            glm::vec2(0, 0),
            glm::vec2(0.5, 1)
        };

        // Colours
        std::vector<glm::vec4> colours
        {
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
        };

        //// Calculate the minimal and maximal
        //mesh->min = mesh->positions[0];
        //mesh->max = mesh->positions[0];
        //for (auto &v : mesh->positions) {
        //	mesh->min = glm::min(mesh->min, v);
        //	mesh->max = glm::max(mesh->max, v);
        //}

        mesh->positions = positions;
        mesh->tex_coords = tex_coords;
        mesh->colours = colours;

        return mesh;
    }

	// map of functions for different shapes
	std::map<std::string, std::function<mesh_geom*()>> generation_functions =
    {
        { "rectangle", generate_rect },
        { "plane", generate_plane },
        { "cube", generate_cube },
	};

	// depending on whether a file or shape has been inputted - create the mesh.
    std::shared_ptr<mesh_geom> load_mesh(std::string msh_)
    {
		auto e = glGetError();
		mesh_geom* mesh = nullptr;
		if (generation_functions.count(msh_))
		{
			mesh = generation_functions[msh_]();
		}
		else if (msh_.size() > 0)
		{
			mesh = get_model_mesh(msh_);
		}
		else
		{
			std::cerr << "ERROR - empty string" << std::endl;
			throw std::runtime_error("Error loading mesh");
			return nullptr;
		}
		
		// create buffer objects 
        glData *om = new glData();
        mesh->GpuData = om;
        om->type = GL_TRIANGLES;
		e = glGetError();
        // Add the buffers to the geometry

        add_buffer(*om, mesh->positions, BUFFER_INDEXES::POSITION_BUFFER);

        if (mesh->colours.size() != 0)
            add_buffer(*om, mesh->colours, BUFFER_INDEXES::COLOUR_BUFFER);
        if (mesh->normals.size() != 0)
		{
            add_buffer(*om, mesh->normals, BUFFER_INDEXES::NORMAL_BUFFER);
            // generate_tb(normals);
        }
        if (mesh->tex_coords.size() != 0) 
            add_buffer(*om, mesh->tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
        

        if (mesh->indices.size() != 0)
		{
            add_index_buffer(*om, mesh->indices);
            om->has_indices = true;
        }
        else
        {
            om->vertex_count = mesh->positions.size();
        }
		e = glGetError();
        return std::shared_ptr<mesh_geom>(mesh);
    }

	void gl::render(glData *om, GLuint programID, glm::mat4 MVP)
	{
		auto e1 = glGetError();
		auto loc = glGetUniformLocation(programID, "MVP");

		glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(MVP));
		auto e3 = glGetError();
		// Bind the vertex array object for the
		glBindVertexArray(om->vao);
		auto e4 = glGetError();
		// Check for any OpenGL errors
		if (gl::CHECK_GL_ERROR)
		{
			// Display error
			std::cerr << "ERROR - rendering geometry" << std::endl;
			std::cerr << "Could not bind vertex array object" << std::endl;
			// Throw exception
			throw std::runtime_error("Error rendering geometry");
		}
		// If there is an index buffer then use to render
		if (om->has_indices)
		{
			// Bind index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, om->index_buffer);
			// Check for error
			if (gl::CHECK_GL_ERROR)
			{
				std::cerr << "ERROR - rendering geometry" << std::endl;
				std::cerr << "Could not bind index buffer" << std::endl;
				// Throw exception
				throw std::runtime_error("Error rendering geometry");
			}

			// Draw elements
			glDrawElements(om->type, om->indice_count, GL_UNSIGNED_INT, nullptr);
			// Check for error
			if (gl::CHECK_GL_ERROR)
			{
				// Display error
				std::cerr << "ERROR - rendering geometry" << std::endl;
				std::cerr << "Could not draw elements from indices" << std::endl;
				// Throw exception
				throw std::runtime_error("Error rendering geometry");
			}
		}
		else
		{
			// Draw arrays
			glDrawArrays(om->type, 0, om->vertex_count);
			// Check for error
			if (gl::CHECK_GL_ERROR)
			{
				std::cerr << "ERROR - rendering geometry" << std::endl;
				std::cerr << "Could not draw arrays" << std::endl;
				// Throw exception
				throw std::runtime_error("Error rendering geometry");
			}
		}
	}



}
