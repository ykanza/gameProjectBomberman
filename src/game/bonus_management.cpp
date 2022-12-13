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

template <typename T>
RL::NonAnimatedModel createBonusInstance(pos_t position, int bonus) {
    std::string texture;
    if (bonus == 0)
        texture = "assets/bonus/fireup.png";
    else if (bonus == 1)
        texture = "assets/bonus/bombup.png";
    else if (bonus == 2)
        texture = "assets/bonus/speedup.png";

    return T({ {position.x, position.y, position.z}, {0.0, 0.0, 0.0}, {0.5,0.5,0.5}, 0 }, "assets/bonus/powerup.glb", texture.c_str());
}

void setBonusPosition(std::vector <RL::NonAnimatedModel> &bonus, const std::vector<Block> &allBlock)
{
    int bonusType = 0;
    pos_t posBonus;
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> distBonusType(0, 2);
    static std::uniform_int_distribution<int> distDropRate(0, 1);

    for (auto &block : allBlock) {
        if (block.getType() == BRICK && distDropRate(mt) == 0) {
            bonusType = distBonusType(mt);
            posBonus = block.getPosition();
            posBonus.y -= 0.7;
            bonus.push_back(createBonusInstance<RL::NonAnimatedModel>(posBonus, bonusType));
            bonus.back().setBonusType(bonusType);
        }
    }
}

void checkBonus(std::vector<RL::NonAnimatedModel> &bonus, std::unique_ptr<APlayer> &player, std::unique_ptr <Engine> &engine)
{
    static const Vector3 bonusSize = {2.00f, 1.00f, 2.00f};

    auto iterator = bonus.begin();
    for (auto &powerup : bonus) {
        if (player->isThereACollisionWithBlock
        ({powerup.getPosition().x, powerup.getPosition().y + 0.7f, powerup.getPosition().z}, bonusSize)) {
            if (powerup.getBonusType() == 0) {
                player->setNewRangeBomb();
            } else if (powerup.getBonusType() == 1) {
                player->setNewMaxBomb();
                player->setNewBomb();
            } else if (powerup.getBonusType() == 2) {
                player->setSpeed();
            }
            bonus.erase(iterator);
        }
        iterator++;
    }
}