#include<iostream>
#include"user.hpp"

using namespace std;

int main(int argc, char* argv[]){

    User Ali("Ali");
    User Kanan("Kanan");

    Window* window=Window::create();

    while(!Ali.is_defeated() && !Kanan.is_defeated()){
        window->on_execute(Ali, Kanan);
        window->on_execute(Kanan, Ali);
    }

    delete window;

    return 0;
}
