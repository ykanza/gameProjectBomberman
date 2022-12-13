//
// Created by ilias on 09/06/2021.
//

#ifndef BOMBERMAN_GAMEMAP_H
#define BOMBERMAN_GAMEMAP_H

#include <vector>
#include "../Object/Block.h"
#include "../../../raylib/graphics/Model/Model.h"

class GameMap {
public:
    GameMap();
    ~GameMap() = default;
public:
    void setMap(float);
    void createMap(float);
    void draw();
    void drawBackGround();
public:
    std::vector<Block> &getMapBlocks(); //blocks will be modified so don't return const
    std::vector<RL::NonAnimatedModel> &getMapModels(); //blocks will be modified so don't return const
    RL::NonAnimatedModel &getBackGround(); //blocks will be modified so don't return const
    void clearMap();
private:
    std::vector<Block> mapBlocks;
    std::vector<RL::NonAnimatedModel> mapModels;
    RL::NonAnimatedModel background;
};

#endif //BOMBERMAN_GAMEMAP_H
