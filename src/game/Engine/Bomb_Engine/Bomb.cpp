#include <memory>
#include "Bomb.hpp"
#include "../Player/APlayer.h"

Bomb::Bomb()
{
    this->nbMaxBomb = 1;
    this->nbActualBomb = this->nbMaxBomb;
    this->lenBomb = 1;
}

float calculateDist(pos_t tmp, pos_t block)
{
    return sqrt(pow((tmp.x - block.x), 2) + pow((tmp.z - block.y), 2));
}

static pos_t getClosestCase(pos_t p, const std::vector<Block> &allBlock)
{
    p.z += 1.00f;
    float distance = calculateDist(p, allBlock[0].getPosition());
    float tmpDist = 0;
    pos_t tmp = allBlock[0].getPosition();
    tmp.y = -1.00f;

    for (auto &e : allBlock) {
        tmpDist = calculateDist(p, e.getPosition());
        if (distance > tmpDist) {
            distance = tmpDist;
            tmp.x = e.getPosition().x;
            tmp.z = e.getPosition().y - 1.0f;
        }
    }
    return tmp;
}

static int &getClosestCaseFire(const pos_t &p, const std::vector<Block> &allBlock)
{
    static float distance = 0;
    static float tmpDist = 0;
    static int index = 0;
    static int i = 0;

    distance = calculateDist({p.x, p.z, p.y}, allBlock[0].getPosition());
    index = 0;
    i = 0;
    for (auto &e : allBlock) {
        tmpDist = calculateDist({p.x, p.z, p.y}, e.getPosition());
        if (distance > tmpDist) {
            distance = tmpDist;
            index = i;
        }
        i++;
    }
    return index;
}

bool operator==(const pos_t& lpos, const pos_t& rpos)
{
    return lpos.x == rpos.x && lpos.y == rpos.y && lpos.z == rpos.z;
}

static void searchGroundAndSetDangerousness(std::vector<Block> &allBlock, const pos_t &pos)
{
    for (auto &block : allBlock) {
        if (block.getPosition() == pos && block.getType() == GROUND)
            block.setDangerousness(true);
    }
}

void Bomb::setDangerousnessFuturBlasts(getPositionsType &getPositions,
std::vector<Block> &allBlock, const pos_t &VbombPos) const
{
    static int index = 0;
    static BlockTypes blockType;
    static pos_t PbombPos = {0};

    PbombPos = {VbombPos.x, VbombPos.z + 1.0f, VbombPos.y + 1.0f};
    for (auto &block : allBlock) {
        if (block.getPosition() == PbombPos && block.getType() == GROUND) {
            block.setBombOnIt(true);
            block.setDangerousness(true);
            break;
        }
    }
    for (int i = 1; i <= this->lenBomb; i++) {
        for (auto &getPosition : getPositions) {
            if (getPosition.first) {
                index = getClosestCaseFire(getPosition.second(VbombPos, static_cast<float>(i)), allBlock);
                blockType = allBlock[index].getType();
                if (blockType != WALL && blockType != PILAR) {
                    searchGroundAndSetDangerousness(allBlock, allBlock[index].getPosition());
                } else
                    getPosition.first = false;
            }
        }
    }
    std::for_each(getPositions.begin(), getPositions.end(), [] (auto &getPosition) {getPosition.first = true;});
}

static void resetBombAndBlastOnIt(const pos_t &pos, std::vector<Block> &allBlock)
{
    static pos_t bombPos = {0};

    bombPos = {pos.x, pos.z + 1.0f, pos.y + 1.0f};
    for (auto &block : allBlock) {
        if (block.getPosition() == bombPos && block.getType() == GROUND) {
            block.setBombOnIt(false);
            block.setBlastOnIt(false);
            break;
        }
    }
}

