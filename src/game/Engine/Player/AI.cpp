/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** TODO: add description
*/

#include "AI.h"

AI::AI(RL::AnimatedModel &model, pos_t position, playerNum nbP) : APlayer(model, position, nbP) {
    this->bombDepositRequested = false;
}

void AI::dropBomb(const std::vector<Block> &allBlock, RL::Audio &audio,
std::vector<std::unique_ptr<APlayer>> &players)
{
    if (bombDepositRequested && bomb.getNbActualBomb() > 0) {
        bomb.dropBomb(position, allBlock, players);
        audio.playSound("bomb_drop");
        bombDepositRequested = false;
    }
}

static bool getDangerousnessClosestBlock(const std::vector<Block> &mapBlocks, const Vector3 &playerPos)
{
    static const Vector3 blockSize = {2.40f, 1.0f, 2.40f};
    static const Vector3 playerSize = {1.00f, 1.00f, 1.00f};

    for (auto &currBlock : mapBlocks) {
        Vector3 blockPos = {currBlock.getPosition().x, currBlock.getPosition().z,
                            currBlock.getPosition().y - blockSize.x / 2.00f};
        if (RL::Graphics::isThereACollision(playerPos, playerSize, blockPos, blockSize))
            return currBlock.getDangerousness();
    }

    return false;
}

void AI::setRandomDirectionInVec(std::vector<Direction>& vecDirection)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(vecDirection.size() - 1));
    this->direction = vecDirection[dist(mt)];
}

bool AI::setMoveMembers(std::vector<Direction>& freeCase,
std::vector<Direction>& safeCase, updateMapType &updateMap)
{
    static bool isDirectionFound = false;
    static bool isMoving = false;

    isMoving = false;
    if (!freeCase.empty()) {
        for (auto &dir : safeCase.empty() ? freeCase : safeCase) {
            if (dir == direction) {
                isDirectionFound = true;
                break;
            }
        }
        if (!isDirectionFound)
            setRandomDirectionInVec(safeCase.empty() ? freeCase : safeCase);
        updateMap[direction].second(position);
        rotation = updateMap[direction].first.rotationAxis;
        rotationAngle = updateMap[direction].first.rotationAngle;
        freeCase.clear();
        safeCase.clear();
        isMoving = true;
    }
    isDirectionFound = false;

    return isMoving;
}

bool AI::move(const std::vector<Block> &mapBlocks)
{
    float speed = this->speed;
    static updateMapType updateMap = {
        {UP, {{{-1.0f, 0.0f, 0.0f}, 90.0f}, [&speed] (pos_t &pos) {pos.z += (0.2f + speed);}}},
        {LEFT, {{{-1.0f, 1.0f, 1.0f}, 120.0f}, [&speed] (pos_t &pos) {pos.x += (0.2f + speed);}}},
        {DOWN, {{{0.0f, -1.0f, -1.0f}, 180.0f}, [&speed] (pos_t &pos) {pos.z -= (0.2f + speed);}}},
        {RIGHT, {{{-1.0f, -1.0f, -1.0f}, 120.0f}, [&speed] (pos_t &pos) {pos.x -= (0.2f + speed);}}}
    };
    static pos_t reqPos = {0};
    static std::chrono::steady_clock::time_point startBombDeposit = std::chrono::steady_clock::now();
    static std::vector<Direction> freeCase;
    static std::vector<Direction> safeCase;

    for (auto &dir : updateMap) {
        reqPos = position;
        dir.second.second(reqPos);
        if (!isThereACollisionWithBlocks(mapBlocks, {reqPos.x, reqPos.y, reqPos.z})) {
            freeCase.push_back(dir.first);
            if (!getDangerousnessClosestBlock(mapBlocks, {reqPos.x, reqPos.y, reqPos.z}))
                safeCase.push_back(dir.first);
        } else if (collidedBlockType == BRICK
        && (DURATION_CAST_MILISEC(std::chrono::steady_clock::now() - startBombDeposit).count() >= 5000)) {
                bombDepositRequested = true;
                startBombDeposit = std::chrono::steady_clock::now();
        }
    }
    setMoveMembers(freeCase, safeCase, updateMap);

    return true;
}