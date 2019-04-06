
#pragma once

#define HUMAN       true
#define COMPUTER    false

#define EASY    0
#define NORMAL  1
#define HARD    2

typedef bool type_t;
typedef unsigned diff_t;

struct User_Status{
    bool type_=HUMAN;
    unsigned difficulty_;

    User_Status(){}
    User_Status(type_t type, diff_t difficulty):
        type_(type), difficulty_(difficulty) {}
};