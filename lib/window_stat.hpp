
#pragma once

#include"position.hpp"

#define INIT_MODE true
#define PLAY_MODE false

#define CELL_SIZE       50
#define FIELD_WIDTH     (CELL_SIZE*MAX_COLUMN)
#define FIELD_HEIGHT    (CELL_SIZE*MAX_ROW)
#define BORDER_WIDTH    10

#define N_2xSHIP 1
#define N_3xSHIP 2
#define N_4xSHIP 1
#define N_5xSHIP 1

struct Window_Status{
    bool mod=INIT_MODE;
    bool SET=false, CHOOSED=false;
    unsigned n_available_ships[4]{
        N_2xSHIP, N_3xSHIP, N_4xSHIP, N_5xSHIP
    };
    unsigned ship_size=0;
    bool orientation=VERTICAL;       // true - vertical, false - horizontal

    void reset(){
        SET=CHOOSED=false;
        ship_size=0;
        orientation=VERTICAL;
        n_available_ships[0]=N_2xSHIP;
        n_available_ships[1]=N_3xSHIP;
        n_available_ships[2]=N_4xSHIP;
        n_available_ships[3]=N_5xSHIP;
    }
};