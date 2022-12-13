//
// Created by ilias on 10/06/2021.
//

#include <algorithm>
#include <utility>
#include <PlayerNum.h>
#include <iostream>
#include "APlayer.h"
#include "rotationValues.h"

APlayer::APlayer(RL::AnimatedModel &model, const pos_t &position, playerNum nbP) : model(model)
{
    static const std::vector<std::pair<std::vector<KeyboardKey>, KeyboardKey>> vKeys = {
        {{KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT}, KEY_SPACE},
        {{KEY_E, KEY_S, KEY_D, KEY_F}, KEY_R},
        {{KEY_G, KEY_V, KEY_B, KEY_N}, KEY_H},
        {{KEY_I, KEY_J, KEY_K, KEY_L}, KEY_O}
    };
    this->movementKeys = vKeys[nbP].first;
    this->num = nbP;
    this->dropBombKey = vKeys[nbP].second;
    this->position = position;
    this->direction = NONE;
    this->score = 0;
    static const std::vector<std::pair<pos_t, float>> rotJ = {
        {{0.0f, -1.0f, -1.0f}, 180.0f},
        {{-1.0f, 0.0f, 0.0f}, 90.0f},
        {{-1.0f, -1.0f, -1.0f}, 120.0f},
        {{-1.0f, 1.0f, 1.0f}, 120.0f}
    };
    this->rotation = rotJ[nbP].first;
    this->rotationAngle = rotJ[nbP].second;
    this->scale = {0.02f, 0.02f, 0.02f};
    this->isDead = false;
    this->speed = 0;
    this->collidedBlockType = GROUND;
    this->isOnBomb = false;
}

const pos_t &APlayer::getPosition() const {
    return this->position;
}

void APlayer::setPosition(const pos_t &pos) {
    this->position = pos;
}

const pos_t &APlayer::getRotation() const {
    return this->rotation;
}

void APlayer::setRotation(const pos_t &_rotation) {
    this->rotation = _rotation;
}

const Direction &APlayer::getDirection() const {
    return this->direction;
}

void APlayer::setDirection(const Direction &_direction) {
    this->direction = _direction;
}

void APlayer::setScale(const pos_t &_scale)
{
    this->scale = _scale;
}

const pos_t &APlayer::getScale() const
{
    return this->scale;
}

const bool &APlayer::getIsDead() const {
    return this->isDead;
}

void APlayer::setIsDead(const bool &dead) {
    this->isDead = dead;
}

bool APlayer::isThereACollisionWithBlocks(const std::vector<Block> &mapBlocks, const Vector3 &playerPos)
{
    static const Vector3 blockSize = {2.00f, 1.0f, 2.00f};
    static const Vector3 playerSize = {1.00f, 1.00f, 1.00f};
    static bool isThereACollision = false;
    bool collisionWBomb = false;

    collidedBlockType = BASIC;
    isThereACollision = std::any_of(mapBlocks.begin(), mapBlocks.end(), [&playerPos, &collisionWBomb, this] (auto &currBlock) {
        BlockTypes currBlockType = currBlock.getType();
        Vector3 blockPos = {currBlock.getPosition().x, currBlock.getPosition().z,
        currBlock.getPosition().y - blockSize.x / 2.00f};
        if (RL::Graphics::isThereACollision(playerPos, playerSize,
        blockPos, blockSize)) {
            if (currBlock.getBombOnIt())
                collisionWBomb = true;
            if (currBlockType != GROUND) {
                collidedBlockType = currBlockType;
                return true;
            }
        }
        return false;
    });
    if (!isThereACollision && !collisionWBomb) {
        if (isOnBomb)
            isOnBomb = false;
        return false;
    }

    return (!(isOnBomb && collidedBlockType == BASIC));
}

bool APlayer::isThereACollisionWithBlock(const pos_t &blockPos, const Vector3 &blockSize)
{
    static const Vector3 playerSize = {1.00f, 1.00f, 1.00f};
    static Vector3 VblockPos = {0};
    VblockPos = {blockPos.x, blockPos.z, blockPos.y - blockSize.x / 2.00f};

    return RL::Graphics::isThereACollision({position.x, position.y, position.z}, playerSize, VblockPos, blockSize);
}

bombAnimation_t &APlayer::updateTimer(std::vector<Block>& allBlock)
{
    return this->bomb.updateTimer(allBlock);
}

const std::vector<bomb_t> &APlayer::getBomb()
{
    return this->bomb.getBomb();
}

void APlayer::setRotationAngle(float &_rotationAngle)
{
    this->rotationAngle = _rotationAngle;
}

float APlayer::getRotationAngle() const
{
    return this->rotationAngle;
}

RL::AnimatedModel &APlayer::getModel()
{
    return this->model;
}

void APlayer::setModel(const RL::AnimatedModel& _model)
{
    this->model = _model;
}

const std::vector<KeyboardKey> &APlayer::getMovementKeys()
{
    return this->movementKeys;
}

int APlayer::getPlayerNbMaxBomb()
{
    return this->bomb.getNbMaxBomb();
}

int APlayer::getNbActualBomb()
{
    return this->bomb.getNbActualBomb();
}

const int &APlayer::getRangeBomb() const
{
    return this->bomb.getRangeBomb();
}

void APlayer::setNewBomb()
{
    this->bomb.setNewBomb();
}

void APlayer::setNewMaxBomb()
{
    this->bomb.setNewMaxBomb();
}

void APlayer::setNewRangeBomb()
{
    this->bomb.setNewRangeBomb();
}

const playerNum &APlayer::getPlayerNum() const
{
    return this->num;
}

const KeyboardKey &APlayer::getDropBombKey()
{
    return this->dropBombKey;
}

void APlayer::setSpeed()
{
    this->speed += 0.05;
}

const float &APlayer::getSpeed() const {
    return this->speed;
}

void APlayer::setIsOnBomb(bool _isOnBomb) {
    this->isOnBomb = _isOnBomb;
}

const bool &APlayer::getIsOnBomb() const
{
    return this->isOnBomb;
}