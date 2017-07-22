#version 330

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
    vec2 TexCoords = vec2(Txtcoor.x,Txtcoor.y);

    // 从法线贴图范围[0,1]获取法线
    //vec3 Normal = texture(normalMap, TexCoords).rgb;
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

    // 镜面高光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);

    //color = vec4(diffuse, 1.0f);

    //color = vec4(ambient,1.0);

    //color = vec4(ambient,1.0);
}
