
#include<string>

#pragma once

#include"field.hpp"
#include"user_stat.hpp"
#include"net_pack.h"

class User{
    private:
    std::string name_="Bot";
    Field field_;
    User_Status status_;
    Net_Pack net_pack_;

    public:
    explicit User(const std::string& name, const User_Status& status=User_Status()): 
        name_(name), status_(status) {}
    explicit User(const std::string& name, const User_Status& status, const Net_Pack& net_pack): 
        name_(name), status_(status), net_pack_(net_pack) {}
    explicit User(const User_Status& status):
        status_(status) {}
    ~User(){}

    const std::string& name() const;
    void copy_status(unsigned* status) const;
    void copy_only_others_status(unsigned* status) const;
    void copy_only_ship_status(unsigned* status) const;
    bool set_ship(unsigned index, const Position& position, unsigned length, bool orientation);
    void set_recent_succesful_shot(const Position position);
    void set_net_type(NET_TYPE net_type, const std::string& ip_address="");
    void place_ships();
    unsigned fire(const Position& position);
    bool is_defeated() const;
    bool is_bot() const;
    bool is_multi_player() const;
    Position get_recent_succesful_shot() const;
    level_t get_level() const;
    Package& get_package();
    int get_server_sock() const;
    int get_client_sock() const;
    bool is_server() const;
    bool activate_networking();
};
