#include"field.hpp"

#define BORDER_LENGTH 1

Field::Field(){
    for(unsigned i=0;i<MAX_CELL;++i){ is_shot_[i]=enemy_is_shot_[i]=0; }
}

bool Field::set_ship(unsigned index, const Position& position, unsigned length, bool orientation){
    if(is_crashed(position, length, orientation)){
        std::cout<<"Ships intersect or is adjacent. Replace your ship again!\n";
        return false;
    }
    for(unsigned l=0;l<length;++l){
        if(orientation){
            if(Field::is_out(position.x_, position.y_+l)){
                std::cout<<"A ship is out of board!\n";
                return false;
            }
        } else{
            if(Field::is_out(position.x_+l ,position.y_)){
                std::cout<<"A ship is out of board!\n";
                return false;
            }
        }
    }
    for(unsigned i=0;i<length;++i){
        if(orientation){
            is_shot_[MAX_ROW*position.y_+position.x_+MAX_ROW*i]=3;
        } else{
            is_shot_[MAX_ROW*position.y_+position.x_+i]=3;
        }
    }
    ships_[index].init(position, length, orientation);
    return true;
}

bool Field::is_out(int x, int y){
    if(x<0 || x>=MAX_COLUMN || y<0 || y>=MAX_ROW) return true;
    return false;
}

unsigned Field::fire(const Position& position){
    if(Field::is_out(position.x_, position.y_)){
           std::cout<<"Point is out of board!\n";
           return 0;
    }
    if(is_shot_[MAX_COLUMN*position.y_+position.x_]!=S_SHIP_EXISTS && 
       is_shot_[MAX_COLUMN*position.y_+position.x_]){
        std::cout<<"Cannot shoot here more than once!\n";
        return 0;
    }
    for(auto& ship: ships_){
        if(ship.fire(position)){
            is_shot_[MAX_COLUMN*position.y_+position.x_]=S_SHOT_SHIP;
            return S_SHOT_SHIP;
        }
    }
    is_shot_[MAX_COLUMN*position.y_+position.x_]=S_SHOT_SEA;
    return S_SHOT_SEA;
}

bool Field::is_defeated() const{
    for(auto ship: ships_){
        if(!ship.is_defeated()) return false;
    }
    return true;
}

bool Field::is_crashed(const Position& position, unsigned length, bool orientation) const{
    for(unsigned i=0;i<MAX_SHIPS;++i){
        if(ships_[i].get_length()==1) continue;
        for(unsigned k=0;k<length;++k){
            for(unsigned j=0;j<ships_[i].get_length();++j){
                Position position1;
                if(orientation){
                    position1.x_=position.x_;
                    position1.y_=position.y_+k;
                } else{
                    position1.x_=position.x_+k;
                    position1.y_=position.y_;
                }
                if( position1.compare(ships_[i].get_position(j), [](int x1, int x2){return x1<=x2+BORDER_LENGTH;}, [](int y1, int y2){return y1<=y2+BORDER_LENGTH;}) &&
                    position1.compare(ships_[i].get_position(j), [](int x1, int x2){return x1>=x2-BORDER_LENGTH;}, [](int y1, int y2){return y1>=y2-BORDER_LENGTH;}) ) return true;    
            }
        }
    }
    return false;
}

unsigned Field::operator[](unsigned i) const{
    if(i>=MAX_CELL) return -1;
    return is_shot_[i];
}