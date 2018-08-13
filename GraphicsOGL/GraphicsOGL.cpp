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

	// open shader files
	ifstream vShaderFile;
	ifstream fShaderFile;
	vShaderFile.open("Shaders/VShaderV1.txt");
	fShaderFile.open("Shaders/FShaderV1.txt");

	// read file content
	stringstream vShaderStream, fShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	//close file handlers
	vShaderFile.close();
	fShaderFile.close();

	//convert stream into string
	string vertexCode = vShaderStream.str();
	string fragmentCode = fShaderStream.str();

	const char* vCode = vertexCode.c_str();
	const char* fCode = fragmentCode.c_str();

	// compile shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vCode, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fCode, NULL);
	glCompileShader(fragmentShader);

	//check shader compilation success
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// create a shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check shader program creation success
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// get rid of our shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// vertices of a triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// generating a VBO and VAO
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);	
	// bind VAO
	glBindVertexArray(VAO);

	// bind  VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// link vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// process user input
		processInput(window);

		// rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw image
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate the program
	glfwTerminate();
    return 0;
}

/*
Processing user input
*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*
callback function for when the window is resized
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

