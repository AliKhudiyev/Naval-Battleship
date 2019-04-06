#include<iostream>
#include"window.hpp"

#define INIT_ALL(name1, name2)                      \
    srand(time(NULL));                              \
    cout<<"Enter a name: "; cin>>name1;             \
    if(argc==1){                                    \
        cout<<"Enter a name: "; cin>>name2;         \
    } else if(!strcmp(argv[1], "-b")) type=COMPUTER;

using namespace std;

int main(int argc, char* argv[]){

    string name1, name2("Bot");
    bool type=HUMAN;
    INIT_ALL(name1, name2)

    User Player1(name1);
    User Player2(name2, type);

    Window* window=Window::Create();    
    window->run(Player1, Player2);
    delete window;

    return 0;
}
