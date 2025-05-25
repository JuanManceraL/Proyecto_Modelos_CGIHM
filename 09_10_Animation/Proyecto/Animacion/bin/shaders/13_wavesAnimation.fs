#version 330 core

in vec2 TexCoords;
in vec3 vReflect;
in vec3 vRefract[3];
in float reflectionCoefficient;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform samplerCube cubetex;
uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{   
    // Usamos texture() en lugar de textureCube() y simplificamos las coordenadas
    vec4 reflectedColor = texture(cubetex, vReflect);
    
    // Refracción con canales separados
    vec4 refractedColor;
    refractedColor.r = texture(cubetex, vRefract[0]).r;
    refractedColor.g = texture(cubetex, vRefract[1]).g;
    refractedColor.b = texture(cubetex, vRefract[2]).b;
    refractedColor.a = 1.0;

    // Animación de coordenadas de textura
    vec2 animatedCoords = TexCoords;
    animatedCoords.x += 0.001 * time; // Movimiento horizontal suave

    // Mezcla Fresnel mejorada usando mix()
    vec4 fresnelEffect = mix(refractedColor, reflectedColor, reflectionCoefficient);
    
    // Textura base con animación
    vec4 baseTexture = texture(texture_diffuse1, animatedCoords);
    
    // Combinación final
    FragColor = baseTexture * fresnelEffect;
    FragColor.a = 1.0; // Aseguramos opacidad completa
}