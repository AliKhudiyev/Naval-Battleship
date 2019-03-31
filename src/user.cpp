#include"user.hpp"
#include<cstdlib>

unsigned User::play(User& user){
    int stat=window_.on_execute(user.get_field());
    window_.set(1);
    // unsigned x, y;
    // std::cout<<name_<<"| Enter to shoot: ";
    // std::cin>>x>>y;
    // Position position(x, y);
    // unsigned stat=user.fire(position);
    // std::cout<<"Play status: "<<stat<<'\n';
    return stat;
}
