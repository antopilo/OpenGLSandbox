#shader vertex
#version 460 core
// Have you ever seen Godot shader. The whole engine has ONE monolithic shader.
// Also, how do you want me to split this in multiple shaders lmao.
// Click upper right Round thing
// DO CODE REVIEW yep
// im following u daddy
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 UVPosition;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 Tangent;
layout(location = 4) in vec3 Bitangent;
layout(location = 3) in float TextureId;

out flat vec2 v_UVPosition;
out flat float v_TextureId;
out vec3 v_Normal;
out vec3 v_FragPos;
out vec3 v_ViewPos;
out mat3 v_TBN;
out mat3 v_WTBN;
out vec3 v_Tangent;
out vec3 v_Bitangent;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

void main()
{
    mat3 normalMatrix = mat3(transpose(inverse(u_Model)));
    v_Normal = vec3(vec4(Normal, 1.0f));

    vec3 N = normalize((u_Model * vec4(Normal, 0.0f)).xyz);
    vec3 T = normalize((u_Model * vec4(Tangent, 0.0f)).xyz);
    vec3 B = normalize((u_Model * vec4(Bitangent, 0.0f)).xyz);
    v_TBN = mat3(T, B, N);

    v_Tangent = T;
    v_Bitangent = B;

    v_UVPosition = UVPosition;
    v_TextureId = TextureId;

    gl_Position = u_Projection * u_View * u_Model * vec4(VertexPosition, 1.0f);
    v_FragPos = vec3(u_Model * vec4(VertexPosition, 1.0f));
    v_ViewPos = VertexPosition;
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
    mat4 LightTransform;
    sampler2D ShadowMap;

};

out vec4 FragColor;

// Textures
uniform sampler2D u_Textures[2];

const int MaxLight = 20;
uniform int LightCount = 0;
uniform Light Lights[MaxLight];

// Debug
uniform int u_ShowNormal;

// Lighting
uniform vec3 u_AmbientColor;
uniform vec4 u_LightColor;
uniform vec3 u_LightDirection;
uniform float u_Exposure;

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
uniform int m_HasAlbedo; // I would advise against doing this stuff. just need default normal which is 0.5f 0.5f 1.0f.
uniform sampler2D m_Albedo; // yeah just think about it // normal maps are in tangent space which means the default should be a vector pointing straight towards the camera right? ie 0.0, 0.0, 1.0
uniform int m_HasMetalness; // But normal maps can also contain colors where the vectors face away such as vec3(0.2, 0.4, -1.0f) right? yeah
uniform sampler2D m_Metalness; // Well normal maps are stored as colors so you can't have negative values. So they are mapped from the range of -1 to 1, to 0 to 1
uniform int m_HasRoughness; // That is why you do the [normal * 2.0f - 1.0f]; to put it into to range of -1 to 1. yeah 0 - 1 -> -1 - 1
uniform sampler2D m_Roughness; // So vec3(0.0, 0.0, 1.0) put into the range of 0 to 1 is (0.5, 0.5, 1.0). easy.
uniform int m_HasAO;
uniform sampler2D m_AO;
uniform int m_HasNormal;
uniform sampler2D m_Normal;
uniform int m_HasDisplacement;
uniform sampler2D m_Displacement;

in vec3 v_FragPos;
in vec3 v_ViewPos;
in vec2 v_UVPosition;
in flat vec3 v_Normal;
in mat3 v_TBN;
in flat float v_TextureId;

in vec3 v_Tangent;
in vec3 v_Bitangent;

const float PI = 3.141592653589793f; // mark this as static const wait idk if you can do that in glsl
float height_scale = 0.03f;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir) // nice never done this // its easy Af its basicalyy returns a uv coords . that u use everywhere
{
    // number of depth layers
    const float minLayers = 8.0;
    const float maxLayers = 64.0;
    float numLayers = mix(maxLayers, minLayers, max(dot(vec3(0.0, 0.0, 1.0), viewDir), 0.0));

    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy * height_scale;
    vec2 deltaTexCoords = P / numLayers;

    // get initial values
    vec2  currentTexCoords = texCoords;
    float currentDepthMapValue = 1.0f - texture(m_Displacement, currentTexCoords).r;

    while (currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = 1.0f - texture(m_Displacement, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = 1.0f - texture(m_Displacement, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;

    //float height = 1.0f - texture(m_Displacement, texCoords).r;
    //vec2 p = viewDir.xy / viewDir.z * (height * height_scale);
    //return texCoords - p;
}

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

float ShadowCalculation(vec4 fragPosLightSpace, sampler2D shadowMap, vec3 normal, vec3 lightDir)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    return shadow;
}

void main()
{
    // Parallax UV offset.
    vec3 tangentViewPos = v_TBN * u_EyePosition;
    vec3 tangentFragPos = v_TBN * v_FragPos;
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
    vec2 texCoords = ParallaxMapping(v_UVPosition, viewDir);
    vec2 finalTexCoords = texCoords;

    vec3 finalAlbedo = texture(m_Albedo, finalTexCoords).rgb;
    float finalRoughness = texture(m_Roughness, finalTexCoords).r;
    float finalMetalness = texture(m_Metalness, finalTexCoords).r;
    float finalAO        = texture(m_AO, finalTexCoords).r;

    vec3  finalNormal   = texture(m_Normal, finalTexCoords).rgb;
    finalNormal = finalNormal * 2.0 - 1.0;
    finalNormal = v_TBN * normalize(finalNormal);

    vec3 N = normalize(finalNormal);
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

        float distance = length(Lights[i].Position - v_FragPos);
        float attenuation = 1.0 / (distance * distance);
        
        if (Lights[i].Type == 0) {
            L = Lights[i].Direction;
            attenuation = 1.0f;
        }

        float shadow = ShadowCalculation(Lights[0].LightTransform * vec4(v_FragPos, 1.0f), Lights[0].ShadowMap, N, Lights[0].Direction);
        
        vec3 H = normalize(V + L);
        vec3 radiance = Lights[i].Color * attenuation * (1.0f - shadow);

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
        Lo += (kD * finalAlbedo / PI + specular) * radiance * NdotL;// note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }

  
 

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
    color = pow(color, vec3(1.0 / u_Exposure));
    // Im already rendering to a texture
    // Cant I just copy the texture I just rendered to and flip it and put it in the places that needs reflection.
    // Ok well, that might be a new reflection system I just invented right now at the moment. 
    // cant SSR be used on something else than floors nice. I was confusing it with planar reflection
    // So todo list:
    // refact shader and better material system
    // SSR - relies on deferred shading btw yes you are forward. If you do not know if you are forward or deferred, you are definitely forward. xD following
    // am I forward?
    // I have 2 steps
    // Skybox 
    // Geometry Follow me.
   
    color = mix(color, finalNormal, u_ShowNormal);

    FragColor = vec4(color, 1.0); // so If i wanted to implement other stuff like SSR and bloom. I would need another render texture? using this same shader?
}// SCREEN SPACE REFLECTION
// nah screen space reflections work with data already on the screen
// so you can't reflect stuff that hasn't already been rendered
// in a pass after the lighting pass; so after this one
// you get a reflection vector and ray march the depth buffer
// then you sample from the already lit image
// ssr can be used on everything; as long as whatever it should be rendering is on screen, it will show up as a reflection
// Yes.