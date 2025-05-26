#ifndef PARTICLES_H
#define PARTICLES_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

struct Particle {
    glm::vec3   p0;
    glm::vec3   position;
    glm::vec3   velocity;
    glm::vec3   acceleration;
    glm::vec3   force;
    float       mass;
};

class Particles
{
public:
    // Material Attributes
    vector<Particle> particles;

    Particles(unsigned int numParticles) {
        for (unsigned int i = 0; i < numParticles; i++) {
            Particle P;
            // Array de posiciones predefinidas (x, z)
            float posiciones[4][2] = {
                {-11.7f, 15.3f},
                {-12.3f, 17.1f},
                {-13.5f, 16.5f},
                {-13.5f, 15.3f}
            };

            // Selecciona una posición aleatoria del array
            int indice = rand() % 4;  // 0, 1, 2 o 3 (4 posiciones posibles)

            // Asigna las coordenadas X y Z según el índice seleccionado
            P.p0.x = posiciones[indice][0];  // X exacto (-11.7, -12.3, -13.5, etc.)
            P.p0.y = (float)(rand() % 2) * 0.5f + 1.0f;  // Y entre 1.0 y 1.5 (1.0 o 1.5)
            P.p0.z = posiciones[indice][1];  // Z exacto (15.3, 17.1, 16.5, etc.)

            P.position = P.p0;
            // Da una velocidad inicial hacia arriba para el efecto de chispas
            P.velocity = glm::vec3(
                (float)(rand() % 100 - 50) / 100.0f,  // Pequeña variación en X (-0.5 a 0.5)
                (float)(rand() % 3 + 1),             // Velocidad vertical más lenta (1 a 3)
                (float)(rand() % 100 - 50) / 100.0f   // Pequeña variación en Z (-0.5 a 0.5)
            );
            P.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
            P.force = glm::vec3(0.0f, 0.0f, 0.0f);
            P.mass = 0.001f;

            particles.push_back(P);
        }
    }
    ~Particles() {}

    void setGravity(glm::vec3 g) { gravity = g; }
    glm::vec3 getGravity() { return gravity; }

    void UpdatePhysics(float deltaTime) {
        for (int i = 0; i < (int)(particles.size()); i++) {
            Particle* P = &particles.at(i);
            // Cambia la condición para reiniciar cuando la partícula suba demasiado
            if (P->position.y > 2.0f) P->position = P->p0;  // reinicia cuando supere cierta altura

            P->force = P->mass * gravity;         // Suma de fuerzas totales actuando en la partícula
            P->acceleration = P->force / P->mass; // segunda ley de Newton
            P->velocity += P->acceleration * deltaTime; // Integral de la aceleración -> velocidad
            P->position += P->velocity * deltaTime;     // Integral de la velocidad -> posición
        }
    }

private:
    // Cambia la gravedad para que empuje hacia arriba (valor positivo en Y)
    glm::vec3 gravity = glm::vec3(0.0f, 0.001f, 0.0f);
};

#endif