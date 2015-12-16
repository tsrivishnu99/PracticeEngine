#version 430 core // Identifies the version of the shader, this line must be on a separate line from the rest of the shader code
 
layout(location = 0) in vec3 in_position;	// Get in a vec3 for position
layout(location = 1) in vec3 in_normal;
//layout(location = 2) in vec3 in_tangent;
//layout(location = 3) in vec2 in_texCoord;

out vec4 frag_Color;					// Our vec4 color variable containing r, g, b, a

//uniform mat4 MVP;				// Our uniform MVP matrix to modify our position values

void main(void)
{
	vec3 normal = in_normal;
	//vec3 tangent = in_tangent;
	//vec2 texCoord = vec2(1.0f);

	frag_Color = vec4(0.3f,0.0f,0.6f,0.5f) + vec4(normal,0.0f) * 0.001f;//vec4(normal + tangent + vec3(texCoord,1.0f) ,1.0f) ;
	gl_Position = vec4(in_position, 1.0f);
}
