//
// Created by ilias on 07/06/2021.
//

#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include <string>

typedef struct pos_s
{
    float x;
    float y;
    float z;
} pos_t;

enum BlockTypes {
    BASIC,
    BREAKABLE_BASIC,
    UNBREAKABLE_BASIC,
    WALL,
    BRICK,
    PILAR,
    GROUND
};

typedef struct {
    std::string model_file;
    std::string animation_file;
    std::string texture_file;
} animatedModelConf_t;

typedef struct xForm_s {
    pos_t position = {0, 0, 0};
    pos_t rotation = {0.0, 1.0, 0.0};
    pos_t scale = {1, 1, 1};
    float rotationAngle = -90.0;
} xForm_t;

float calculateDist(pos_t tmp, pos_t block);
#endif //BOMBERMAN_GAME_H
