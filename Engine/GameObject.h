#pragma once
#include "GLIncludes.h"
#include "Material.h"
#include "Mesh.h"
#include "Program.h"

class GameObject
{
private:
	std::vector<Mesh> p_mesh;
	Program p_program;
	glm::vec3 p_position;												// Stores the Position of the object in world space
	glm::quat p_orientation;											// Stores the orientation of the obejct in quaternions
	glm::mat4 p_transformation;											// Stores the transformation matrix of the object

public:
	GameObject();
	GameObject(const GameObject &copy);
	~GameObject();
	
	void setProgram(Program program);
	void setMesh(Mesh m);
	void setOrientation(float x, float y, float z);						// set the orientaion of the object
	void rotateAngleAxis(float angle, glm::vec3 axis);					// rotate the object by "angle" along the provided axis
	void rotateEulerAngles(float x, float y, float z);					// rotate the object by x along x axis, y along y axis, and z along z axis.
	void rotateQuaternions(glm::quat rotate);							// rotate the object by the given quaternion
	void setPosition(float x, float y, float z);						// Set the position of the object
	void setPosition(glm::vec3 newPos);									// Set the position of the object

	glm::mat4 getTransformationMatrix();								// Computes the transformation matrix for the current position and orientation and returns it 
	void draw();													// Draw call

	GameObject* m_parent;
};

