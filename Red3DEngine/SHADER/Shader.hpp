#pragma once

#define	STRINGIZE(x)	#x

#ifdef __ANDROID__

#define	SHADER(shader) "#version 300 es\n" STRINGIZE(shader)

#else

#define	SHADER(shader) "#version 330\n" STRINGIZE(shader)

#endif

static const char * PBR_VERTEX = SHADER(
                layout (location = 0) in vec3 aPos;
                layout (location = 1) in vec3 aNormal;
                layout (location = 2) in vec3 aTexCoords;

                out vec2 TexCoords;
                out vec3 WorldPos;
                out vec3 Normal;

                uniform mat4 projection;
                uniform mat4 view;
                uniform mat4 model;

                void main()
                {
                    TexCoords = aTexCoords.xy;
                    WorldPos = vec3(model * vec4(aPos, 1.0));
                    Normal = mat3(model) * aNormal;

                    gl_Position =  projection * view * vec4(WorldPos, 1.0);
                }
            );

static const char * PBR_FRAGMENT = SHADER(
                out vec4 FragColor;
                in vec2 TexCoords;
                in vec3 WorldPos;
                in vec3 Normal;

                // material parameters
                uniform sampler2D albedoMap;
                uniform sampler2D normalMap;
                uniform sampler2D metallicMap;
                uniform sampler2D roughnessMap;
                uniform sampler2D aoMap;

                // lights
                uniform vec3 lightPositions[4];
                uniform vec3 lightColors[4];

                uniform vec3 camPos;

                const float PI = 3.14159265359;

                vec3 getNormalFromMap()
                {
                    vec3 tangentNormal = texture(normalMap, TexCoords).xyz * 2.0 - 1.0;

                    vec3 Q1  = dFdx(WorldPos);
                    vec3 Q2  = dFdy(WorldPos);
                    vec2 st1 = dFdx(TexCoords);
                    vec2 st2 = dFdy(TexCoords);

                    vec3 N   = normalize(Normal);
                    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
                    vec3 B  = -normalize(cross(N, T));
                    mat3 TBN = mat3(T, B, N);

                    return normalize(TBN * tangentNormal);
                }

                // ----------------------------------------------------------------------------
                float DistributionGGX(vec3 N, vec3 H, float roughness)
                {
                    float a = roughness*roughness;
                    float a2 = a*a;
                    float NdotH = max(dot(N, H), 0.0);
                    float NdotH2 = NdotH*NdotH;

                    float nom   = a2;
                    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
                    denom = PI * denom * denom;

                    return nom / denom;
                }

                // ----------------------------------------------------------------------------
                float GeometrySchlickGGX(float NdotV, float roughness)
                {
                    float r = (roughness + 1.0);
                    float k = (r*r) / 8.0;

                    float nom   = NdotV;
                    float denom = NdotV * (1.0 - k) + k;

                    return nom / denom;
                }

                // ----------------------------------------------------------------------------
                float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
                {
                    float NdotV = max(dot(N, V), 0.0);
                    float NdotL = max(dot(N, L), 0.0);
                    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
                    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

                    return ggx1 * ggx2;
                }

                // ----------------------------------------------------------------------------
                vec3 fresnelSchlick(float cosTheta, vec3 F0)
                {
                    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
                }

                // ----------------------------------------------------------------------------
                void main()
                {
                    vec3 albedo     = pow(texture(albedoMap, TexCoords).rgb, vec3(2.2));
                    float metallic  = texture(metallicMap, TexCoords).r;
                    float roughness = texture(roughnessMap, TexCoords).r;
                    float ao        = texture(aoMap, TexCoords).r;

                    albedo = vec3(0.5,0.0,0.0);
                    metallic = 0.5;
                    roughness = 0.25;
                    ao = 1.0;

                    //vec3 N = getNormalFromMap();
                    //vec3 V = normalize(camPos - WorldPos);


                    vec3 N = normalize(Normal);
                    vec3 V = normalize(camPos - WorldPos);

                    vec3 F0 = vec3(0.04);
                    F0 = mix(F0, albedo, metallic);

                    vec3 Lo = vec3(0.0);

                    for(int i = 0; i < 4; ++i)
                    {
                        // calculate per-light radiance
                        vec3 L = normalize(lightPositions[i] - WorldPos);
                        vec3 H = normalize(V + L);
                        float distance = length(lightPositions[i] - WorldPos);
                        float attenuation = 1.0 / (distance * distance);
                        vec3 radiance = lightColors[i] * attenuation;

                        // Cook-Torrance BRDF
                        float NDF = DistributionGGX(N, H, roughness);
                        float G   = GeometrySmith(N, V, L, roughness);
                        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

                        vec3 nominator    = NDF * G * F;
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
                        kD *= 1.0 - metallic;

                            // scale light by NdotL
                        float NdotL = max(dot(N, L), 0.0);

                            // add to outgoing radiance Lo
                        Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
                    }

                    vec3 ambient = vec3(0.03) * albedo * ao;

                    vec3 color = ambient + Lo;

                    // HDR
                    color = color / (color + vec3(1.0));
                    // gamma
                    color = pow(color, vec3(1.0/2.2));

                    FragColor = vec4(color, 1.0);

                    //FragColor = vec4(TexCoords ,0.0, 1.0);
                }
            );




