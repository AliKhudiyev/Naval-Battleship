#include"position.hpp"

void Position::init(unsigned x, unsigned y){
    x_=x;    y_=y;
}

std::istream& operator>>(std::istream& in, Position& position){
    in>>position.x_>>position.y_;
    return in;
}

bool Position::operator==(const Position& position) const{
    if(x_==position.x_ && y_==position.y_) return true;
    return false;
}

bool Position::operator!=(const Position& position) const{
    if(x_!=position.x_ || y_!=position.y_) return true;
    return false;
}