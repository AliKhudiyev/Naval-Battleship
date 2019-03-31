
#include<vector>
#include<string>

#pragma once

#include"position.hpp"

class Ship{
    private:
    std::vector<Position> positions_;
    bool orientation_;
    unsigned length_;

    public:
    Ship(){
        length_=1;
    }

    void init(const Position& position, unsigned length, bool orientation);
    unsigned get_length() const;
    const Position& get_position(unsigned i) const;
    bool fire(const Position& position);
    bool is_defeated() const;
};
