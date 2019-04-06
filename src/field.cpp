#include"field.hpp"

#define BORDER_LENGTH 1

Field::Field(){
    for(unsigned i=0;i<MAX_CELL;++i){ is_shot_[i]=0; }
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

void Field::set_recent_succesful_shot(const Position position){
    recent_succesful_shot_=position;
}

bool Field::is_out(int x, int y){
    if(x<0 || x>=MAX_COLUMN || y<0 || y>=MAX_ROW) return true;
    return false;
}

Position Field::generate(unsigned max_x, unsigned max_y, unsigned* status){
    Position position;
    unsigned i=0;
    int k=rand()%(max_x*max_y);
    // std::cout<<"k: "<<k<<'\n';
    for(unsigned j=0;k!=-1;++j){
        if(j>=MAX_CELL) j=0;
        if(!status[j]){ i=j; --k; }
    }
    position=Position(i-(i/MAX_COLUMN)*MAX_COLUMN, i/MAX_COLUMN);
    return position;
}

Position Field::generate(const Position& max_position, const Position& position, unsigned* status){
    Position p1=position, p2(-1, -1), pos;
    bool orientation=VERTICAL;
    int direction=1;
    std::cout<<"RSS : "<<p1.x_<<' '<<p1.y_<<'\n';
    for(unsigned i=1;i<MAX_SHIP_LENGTH;++i){
        if(!Field::is_out(p1.x_+i, p1.y_) && status[MAX_COLUMN*p1.y_+p1.x_+i]==1){
            p2=Position(p1.x_+i, p1.y_);
            orientation=HORIZONTAL;
        }
        else if(!Field::is_out(p1.x_-i, p1.y_) && status[MAX_COLUMN*p1.y_+p1.x_-i]==1){
            p2=Position(p1.x_-i, p1.y_);
            orientation=HORIZONTAL;
        }
        else if(!Field::is_out(p1.x_, p1.y_+i) && status[MAX_COLUMN*(p1.y_+i)+p1.x_]==1){
            p2=Position(p1.x_, p1.y_+i);
            orientation=VERTICAL;
        }
        else if(!Field::is_out(p1.x_, p1.y_-i) && status[MAX_COLUMN*(p1.y_-i)+p1.x_]==1){
            p2=Position(p1.x_, p1.y_-i);
            orientation=VERTICAL;
        }
        else if(!Field::is_out(p1.x_+i, p1.y_) && status[MAX_COLUMN*p1.y_+p1.x_+i]==0){
            if(p2!=DEFAULT_POSITION) break;
            p2=Position(p1.x_+i, p1.y_);
            orientation=HORIZONTAL;
            break;
        }
        else if(!Field::is_out(p1.x_-i, p1.y_) && status[MAX_COLUMN*p1.y_+p1.x_-i]==0){
            if(p2!=DEFAULT_POSITION) break;
            p2=Position(p1.x_-i, p1.y_);
            orientation=HORIZONTAL;
            break;
        }
        else if(!Field::is_out(p1.x_, p1.y_+i) && status[MAX_COLUMN*(p1.y_+i)+p1.x_]==0){
            if(p2!=DEFAULT_POSITION) break;
            p2=Position(p1.x_, p1.y_+i);
            orientation=VERTICAL;
            break;
        }
        else if(!Field::is_out(p1.x_, p1.y_-i) && status[MAX_COLUMN*(p1.y_-i)+p1.x_]==0){
            if(p2!=DEFAULT_POSITION) break;
            p2=Position(p1.x_, p1.y_-i);
            orientation=VERTICAL;
            break;
        }
    }
    if(Position::distance(p1, p2)==5) pos=Field::generate(max_position.x_, max_position.y_, status);
    else if(orientation){
        if(p1.y_-p2.y_>0) direction=-1;
        if(!Field::is_out(p1.x_, p1.y_-direction) && status[MAX_COLUMN*(p1.y_-direction)+p1.x_]==0){
            pos=Position(p1.x_, p1.y_-direction);
        }
        else if(!Field::is_out(p2.x_, p2.y_+direction) && status[MAX_COLUMN*(p1.y_+direction)+p1.x_]==0){
            pos=Position(p1.x_, p1.y_+direction);
        }
        else pos=Field::generate(max_position.x_, max_position.y_, status);
    }
    else{
        if(p1.x_-p2.x_>0) direction=-1;
        if(!Field::is_out(p1.x_-direction, p1.y_) && status[MAX_COLUMN*p1.y_+p1.x_-direction]==0){
            pos=Position(p1.x_-direction, p1.y_);
        }
        else if(!Field::is_out(p1.x_+direction, p1.y_) && status[MAX_COLUMN*p1.y_+p1.x_+direction]==0){
            pos=Position(p1.x_+direction, p1.y_);
        }
        else pos=Field::generate(max_position.x_, max_position.y_, status);
    }

    return pos;
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

Position Field::get_recent_succesful_shot() const{
    return recent_succesful_shot_;
}