
#include<string>

#pragma once

#include"field.hpp"

class User{
    private:
    std::string name_;
    Field field_;

    public:
    User(const std::string& name): 
        name_(name) {}
    ~User(){}

    const std::string& name() const{ return name_; }
    void copy_status(unsigned* status){
        for(unsigned i=0;i<121;++i) status[i]=field_[i];
    }
    unsigned play(User& user);
    unsigned fire(const Position& position){
        unsigned stat=field_.fire(position);
        return stat;
    }
    bool is_defeated(){
        return field_.is_defeated();
    }

};
