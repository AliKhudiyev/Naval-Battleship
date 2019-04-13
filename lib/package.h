
#ifndef PACKAGE
#define PACKAGE

#include"position.hpp"

struct Package{
    Position position=DEFAULT_POSITION;
    unsigned status=0;

    void set_position(const Position& pos){
        position=pos;
        // status=5;
    }
    void set_status(unsigned stat){
        status=stat;
        // position=DEFAULT_POSITION;
    }
};

#endif
