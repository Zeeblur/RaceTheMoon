//
// Created by zoe on 28/09/17.
//

#include <iostream>
#include <GLFW/glfw3.h>


int main()
{
    std::cout << "hello world" << std::endl;
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Race The Window", nullptr, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}