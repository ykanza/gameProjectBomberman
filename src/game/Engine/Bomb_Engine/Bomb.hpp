//
// Created by ilias on 07/06/2021.
//

#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H

#include <map>
#include <list>
#include <vector>
#include <chrono>
#include <raylib.h>
#include <cmath>
#include <functional>
#include <algorithm>
#include "../../../../include/game.h"
#include "../../../raylib/myRaylib.h"
#include "../Object/Block.h"

/**************************
 Struct to return in getBomb() -> to manage multiple dropBomb
*************************/

typedef std::vector<std::pair<bool, const std::function<pos_t(const pos_t &, const float)>>> getPositionsType;

typedef struct bomb_s {
    pos_t position;
    bool isDrop;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
} bomb_t;

/**************************
 Struct to return in updateTimer(); -> to manage multiple bombe explosion
*************************/
typedef struct bombAnimation_s {
    std::list <Vector3> position;
    bool hasExplose;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    std::pair<bool, float> blastScale;
} bombAnimation_t;

class APlayer;
class Bomb
{
    public:
        Bomb();
        ~Bomb() = default;
    public:
        bombAnimation_t &updateTimer(std::vector<Block> &allBlock);
        void dropBomb(const pos_t &p, const std::vector<Block> &allBlock,
        std::vector<std::unique_ptr<APlayer>> &players);
        void fillPositionCurrBlasts(getPositionsType &getPositions, std::vector<Block> &allBlock, const pos_t &bombPos, bombAnimation_t &tmp);
        void setDangerousnessFuturBlasts(getPositionsType &getPositions, std::vector<Block> &allBlock, const pos_t &VbombPos) const;
        void setNewBomb();
        void setNewMaxBomb();
        void setNewRangeBomb();

    public:
        const std::vector<bomb_t> &getBomb() const;
        // void resetMaxBomb();
        // void resetRangeBomb();
        const int &getNbMaxBomb() const;
        const int &getNbActualBomb() const;
        const int &getRangeBomb() const;

    private:
        int nbMaxBomb;
        int nbActualBomb;
        int lenBomb;
        std::vector <bomb_t> bomb;
};

#endif //BOMBERMAN_BOMB_H
