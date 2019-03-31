#include"user.hpp"
#include<cstdlib>

const std::string& User::name() const{
    return name_;
}

void User::copy_status(unsigned* status) const{
    for(unsigned i=0;i<121;++i) status[i]=field_[i];
}

unsigned User::fire(const Position& position){
    unsigned stat=field_.fire(position);
    return stat;
}

bool User::is_defeated() const{
    return field_.is_defeated();
}