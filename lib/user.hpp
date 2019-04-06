
#include<string>

#pragma once

#include"field.hpp"

#define HUMAN       true
#define COMPUTER    false

#define EASY    true
#define NORMAL  false

#define BOT User("Bot", COMPUTER)

class User{
    private:
    std::string name_;
    Field field_;
    bool type_;

    public:
    User(const std::string& name, bool type=HUMAN): 
        name_(name), type_(type) {}
    ~User(){}

    const std::string& name() const;
    void copy_status(unsigned* status) const;
    void copy_only_ship_status(unsigned* status) const;
    bool set_ship(unsigned index, const Position& position, unsigned length, bool orientation);
    void place_ships();
    unsigned fire(const Position& position);
    bool is_defeated() const;
    bool is_bot() const;
};
