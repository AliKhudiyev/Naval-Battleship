
#include<iostream>

#pragma once

#define MAX_COLUMN  11
#define MAX_ROW     11

#define MAX_CELL    (MAX_COLUMN*MAX_ROW)
#define MAX_SHIPS   5

using func_ptr_t = bool (*)(int, int);

struct Position{
    int x_, y_;

    Position()=default;
    Position(int x, int y): 
        x_(x), y_(y) {}

    void init(unsigned x, unsigned y);
    friend std::istream& operator>>(std::istream& in, Position& position);
    bool operator==(const Position& position) const;
    bool operator!=(const Position& position) const;
    void operator=(const Position& position);
    bool compare(const Position& position, func_ptr_t compare_x, func_ptr_t compare_y);
    static Position generate(int max_x, int max_y);
};
