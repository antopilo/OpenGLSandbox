#shader vertex
#version 460 core

layout(location = 0) in vec3 VertexPosition;

void main()
{
    gl_Position = vec4(VertexPosition, 1.0f);
}

#shader fragment
#version 460 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
