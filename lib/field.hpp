
#include<iostream>

#pragma once

#include"ship.hpp"

static const unsigned nb_ship=MAX_SHIPS;
static const unsigned nb_shot=121;

class Field{
    private:
    Ship ships_[MAX_SHIPS];
    unsigned is_shot_[121];     // 0 - not shot and not ship, 1 - shot ship, 2 - shot sea, 3 - ship exists
    unsigned enemy_is_shot_[121];

    public:
    Field();
    static bool is_out(int x, int y);
    unsigned fire(const Position& position);
    bool is_defeated() const;
    bool is_crashed(const Position& position, unsigned length, bool orientation) const;
    unsigned operator[](unsigned i) const;
};
