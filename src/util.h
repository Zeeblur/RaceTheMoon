// General utility functions

#pragma once
#include <fstream>
#include <iostream>
// Checks for any OpenGL errors
inline bool get_GL_error(int line, const std::string& file)
{
	// Get the current error
	GLenum error = glGetError();
	// If there is an error display message
	if (error)
	{
		// Display error
		std::cerr << "OpenGL Error: " << gluErrorString(error) << std::endl;
		std::cerr << "At line " << line << " in file " << file.c_str() << std::endl;
		return true;
	}
	return false;
}
#define CHECK_GL_ERROR get_GL_error(__LINE__, __FILE__)

// Utility function to check if a file exists
inline bool check_file_exists(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}