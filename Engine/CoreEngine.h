#pragma once
#include "EngineClock.h"
#include "Program.h"
#include "GameObject.h"

class CoreEngine
{
private:
	//Members
	static EngineClock Clock;
	GLFWwindow* p_window;

	//Functions
	
public:
	CoreEngine();
	~CoreEngine();

	void gameLoop();
	void init(int width, int height, std::string Title);
};

