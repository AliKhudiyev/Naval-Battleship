
#include<iostream>

#pragma once

#define VERTICAL    true
#define HORIZONTAL  false

#define MAX_COLUMN  11
#define MAX_ROW     11

#define MAX_CELL        (MAX_COLUMN*MAX_ROW)
#define MAX_SHIPS       5
#define MAX_SHIP_LENGTH 5

#define DEFAULT_POSITION Position(-1, -1)

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
    static unsigned distance(const Position& position1, const Position& position2);
};
