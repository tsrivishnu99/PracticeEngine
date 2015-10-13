#include "Transform.h"


Transform::Transform() : m_position(glm::vec3(0)),
m_transformation(glm::mat4(1)),
m_orientation(glm::quat(glm::vec3(0, 0, 0)))
{
}

Transform::Transform(const Transform &copy)
{
	m_position = copy.m_position;
	m_transformation = copy.m_transformation;
	m_orientation = copy.m_orientation;
}

Transform::~Transform()
{
}

glm::mat4 Transform::getTransformationMatrix()
{
	//Compute the transformation matrix for each object only when it being called. That way it will be computed only once every rendercall (that too if it is being rendered).
	m_transformation = glm::mat4_cast(m_orientation);
	m_transformation = glm::translate(m_position) * m_transformation;

	return m_transformation;
}

#pragma region movement Functions
void Transform::setOrientation(float x, float y, float z)
{
	m_orientation = glm::quat(glm::vec3(x, y, z));
}

void Transform::rotateAngleAxis(float angle, glm::vec3 axis)
{
	// In quaternions, to concatenate rotations, we simply multiply the two quaternions.
	// If the object needs to be rotated by a first then by b, then the resulting quaterions can be simplified to (ba) i.e. b * a 
	glm::quat rotation = glm::quat(angle / 2.0f, glm::normalize(axis));
	m_orientation = rotation * m_orientation;
}

void Transform::rotateEulerAngles(float x, float y, float z)
{
	// Create 3 quaternions for rotation along three separate axis and multiply them to the orientaion quaternion.
	glm::quat rotateX(x / 2.0f, glm::vec3(1, 0, 0));
	glm::quat rotateY(y / 2.0f, glm::vec3(0, 1, 0));
	glm::quat rotateZ(z / 2.0f, glm::vec3(0, 0, 1));

	m_orientation = rotateZ * rotateY * rotateX * m_orientation;
}

void Transform::rotateQuaternions(glm::quat rotate)
{
	// Just multiply the quaternion with current orientation quaternion
	m_orientation = rotate * m_orientation;
}

void Transform::setPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void Transform::setPosition(glm::vec3 newPos)
{
	m_position = newPos;
}
#pragma endregion movement Functions
