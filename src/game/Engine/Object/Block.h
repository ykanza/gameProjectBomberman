//
// Created by ilias on 09/06/2021.
//

#ifndef BOMBERMAN_BLOCK_H
#define BOMBERMAN_BLOCK_H

#include "../../../raylib/myRaylib.h"

class Block {
    public:
        explicit Block(pos_t position = {0, 0, 0});
        ~Block() = default;
        void draw(RL::NonAnimatedModel &model);

    protected:
        bool breakable;
        bool dangerousness;
        bool bombOnIt;
        bool blastOnIt;
        pos_t position;
        BlockTypes type;

    public:
        const bool &isBreakable() const;
        const pos_t &getPosition() const;
        const BlockTypes &getType() const;
        bool getDangerousness() const;
        void setDangerousness(bool);
        bool getBombOnIt() const;
        void setBombOnIt(bool);
        bool getBlastOnIt() const;
        void setBlastOnIt(bool);
};

class BreakableBlock : public Block {
    public:
        explicit BreakableBlock(pos_t position = {0, 0, 0});
        ~BreakableBlock() = default;
};

class UnbreakableBlock : public Block {
    public:
        explicit UnbreakableBlock(pos_t position = {0, 0, 0});
        ~UnbreakableBlock() = default;
};

class Wall : public UnbreakableBlock {
public:
    Wall(pos_t position = {0, 0, 0});
    ~Wall() = default;
};

class Pilar : public UnbreakableBlock {
public:
    Pilar(pos_t position = {0, 0, 0});
    ~Pilar() = default;
};

class Ground : public UnbreakableBlock {
public:
    Ground(pos_t position = {0, 0, 0});
    ~Ground() = default;
};

class Brick : public BreakableBlock {
public:
    Brick(pos_t position = {0, 0, 0});
    ~Brick() = default;
};

#endif //BOMBERMAN_BLOCK_H
