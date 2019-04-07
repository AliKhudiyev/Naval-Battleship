
#pragma once

#include"ship.hpp"

#define S_NSHOT_NSHIP   0
#define S_SHOT_SHIP     1
#define S_SHOT_SEA      2
#define S_SHIP_EXISTS   3

class Field{
    private:
    Ship ships_[MAX_SHIPS];
    unsigned is_shot_[MAX_CELL];     // 0 - not shot and not ship, 1 - shot ship, 2 - shot sea, 3 - ship exists
    Position recent_succesful_shot_=DEFAULT_POSITION;

    public:
    Field();

    bool set_ship(unsigned index, const Position& position, unsigned length, bool orientation);
    void set_recent_succesful_shot(const Position position);
    static bool is_out(int x, int y);
    static Position generate(const unsigned* const status, unsigned level=0);
    static Position generate(const Position& position, const unsigned* const status, unsigned level);
    unsigned fire(const Position& position);
    bool is_defeated() const;
    bool is_crashed(const Position& position, unsigned length, bool orientation) const;
    Position get_recent_succesful_shot() const;

    // getter operator for is_shot_
    unsigned operator[](unsigned i) const;
};
