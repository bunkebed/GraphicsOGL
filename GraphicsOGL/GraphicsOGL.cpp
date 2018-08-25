//------------------------------------------------------
// Code adapted from Code adapted from https://learnopengl.com
// GraphicsOGL.cpp : Driver for the application
//

// Graphics API Imports
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Imports
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Shader.h"

// function prototypes
void processInput(GLFWwindow *window);
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

	// load shaders
	Shader shader("Shaders/v1.vs.txt", "Shaders/v1.fs.txt");

	// vertices of a rectangle
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	// generating a VBO, VAO, and EBO
	unsigned int VBO, VAO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);	

	//----------------------------
	// setup triangle
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// use the shader and set an offset value
	shader.use();

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// process user input
		processInput(window);

		// rendering
		float time = glfwGetTime();
		float redValue = sin(time) / 2.0f + 0.5f;
		glClearColor(redValue, 0.05f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw first triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Terminate the program
	glfwTerminate();
    return 0;
}

//-------------------------------------------------------
// Process user input
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//--------------------------------------------------------
// callback for when the window size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

