#pragma once
#include "GL\glew.h"
//#include "glfw.h"
#include <vector>
/*
Stores the image information for texturing objects
*/
class texture
{
private:
    // The OpenGL ID of the texture data
    GLuint _id = 0;
    // The width of the texture
    GLuint _width = 0;
    // The height of the texture
    GLuint _height = 0;
    // The type of the texture
    GLenum _type = 0;
public:
    // Default constructor
    texture() { }
    /*
    Loads a texture from the given filename with mipmaps and anisotropic
    filtering determined by the user.
    */
	texture(const std::string &filename, bool mipmaps, bool anisotropic);
   // Default copy constructor and assignment operator
    texture(const texture &other) = default;
    texture& operator=(const texture &rhs) = default;
    // Destroys the texture
    ~texture() { }
    // Gets the OpenGL ID of the texture
    GLuint get_id() const { return _id; }
    // Gets the width of the texture
    GLuint get_width() const { return _width; }
    // Gets the height of the texture
    GLuint get_height() const { return _height; }
    // Gets the type of the texture
    GLuint get_type() const { return _type; }
};