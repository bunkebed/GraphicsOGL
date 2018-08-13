// GraphicsOGL.cpp : Driver for the application
//

// Graphics API Imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Imports
#include <iostream>
using namespace std;

// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window!" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize Glad!" << endl;
		return -1;
	}

	// tell opengl the size of the rendering window
	glViewport(0, 0, 800, 600);

	// set callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate the program
	glfwTerminate();
    return 0;
}

/*
callback function for when the window is resized
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

