//
// Created by ilias on 09/06/2021.
//

#include "Block.h"

//************ BLOCK ***********

Block::Block(pos_t position) {
    this->breakable = false;
    this->dangerousness = false;
    this->position = position;
    this->type = BASIC;
    this->bombOnIt = false;
    this->blastOnIt = false;
}

const bool &Block::isBreakable() const {
    return this->breakable;
}

const pos_t &Block::getPosition() const {
    return this->position;
}

const BlockTypes &Block::getType() const {
    return this->type;
}

void Block::draw(RL::NonAnimatedModel &model) {
    model.draw({this->position});
}

bool Block::getDangerousness() const
{
    return this->dangerousness;
}

void Block::setDangerousness(bool _dangerousness)
{
    this->dangerousness = _dangerousness;
}

bool Block::getBombOnIt() const
{
    return this->bombOnIt;
}

void Block::setBombOnIt(bool _bombOnIt)
{
    this->bombOnIt = _bombOnIt;
}

bool Block::getBlastOnIt() const
{
    return this->blastOnIt;
}

void Block::setBlastOnIt(bool _blastOnIt)
{
    this->blastOnIt = _blastOnIt;
}

//*********** BREAKABLE BLOCK *********
BreakableBlock::BreakableBlock(pos_t position) : Block(position) {
    this->breakable = true;
    this->type = BREAKABLE_BASIC;
}

//*********** UNBREAKABLE BLOCK *********
UnbreakableBlock::UnbreakableBlock(pos_t position) : Block(position) {
    this->type = UNBREAKABLE_BASIC;
}

//********** WALL *********************
Wall::Wall(pos_t position) : UnbreakableBlock(position) {
    this->type = WALL;
}

//************* PILAR *****************8
Pilar::Pilar(pos_t position) : UnbreakableBlock(position) {
    this->type = PILAR;
}

//************* GROUND *****************8
Ground::Ground(pos_t position) : UnbreakableBlock(position) {
    this->type = GROUND;
}

//********* BRICK *********************
Brick::Brick(pos_t position) : BreakableBlock(position) {
    this->type = BRICK;
}