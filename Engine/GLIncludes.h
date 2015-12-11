
#ifndef _GL_INCLUDES_H
#define _GL_INCLUDES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
#include <algorithm>
#include "soil\SOIL.h"
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtx\rotate_vector.hpp"

#define PI 3.14159265

struct Vertex
{
	glm::vec3 position;
	//glm::vec3 normal;
	//glm::vec3 tangent;
	//glm::vec2 texCoord;
};
#endif _GL_INCLUDES_H