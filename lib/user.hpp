
#include<string>

#pragma once

// #include"field.hpp"
#include"window.hpp"

class User{
    private:
    std::string name_;
    Window window_;

    public:
    User(const std::string& name): 
        name_(name) {}
    ~User(){}

    // void play();
    unsigned play(User& user);
    // unsigned fire(const Position& position);
    // bool is_defeated() const;
    // void set_window(const Position& position, unsigned stat, unsigned pass=0);
    Field* get_field(){ return window_.get_field(); }

    // public:
    // Position position;
    // bool is_shot;
};
