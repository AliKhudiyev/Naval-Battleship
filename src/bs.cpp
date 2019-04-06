#include<iostream>
#include"window.hpp"

#define INIT_ALL(name1, name2)                      \
    srand(time(NULL));                              \
    cout<<"Enter a name: "; cin>>name1;             \
    if(argc==1){                                    \
        cout<<"Enter a name: "; cin>>name2;         \
    } else if(argc>=2 && !strcmp(argv[1], "-b")){   \
        type=COMPUTER;                              \
        if(argc==3) difficulty=atoi(argv[2]);       \
    }

using namespace std;

int main(int argc, char* argv[]){

    string name1, name2("Bot");
    type_t type=COMPUTER;
    diff_t difficulty=1;
    INIT_ALL(name1, name2)

    User Player1(name1);
    User Player2(User_Status(type, difficulty));

    Window* window=Window::Create();    
    Window::run(Player1, Player2);
    delete window;

    return 0;
}
