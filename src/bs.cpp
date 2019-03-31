#include<iostream>
#include"window.hpp"

using namespace std;

int main(int argc, char* argv[]){

    User Ali("Ali");
    User Kanan("Kanan");

    Window* window=Window::Create();
    unsigned stat;
    while(1){
        stat=window->on_execute(Ali, Kanan);
        if(Kanan.is_defeated()){
            std::cout<<Ali.name()<<" won!\n";
            break;
        } else if(stat==2){
            std::cout<<"Quitting the game.\n";
            break;
        }
        stat=window->on_execute(Kanan, Ali);
        if(Ali.is_defeated()){
            std::cout<<Kanan.name()<<" won!\n";
            break;
        } else if(stat==2){
            std::cout<<"Quitting the game.\n";
            break;
        }
    }

    delete window;

    return 0;
}
