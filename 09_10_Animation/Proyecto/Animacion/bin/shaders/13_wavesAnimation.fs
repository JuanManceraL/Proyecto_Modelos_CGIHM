#version 330 core

#extension GL_NV_shadow_samplers_cube : enable

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// incoming Fresnel reflection and refraction parameters
in vec3  vReflect;
in vec3  vRefract[3];
in float reflectionCoefficient;

// the cubemap texture
uniform samplerCube cubetex;


void main()
{   

    // Fresnel
    vec4 reflectedColor = textureCube( cubetex, vec3( vReflect.x, vReflect.yz ) );
    vec4 refractedColor = vec4( 0.0f );

    refractedColor.r = textureCube( cubetex, vec3( vRefract[0].x, vRefract[0].yz ) ).r;
    refractedColor.g = textureCube( cubetex, vec3( vRefract[1].x, vRefract[1].yz ) ).g;
    refractedColor.b = textureCube( cubetex, vec3( vRefract[2].x, vRefract[2].yz ) ).b;

    vec2 coordsT = TexCoords;
     coordsT.x += 0.1f * (0.01)*time;
    // coordsT.y += 0.1f * (0.01)*time;


    vec4 fresnelColor = reflectionCoefficient * reflectedColor + (1 - reflectionCoefficient) * refractedColor;
    vec4 texel = texture(texture_diffuse1, coordsT);

    FragColor = texel*fresnelColor;
    FragColor.a = 1.0f;
}