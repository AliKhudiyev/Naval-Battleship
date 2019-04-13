
#pragma once

#define HUMAN           0
#define COMPUTER        1
#define MULTI_PLAYER    2
#define MAX_PLAYERS     2

#define EASY    0
#define NORMAL  1
#define HARD    2

typedef unsigned type_t;
typedef unsigned level_t;

struct User_Status{
    type_t type_=HUMAN;
    level_t level_;

    User_Status()=default;
    User_Status(type_t type, level_t level):
        type_(type), level_(level) {}
};