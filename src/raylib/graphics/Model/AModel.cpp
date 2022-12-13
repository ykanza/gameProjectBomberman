//
// Created by ilias on 16/06/2021.
//

#include "AModel.h"

RL::AModel::AModel(const xForm_t &transform, const std::string &modelFilePath, const std::string &texturePath) {
    this->transform = transform;
    this->model = LoadModel(modelFilePath.c_str());
    if (texturePath != "") {
        this->texture = LoadTexture(texturePath.c_str());
        SetMaterialTexture(&this->model.materials[0], MAP_DIFFUSE, this->texture);
    }
}

void RL::AModel::setPosition(const pos_t &position) {
    this->transform.position = position;
}

void RL::AModel::setRotation(const pos_t &rotation) {
    this->transform.rotation = rotation;
}

void RL::AModel::setScale(const pos_t &scale) {
    this->transform.scale = scale;
}

void RL::AModel::setAngle(const float &angle) {
    this->transform.rotationAngle = angle;
}

const pos_t &RL::AModel::getPosition() const {
    return this->transform.position;
}

const pos_t &RL::AModel::getRotation() const {
    return this->transform.rotation;
}

const pos_t &RL::AModel::getScale() const {
    return this->transform.scale;
}

Model &RL::AModel::getModel() {
    return this->model;
}

Texture2D &RL::AModel::getTexture() {
    return this->texture;
}
