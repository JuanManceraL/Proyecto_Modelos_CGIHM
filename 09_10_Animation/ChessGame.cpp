#include "ChessGame.h"
#include <iostream>

ChessGame::ChessGame() : pick_place(true) {
    // Inicializar posiciones de las piezas
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
    whites.push_back({ "Torre Blanca 2", &torre2BlancoPos, whitesTeam, Torre, 1 });
    whites.push_back({ "Caballo Blanco 2", &caballo2BlancoPos, whitesTeam, Caballo, 1 });
    whites.push_back({ "Alfil Blanco 2", &alfil2BlancoPos, whitesTeam, Alfil, 1 });
    whites.push_back({ "Rey Blanco", &reyBlancoPos, whitesTeam, Rey, 1 });
    whites.push_back({ "Reyna Blanca", &reynaBlancoPos, whitesTeam, Reyna, 1 });
    whites.push_back({ "Alfil Blanco", &alfil1BlancoPos, whitesTeam, Alfil, 1 });
    whites.push_back({ "Caballo Blanco", &caballo1BlancoPos, whitesTeam, Caballo, 1 });
    whites.push_back({ "Torre Blanca", &torre1BlancoPos, whitesTeam, Torre, 1 });

    for (int i = 0; i < peonesBlancoPos.size(); ++i) {
        whites.push_back({ "Peon Blanco " + std::to_string(i), &peonesBlancoPos[i], whitesTeam, Peon, 1 });
    }

    // Inicializar piezas negras
    blacks.push_back({ "Torre Negra", &torre1NegroPos, blacksTeam, Torre, 1 });
    blacks.push_back({ "Caballo Negro", &caballo1NegroPos, blacksTeam, Caballo, 1 });
    blacks.push_back({ "Alfil Negro", &alfil1NegroPos, blacksTeam, Alfil, 1 });
    blacks.push_back({ "Rey Negro", &reyNegroPos, blacksTeam, Rey, 1 });
    blacks.push_back({ "Reyna Negra", &reynaNegroPos, blacksTeam, Reyna, 1 });
    blacks.push_back({ "Alfil Negro 2", &alfil2NegroPos, blacksTeam, Alfil, 1 });
    blacks.push_back({ "Caballo Negro 2", &caballo2NegroPos, blacksTeam, Caballo, 1 });
    blacks.push_back({ "Torre Negra 2", &torre2NegroPos, blacksTeam, Torre, 1 });

    for (int i = peonesNegroPos.size() - 1; i >= 0; --i) {
        blacks.push_back({ "Peon Negro " + std::to_string(i), &peonesNegroPos[i], blacksTeam, Peon, 1 });
    }
}

void ChessGame::Render(Shader* shader) {
    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", model);
    Tablero->Draw(*shader);

    // Dibujar piezas blancas
    model = glm::mat4(1.0f);
    model = glm::translate(model, reyBlancoPos);
    shader->setMat4("model", model);
    ReyBlanco->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, torre1BlancoPos);
    shader->setMat4("model", model);
    TorreBlanca->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, torre2BlancoPos);
    shader->setMat4("model", model);
    TorreBlanca->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, alfil1BlancoPos);
    shader->setMat4("model", model);
    AlfilBlanco->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, alfil2BlancoPos);
    shader->setMat4("model", model);
    AlfilBlanco->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, caballo1BlancoPos);
    shader->setMat4("model", model);
    CaballoBlanco->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, caballo2BlancoPos);
    shader->setMat4("model", model);
    CaballoBlanco->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, reynaBlancoPos);
    shader->setMat4("model", model);
    ReynaBlanca->Draw(*shader);

    // Dibujar peones blancos
    for (const auto& pos : peonesBlancoPos) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        shader->setMat4("model", model);
        PeonBlanco->Draw(*shader);
    }

    // Dibujar piezas negras
    model = glm::mat4(1.0f);
    model = glm::translate(model, reyNegroPos);
    shader->setMat4("model", model);
    ReyNegro->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, torre1NegroPos);
    shader->setMat4("model", model);
    TorreNegra->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, torre2NegroPos);
    shader->setMat4("model", model);
    TorreNegra->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, alfil1NegroPos);
    shader->setMat4("model", model);
    AlfilNegro->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, alfil2NegroPos);
    shader->setMat4("model", model);
    AlfilNegro->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, caballo1NegroPos);
    shader->setMat4("model", model);
    CaballoNegro->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, caballo2NegroPos);
    shader->setMat4("model", model);
    CaballoNegro->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, reynaNegroPos);
    shader->setMat4("model", model);
    ReynaNegra->Draw(*shader);

    // Dibujar peones negros
    for (const auto& pos : peonesNegroPos) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        shader->setMat4("model", model);
        PeonNegro->Draw(*shader);
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