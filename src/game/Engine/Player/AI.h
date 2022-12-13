/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** TODO: add description
*/
#ifndef BOMBERMAN_AI_H
#define BOMBERMAN_AI_H

#include <unordered_map>
#include <functional>
#include <algorithm>
#include <utility>
#include <random>
#include "APlayer.h"
#include "rotationValues.h"

#define DURATION_CAST_MILISEC(val) std::chrono::duration_cast<std::chrono::milliseconds>(val)

typedef std::unordered_map<Direction, std::pair<rotationValues_t, std::function<void(pos_t &pos)>>> updateMapType;

class AI : public APlayer {
public:
    AI(RL::AnimatedModel &, pos_t, playerNum);
    ~AI() override = default;

public:
    void dropBomb(const std::vector<Block> &allBlock, RL::Audio &audio,
    std::vector<std::unique_ptr<APlayer>> &players) override;
    bool move(const std::vector<Block> &mapBlocks) override;
    void setRandomDirectionInVec(std::vector<Direction>& vecDirection);
    bool setMoveMembers(std::vector<Direction>& freeCase, std::vector<Direction>& safeCase,
    std::unordered_map<Direction, std::pair<rotationValues_t, std::function<void(pos_t &pos)>>> &updateMap);

private:
    bool bombDepositRequested;
};



#endif //BOMBERMAN_AI_H
