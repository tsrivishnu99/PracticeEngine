#pragma once
#include "GLIncludes.h"

class Transform
{
public:
	glm::vec3 m_position;												// Stores the Position of the object in world space
	glm::quat m_orientation;											// Stores the orientation of the obejct in quaternions
	glm::mat4 m_transformation;											// Stores the transformation matrix of the object

	Transform();
	Transform(const Transform &copy);
	~Transform();

	void setOrientation(float x, float y, float z);						// set the orientaion of the object
	void rotateAngleAxis(float angle, glm::vec3 axis);					// rotate the object by "angle" along the provided axis
	void rotateEulerAngles(float x, float y, float z);					// rotate the object by x along x axis, y along y axis, and z along z axis.
	void rotateQuaternions(glm::quat rotate);							// rotate the object by the given quaternion
	void setPosition(float x, float y, float z);						// Set the position of the object
	void setPosition(glm::vec3 newPos);									// Set the position of the object

	glm::mat4 getTransformationMatrix();								// Computes the transformation matrix for the current position and orientation and returns it 

};

