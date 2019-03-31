#include"field.hpp"

Field::Field(){
    unsigned ship_size[4]{2,1,1,1};
    for(unsigned i=0;i<MAX_CELL;++i){ is_shot_[i]=enemy_is_shot_[i]=0; }
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
        if(Field::is_out(x, y)){
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

        for(unsigned l=0;l<length;++l){
            if(orientation){
                if(Field::is_out(x, y+l)){
                    std::cout<<"A ship is out of board!\n";
                    goto POSITIONING;
                }
            } else{
                if(Field::is_out(x+l ,y)){
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

bool Field::is_out(int x, int y){
    if(x<0 || x>10 || y<0 || y>10) return true;
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
    is_shot_[11*position.y_+position.x_]=S_SHOT_SEA;
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

unsigned Field::operator[](unsigned i) const{
    if(i>=MAX_CELL) return -1;
    return is_shot_[i];
}