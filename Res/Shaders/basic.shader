#shader vertex
#version 460 core

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 UVPosition;
layout(location = 2) in vec3 Normal;
layout(location = 3) in float TextureId;

out vec2 v_UVPosition;
out flat float v_TextureId;
out flat vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{

    v_UVPosition = UVPosition;
    v_TextureId = TextureId;
    v_Normal = vec3(u_Model * vec4(Normal, 1.0f));
    v_FragPos = vec3(u_Model * vec4(VertexPosition, 1.0f));
    gl_Position = u_Projection * u_View * u_Model * vec4(VertexPosition, 1.0f);
}

#shader fragment
#version 460 core

out vec4 FragColor;

// Textures
uniform sampler2D u_Textures[2];

// Lighting
uniform vec4 u_AmbientColor;
uniform vec4 u_LightColor;
uniform vec3 u_LightDirection;
// Specular
uniform float u_Shininess;
uniform float u_Strength;
uniform vec3 u_EyePosition;

in vec3 v_FragPos;
in vec2 v_UVPosition;
in flat vec3 v_Normal;
in flat float v_TextureId;

void main()
{
    int index = int(v_TextureId);
    vec4 objectColor = texture(u_Textures[index], v_UVPosition) * vec4(1.0f, 1.0, 1.0f, 1.0f);

    vec3 eyeDirection = normalize(u_EyePosition - v_FragPos);
    vec3 HalfVector = normalize(eyeDirection + u_LightDirection);
    
    float diffuse = max(0.0, dot(v_Normal, normalize(u_LightDirection)));
    float specular = max(0.0, dot(v_Normal, HalfVector));

    // Surfaces facing away from the light (negative dot product)
    // won't be lit by the directional light.
    if (diffuse == 0.0)
        specular = 0.0;
    else
        specular = pow(specular, u_Shininess);

    // Add specular on top of object color.
    vec3 scatteredLight = u_AmbientColor.rgb + u_LightColor.rgb * diffuse;
    vec3 reflectedLight = u_LightColor.rgb * specular * u_Strength;
    vec3 rgb = min((scatteredLight.rgb + reflectedLight.rgb), vec3(1.0f));

    FragColor = vec4(rgb, objectColor.a);
}
