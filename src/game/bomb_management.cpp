//
// Created by ilias on 18/06/2021.
//

#include <list>
#include "Menu/Menu.hpp"
#include <algorithm>
#include "../raylib/myRaylib.h"
#include "Engine/Engine.h"

void bombHasExplose(bombAnimation_t &bomb, std::unique_ptr <Engine> &engine,
RL::NonAnimatedModel &fire, std::unique_ptr<APlayer> &player)
{
    static const Vector3 blastSize = {2.40f, 1.00f, 2.40f};

    if (bomb.blastScale.second > 2.90f)
        bomb.blastScale.first = true;
    if (bomb.blastScale.second < 1.80f && bomb.blastScale.first)
        bomb.blastScale.first = false;
    for (auto &deflagration : bomb.position) {
        auto iterator = engine->gameMap.getMapBlocks().begin();
        for (auto &block : engine->gameMap.getMapBlocks()) {
            if (block.getPosition().x == deflagration.x &&
                block.getPosition().y == deflagration.y + 1.0f &&
                (block.getType() == GROUND || block.getType() == BRICK)) {
                if (block.getType() == BRICK)
                    engine->gameMap.getMapBlocks().erase(iterator);
                if (player->isThereACollisionWithBlock(block.getPosition(), blastSize))
                    player->setIsDead(true);
                fire.drawEx({
                    {deflagration.x, deflagration.z, deflagration.y},
                    {1.00f,          0.00f,          0.00f},
                    {bomb.blastScale.second, bomb.blastScale.second, bomb.blastScale.second},
                    -90
                });
            }
            iterator++;
        }
    }
    bomb.blastScale.second += bomb.blastScale.first ? -0.30f : 0.30f;
}

void bombManagement(std::unique_ptr <Engine> &engine, std::unique_ptr <RL::Graphics> &visual,
std::vector <bombAnimation_t> &listBombAnimation, std::unique_ptr<APlayer> &player)
{
    static bombAnimation_t initRef = {};
    static bombAnimation_t &bombReturn = initRef;

    player->dropBomb(engine->gameMap.getMapBlocks(), engine->audio, engine->players);
    bombReturn = player->updateTimer(engine->gameMap.getMapBlocks());
    if (bombReturn.hasExplose) {
        listBombAnimation.push_back(bombReturn);
        engine->audio.playSound("bomb_explosion");
    }
    for (auto &e : listBombAnimation) {
        if (e.hasExplose) {
            bombHasExplose(e, engine, engine->fire, player);
            e.end = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(e.end - e.start).count() >= 1000) {
                auto &allBlocks = engine->gameMap.getMapBlocks();
                std::for_each(e.position.begin(), e.position.end(), [&allBlocks] (auto &deflagration) {
                    for (auto &block : allBlocks) {
                        if (block.getPosition().x == deflagration.x && block.getPosition().y == deflagration.y + 1.0f)
                            block.setDangerousness(false);
                    }
                });
                listBombAnimation.erase(listBombAnimation.begin());
            }
        }
    }
}
