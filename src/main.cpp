#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "common.h"
#include "../lib/glfw/glfw3.h"
#include <fstream>
#include "vertex.h"
#include "shader.h"
#include "buffer.h"
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


std::string readString(const std::string& filename) {
	std::ifstream ifs(filename.c_str(), std::ios_base::binary | std::ios_base::ate);
	std::vector<char> chars(ifs.tellg());
	ifs.seekg(0);
	ifs.read(chars.data(), chars.size());
	return std::string(chars.data(), chars.size());
}

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	// initialize opengl extensions
	if ( glewInit() != GLEW_OK ) {
		std::cout << "could not initialize opengl extensions" << std::endl;
		glfwTerminate();
		return -1;
	}

	// load shaders code
	std::string vertexShaderSource = readString("data/vertex.glsl");
	std::string fragmentShaderSource = readString("data/fragment.glsl");

	
	std::shared_ptr<Shader> shader(new Shader(vertexShaderSource, fragmentShaderSource));

	if (shader->getError().size() > 0) 
	{
		glDeleteProgram(shader->getId());
		glfwTerminate();
		/*delete(shader);*/
		return -1;	
	}

	shader->use();
	
	// initialize opengl states
	glEnable(GL_SCISSOR_TEST);

	glm::vec3 v1( 0,  1, 0);
	glm::vec3 v2(-1, -1, 0);
	glm::vec3 v3(1, -1, 0);
	glm::vec4 c1( 1,  0, 0, 1);	
	glm::vec4 c2( 0,  1, 0, 1);
	glm::vec4 c3( 0,  0, 1, 1);

	// define triangle
	std::vector<Vertex> vertices = {
		
		Vertex(v1,c1),
		Vertex(v2,c2),
		Vertex(v3,c3)

	};

	std::vector<uint32_t> indexes = {};

	// store triangle in vram
	std::shared_ptr<Buffer> buffer(new Buffer(vertices, indexes));
	
	
	// main loop
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

		// setup viewport
		glViewport(0, 0, screenWidth, screenHeight);
		glScissor(0, 0, screenWidth, screenHeight);

		// clear screen
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//// draw with vertex arrays & vbos
		buffer->draw(*shader);

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown	
	glfwTerminate();
	//glDeleteProgram(shader->getId());
	//glDeleteBuffers(1, &vertexBuffer);
	
	/*delete(shader);*/
}
