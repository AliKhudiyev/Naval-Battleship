
#include<string>

#pragma once

struct Cell{
    unsigned x, y;
    unsigned stat;      // 0 - normal, 1 - shotSea, 2 - shotShip
    std::string image;
};
