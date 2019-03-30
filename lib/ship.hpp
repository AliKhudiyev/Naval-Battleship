
#include<vector>
#include<string>

#pragma once

#include"position.hpp"

class Ship{
    private:
    // std::string label_;
    std::vector<Position> positions_;
    bool orientation_;
    unsigned length_;
    std::vector<bool> is_shot_;

    public:
    Ship(){
        length_=1;
    }
    // Ship(const std::string& label);
    Ship(const Position position, unsigned length, bool orientation);
    // Ship(const std::string& label, const Position position, unsigned length, bool orientation);
    ;
    ~Ship(){}

    void init(const Position& position, unsigned length, bool orientation);
    // void set_length(unsigned length);
    unsigned get_length() const;
    const Position& get_position(unsigned i) const;
    bool fire(const Position& position);
    bool is_defeated() const;
};
