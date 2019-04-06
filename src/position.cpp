#include"position.hpp"
#include<cmath>

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

void Position::operator=(const Position& position){
    x_=position.x_;
    y_=position.y_;
}

bool Position::compare(const Position& position, func_ptr_t compare_x, func_ptr_t compare_y){
    return (compare_x(x_, position.x_) && compare_y(y_, position.y_));
}

Position Position::generate(int max_x, int max_y){
    return Position(rand()%max_x, rand()%max_y);
}

unsigned Position::distance(const Position& position1, const Position& position2){
    return sqrt(pow(position2.x_-position1.x_, 2)+pow(position2.y_-position1.y_, 2));
}