
#include<string>

#pragma once

#include"field.hpp"
#include"user_status.hpp"

#define BOT User("Bot", COMPUTER)

class User{
    private:
    std::string name_="Bot";
    Field field_;
    User_Status status_;

    public:
    explicit User(const std::string& name): 
        name_(name) {}
    explicit User(const User_Status& status):
        status_(status) {}
    ~User(){}

    const std::string& name() const;
    void copy_status(unsigned* status) const;
    void copy_only_ship_status(unsigned* status) const;
    bool set_ship(unsigned index, const Position& position, unsigned length, bool orientation);
    void place_ships();
    Position generate(unsigned max_x, unsigned max_y);
    unsigned fire(const Position& position);
    bool is_defeated() const;
    bool is_bot() const;
};
