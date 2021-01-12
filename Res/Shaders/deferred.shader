#shader vertex
#version 460 core
// Have you ever seen Godot shader. The whole engine has ONE monolithic shader.
// Also, how do you want me to split this in multiple shaders lmao.
// Click upper right Round thing
// DO CODE REVIEW yep
// im following u daddy

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 UVPosition;

out flat vec2 UV;
out vec3 FragPos;
out mat4 InvProjection;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

void main()
{
    UV = UVPosition;
    FragPos = VertexPosition;
    gl_Position = VertexPosition;
}

#shader fragment
#version 460 core

out vec4 FragColor;

in vec3 FragPos;

// Camera
uniform float u_Exposure;
uniform vec3 EyePosition;

// IBL
uniform samplerCube u_IrradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D   brdfLUT;

// Material
uniform sampler2D m_Depth;
uniform sampler2D m_Albedo; 
uniform sampler2D m_Metalness; 
uniform sampler2D m_AO;
uniform sampler2D m_Normal;



float3 VSPositionFromDepth(float2 vTexCoord)
{
    // Get the depth value for this pixel
    float z = tex2D(m_Depth, vTexCoord);
    // Get x/w and y/w from the viewport position
    float x = vTexCoord.x * 2 - 1;
    float y = (1 - vTexCoord.y) * 2 - 1;
    float4 vProjectedPos = float4(x, y, z, 1.0f);
    // Transform by the inverse projection matrix
    float4 vPositionVS = mul(vProjectedPos, );
    // Divide by w to get the view-space position
    return vPositionVS.xyz / vPositionVS.w;
}

void main()
{
    vec3 worldPos = VSPositionFromDepth(UV);

    // Convert from [0, 1] to [-1, 1].
    vec3 albedo     = texture(m_Albedo, uv).rgb;
    vec3 normal     = (texture(m_Normal, uv).rgb - 0.5) * 2.0;
    vec3 metallic   = texture(m_Material, uv).r;
    vec3 roughness  = texture(m_Material, uv).g;
    vec3 ao         = texture(m_Material, uv).b;

    vec3 N = normalize(normal);
    vec3 V = normalize(EyePosition - worldPos);
    vec3 R = reflect(-V, N);
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, vec3(metallic));

    // reflectance equation
    vec3 Lo = vec3(0.0);
    vec3 eyeDirection = normalize(EyePosition - worldPos);
    /*
    for (int i = 0; i < LightCount; i++)
    {
        vec3 L = normalize(Lights[i].Position - v_FragPos);

        float distance = length(Lights[i].Position - v_FragPos);
        float attenuation = 1.0 / (distance * distance);

        if (Lights[i].Type == 0) {
            L = Lights[i].Direction;
            attenuation = 1.0f;
        }

        float shadow = ShadowCalculation(Lights[i].LightTransform * vec4(v_FragPos, 1.0f), Lights[i].ShadowMap, N, Lights[i].Direction);

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
    */

    /// ambient lighting (we now use IBL as the ambient term)
    vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);

    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;

    vec3 irradiance = texture(u_IrradianceMap, N).rgb;
    vec3 diffuse = irradiance * albedo;

    // sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part.
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * ao;
    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0 / u_Exposure));

    FragColor = vec4(color, 1.0); // so If i wanted to implement other stuff like SSR and bloom. I would need another render texture? using this same shader?
}