//
// Created by zoe on 03/10/17.
//
#include <fstream>
#include <string>
#include <vector>
#include "glfw.h"


namespace glfw
{
    GLFWwindow* window;

    int runWindow(int resX, int resY, bool windowed)
    {
        // Initialise GLFW
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            getchar();
            return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        auto monitor = glfwGetPrimaryMonitor();
        auto mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        // Open a window and create its OpenGL context
        window = glfwCreateWindow(resX, resY, "Race The Moon", NULL, NULL);
        if (window == NULL) {
            fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
            getchar();
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

		if (windowed)
			glfwSetWindowMonitor(glfw::window, NULL, ((1920 - resX) / 2), ((1080 - resY) / 2), resX, resY, GLFW_DONT_CARE);
		else
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, resX, resY, GLFW_DONT_CARE);

        glewExperimental = GL_TRUE;
        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            getchar();
            glfwTerminate();
            return -1;
        }

        auto f = glGetError();
		auto g = glGetError();

        glViewport(0, 0, resX, resY);

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		auto e = glGetError();

        return 0;

    }

	void closeWindow()
	{

	}
	
}
