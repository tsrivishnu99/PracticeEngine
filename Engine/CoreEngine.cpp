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

	// Enables blending, which we will use for Alpha Blending our texture.
	// Basically, all color data for pixels has 4 floats, RGB is straightforward. It's just the value of Red, Green, and Blue. The fourth value is A, for Alpha. Alpha is the 
	// transparency value, basically determining that 1.0 means it is fully visible, and 0.0 is invisible, meaning 0.5 is halfway see-through. The sample texture we are using 
	// has transparency, so we are enabling blending to allow that transparency to be visible in our engine (otherwise, it will just be rendered black wherever it is transparent).
	// Note that this can have unwanted effects in other applications, and only certain file types actually include transparency (such as PNG).
	glEnable(GL_BLEND);

	// The glBlendFunc controls how the blending actually occurs. This particular setting modifies the incoming color by its alpha value, and then modifies the destination color by 
	// one minus the alpha value of the incoming color. Then the two are summed up and displayed.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Determines the interpretation of polygons for rasterization. The first parameter, face, determines which polygons the mode applies to.
	// The face can be either GL_FRONT, GL_BACK, or GL_FRONT_AND_BACK
	// The mode determines how the polygons will be rasterized. GL_POINT will draw points at each vertex, GL_LINE will draw lines between the vertices, and 
	// GL_FILL will fill the area inside those lines.
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
	
	while (1)
	{
		object->draw();
		glfwSwapBuffers(p_window);
	}
}