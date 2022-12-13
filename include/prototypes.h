//
// Created by ilias on 09/06/2021.
//

#ifndef BOMBERMAN_PROTOTYPES_H
#define BOMBERMAN_PROTOTYPES_H

#include <vector>
#include "game.h"
#include "../src/game/Engine/Object/Block.h"
#include "../src/raylib/myRaylib.h"
#include "../src/game/Engine/Engine.h"

template <typename T>
Block createBlockInstance(pos_t position = {0, 0 ,0});

void bombManagement(std::unique_ptr <Engine> &engine, std::unique_ptr <RL::Graphics> &visual,
std::vector <bombAnimation_t> &listBombAnimation, std::unique_ptr<APlayer> &player);

void checkBonus(std::vector <RL::NonAnimatedModel> &bonus, std::unique_ptr<APlayer> &player, std::unique_ptr <Engine> &engine);

void setBonusPosition(std::vector <RL::NonAnimatedModel> &bonus, const std::vector<Block> &allBlock);

void setImagesMenu(std::unique_ptr<RL::Graphics> &visual);

void setHud(std::unique_ptr <RL::Graphics> &visual);

pos_t getClosestCaseBomb(pos_t p, const std::vector<Block> &allBlock);

int displayGameOver(std::unique_ptr<RL::Graphics> &visual, std::unique_ptr<RL::Window> &window, std::unique_ptr<Engine> &engine, GameSettings gameSettings);

void drawHud(std::unique_ptr <RL::Graphics> &visual, std::unique_ptr <Engine> &engine, int);

void unLoadAllImages(std::unique_ptr <RL::Graphics> &visual);

#endif //BOMBERMAN_PROTOTYPES_H
