//
// Created by ilias on 09/06/2021.
//

#include <ctime>
#include "GameMap.h"

template <typename T>
Block createBlockInstance(pos_t position) {
    return T(position);
}

GameMap::GameMap() : background({ 0 }, "assets/map/background.gltf", "assets/map/background.png") {
    mapModels.push_back(RL::NonAnimatedModel({ 0 }, "assets/map/brick.gltf"));
    mapModels.push_back(RL::NonAnimatedModel({ 0 }, "assets/map/ground.gltf"));
    mapModels.push_back(RL::NonAnimatedModel({ 0 }, "assets/map/wall.gltf"));
    mapModels.push_back(RL::NonAnimatedModel({ 0 }, "assets/map/pilar.gltf"));
}

void GameMap::setMap(float mapSize) {
    createMap(mapSize);
    background.setPosition({ mapSize * 1.0f, mapSize * 4.5f, 10 });
    background.setRotation({ 0 });
    background.setScale({ mapSize * 3.1f, 1, 1 });
    background.setAngle(0);
}

void GameMap::clearMap() {
    this->mapBlocks.clear();
}

std::vector<Block> &GameMap::getMapBlocks() {
    return this->mapBlocks;
}

std::vector<RL::NonAnimatedModel> &GameMap::getMapModels() {
    return this->mapModels;
}

RL::NonAnimatedModel &GameMap::getBackGround() {
    return this->background;
}

void GameMap::draw() {
    for (auto &e : this->mapBlocks) {
        switch (e.getType()) {
            case BRICK:
                e.draw(mapModels[0]);
                break;
            case GROUND:
                e.draw(mapModels[1]);
                break;
            case WALL:
                e.draw(mapModels[2]);
                break;
            case PILAR:
                e.draw(mapModels[3]);
                break;
        }
    }
}

void GameMap::drawBackGround() {
    this->background.draw();
}

bool checkWall(int i, int j, int mapSize) {
    if (i == 0 || i == mapSize - 1 || j == 0 || j == mapSize - 1)
        return true;
    return false;
}

bool checkSpawn(int i, int j, int mapSize) {
    int tab_i[12] = { 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1 };
    int tab_j[12] = { 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2 };
    bool plus_i = true, plus_j = false;
    int temp_i = 0, temp_j = 0;
    for (int x = 0; x != 12; x++) {
        plus_i = (x % 3 == 0) ? !plus_i : plus_i;
        plus_j = (x == 6) ? !plus_j : plus_j;
        temp_i = (plus_i) ? i + tab_i[x] : i - tab_i[x];
        temp_j = (plus_j) ? j + tab_j[x] : j - tab_j[x];
        if (checkWall(temp_i, j, mapSize) && checkWall(i, temp_j, mapSize))
            return true;
    }
    return false;
}

void GameMap::createMap(float mapSize) {
    float scale = 2.4;
    std::srand(time(nullptr));
    for (int i = 0; i != mapSize; i++) {
        for (int j = 0; j != mapSize; j++) {
            if (checkWall(i, j, mapSize))
                this->mapBlocks.push_back(createBlockInstance<Wall>({ i * scale, j * scale, 0.0f }));
            else if (checkSpawn(i, j, mapSize)) {
                this->mapBlocks.push_back(createBlockInstance<Ground>({ i * scale, j * scale, 0.0f }));
            } else if (i % 2 == 0 && j % 2 == 0) {
                this->mapBlocks.push_back(createBlockInstance<Pilar>({ i * scale, j * scale, 0.0f }));
            } else {
                if (std::rand() % 4 != 0)
                    this->mapBlocks.push_back(createBlockInstance<Brick>({ i * scale, j * scale, 0.0f }));
                this->mapBlocks.push_back(createBlockInstance<Ground>({ i * scale, j * scale, 0.0f }));
            }
        }
    }
}