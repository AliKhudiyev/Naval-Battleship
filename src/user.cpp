#include"user.hpp"
#include<cstdlib>

unsigned User::play(User& user){
    int stat=window_.on_execute(user.get_field());
    window_.set(1);
    return stat;
}
