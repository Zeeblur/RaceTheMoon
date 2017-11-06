#include <assert.h>
#include "texture.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <IL/il.h>
#include <IL/ilu.h>
#include "opengl_util.h"
#define CHECK_GL_ERROR gl::CheckGL(__LINE__, __FILE__)

bool get_devil_error() {
	bool ret = false;
	ILenum error = ilGetError();

	if (error != IL_NO_ERROR) {
		do {
			ret = true;
			std::cerr << "DevIL error: " << iluErrorString(error) << std::endl;
		} while ((error = ilGetError()));
	}
	return ret;
}

bool check_file_exists(const std::string &filename) {
	std::ifstream file(filename);
	return file.good();
}

// Creates a new texture object from the given file with mipmaps and anisotropic filtering defined
texture::texture(const std::string &filename, bool mipmaps, bool anisotropic) 
{
	

	// Check if file exists
	if (!check_file_exists(filename)) {
		// Failed to read file.  Display error
		std::cerr << "ERROR - could not load texture " << filename << std::endl;
		std::cerr << "File Does Not Exist" << std::endl;
		// Throw exception
		throw std::runtime_error("Error adding texture");
	}
	// Initialise devIL
	ilInit();
	iluInit();
	ILuint ImgId = -1;
	// Generate the main image name to use.
	ilGenImages(1, &ImgId);

	// Bind this image name.
	ilBindImage(ImgId);

	auto success = ilLoadImage(filename.c_str());

	if (get_devil_error()) {
		throw std::runtime_error("Error creating texture");
	}

	{
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
			iluFlipImage();
		}
	}

	// Convert the image into a suitable format to work with
	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	const auto width = ilGetInteger(IL_IMAGE_WIDTH);
	const auto height = ilGetInteger(IL_IMAGE_HEIGHT);
	auto pixel_data = ilGetData();

	// Generate texture with OpenGL
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	// Check for any errors with OpenGL
	if (CHECK_GL_ERROR) {
		// Problem creating texture object
		std::cerr << "ERROR - loading texture " << filename.c_str() << std::endl;
		std::cerr << "Could not allocate texture with OpenGL" << std::endl;
		// Set id to 0
		_id = 0;
		// Throw exception
		throw std::runtime_error("Error creating texture");
	}

	// Set texture parameters
	if (mipmaps) {
		// Turn on linear mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		CHECK_GL_ERROR; // Not considered fatal here
	}
	else {
		// Basic scaling
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		CHECK_GL_ERROR; // Not considered fatal here
	}
	if (anisotropic) {
		// Turn on anisotropic filtering
		float max_anisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
		CHECK_GL_ERROR; // Non-fatal
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
		CHECK_GL_ERROR; // Non-fatal
	}

	// Now set texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixel_data[0]);
	// clear out ddata from DevIL
	ilDeleteImage(ImgId);
	pixel_data = nullptr;

	// Check if error
	if (CHECK_GL_ERROR) {
		// Error loading texture data into OpenGL
		std::cerr << "ERROR - loading texture " << filename.c_str() << std::endl;
		std::cerr << "Could not load texture data in OpenGL" << std::endl;
		// Unallocate image with OpenGL
		glDeleteTextures(1, &_id);
		_id = 0;
		// Throw exception
		throw std::runtime_error("Error creating texture");
	}

	// Generate mipmaps
	if (mipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);

	// Set attributes
	_height = height;
	_width = width;
	_type = GL_TEXTURE_2D;

	// Unload image data
	// FreeImage_Unload(image);
	CHECK_GL_ERROR; // Non-fatal - just info

					// Log
	std::clog << "LOG - texture " << filename.c_str() << " loaded, " << width << 'x' << height << std::endl;
}