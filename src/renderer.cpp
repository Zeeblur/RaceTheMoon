#include "renderer.h"
//#include <string>
#include <sstream>
//#include <GL/glew.h>
#include <assimp/Importer.hpp>"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include "glfw.h"
#include "util.h"


render_component::render_component(std::shared_ptr<entity> e, render_data &data)
	: _parent(e), _data(data)
{
	_active = false;
	_data.visible = true;
}

bool render_component::initialise()
{
	return true;
}

bool render_component::load_content()
{
	return true;
}

void render_component::update(float delta_time)
{
	// This should never be called.
}

void render_component::render()
{
	if (_data.visible)
	{
		// "Generate" the transform matrix.
		std::stringstream ss;
		ss << "(" << _parent->get_trans().x << ", " << _parent->get_trans().y << ", " << _parent->get_trans().z << ")" << std::endl;
		_data.transform = ss.str();
	}
}

void render_component::unload_content()
{

}

void render_component::shutdown()
{

}

renderer::renderer()
{
	_active = false;
}

std::shared_ptr<render_component> renderer::build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader, Effect effect, Mesh mesh)
{
	_data.push_back(render_data());
	_data.back().colour = colour;
	_data.back().shape = shape;
	_data.back().shader = shader;
	_data.back().effect = effect;
	_data.back().mesh = mesh;
	return std::make_shared<render_component>(e, std::ref(_data.back()));
}

bool renderer::initialise()
{
	std::cout << "Renderer initialising" << std::endl;
	return true;
}

bool renderer::load_content()
{
	std::cout << "Renderer loading content" << std::endl;
	return true;
}

void renderer::update(float delta_time)
{
	// Should never be called
	std::cout << "Renderer updating" << std::endl;

}

void renderer::render()
{
	std::cout << "Renderer rendering" << std::endl;
	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto &d : _data)
	{
		if (d.visible)
		{
			// TODO: open gl calls

			std::cout << "Rendering " << d.colour << " ";
			std::cout << d.shape << " using " << d.shader;
			std::cout << " shading at position " << d.transform << std::endl;
		}
	}

	glfwSwapBuffers(glfw::window);
	glfwPollEvents();
}

void renderer::unload_content()
{
	std::cout << "Renderer unloading content" << std::endl;
}

void renderer::shutdown()
{
	std::cout << "Renderer shutting down" << std::endl;
}

// **** ASSIMP CODE FROM SAM'S ENGINE ****

const static glm::vec4 coloursD[3] = { glm::vec4(0.533f, 0.898f, 0.231, 1.0f), glm::vec4(1.0f, 0.698f, 0.259, 1.0f),
																			 glm::vec4(0.412f, 0.227f, 0.702f, 1.0f) };

bool Findfile(std::string &path) {
	static const std::string filedirs[] = { "", "res/", "res/mdl/", "res/fonts/", "res/sound/", "res/shaders/ogl/" };
	for (const auto s : filedirs) {
		std::ifstream inFile((s + path).c_str(), std::ifstream::in);
		if (inFile.good()) {
			path = s + path;
			return true;
		}
	}
	return false;
}

bool read_file(const std::string &filename, std::string &content) {
	// Create filestream
	std::ifstream file(filename, std::ios_base::in);
	// Check that file exists.  If not, return false
	if (file.bad())
		return false;

	// File is good.  Read contents
	std::stringstream buffer;
	buffer << file.rdbuf();

	// Get contents from the file
	content = buffer.str();

	// Close file and return true
	file.close();
	return true;
}

Mesh *renderer::GetMesh(const std::string &file) {
	std::string path = file;
	if (!Findfile(path)) {
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
	Mesh *ret = new Mesh();

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
		    ret->colours.push_back(coloursD[i % 3]);
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

	// hand over to implemntation
	util::LoadModel(ret);

	// Log success
	std::clog << "LOG - geometry " << path << " loaded "
		<< (ret->normals.size() ? "With normals & " : "With no normals & ")
		<< (ret->tex_coords.size() ? "With UVs" : "With no UVs") << std::endl;

	return ret;
}

Effect *renderer::GetEffect(const std::string &path) {
	std::string vert_path = path + ".vert";
	std::string frag_path = path + ".frag";
	std::string geom_path = path + ".geom";
	std::string vert_file, frag_file, geom_file;

	if (!Findfile(vert_path) || !read_file(vert_path, vert_file)) {
		throw std::runtime_error("Error loading vert");
	}

	if (!Findfile(frag_path) || !read_file(frag_path, frag_file)) {
		throw std::runtime_error("Error loading vert");
	}

	auto e = new Effect();
	e->name = path;
	e->has_geometry = (Findfile(geom_path) && read_file(geom_path, geom_file));

	util::LoadEffect(e, vert_file, frag_file, geom_file);

	return e;
}

// **** END OF ASSIMP CODE ****