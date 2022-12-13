//
// Created by ilias on 07/06/2021.
//

#ifndef BOMBERMAN_ENGINE_H
#define BOMBERMAN_ENGINE_H

#include "Map/GameMap.h"
#include "../../raylib/audio/audio.h"
#include "Player/APlayer.h"
#include "../../errors/Error.h"
#include "Player/Player.hpp"
#include "Player/AI.h"
#include <memory>

struct GameSettings {
    float mapSize = 11;
    int nbHumanPlayer = 2;
    int nbAIPlayer = 0;
};

class Engine {
public:
    Engine();
    ~Engine() = default;
    RL::Audio audio;
    GameMap gameMap;

public:
    template <typename PType>
    void createNewPlayer(pos_t, RL::AnimatedModel &, playerNum);
    int getDeadPlayer();
    int getAlivePlayer();
public:
    std::vector<std::unique_ptr<APlayer>> players;
    bool isInGameOverMenu;
    RL::AnimatedModel bomb;
    std::vector<RL::AnimatedModel> playersModel;
    RL::NonAnimatedModel fire;
};

template <typename PType>
void Engine::createNewPlayer(pos_t position, RL::AnimatedModel &model, playerNum nbP)
{
    this->players.push_back(std::move(std::make_unique<PType>(model, position, nbP)));
    if (this->players.back() == nullptr) {
        throw (err::Player("Failed to created new player"));
    }
}

#endif //BOMBERMAN_ENGINE_H
