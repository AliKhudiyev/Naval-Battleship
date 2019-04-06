#include"user.hpp"
#include<cstdlib>
#include<ctime>

const std::string& User::name() const{
    return name_;
}

void User::copy_status(unsigned* status) const{
    for(unsigned i=0;i<MAX_CELL;++i) status[i]=field_[i];
}

void User::copy_only_others_status(unsigned* status) const{
    for(unsigned i=0;i<MAX_CELL;++i) status[i]=field_[i]==3? 0 : field_[i];
}

void User::copy_only_ship_status(unsigned* status) const{
    for(unsigned i=0;i<MAX_CELL;++i){
        if(field_[i]==S_SHIP_EXISTS) status[i]=field_[i];

    }
}

bool User::set_ship(unsigned index, const Position& position, unsigned length, bool orientation){
    return field_.set_ship(index, position, length, orientation);
}

void User::set_recent_succesful_shot(const Position position){
    field_.set_recent_succesful_shot(position);
}

void User::place_ships(){
    Position position;
    bool orientation;
    unsigned length;
    unsigned available_ships[]{2, 3, 3, 4, 5};

    for(unsigned i=0;i<MAX_SHIPS;){
        length=available_ships[i];
        orientation=rand()%2? true : false;
        position=Position(rand()%MAX_COLUMN, rand()%MAX_ROW);
        if(!set_ship(i++, position, length, orientation)) --i;
    }
}

unsigned User::fire(const Position& position){
    return field_.fire(position);
}

bool User::is_defeated() const{
    return field_.is_defeated();
}

bool User::is_bot() const{ return status_.type_==COMPUTER; }

Position User::get_recent_succesful_shot() const{
    return field_.get_recent_succesful_shot();
}

level_t User::get_level() const{ return status_.level_; }