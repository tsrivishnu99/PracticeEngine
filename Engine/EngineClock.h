#pragma once
#include "GLIncludes.h"

class EngineClock
{
private:
	//Members
	double p_time = 0.0f;
	double p_timeBase = 0.0f;
	double p_accumulator = 0.0f;
	double p_timeStep = 0.012;					// number of milliseconds we intend for the physics to update (default is of 60 fps).
	
	//Functions
	void(*ptr_update) (float);					// This is pointer to the update function in the coreEngine
public:
	EngineClock();
	~EngineClock();
	EngineClock(void (*Update) (float));		// This constructor gets the fuction pointer from the coreEngine. This is done, So that the core does not have to resend the function pointer every time.
	
	void checkTime();							// This function will be called by the coreEngine every game loop
	void setFPS(int FramesPerSecond);			// This function sets the timestep indirectly by computing it from the FPS, which is maintained by the clock. Total number of frames displayed in 1 second is sent as a parameter.
	void setTimeStep(float dt);					// This function sets the timeStep directly.
	double getTimeStep() const;					// Return the current timestep
};


