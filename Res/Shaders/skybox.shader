#shader vertex
#version 460 core

layout(location = 0) in vec3 vertexPosition;

out vec3 TexCoords;
out vec3 LocalPos;

uniform mat4 projection;
uniform mat4 view;
void main()
{
    TexCoords = vertexPosition;
    LocalPos = vertexPosition;
    gl_Position = projection * mat4(mat3(view)) * vec4(vertexPosition, 1.0);
}

#shader fragment
#version 460 core
out vec4 FragColor;

in vec3 TexCoords;
in vec3 LocalPos;

uniform int isHDR;
uniform int convulate;
uniform sampler2D equirectangularMap;
uniform samplerCube skybox;
const float PI = 3.14159265359;
const vec2 invAtan = vec2(0.1591, 0.3183);


vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{
    if (convulate == 1) {
        // The world vector acts as the normal of a tangent surface
        // from the origin, aligned to WorldPos. Given this normal, calculate all
        // incoming radiance of the environment. The result of this radiance
        // is the radiance of light coming from -Normal direction, which is what
        // we use in the PBR shader to sample irradiance.
        vec3 N = normalize(LocalPos);

        vec3 irradiance = vec3(0.0);

        // tangent space calculation from origin point
        vec3 up = vec3(0.0, 1.0, 0.0);
        vec3 right = cross(up, N);
        up = cross(N, right);

        float sampleDelta = 0.001;
        float nrSamples = 0.0;
        for (float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
        {
            for (float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
            {
                // spherical to cartesian (in tangent space)
                vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
                // tangent space to world
                vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;

                irradiance += texture(skybox, sampleVec).rgb * cos(theta) * sin(theta);
                nrSamples++;
            }
        }
        irradiance = PI * irradiance * (1.0 / float(nrSamples));

        FragColor = vec4(irradiance, 1.0);
    }
    else {
        if (isHDR == 1) {
            vec2 uv = SampleSphericalMap(normalize(LocalPos)); // make sure to normalize localPos
            vec3 color = texture(equirectangularMap, uv).rgb;
            FragColor = vec4(color, 1.0);
        }
        else {
            vec4 sky = texture(skybox, TexCoords);
            FragColor = sky;
        }
    }
    
}
