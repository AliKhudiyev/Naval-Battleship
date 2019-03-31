
#include<iostream>

#pragma once

#define MAX_SHIPS 5

struct Position{
    int x_, y_;

    Position()=default;
    Position(int x, int y): 
        x_(x), y_(y) {}

    void init(unsigned x, unsigned y);
    friend std::istream& operator>>(std::istream& in, Position& position);
    bool operator==(const Position& position) const;
    bool operator!=(const Position& position) const;
};
