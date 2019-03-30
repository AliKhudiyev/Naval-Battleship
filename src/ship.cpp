#include"ship.hpp"

bool Ship::fire(const Position& position){
    for(unsigned i=0;i<positions_.size();++i){
        if(positions_[i]==position && !is_shot_[i]){
            is_shot_[i]=true;
            --length_;
            return true;
        }
    }
    return false;
}

bool Ship::is_defeated() const{
    if(length_==0) return true;
    return false;
}

unsigned Ship::get_length() const{
    return length_;
}

const Position& Ship::get_position(unsigned i) const{
    return positions_[i];
}

void Ship::init(const Position& position, unsigned length, bool orientation){
    positions_.resize(length);
    is_shot_.resize(length);
    positions_[0]=position;
    if(orientation){
        for(unsigned i=1;i<length;++i){
            positions_[i].x_=position.x_;
            positions_[i].y_=position.y_+i;
        }
    } else{
        for(unsigned i=1;i<length;++i){
            positions_[i].x_=position.x_+i;
            positions_[i].y_=position.y_;
        }
    }
    length_=length;
    orientation_=orientation;
    for(unsigned i=0;i<length;++i) is_shot_[i]=false;
}