#shader vertex
#version 460 core

layout(location = 0) in vec3 VertexPosition;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    //gl_Position = u_Projection * u_View * u_Model * vec4(VertexPosition, 1.0f);
    gl_Position = vec4(VertexPosition, 1.0f);
}

#shader fragment
#version 460 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
