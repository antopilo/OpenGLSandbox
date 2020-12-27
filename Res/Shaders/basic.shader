#shader vertex
#version 460 core

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 UVPosition;
layout(location = 2) in float TextureId;

out vec2 v_UVPosition;
out flat float v_TextureId;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    v_UVPosition = UVPosition;
    v_TextureId = TextureId;
    gl_Position = u_Projection * u_View * u_Model * vec4(VertexPosition, 1.0f);
}

#shader fragment
#version 460 core

out vec4 FragColor;

uniform sampler2D u_Textures[2];
uniform vec4 u_AmbientColor;
in vec2 v_UVPosition;
in flat float v_TexId;


void main()
{
    int index = int(v_TexId);
    vec4 objectColor = texture(u_Textures[1], v_UVPosition) * vec4(1.0f, 1.0, 1.0f, 1.0f);

    vec4 scatteredLight = u_AmbientColor; // This is the only light.

    FragColor = min(objectColor * scatteredLight, vec4(1.0f));
}
