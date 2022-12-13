//
// Created by ilias on 18/06/2021.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include "Menu/Menu.hpp"
#include "../raylib/myRaylib.h"
#include "Engine/Engine.h"
#include "prototypes.h"

int displayGameOver(std::unique_ptr<RL::Graphics> &visual, std::unique_ptr<RL::Window> &window, std::unique_ptr<Engine> &engine, GameSettings gameSettings)
{
    int playerThatWin = engine->getAlivePlayer();

    visual->beginDrawing();
    visual->drawImage("GameOver", 0, 0);
    if (playerThatWin == -1)
        DrawText("Every one lost !!", 550, 20, 120, BLUE);
    else
        DrawText(TextFormat("Player %i won !", playerThatWin + 1), 550, 20, 120, BLUE);
    if (window->isMouseInRange(1175, 788, 170, 68)) {
        if (RL::Event::isMouseClicked()) {
            window->setShouldClose(true);
            visual->endDrawing();
            return 1;
        }
    }
    if (window->isMouseInRange(635, 790, 195, 68)) {
        if (RL::Event::isMouseClicked()) {
            engine->players[J1]->setPosition({2.5, -1, 1.5});
            engine->players[J2]->setPosition({(gameSettings.mapSize * 2.1f), -1, (gameSettings.mapSize * 2.4f) - 5.0f});
            engine->players[J1]->setIsDead(false);
            engine->players[J2]->setIsDead(false);
            visual->endDrawing();
            return 2;
        }
    }
    visual->endDrawing();
    return 0;
}

void drawHud(std::unique_ptr <RL::Graphics> &visual, std::unique_ptr <Engine> &engine, int nbPlayers)
{
    std::string nbBomb;
    if (nbPlayers >= 1) {
        if (!engine->players[J1]->getIsDead()) {
            visual->drawImage("StatJ1", 10, 10);
        } else {
            visual->drawImage("StatJ1Dead", 10, 10);
            visual->drawImage("Cross", 30, 30);
        }
        DrawText(std::to_string(engine->players[J1]->getRangeBomb()).c_str(), 298, 35, 30, BLACK);
        DrawText(std::to_string((int)(engine->players[J1]->getSpeed()*20)).c_str(), 298, 80, 30, BLACK);
        nbBomb = std::to_string(engine->players[J1]->getNbActualBomb()) + "/" + std::to_string(engine->players[J1]->getPlayerNbMaxBomb());
        DrawText(nbBomb.c_str(), 298, 125, 30, BLACK);
    }
    if (nbPlayers >= 2) {
        if (!engine->players[J2]->getIsDead()) {
            visual->drawImage("StatJ2", 1550, 850);
        } else {
            visual->drawImage("StatJ2Dead", 1550, 850);
            visual->drawImage("Cross", 1570, 870);
        }
        DrawText(std::to_string(engine->players[J2]->getRangeBomb()).c_str(), 1828, 875, 30, BLACK);
        DrawText(std::to_string((int)(engine->players[J2]->getSpeed()*20)).c_str(), 1828, 920, 30, BLACK);
        nbBomb = std::to_string(engine->players[J2]->getNbActualBomb()) + "/" + std::to_string(engine->players[J2]->getPlayerNbMaxBomb());
        DrawText(nbBomb.c_str(), 1828, 965, 30, BLACK);
    }
    if (nbPlayers >= 3) {
        if (!engine->players[J3]->getIsDead()) {
            visual->drawImage("StatJ3", 10, 850);
        } else {
            visual->drawImage("StatJ3Dead", 10, 850);
            visual->drawImage("Cross", 30, 870);
        }
        DrawText(std::to_string(engine->players[J3]->getRangeBomb()).c_str(), 298, 875, 30, BLACK);
        DrawText(std::to_string((int)(engine->players[J3]->getSpeed()*20)).c_str(), 298, 920, 30, BLACK);
        nbBomb = std::to_string(engine->players[J3]->getNbActualBomb()) + "/" + std::to_string(engine->players[J3]->getPlayerNbMaxBomb());
        DrawText(nbBomb.c_str(), 298, 965, 30, BLACK);
    }
    if (nbPlayers >= 4) {
        if (!engine->players[J4]->getIsDead()) {
            visual->drawImage("StatJ4", 1550, 10);
        } else {
            visual->drawImage("StatJ4Dead", 1550, 10);
            visual->drawImage("Cross", 1570, 30);
        }
        DrawText(std::to_string(engine->players[J4]->getRangeBomb()).c_str(), 1828, 35, 30, BLACK);
        DrawText(std::to_string((int)(engine->players[J4]->getSpeed()*20)).c_str(), 1828, 80, 30, BLACK);
        nbBomb = std::to_string(engine->players[J4]->getNbActualBomb()) + "/" + std::to_string(engine->players[J4]->getPlayerNbMaxBomb());
        DrawText(nbBomb.c_str(), 1828, 125, 30, BLACK);
    }
}