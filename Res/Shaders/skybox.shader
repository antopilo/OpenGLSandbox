#shader vertex
#version 460 core

layout(location = 0) in vec3 vertexPosition;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
void main()
{
    TexCoords = vertexPosition;
    gl_Position = projection * mat4(mat3(view)) * vec4(vertexPosition, 1.0);
}

#shader fragment
#version 460 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
    vec4 sky = texture(skybox, TexCoords);
    FragColor = sky;
}
