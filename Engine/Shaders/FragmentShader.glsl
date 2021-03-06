#version 430 core // Identifies the version of the shader, this line must be on a separate line from the rest of the shader code

layout(location = 0) out vec4 out_color; // Establishes the variable we will pass out of this shader.

in vec4 frag_Color;	// Take in a vec4 for color
 
void main(void)
{
	out_color = frag_Color; // Set our out_color equal to our in color, basically making this a pass-through shader.
}