#include "EngineClock.h"


EngineClock::EngineClock()
{
}


EngineClock::~EngineClock()
{
}

EngineClock::EngineClock(void(*Update) (float))
{
	ptr_update = Update;
}

void EngineClock::setFPS(int FramesPerSecond)
{
	float t = 1.0f / ((float)FramesPerSecond);

	p_timeStep = t;
}

void EngineClock::setTimeStep(float dt)
{
	p_timeStep = dt;
}

double EngineClock::getTimeStep() const
{
	return p_timeStep;
}

void EngineClock::checkTime()
{
	// Get the current time.
	p_time = glfwGetTime();

	// Get the time since we last ran an update.
	double dt = p_time - p_timeBase;

	// If more time has passed than our physics timestep.
	if (dt > p_timeStep)
	{

		p_timeBase = p_time; // set new last updated time

		// Limit dt
		if (dt > 0.25)
		{
			dt = 0.25;
		}
		p_accumulator += dt;

		// Update physics necessary amount
		while (p_accumulator >= p_timeStep)
		{
			ptr_update((float) p_timeStep);
			p_accumulator -= p_timeStep;
		}
	}
}