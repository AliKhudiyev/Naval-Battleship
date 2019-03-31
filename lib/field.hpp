
#include<iostream>

#pragma once

#include"ship.hpp"

static const unsigned nb_ship=MAX_SHIPS;
static const unsigned nb_shot=121;

class Field{
    private:
    Ship ships_[MAX_SHIPS];
    unsigned is_shot_[121];     // 0 - not shot and not ship, 1 - shot ship, 2 - shot sea, 3 - ship exists
    unsigned enemy_is_shot_[121];

    public:
    Field(){
        unsigned ship_size[4]{2,1,1,1};
        for(unsigned i=0;i<121;++i){ is_shot_[i]=0; is_shot_[i]=0; }
        for(unsigned i=0;i<MAX_SHIPS;++i){
            SELECTION:
            std::cout<<"Enter a ship size: ";
            unsigned length;
            std::cin>>length;
            if(length<2 || length>5){
                std::cout<<"Not such a ship!\n";
                goto SELECTION;
            }
            if(ship_size[length-2]) --ship_size[length-2];
            else{
                std::cout<<"Choose another ship.\n";
                goto SELECTION;
            }

            POSITIONING:
            std::cout<<"Enter a beginning position: ";
            int x, y;
            std::cin>>x>>y;
            if(x<0 || x>10 || y<0 || y>10){
                std::cout<<"Position is out of the board!\n";
                goto POSITIONING;
            }
            Position position(x, y);

            ORIENTATIONING:
            std::cout<<"Enter an orientation (h/v): ";
            char ornt;
            bool orientation;
            std::cin>>ornt;
            if(ornt=='h') orientation=false;
            else if(ornt=='v') orientation=true;
            else{
                std::cout<<"Not such an orientation!\n";
                goto ORIENTATIONING;
            }

            /**/
            for(unsigned l=0;l<length;++l){
                if(orientation){
                    if(is_out(x, y+l)){
                        std::cout<<"A ship is out of board!\n";
                        goto POSITIONING;
                    }
                } else{
                    if(is_out(x+l ,y)){
                        std::cout<<"A ship is out of board!\n";
                        goto POSITIONING;
                    }
                }
            }

            if(is_crashed(position, length, orientation)){
                std::cout<<"Ships intersect, replace again.\n";
                ++ship_size[length-2];
                goto SELECTION;
            }
            ships_[i].init(position, length, orientation);
            for(unsigned l=0;l<length;++l){
                if(orientation){
                    is_shot_[11*y+x+11*l]=3;
                } else{
                    is_shot_[11*y+x+l]=3;
                }
            }
        }
        std::cout<<"Initialized!\n";
        std::cout<<"\033[2J\033[1;1H";
    }
    bool is_out(int x, int y){
        if(x<0 || x>10 || y<0 || y>10) return true;
        return false;
    }
    unsigned fire(const Position& position);
    bool is_defeated() const;
    bool is_crashed(const Position& position, unsigned length, bool orientation) const;
    unsigned operator[](unsigned i) const{ return is_shot_[i]; }
};
