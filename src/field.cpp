#include"field.hpp"

unsigned Field::fire(const Position& position){
    if(position.x_<0 || position.x_>10 ||
       position.y_<0 || position.y_>10){
           std::cout<<"Point is out of board!\n";
           return 0;
    }
    if(is_shot_[11*position.y_+position.x_]!=3 && is_shot_[11*position.y_+position.x_]){
        std::cout<<"Cannot shoot here more than once!\n";
        return 0;
    }
    for(auto& ship: ships_){
        if(ship.fire(position)){
            is_shot_[11*position.y_+position.x_]=1;
            return 1;
        }
    }
    is_shot_[11*position.y_+position.x_]=2;
    return 2;
}

bool Field::is_defeated() const{
    for(auto ship: ships_){
        if(!ship.is_defeated()) return false;
    }
    return true;
}

// intersection bug
bool Field::is_crashed(const Position& position, unsigned length, bool orientation) const{
    for(unsigned i=0;i<MAX_SHIPS;++i){
        if(ships_[i].get_length()==1) continue;
        for(unsigned k=0;k<length;++k){
            for(unsigned j=0;j<ships_[i].get_length();++j){
                Position position1;
                if(orientation){
                    position1.x_=position.x_;
                    position1.y_=position.y_+k;
                    if(position1==ships_[i].get_position(j)){
                        return true;
                    }
                } else{
                    position1.x_=position.x_+k;
                    position1.y_=position.y_;
                    if(position1==ships_[i].get_position(j)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}