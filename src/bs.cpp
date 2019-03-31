#include<iostream>
#include"window.hpp"
#include"user.hpp"

using namespace std;

int main(int argc, char* argv[]){

    User Ali("Ali");
    User Kanan("Kanan");

    Window window;
    
    while(1){
        window.on_execute(Ali, Kanan);
        if(Kanan.is_defeated()){
            std::cout<<Ali.name()<<" won!\n";
            break;
        }
        window.on_execute(Kanan, Ali);
        if(Ali.is_defeated()){
            std::cout<<Kanan.name()<<" won!\n";
            break;
        }
    }

    return 0;
}
