
#pragma once

#define INIT_MODE true
#define PLAY_MODE false

#define FIELD_WIDTH     550
#define FIELD_HEIGHT    550
#define BORDER_WIDTH    10
#define CELL_SIZE       50

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
    bool orientation=true;       // true - vertical, false - horizontal

    void reset(){
        SET=CHOOSED=false;
        ship_size=0;
        orientation=true;
        n_available_ships[0]=N_2xSHIP;
        n_available_ships[1]=N_3xSHIP;
        n_available_ships[2]=N_4xSHIP;
        n_available_ships[3]=N_5xSHIP;
    }
};