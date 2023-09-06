#version 330 core
out vec4 FragColor;

#define MAX_LIGHTS 4
uniform sampler2D ourTexture;

in vec3 FragPos;
//in vec4 outColor;
in vec2 TexCoords;
in vec3 Normal; //Light

struct Material {
    sampler2D diffuse;
    sampler2D specular; 
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  

struct DirectionLight
{
    vec3 color;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    int isActive;
};
uniform DirectionLight directionLight;

struct PointLight
{
    vec3 color;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    int isActive;
};
uniform PointLight pointLight[MAX_LIGHTS];

struct SpotLight
{
    vec3 color;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    int isActive;
};
uniform SpotLight spotLight[MAX_LIGHTS];

uniform vec3 viewPos; 
//uniform vec3 lightPos; 
//uniform vec3 lightColor; // color + ambient
uniform vec3 objectColor;

vec4 CalculateDirectionData(vec3 normal, vec3 viewDirection);
vec4 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 viewDirection);
vec4 CalculateSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDirection);

void main()
{
	//vec3 ambient = ambient.color * ambient.strength;
	//gl_FragColor = texture(ourTexture, TexCoords) * (outColor * vec4(ambient,1.0));

	//vec3 ambient = light.ambient * material.ambient;
	//
    //// diffuse 
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * (diff * material.diffuse);
    //
    //// specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  
    //
    ////vec3 result = (ambient + diffuse) * objectColor;
    //vec3 result = (ambient + diffuse + specular);
	//gl_FragColor = texture(ourTexture, TexCoords) * (outColor * vec4(result,1.0));
	//FragColor= texture(ourTexture, TexCoords) * (outColor * vec4(lightColor,1.0));
   
    //vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
  	//
    //// diffuse 
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    //
    //// specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    //    
    //vec3 result = ambient + diffuse + specular ;

    vec4 resultColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(viewPos - FragPos);

    if (directionLight.isActive != 0)
    {
        resultColor += CalculateDirectionData(normal, viewDirection);
    }

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (pointLight[i].isActive != 0)
        {
            resultColor += CalculatePointLight(pointLight[0], normal, viewDirection);
        }
    }

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (spotLight[i].isActive != 0)
        {
            resultColor += CalculateSpotLight(spotLight[0], normal, viewDirection);
        }
    }
    //resultColor += CalculatePointLight(pointLight[0], normal, viewDirection);
    gl_FragColor = resultColor ;

}
vec4 CalculateDirectionData(vec3 normal, vec3 viewDirection)
{
    // ambient
    vec3 ambient = directionLight.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse
    vec3 lightDir = normalize(-directionLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = directionLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    vec3 specular = directionLight.specular * spec * vec3(texture(material.specular, TexCoords));
    
    float alpha = texture(material.diffuse,TexCoords).a;
    return vec4((ambient + diffuse + specular) *  directionLight.color ,alpha);
}
vec4 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 viewDirection)
{
    // ambient
    vec3 ambient =  pointLight.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse 
    //vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(pointLight.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * spec * vec3(texture(material.specular, TexCoords));

    // attenuation
    float distance = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return vec4((ambient + diffuse + specular) * pointLight.color, 1.0f);
}
vec4 CalculateSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDirection)
{
    // ambient
    vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse 
    //vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(spotLight.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * spec * vec3(texture(material.specular, TexCoords));

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-spotLight.direction));
    float epsilon = (spotLight.cutOff - spotLight.outerCutOff);
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float distance = length(spotLight.position - FragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return vec4((ambient + diffuse + specular) * spotLight.color, 1.0f);
}