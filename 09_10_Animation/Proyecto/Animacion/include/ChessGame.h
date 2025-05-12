#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <model.h>
#include "Board.h"
#include "Character.h"

class ChessGame {
public:
    // Constantes para tipos de piezas y equipos
    static const unsigned int Torre = 1;
    static const unsigned int Caballo = 2;
    static const unsigned int Alfil = 3;
    static const unsigned int Reyna = 4;
    static const unsigned int Rey = 5;
    static const unsigned int Peon = 6;
    static const unsigned int whitesTeam = 1;
    static const unsigned int blacksTeam = 2;

    ChessGame();
    ~ChessGame();

    void Initialize();
    void LoadModels();
    void InitPieces();
    void HandleMouseClick(const glm::vec3& posMouse);
    void HandleRightClick();
    bool IsPieceSelected() const;
    void CancelSelection();
    void CheckGameStatus() const;
    Board& GetBoard();
    const std::vector<Character>& GetWhites() const;
    const std::vector<Character>& GetBlacks() const;

    // Declaraciones de las variables miembro (sin inicialización)
    glm::vec3 reyBlancoPos;
    glm::vec3 torre1BlancoPos;
    glm::vec3 alfil1BlancoPos;
    glm::vec3 caballo1BlancoPos;
    glm::vec3 reynaBlancoPos;
    glm::vec3 torre2BlancoPos;
    glm::vec3 caballo2BlancoPos;
    glm::vec3 alfil2BlancoPos;
    std::vector<glm::vec3> peonesBlancoPos;

    glm::vec3 reyNegroPos;
    glm::vec3 torre1NegroPos;
    glm::vec3 alfil1NegroPos;
    glm::vec3 caballo1NegroPos;
    glm::vec3 reynaNegroPos;
    glm::vec3 torre2NegroPos;
    glm::vec3 caballo2NegroPos;
    glm::vec3 alfil2NegroPos;
    std::vector<glm::vec3> peonesNegroPos;

    Model* TorreBlanca;
    Model* AlfilBlanco;
    Model* PeonBlanco;
    Model* ReyBlanco;
    Model* CaballoBlanco;
    Model* ReynaBlanca;
    Model* Tablero;
    Model* TorreNegra;
    Model* AlfilNegro;
    Model* PeonNegro;
    Model* ReyNegro;
    Model* CaballoNegro;
    Model* ReynaNegra;

    Board board;
    std::vector<Character> whites;
    std::vector<Character> blacks;
    bool pick_place;
    float originX, originZ, destinationX, destinationZ;
};
