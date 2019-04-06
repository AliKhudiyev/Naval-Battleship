
#pragma once

#define HUMAN       true
#define COMPUTER    false

#define EASY    0
#define NORMAL  1
#define HARD    2

typedef bool type_t;
typedef unsigned level_t;

struct User_Status{
    bool type_=HUMAN;
    unsigned level_;

    User_Status(){}
    User_Status(type_t type, level_t level):
        type_(type), level_(level) {}
};