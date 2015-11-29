#include "CoreEngine.h"


CoreEngine::CoreEngine()
{
}


CoreEngine::~CoreEngine()
{
}

void CoreEngine::init(int width, int height, std::string Title)
{
	glfwInit();

	// Creates a window given (width, height, title, monitorPtr, windowPtr).
	// Don't worry about the last two, as they have to do with controlling which monitor to display on and having a reference to other windows. Leaving them as nullptr is fine.
	p_window = glfwCreateWindow(width, height, Title.c_str(), nullptr, nullptr);

	// Makes the OpenGL context current for the created window.
	glfwMakeContextCurrent(p_window);

	// Sets the number of screen updates to wait before swapping the buffers.
	glfwSwapInterval(1);


	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		getchar();
		exit(EXIT_FAILURE);
	}


	glFrontFace(GL_CCW);

	//glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CoreEngine::gameLoop()
{
	Program program;
	Shader vertexShader("Shaders\\VertexShader.glsl", GL_VERTEX_SHADER);
	Shader fragmentShader("Shaders\\FragmentShader.glsl", GL_FRAGMENT_SHADER);
	
	program.attachShader(vertexShader);
	program.attachShader(fragmentShader);
	program.linkProgram();

	program.addAttribute("in_position", 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	program.addAttribute("in_normal", 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
	program.addAttribute("in_tangent", 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, tangent));
	program.addAttribute("in_texCoord", 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texCoord));

	GameObject* object = resourceManager.loadObject("Nanosuit/nanosuit.obj", program);
	
	object->m_transform.m_position = glm::vec3(0, 0, 10.0f);

	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f,0.3f,0.3f,1.0f);
		object->draw();
		glfwSwapBuffers(p_window);
	}
}