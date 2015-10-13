#include "GameObject.h"

#pragma region constructor and destructor
GameObject::GameObject() :	p_position(glm::vec3(0)),
							p_transformation(glm::mat4(1)),
							p_orientation(glm::quat(glm::vec3(0, 0, 0)))
{
}

GameObject::GameObject( const GameObject &copy)
{
	p_position = copy.p_position;
	p_transformation = copy.p_transformation;
	p_orientation = copy.p_orientation;
	p_program = copy.p_program;
	p_mesh = copy.p_mesh;
}

GameObject::~GameObject()
{
}
#pragma endregion constructor and destructor

glm::mat4 GameObject::getTransformationMatrix() 
{
	//Compute the transformation matrix for each object only when it being called. That way it will be computed only once every rendercall (that too if it is being rendered).
	p_transformation = glm::mat4_cast(p_orientation);
	p_transformation = glm::translate(p_position) * p_transformation;

	return p_transformation;
}

void GameObject::setProgram(Program program)
{
	p_program = program;
}

void GameObject::setMesh(Mesh m)
{
	p_mesh.push_back(m);
}

#pragma region movement Functions
void GameObject::setOrientation(float x, float y, float z)
{
	p_orientation = glm::quat(glm::vec3(x, y, z));
}

void GameObject::rotateAngleAxis(float angle, glm::vec3 axis)
{
	// In quaternions, to concatenate rotations, we simply multiply the two quaternions.
	// If the object needs to be rotated by a first then by b, then the resulting quaterions can be simplified to (ba) i.e. b * a 
	glm::quat rotation = glm::quat(angle / 2.0f, glm::normalize(axis));
	p_orientation = rotation * p_orientation;
}

void GameObject::rotateEulerAngles(float x, float y, float z)
{
	// Create 3 quaternions for rotation along three separate axis and multiply them to the orientaion quaternion.
	glm::quat rotateX(x / 2.0f, glm::vec3(1, 0, 0));
	glm::quat rotateY(y / 2.0f, glm::vec3(0, 1, 0));
	glm::quat rotateZ(z / 2.0f, glm::vec3(0, 0, 1));

	p_orientation = rotateZ * rotateY * rotateX * p_orientation;
}

void GameObject::rotateQuaternions(glm::quat rotate)
{
	// Just multiply the quaternion with current orientation quaternion
	p_orientation = rotate * p_orientation;
}

void GameObject::setPosition(float x, float y, float z)
{
	p_position = glm::vec3(x, y, z);
}

void GameObject::setPosition(glm::vec3 newPos)
{
	p_position = newPos;
}
#pragma endregion movement Functions

void GameObject::draw()
{
	p_program.UseProgram();
	/*
		Entire draw call need to addressed here
	*/
	for (GLuint i = 0; i < p_mesh.size(); i++)
		p_mesh[i].draw();
}

