#version 330 core

in vec3 vNormal;
in vec3 vFragPos;
in vec2 vUV;

uniform vec3 uViewPos;
uniform vec3 uKa;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShin;

uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 FragColor;

void main() {
    vec3 N = normalize(vNormal);
    vec3 L = normalize(lightPos - vFragPos);
    vec3 V = normalize(uViewPos - vFragPos);
    vec3 R = reflect(-L, N);

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(R, V), 0.0), uShin);

    vec3 ambient = uKa * lightColor * 0.2;
    vec3 diffuse = diff * uKd * lightColor;
    vec3 specular = spec * uKs * lightColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(pow(result, vec3(1.0 / 2.2)), 1.0); // sRGB correction
}
