#pragma once

#include <iostream>
#include "entity.h"
#include "component.h"
#include "subsystem.h"
#include "glfw.h"
#include "opengl_util.h"

//static GLuint glfw::LoadShaders(char const* vertex_file_path, char const* fragment_file_path);
#include <glm/glm.hpp>




// Effect struct
struct Effect
{
	std::string name;
	bool has_geometry;
	bool is_compute;
	void *GpuData;
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


struct render_data
{
    bool visible = false;
    // Let's pretend this is a matrix that was built.
    std::string transform = "(0, 0, 0)";
    std::string colour = "Red";
    std::string shape = "Sphere";
    std::string shader = "Phong";
		// Reference to structs
	  Effect effect;
		Mesh mesh;

};

struct render_component : public component
{
private:
    render_data &_data;

    std::shared_ptr<entity> _parent;
public:
	  render_component(std::shared_ptr<entity> e, render_data &data);

		bool initialise() override final;

		bool load_content() override final;

		void update(float delta_time) override final;

		void render() override final;

		void unload_content() override final;

    void shutdown() override final;
};

class renderer : public subsystem
{
private:
    std::vector<render_data> _data;

	renderer();

	GLuint vertexArrayID = 0;
	GLuint vertexbuffer = 0;
	GLuint programID = 0;

public:

    inline static std::shared_ptr<renderer> get()
    {
        static std::shared_ptr<renderer> instance(new renderer());
        return instance;
    }

	std::shared_ptr<render_component> build_component(std::shared_ptr<entity> &e, std::string colour, std::string shape, std::string shader, Effect effect, Mesh mesh);
	bool initialise();

	bool load_content();

	void update(float delta_time);

    void render();

	void unload_content();
	void shutdown();

	static Mesh *GetMesh(const std::string &path);
	static Effect *GetEffect(const std::string &path);

};