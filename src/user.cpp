#include"user.hpp"
#include<cstdlib>
#include<ctime>

int Rand(int max){
    return rand()%max;
}

Position rand_position(int max_x, int max_y){
    return Position(Rand(max_x), Rand(max_y));
}

/*   User class function definitions   */

const std::string& User::name() const{
    return name_;
}

void User::copy_status(unsigned* status) const{
    for(unsigned i=0;i<MAX_CELL;++i) status[i]=field_[i];
}

void User::copy_only_ship_status(unsigned* status) const{
    for(unsigned i=0;i<MAX_CELL;++i){
        if(field_[i]==S_SHIP_EXISTS) status[i]=field_[i];

    }
}

bool User::set_ship(unsigned index, const Position& position, unsigned length, bool orientation){
    return field_.set_ship(index, position, length, orientation);
}

void User::place_ships(){
    Position position;
    bool orientation;
    unsigned length;
    unsigned available_ships[]{2, 3, 3, 4, 5};

    for(unsigned i=0;i<MAX_SHIPS;){
        length=available_ships[i];
        orientation=Rand(2)? true : false;
        position=rand_position(MAX_COLUMN, MAX_ROW);
        if(!set_ship(i++, position, length, orientation)) --i;
    }
}

unsigned User::fire(const Position& position){
    return field_.fire(position);
}

bool User::is_defeated() const{
    return field_.is_defeated();
}

bool User::is_bot() const{ return !type_; }