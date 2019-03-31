
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

    const std::string& name() const;
    void copy_status(unsigned* status) const;
    unsigned fire(const Position& position);
    bool is_defeated() const;
};
