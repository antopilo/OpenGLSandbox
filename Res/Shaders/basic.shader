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
out vec3 v_ViewPos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

void main()
{
    v_UVPosition = UVPosition;
    v_TextureId = TextureId;
    v_Normal = mat3(transpose(inverse(u_Model))) * Normal;
    v_FragPos = vec3(u_Model * vec4(VertexPosition, 1.0f));
    v_ViewPos = vec3(u_Model * vec4(VertexPosition, 1.0f));
    gl_Position = u_Projection * u_View * u_Model * vec4(VertexPosition, 1.0f);
}

#shader fragment
#version 460 core

struct Light {
    int Type; // 0 = directional, 1 = point
    vec3 Direction;
    vec3 Color;
    float Strength;
    vec3 Position;
    float ConstantAttenuation;
    float LinearAttenuation;
    float QuadraticAttenuation;
};

out vec4 FragColor;

// Textures
uniform sampler2D u_Textures[2];

const int MaxLight = 20;
uniform int LightCount = 0;
uniform Light Lights[MaxLight];

// Lighting
uniform vec3 u_AmbientColor;
uniform vec4 u_LightColor;
uniform vec3 u_LightDirection;

// Material
uniform vec3  albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

// Specular
uniform samplerCube u_Skybox;
uniform samplerCube u_IrradianceMap;
uniform float u_Shininess;
uniform float u_Strength;
uniform vec3 u_EyePosition;

// IBL
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D   brdfLUT;

// Material
uniform int m_HasAlbedo;
uniform sampler2D m_Albedo;
uniform int m_HasMetalness;
uniform sampler2D m_Metalness;
uniform int m_HasRoughness;
uniform sampler2D m_Roughness;
uniform int m_HasAO;
uniform sampler2D m_AO;
uniform int m_HasNormal;
uniform sampler2D m_Normal;

in vec3 v_FragPos;
in vec3 v_ViewPos;
in vec2 v_UVPosition;
in flat vec3 v_Normal;
in flat float v_TextureId;

float PI = 3.141592653589793f;

float DistributionGGX(vec3 N, vec3 H, float a)
{
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float k)
{
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float k)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}
void main()
{
    float finalRoughness = roughness;
    float finalMetalness = metallic;
    float finalAO        = ao;
    vec3 finalAlbedo    = albedo;
    //int index = int(v_TextureId);
    //vec4 objectColor = texture(u_Textures[index], v_UVPosition) * vec4(1.0f, 1.0, 1.0f, 1.0f);
    //objectColor.r = 1.0f;

    // PBR
    if (m_HasAlbedo == 1)
        finalAlbedo = texture(m_Albedo, v_UVPosition).rgb;
    if (m_HasRoughness == 1)
        finalRoughness = texture(m_Roughness, v_UVPosition).r;
    if (m_HasMetalness == 1)
        finalMetalness = texture(m_Metalness, v_UVPosition).r;
    if (m_HasAO == 1)
        finalAO        = texture(m_AO, v_UVPosition).r;

    vec3 N = normalize(v_Normal);
    vec3 V = normalize(u_EyePosition - v_FragPos);
    vec3 R = reflect(-V, N);
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, finalAlbedo, finalMetalness);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    vec3 eyeDirection = normalize(u_EyePosition - v_FragPos);
    for (int i = 0; i < LightCount; i++)
    {
        vec3 L = normalize(Lights[i].Position - v_FragPos);
        vec3 H = normalize(V + L);

        float distance = length(Lights[i].Position - v_FragPos);
        float attenuation = 1.0 / (distance * distance);
        
        if (Lights[i].Type == 0) {
            L = Lights[i].Direction;
            attenuation = 1.0f;
        }
        vec3 radiance = Lights[i].Color * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, finalRoughness);
        float G = GeometrySmith(N, V, L, finalRoughness);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 nominator = NDF * G * F;
        float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
        vec3 specular = nominator / denominator;

        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - finalMetalness;

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);

        // add to outgoing radiance Lo
        Lo += (kD * finalAlbedo / PI + specular) * radiance * NdotL; // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again

       //vec3 kS = F;
       //vec3 kD = 1.0 - kS;
       //kD *= 1.0 - metallic;
       //
       //vec3 irradiance = texture(irradianceMap, N).rgb;
       //vec3 diffuse = irradiance * albedo;
       //
       //const float MAX_REFLECTION_LOD = 4.0;
       //vec3 prefilteredColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;
       //vec2 envBRDF = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
       //vec3 specular = prefilteredColor * (F * envBRDF.x + envBRDF.y);
       //
       //vec3 ambient = (kD * diffuse + specular) * ao;
    }

    //PBR


    /// ambient lighting (we now use IBL as the ambient term)
    vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, finalRoughness);

    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - finalMetalness;

    vec3 irradiance = texture(u_IrradianceMap, N).rgb;
    vec3 diffuse = irradiance * finalAlbedo;

    // sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part.
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R, finalRoughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf = texture(brdfLUT, vec2(max(dot(N, V), 0.0), finalRoughness)).rg;
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * finalAO;

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0 / 2.2));

    FragColor = vec4(color, 1.0);
}
