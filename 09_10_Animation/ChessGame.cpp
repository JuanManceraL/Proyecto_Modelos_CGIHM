#include "ChessGame.h"
#include <iostream>

ChessGame::ChessGame() : pick_place(true) {
    // Inicialización de las variables miembro en el constructor
    reyBlancoPos = glm::vec3(-0.3f, 0.2f, -2.1f);
    torre1BlancoPos = glm::vec3(2.1f, 0.2f, -2.1f);
    alfil1BlancoPos = glm::vec3(0.9f, 0.2f, -2.1f);
    caballo1BlancoPos = glm::vec3(1.5f, 0.2f, -2.1f);
    reynaBlancoPos = glm::vec3(0.3f, 0.2f, -2.1f);
    torre2BlancoPos = glm::vec3(-2.1f, 0.2f, -2.1f);
    caballo2BlancoPos = glm::vec3(-1.5f, 0.2f, -2.1f);
    alfil2BlancoPos = glm::vec3(-0.9f, 0.2f, -2.1f);

    peonesBlancoPos = {
        glm::vec3(-2.1f, 0.2f, -1.5f),
        glm::vec3(-1.5f, 0.2f, -1.5f),
        glm::vec3(-0.9f, 0.2f, -1.5f),
        glm::vec3(-0.3f, 0.2f, -1.5f),
        glm::vec3(0.3f, 0.2f, -1.5f),
        glm::vec3(0.9f, 0.2f, -1.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(2.1f, 0.2f, -1.5f)
    };

    reyNegroPos = glm::vec3(-0.3f, 0.2f, 2.1f);
    torre1NegroPos = glm::vec3(-2.1f, 0.2f, 2.1f);
    alfil1NegroPos = glm::vec3(-0.9f, 0.2f, 2.1f);
    caballo1NegroPos = glm::vec3(-1.5f, 0.2f, 2.1f);
    reynaNegroPos = glm::vec3(0.3f, 0.2f, 2.1f);
    torre2NegroPos = glm::vec3(2.1f, 0.2f, 2.1f);
    caballo2NegroPos = glm::vec3(1.5f, 0.2f, 2.1f);
    alfil2NegroPos = glm::vec3(0.9f, 0.2f, 2.1f);

    peonesNegroPos = {
        glm::vec3(2.1f, 0.2f, 1.5f),
        glm::vec3(1.5f, 0.2f, 1.5f),
        glm::vec3(0.9f, 0.2f, 1.5f),
        glm::vec3(0.3f, 0.2f, 1.5f),
        glm::vec3(-0.3f, 0.2f, 1.5f),
        glm::vec3(-0.9f, 0.2f, 1.5f),
        glm::vec3(-1.5f, 0.2f, 1.5f),
        glm::vec3(-2.1f, 0.2f, 1.5f)
    };
}

ChessGame::~ChessGame() {
    // Liberar memoria de los modelos
    delete TorreBlanca;
    delete AlfilBlanco;
    delete PeonBlanco;
    delete ReyBlanco;
    delete CaballoBlanco;
    delete ReynaBlanca;
    delete Tablero;
    delete TorreNegra;
    delete AlfilNegro;
    delete PeonNegro;
    delete ReyNegro;
    delete CaballoNegro;
    delete ReynaNegra;
}

void ChessGame::Initialize() {
    LoadModels();
    InitPieces();
    board.initWhitesBoard(whites);
    board.initBlacksBoard(blacks);
}

void ChessGame::LoadModels() {
    TorreBlanca = new Model("models/Chess/Torre.obj");
    AlfilBlanco = new Model("models/Chess/Alfil.obj");
    PeonBlanco = new Model("models/Chess/Peon.obj");
    ReyBlanco = new Model("models/Chess/Rey.obj");
    CaballoBlanco = new Model("models/Chess/Caballo.obj");
    ReynaBlanca = new Model("models/Chess/Reyna.obj");
    Tablero = new Model("models/Chess/tablero.obj");
    TorreNegra = new Model("models/Chess/Torre2.obj");
    AlfilNegro = new Model("models/Chess/Alfil1.obj");
    PeonNegro = new Model("models/Chess/Peon2.obj");
    ReyNegro = new Model("models/Chess/Rey2.obj");
    CaballoNegro = new Model("models/Chess/Caballo2.obj");
    ReynaNegra = new Model("models/Chess/Reyna2.obj");
}

void ChessGame::InitPieces() {
    // Inicializar piezas blancas
    whites.push_back({ TorreBlanca, "Torre Blanca 2", &torre2BlancoPos, whitesTeam, Torre, 1 });
    whites.push_back({ CaballoBlanco, "Caballo Blanco 2", &caballo2BlancoPos, whitesTeam, Caballo, 1 });
    whites.push_back({ AlfilBlanco, "Alfil Blanco 2", &alfil2BlancoPos, whitesTeam, Alfil, 1 });
    whites.push_back({ ReyBlanco , "Rey Blanco", &reyBlancoPos, whitesTeam, Rey, 1 });
    whites.push_back({ ReynaBlanca, "Reyna Blanca", &reynaBlancoPos, whitesTeam, Reyna, 1 });
    whites.push_back({ AlfilBlanco, "Alfil Blanco", &alfil1BlancoPos, whitesTeam, Alfil, 1 });
    whites.push_back({ CaballoBlanco, "Caballo Blanco", &caballo1BlancoPos, whitesTeam, Caballo, 1 });
    whites.push_back({ TorreBlanca , "Torre Blanca", &torre1BlancoPos, whitesTeam, Torre, 1 });

    for (int i = 0; i < peonesBlancoPos.size(); ++i) {
        whites.push_back({ PeonBlanco, "Peon Blanco " + std::to_string(i), &peonesBlancoPos[i], whitesTeam, Peon, 1 });
    }

    // Inicializar piezas negras
    blacks.push_back({TorreNegra, "Torre Negra", &torre1NegroPos, blacksTeam, Torre, 1 });
    blacks.push_back({ CaballoNegro, "Caballo Negro", &caballo1NegroPos, blacksTeam, Caballo, 1 });
    blacks.push_back({ AlfilNegro, "Alfil Negro", &alfil1NegroPos, blacksTeam, Alfil, 1 });
    blacks.push_back({ ReyNegro, "Rey Negro", &reyNegroPos, blacksTeam, Rey, 1 });
    blacks.push_back({ ReynaNegra, "Reyna Negra", &reynaNegroPos, blacksTeam, Reyna, 1 });
    blacks.push_back({ AlfilNegro, "Alfil Negro 2", &alfil2NegroPos, blacksTeam, Alfil, 1 });
    blacks.push_back({ CaballoNegro, "Caballo Negro 2", &caballo2NegroPos, blacksTeam, Caballo, 1 });
    blacks.push_back({ TorreNegra , "Torre Negra 2", &torre2NegroPos, blacksTeam, Torre, 1 });

    for (int i = peonesNegroPos.size() - 1; i >= 0; --i) {
        blacks.push_back({ PeonNegro, "Peon Negro " + std::to_string(i), &peonesNegroPos[i], blacksTeam, Peon, 1 });
    }
}

void ChessGame::HandleMouseClick(const glm::vec3& posMouse) {
    if (posMouse.x == 9999.0f) return; // Posición fuera del tablero

    auto cell = board.getCellFromPosition(posMouse.x, posMouse.z);

    if (pick_place) {
        if (board.haveCharacter(cell.first, cell.second)) {
            pick_place = false;
            originX = posMouse.x;
            originZ = posMouse.z;
        }
    }
    else {
        destinationX = posMouse.x;
        destinationZ = posMouse.z;
        if (!board.move(originX, originZ, destinationX, destinationZ)) return;
        pick_place = true;
        CheckGameStatus();
    }
}



void ChessGame::HandleRightClick() {
    if (!pick_place) {
        pick_place = true;
    }
}

bool ChessGame::IsPieceSelected() const {
    return !pick_place;
}

void ChessGame::CancelSelection() {
    pick_place = true;
}

void ChessGame::CheckGameStatus() const {
    if (blacks[3].alive == 0) std::cout << "Piezas blancas ganan" << std::endl;
    if (whites[3].alive == 0) std::cout << "Piezas negras ganan" << std::endl;
}

Board& ChessGame::GetBoard() {
    return board;
}

const std::vector<Character>& ChessGame::GetWhites() const {
    return whites;
}

const std::vector<Character>& ChessGame::GetBlacks() const {
    return blacks;
}

/*
Para poder renderizar en el main se bene poner
 *****************************************Prototiposde funciones para el juego*****************************************
void RenderChess(Shader* shader, glm::mat4 model);
glm::vec3 ScreenToWorld(double xpos, double ypos, glm::mat4 projection, glm::mat4 view, float planeY);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
***********************************************************************************************************************


********************************Variables globales para inicializar el juego y obtener posiciones********************************
ChessGame chessGame;
glm::vec3 posMouse(0.0f);
double xpos, ypos;
*********************************************************************************************************************************


********************************************************Dentro de Start()********************************************************
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
*********************************************************************************************************************************


*****************************************Dentro del bucle de renderizado*****************************************
RenderChess(mLightsShader, model);
*****************************************************************************************************************


*****************************************Definición de la función para renderizar piezas*****************************************
void RenderChess(Shader* shader, glm::mat4 model) {
    model = glm::mat4(1.0f);
    shader->setMat4("model", model);
    chessGame.Tablero->Draw(*shader);

    for (Character& current : chessGame.whites) {
        if (current.alive) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, *current.position);
            shader->setMat4("model", model);
            current.model->Draw(*shader);
        }
    }
    for (Character& current : chessGame.blacks) {
        if (current.alive) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, *current.position);
            shader->setMat4("model", model);
            current.model->Draw(*shader);
        }
    }
}
*****************************************************************************************************************************


*****************************************************************************************************************************
Función para convertir coordenadas del mouse a coordenadas del mundo relacionadas a las casillas del tablero (plano Y=0.2)
glm::vec3 ScreenToWorld(double xpos, double ypos, glm::mat4 projection, glm::mat4 view, float planeY = 0.2f) {
    // Convertir coordenadas del mouse a NDC
    double x = (2.0f * xpos) / SCR_WIDTH - 1.0f;
    double y = 1.0f - (2.0f * ypos) /SCR_HEIGHT;

    // Crear vector en espacio de clip
    glm::vec4 rayClip = glm::vec4(x, y, -1.0f, 1.0f);

    // Convertir a espacio de ojos (eye space)
    glm::mat4 invProjection = glm::inverse(projection);
    glm::vec4 rayEye = invProjection * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

    // Convertir a espacio del mundo
    glm::mat4 invView = glm::inverse(view);
    glm::vec4 rayWorld = invView * rayEye;
    glm::vec3 rayDir = glm::normalize(glm::vec3(rayWorld));

    // Calcular intersección con el plano Y = planeY
    float t = (planeY - camera.Position[1]) / rayDir.y;
    glm::vec3 worldPos = camera.Position + t * rayDir;

    float cellSize = 0.6f; // Distancia entre casillas
    float boardOriginX = -2.1f; // Origen del tablero en X
    float boardOriginZ = -2.1f; // Origen del tablero en Z
    int boardSize = 8;          // Tamaño 8x8 casillas

    // Calcular casilla
    float relativeX = (worldPos.x - boardOriginX) / cellSize;
    float relativeZ = (worldPos.z - boardOriginZ) / cellSize;

    int cellX = static_cast<int>(round(relativeX));
    int cellZ = static_cast<int>(round(relativeZ));

    // Verificar si está dentro del tablero
    if (cellX < 0 || cellX >= boardSize || cellZ < 0 || cellZ >= boardSize) {
        // Fuera del tablero
        return glm::vec3(9999.0f);
    }

    // Calcular posición centrada
    float snappedX = boardOriginX + cellX * cellSize;
    float snappedZ = boardOriginZ + cellZ * cellSize;

    return glm::vec3(snappedX, planeY, snappedZ);
}
*****************************************************************************************************************************

****************************************Funcion para manejar agarrar y soltar piezas****************************************
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "(" << posMouse.x << "," << posMouse.y << "," << posMouse.z << ")" << std::endl;
        chessGame.HandleMouseClick(posMouse);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        chessGame.HandleRightClick();
    }
}

*****************************************************************************************************************************

*/