#include<iostream>
#include"window.hpp"

using namespace std;

int main(int argc, char* argv[]){

    User Ali("Ali");
    User Bot=BOT;

    Window* window=Window::Create();
    
    window->run(Ali, Bot);

    delete window;

    return 0;
}