void Bomb::fillPositionCurrBlasts(getPositionsType &getPositions,
std::vector<Block> &allBlock, const pos_t &bombPos, bombAnimation_t &tmp)
{
    static int index = 0;
    static BlockTypes blockType;
    static pos_t tmpPos;

    tmp.position.push_back({bombPos.x, bombPos.z, bombPos.y});
    resetBombAndBlastOnIt(bombPos, allBlock);
    for (int i = 1; i <= this->lenBomb; i++) {
        for (auto &getPosition : getPositions) {
            if (getPosition.first) {
                index = getClosestCaseFire(getPosition.second(bombPos, static_cast<float>(i)), allBlock);
                tmpPos = allBlock[index].getPosition();
                blockType = allBlock[index].getType();
                if (blockType != WALL && blockType != PILAR) {
                    if (allBlock[index].getBombOnIt())
                        allBlock[index].setBlastOnIt(true);
                    tmp.position.push_back({tmpPos.x, tmpPos.y - 1, tmpPos.z});
                } else
                    getPosition.first = false;
            }
        }
    }
    std::for_each(getPositions.begin(), getPositions.end(), [] (auto &getPosition) {getPosition.first = true;});
    this->bomb.erase(this->bomb.begin());
}

static bool isThereBlastOnBomb(pos_t &pos, const std::vector<Block> &allBlock)
{
    static pos_t bombPos = {0};

    bombPos = {pos.x, pos.z + 1.0f, pos.y + 1.0f};
    for (auto &block : allBlock) {
        if (block.getPosition() == bombPos && block.getType() == GROUND) {
            if (block.getBlastOnIt())
                return true;
            break;
        }
    }

    return false;
}

bombAnimation_t &Bomb::updateTimer(std::vector<Block> &allBlock)
{
    static getPositionsType getPositions = {
        {true, [] (const pos_t &pos, const float i) {return pos_t {pos.x + 2.4f * i, pos.z, pos.y};}},
        {true, [] (const pos_t &pos, const float i) {return pos_t {pos.x - 2.4f * i, pos.z, pos.y};}},
        {true, [] (const pos_t &pos, const float i) {return pos_t {pos.x, pos.z + 2.4f * i, pos.y};}},
        {true, [] (const pos_t &pos, const float i) {return pos_t {pos.x, pos.z - 2.4f * i, pos.y};}}
    };
    static bombAnimation_t tmp;

    tmp = {};
    tmp.hasExplose = false;
    if (this->bomb.empty())
        return tmp;
    for (auto &e : this->bomb) {
        e.end = std::chrono::steady_clock::now();
        //Whenever a bomb explose
        if (std::chrono::duration_cast<std::chrono::seconds>(e.end - e.start).count() >= 3
        || isThereBlastOnBomb(e.position, allBlock)) {
            setNewBomb();
            tmp.hasExplose = true;
            tmp.start = std::chrono::steady_clock::now();
            tmp.blastScale.first = false;
            tmp.blastScale.second = 0.00f;
            //Create a list of position to draw explosion animation
            fillPositionCurrBlasts(getPositions, allBlock, e.position, tmp);
            return tmp;
        }
        setDangerousnessFuturBlasts(getPositions, allBlock, e.position);
    }

    return tmp;
}

void Bomb::dropBomb(const pos_t &p, const std::vector<Block> &allBlock,
std::vector<std::unique_ptr<APlayer>> &players)
{
    bomb_t tmp;
    static const Vector3 blockSize = {2.0f, 1.0f, 2.0f};
    static pos_t blockPos = {0};

    this->nbActualBomb -= 1;
    tmp.start = std::chrono::steady_clock::now();
    tmp.isDrop = true;
    tmp.position = getClosestCase(p, allBlock);
    blockPos = {tmp.position.x, tmp.position.z + 1.0f, -1.0f};
    for (auto &player : players) {
        player->isThereACollisionWithBlock(blockPos, blockSize);
        player->setIsOnBomb(true);
    }
    this->bomb.push_back(tmp);
}

void Bomb::setNewMaxBomb()
{
    this->nbMaxBomb += 1;
}

void Bomb::setNewRangeBomb()
{
    this->lenBomb += 1;
}

const std::vector<bomb_t> &Bomb::getBomb() const
{
    return this->bomb;
}

const int &Bomb::getNbMaxBomb() const
{
    return this->nbMaxBomb;
}

const int &Bomb::getNbActualBomb() const
{
    return this->nbActualBomb;
}

const int &Bomb::getRangeBomb() const
{
    return this->lenBomb;
}


void Bomb::setNewBomb()
{
    this->nbActualBomb++;
}