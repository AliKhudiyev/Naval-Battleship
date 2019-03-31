
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

    unsigned play(User& user);
    unsigned fire(const Position& position){
        unsigned stat=1;//window_.get_field()->fire(position);
        std::cout<<"Fire status : "<<stat<<'\n';
        return is_defeated();
    }
    bool is_defeated(){
        return 0;//window_.get_field()->is_defeated();
    }
    // void set_window(const Position& position, unsigned stat, unsigned pass=0);
    Field* get_field(){ return window_.get_field(); }

};
