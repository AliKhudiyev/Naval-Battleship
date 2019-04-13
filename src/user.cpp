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
    for(unsigned i=0;i<MAX_CELL;++i) status[i]=(field_[i]==3)? 0 : field_[i];
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

void User::set_net_type(NET_TYPE net_type, const std::string& ip_address){
    net_pack_.type=net_type;
    net_pack_.network.ip_addr=const_cast<char*>(ip_address.c_str());
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

bool User::is_multi_player() const{ return status_.type_==MULTI_PLAYER; }

Position User::get_recent_succesful_shot() const{
    return field_.get_recent_succesful_shot();
}

level_t User::get_level() const{ return status_.level_; }

Package& User::get_package(){ return net_pack_.package; }

int User::get_server_sock() const{ return net_pack_.network.sock_fd; }

int User::get_client_sock() const{ return net_pack_.network.new_sock_fd; }

bool User::is_server() const{ return net_pack_.type==Server_Net; }

bool User::activate_networking(){
    if(net_pack_.type==Server_Net){    // server
        INIT_ALL_SERVER_ESSENTIALS(net_pack_.network);
    } else if(!net_pack_.type){
        sleep(1);
        INIT_ALL_CLIENT_ESSENTIALS(net_pack_.network, net_pack_.network.ip_addr);
    }
}