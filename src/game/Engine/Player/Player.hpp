/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** TODO: add description
*/
#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include "APlayer.h"

class Player : public APlayer {
public:
    Player(RL::AnimatedModel &, pos_t, playerNum);
    ~Player() override = default;

public:
    void dropBomb(const std::vector<Block> &allBlock, RL::Audio &audio,
    std::vector<std::unique_ptr<APlayer>> &players) override;
    bool move(const std::vector<Block> &mapBlocks) override;
};



#endif //BOMBERMAN_PLAYER_HPP
