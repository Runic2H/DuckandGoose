#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;
void main()
{
	v_Color = a_Color;
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;
in vec4 v_Color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
};