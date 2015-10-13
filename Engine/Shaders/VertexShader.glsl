#version 430 core // Identifies the version of the shader, this line must be on a separate line from the rest of the shader code
 
layout(location = 0) in vec3 in_position;	// Get in a vec3 for position
in vec3 in_normal;
in vec3 in_tangent;
in vec2 in_texCoord;

out vec4 color; // Our vec4 color variable containing r, g, b, a

//uniform mat4 MVP; // Our uniform MVP matrix to modify our position values

void main(void)
{
	color = vec4(0,0,1,1);
	gl_Position = vec4(in_position, 1.0f);
}
