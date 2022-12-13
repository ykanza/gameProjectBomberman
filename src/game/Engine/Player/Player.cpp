/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** TODO: add description
*/

#include <unordered_map>
#include <functional>
#include <utility>
#include "APlayer.h"
#include "rotationValues.h"
#include "Player.hpp"

Player::Player(RL::AnimatedModel &model, pos_t position, playerNum nbP) : APlayer(model, position, nbP) {}

void Player::dropBomb(const std::vector<Block> &allBlock, RL::Audio &audio,
std::vector<std::unique_ptr<APlayer>> &players)
{
    if (RL::Event::isKeyPressed(dropBombKey) && bomb.getNbActualBomb() > 0) {
        bomb.dropBomb(position, allBlock, players);
        audio.playSound("bomb_drop");
    }
}

bool Player::move(const std::vector<Block> &mapBlocks)
{
    float speed = this->speed;
    static std::unordered_map<Direction, std::pair<rotationValues_t,
        std::function<void(pos_t &pos)>>> updateMap = {
        {UP, {{{-1.0f, 0.0f, 0.0f}, 90.0f}, [&speed] (pos_t &pos) {pos.z += (0.2f + speed);}}},
        {LEFT, {{{-1.0f, 1.0f, 1.0f}, 120.0f}, [&speed] (pos_t &pos) {pos.x += (0.2f + speed);}}},
        {DOWN, {{{0.0f, -1.0f, -1.0f}, 180.0f}, [&speed] (pos_t &pos) {pos.z -= (0.2f + speed);}}},
        {RIGHT, {{{-1.0f, -1.0f, -1.0f}, 120.0f}, [&speed] (pos_t &pos) {pos.x -= (0.2f + speed);}}}
    };
    static auto it = movementKeys.end();
    static std::vector<KeyboardKey> &keysPressed = RL::Event::getKeysPressed(false);
    RL::Event::getKeysPressed();

    it = movementKeys.end();
    for (auto &keyPressed : keysPressed) {
        it = std::find(this->movementKeys.begin(), this->movementKeys.end(), keyPressed);
        if (it != movementKeys.end())
            break;
    }
    keysPressed.clear();
    if (it == movementKeys.end())
        return false;
    direction = static_cast<Direction>(it - movementKeys.begin());
    pos_t reqPos = position;
    updateMap[direction].second(reqPos);
    if (!isThereACollisionWithBlocks(mapBlocks, {reqPos.x, reqPos.y, reqPos.z}))
        position = reqPos;
    rotation = updateMap[direction].first.rotationAxis;
    rotationAngle = updateMap[direction].first.rotationAngle;

    return true;
}