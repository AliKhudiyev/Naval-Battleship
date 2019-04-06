#include<iostream>
#include"window.hpp"

#define MAX_PLAYERS 2

#define INIT_ALL()                                  \
    srand(time(NULL));                              \
    if(argc==1){                                    \
        cout<<"Enter a name: "; cin>>name[0];       \
        cout<<"Enter a name: "; cin>>name[1];       \
        type[0]=type[1]=HUMAN;                      \
    }                                               \
    if(argc>=2 && !strcmp(argv[1], "-b")){          \
        if(argc<4){                                 \
            cout<<"Enter a name: "; cin>>name[0];   \
            type[0]=HUMAN;                          \
        }                                           \
        if(argc==3) level[1]=atoi(argv[2]);         \
        else if(argc==4){                           \
            level[0]=atoi(argv[2]);                 \
            level[1]=atoi(argv[3]);                 \
        }                                           \
        if(level[0]>2) level[0]=0;                  \
        if(level[1]>2) level[1]=0;                  \
    }

using namespace std;

// extern unsigned count1;
// extern unsigned count2;

int main(int argc, char* argv[]){

    string name[MAX_PLAYERS]{"", ""};
    type_t type[MAX_PLAYERS]{COMPUTER, COMPUTER};
    level_t level[MAX_PLAYERS]{0, 0};
    INIT_ALL()

    for(unsigned i=0;i<MAX_PLAYERS;++i){
        if(name[i].empty()){
            string tmp;
            tmp=level[i]==0? "Easy" : (level[i]==1? "Normal" : "Hard");
            name[i]=std::to_string(i+1)+". Bot ("+tmp+")";
        }
    }

    User Player1(name[0], User_Status(type[0], level[0]));
    User Player2(name[1], User_Status(type[1], level[1]));

    Window* window=Window::Create();    
    Window::run(Player1, Player2);
    delete window;

    return 0;
}
