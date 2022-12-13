//
// Created by ilias on 10/06/2021.
//

#ifndef BOMBERMAN_APLAYER_H
#define BOMBERMAN_APLAYER_H

#include <Direction.h>
#include <game.h>
#include <memory>
#include "../../../raylib/graphics/Model/Model.h"
#include "../Bomb_Engine/Bomb.hpp"
#include "PlayerNum.h"

class APlayer {
public:
    APlayer(RL::AnimatedModel &, const pos_t &, playerNum);
    virtual ~APlayer() = default;

public:
    // void setPlayer(const pos_t &, const int &);
    void setPosition(const pos_t &);
    const pos_t &getPosition() const;
    void setRotation(const pos_t &);
    const pos_t &getRotation() const;
    void setDirection(const Direction &);
    const Direction &getDirection() const;
    void setScale(const pos_t &);
    const pos_t &getScale() const;
    void setRotationAngle(float &);
    float getRotationAngle() const;
    void setModel(const RL::AnimatedModel &);
    RL::AnimatedModel &getModel();
    const std::vector<bomb_t> &getBomb();
    const std::vector<KeyboardKey> &getMovementKeys();
    int getPlayerNbMaxBomb();
    int getNbActualBomb();
    const int &getRangeBomb() const;
    void setNewBomb();
    void setNewMaxBomb();
    void setNewRangeBomb();
    const playerNum &getPlayerNum() const;
    const KeyboardKey &getDropBombKey();
    void setIsDead(const bool &dead);
    const bool &getIsDead() const;
    void setIsOnBomb(bool);
    const bool &getIsOnBomb() const;
    void setSpeed();
    const float &getSpeed() const;
public:
    virtual bool move(const std::vector<Block> &mapBlocks) = 0;
    bombAnimation_t &updateTimer(std::vector<Block>& allBlock);
    virtual void dropBomb(const std::vector<Block> &, RL::Audio &, std::vector<std::unique_ptr<APlayer>> &) = 0;
    bool isThereACollisionWithBlocks(const std::vector<Block> &mapBlocks, const Vector3 &playerPos);
    bool isThereACollisionWithBlock(const pos_t &blockPos, const Vector3 &blockSize);

protected:
    Bomb bomb;
    KeyboardKey dropBombKey;
    pos_t position{};
    pos_t rotation{};
    pos_t scale{};
    float rotationAngle;
    int score;
    BlockTypes collidedBlockType;
    Direction direction;
    RL::AnimatedModel &model;
    std::vector<KeyboardKey> movementKeys;
    playerNum num;
    bool isDead;
    bool isOnBomb;
    float speed;
};

#endif //BOMBERMAN_APLAYER_H
