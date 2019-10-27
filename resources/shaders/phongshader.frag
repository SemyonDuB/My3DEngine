#version 430 core

in vec3 normal;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 Ld;
uniform vec3 Kd;

uniform vec3 lightPos;

in vec3 FragPos;

void main()
{
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  vec3 dif = Ld * Kd * max(dot(norm, lightDir), 0.0);
  vec3 Diffuse = dif * lightColor;

  vec3 result = (ambient + Diffuse) * objectColor;
  FragColor = vec4(result, 1.0);
}
