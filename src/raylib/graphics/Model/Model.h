//
// Created by ilias on 10/06/2021.
//

#ifndef BOMBERMAN_MODEL_H
#define BOMBERMAN_MODEL_H

#include "AModel.h"
#include "../graphics.hpp"
namespace RL {
    class AnimatedModel : public RL::AModel {
    public:
        AnimatedModel(const xForm_t &transform, animatedModelConf_t model);

        ~AnimatedModel() = default;

    public:
        void draw() override;

        void draw(const xForm_t &transformation) override;

        void drawEx(const xForm_t &transformation) override {}

        void playAnimation(bool onlyFst = false);

        ModelAnimation &getAnimation();

    private:
        ModelAnimation *animation = nullptr;
        int animFrameCounter = 0;
    };

    class NonAnimatedModel : public RL::AModel {
    public:
        NonAnimatedModel(const xForm_t &transform, const std::string &fileName,
                         const std::string &textureName = "");

        ~NonAnimatedModel() = default;

    public:
        void draw() override;

        void draw(const xForm_t &transformation) override;

        void drawEx(const xForm_t &transformation) override;

        void setBonusType(int nb);

        int getBonusType();

    private:
        int bonusType;
    };
}
#endif //BOMBERMAN_MODEL_H