static const char * SKY_VERTEX = SHADER(
                layout (location = 0) in vec3 aPos;

                out vec3 TexCoords;

                uniform mat4 projection;
                uniform mat4 view;

                void main()
                {
                    TexCoords = aPos;
                    gl_Position = projection * view * vec4(aPos, 1.0);
                }
            );

static const char * SKY_FRAGMENT = SHADER(
                out vec4 FragColor;

                in vec3 TexCoords;

                uniform samplerCube skybox;

                void main()
                {
                    FragColor = vec4(TexCoords,1.0);
                    FragColor = texture(skybox, TexCoords);
                }
            );


static const char * PHONG_VERTEX = SHADER(
                layout (location = 0) in vec3 position;
                layout (location = 1) in vec3 normal;
                layout (location = 2) in vec3 txtcoor;
                layout (location = 3) in vec3 tangentsArray;

                out vec3 FragPos;
                out vec3 Txtcoor;
                out vec3 Normal;

                uniform mat4 model;
                uniform mat4 view;
                uniform mat4 projection;

                void main()
                {
                    gl_Position = projection * view *  model * vec4(position, 1.0f);
                    FragPos = vec3(model * vec4(position, 1.0f));
                    Normal = mat3(transpose(inverse(model))) * normal;

                    Txtcoor = txtcoor;
                }
            );

static const char * PHONG_FRAGMENT = SHADER(
                struct Material
                {
                    sampler2D diffuse;
                    sampler2D specular;
                    sampler2D normalMap;
                    float shininess;
                };


                struct Light
                {
                    vec3 position;
                    vec3 ambient;
                    vec3 diffuse;
                    vec3 specular;
                };

                in vec3 FragPos;
                in vec3 Txtcoor;
                in vec3 Normal;

                out vec4 color;

                uniform Light light;
                uniform Material material;
                uniform vec3 viewPos;

                void main()
                {
                    vec2 TexCoords = vec2(Txtcoor.x,  Txtcoor.y);

                    // 从法线贴图范围[0,1]获取法线
                    //Normal = texture(material.normalMap, TexCoords).rgb;
                    // 将法线向量转换为范围[-1,1]
                    //Normal = normalize(Normal * 2.0 - 1.0);

                    // 环境光
                    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
                    // vec3 ambient = light.ambient * vec3(1.0f,0.0f,0.0f);

                    // 漫反射光
                    vec3 norm = normalize(Normal);
                    vec3 lightDir = normalize(light.position - FragPos);
                    float diff = max(dot(norm, lightDir), 0.0);
                    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
                    //diffuse = lightDir;

                    // 镜面高光
                    vec3 viewDir = normalize(viewPos - FragPos);
                    vec3 reflectDir = reflect(-lightDir, norm);
                    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 60.0);
                    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10.0);
                    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

                    vec3 result = ambient + diffuse + specular;
                    color = vec4(result, 1.0f);

                    //color = vec4(vec3(material.shininess), 1.0f);

                    //color = vec4(ambient,1.0);

                    //color = vec4(ambient,1.0);
                }

            );
