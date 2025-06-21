#version 330 core

in vec3 vNormal;
in vec3 vFragPos;
in vec2 vUV;

uniform sampler2D uTexture;
uniform vec3 uViewPos;
uniform vec3 uKa;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShin;

uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    vec3 texColor = texture(uTexture, vUV).rgb;   // couleur issue de la texture

    vec3 N = normalize(vNormal);
    vec3 L = normalize(lightPos - vFragPos);
    vec3 V = normalize(uViewPos - vFragPos);
    vec3 R = reflect(-L, N);

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(R, V), 0.0), uShin);

    vec3 ambient  = uKa * texColor * 0.2;          // lumière ambiante modulée par la texture
    vec3 diffuse  = diff * uKd * texColor;         // lumière diffuse modulée
    vec3 specular = spec * uKs * lightColor;       // spéculaire indépendante de la texture

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(pow(result, vec3(1.0/2.2)), 1.0); // correction gamma → sRGB
}
