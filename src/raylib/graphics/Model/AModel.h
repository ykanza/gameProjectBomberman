//
// Created by ilias on 16/06/2021.
//

#ifndef BOMBERMAN_AMODEL_H
#define BOMBERMAN_AMODEL_H

#include "game.h"
#include "../graphics.hpp"
namespace RL {
    class AModel {
    public:
        AModel(const xForm_t &transform, const std::string &modelFilePath,
               const std::string &texturePath = "");

        ~AModel() = default;

    public:
        virtual void draw() = 0;

        virtual void draw(const xForm_t &transform) = 0;

        virtual void drawEx(const xForm_t &transform) = 0;

    public:
        void setPosition(const pos_t &);

        void setRotation(const pos_t &);

        void setScale(const pos_t &);

        void setAngle(const float &);

        const pos_t &getPosition() const;

        const pos_t &getRotation() const;

        const pos_t &getScale() const;

        Model &getModel();

        Texture2D &getTexture();

    protected:
        xForm_t transform = {0};
        Model model;
        Texture2D texture = {0};
    };
}


#endif //BOMBERMAN_AMODEL_H
