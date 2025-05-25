#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 TexCoords;
out vec3 vReflect;
out vec3 vRefract[3];
out float reflectionCoefficient;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

// Wave animation parameters
uniform float time;
uniform float radius;
uniform float height;

// Fresnel parameters
uniform float mRefractionRatio;
uniform float _Bias;
uniform float _Scale;
uniform float _Power;

void main()
{
    // Aplicar animación de olas
    vec4 PosL = vec4(aPos, 1.0f);
    PosL.z += 0.45 * sin(PosL.x + 0.006 * time);
    PosL.z += 0.45 * sin(PosL.y + 0.006 * time);

    // Transformación a espacio de pantalla
    gl_Position = projection * view * model * PosL;

    // Cálculos para efecto Fresnel
    vec3 posWorld = (model * PosL).xyz;
    vec3 normWorld = normalize(mat3(model[0].xyz, model[1].xyz, model[2].xyz) * aNormal);
    vec3 viewDir = normalize(posWorld - cameraPosition);

    // Reflexión y refracción
    vReflect = reflect(viewDir, normWorld);
    vRefract[0] = refract(viewDir, normWorld, mRefractionRatio * 1.0f);   // Canal rojo
    vRefract[1] = refract(viewDir, normWorld, mRefractionRatio * 0.99f);  // Canal verde
    vRefract[2] = refract(viewDir, normWorld, mRefractionRatio * 0.98f);   // Canal azul

    // Coeficiente de Fresnel (aproximación de Schlick)
    float fresnelTerm = dot(viewDir, normWorld);
    reflectionCoefficient = clamp(_Bias + _Scale * pow(1.0 + fresnelTerm, _Power), 0.0, 1.0);

    TexCoords = aTexCoords;
}