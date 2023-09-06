#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec4 outColor;
out vec2 TexCoords;
out vec3 Normal; // Light

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	//aColor = vec4(1.0,1.0,1.0,1.0);
	FragPos = vec3(model * vec4(aPos, 1.0f));
	//outColor = aColor;
	outColor = vec4(1.0,1.0,1.0,1.0);
	TexCoords = aTexCoord;
	Normal = mat3(transpose(inverse(model))) * aNormal; // Light
}