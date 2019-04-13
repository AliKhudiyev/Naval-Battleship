#include<iostream>
#include<fstream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include"window.hpp"

using namespace std;

int main(int argc, char* argv[]){

    string name[MAX_PLAYERS]{"", ""};
    type_t type[MAX_PLAYERS]{COMPUTER, COMPUTER};
    level_t level[MAX_PLAYERS]{0, 0};
    NET_TYPE net_type=NET_TYPE::Server_Net;
    string ip_address;

    srand(time(NULL));
    if(argc==1){
        cout<<"Enter a name: "; cin>>name[0];
        cout<<"Enter a name: "; cin>>name[1];
        type[0]=type[1]=HUMAN;
    }
    else if(argc>=2 && !strcmp(argv[1], "-b")){
        if(argc<4){
            cout<<"Enter a name: "; cin>>name[0];
            type[0]=HUMAN;
        }
        if(argc==3) level[1]=atoi(argv[2]);
        else if(argc==4){
            level[0]=atoi(argv[2]);
            level[1]=atoi(argv[3]);
        }                                           
        if(level[0]>HARD) level[0]=NORMAL;
        if(level[1]>HARD) level[1]=NORMAL;
    }
    else if(argc<=3 && !strcmp(argv[1], "-m")){
        cout<<"Enter a name: "; cin>>name[0];
        type[0]=MULTI_PLAYER;
        if(argc==3){
            net_type=NET_TYPE::Client_Net;
            std::ifstream invitation;
            invitation.open("invitation.txt", std::ios::in);
            invitation>>ip_address;
            invitation.close();
        }
    }
    else{
        cout<<"Proper usage: ./bs [game option]";
        cout<<" [player option]\n";
    }

    for(unsigned i=0;i<MAX_PLAYERS;++i){
        if(name[i].empty()){
            string tmp;
            tmp=level[i]==EASY? "Easy" : (level[i]==NORMAL? "Normal" : "Hard");
            name[i]=std::to_string(i+1)+". Bot ("+tmp+")";
        }
    }
    
    // cout<<"net type: "<<net_type<<'\n';
    // if(!ip_address.empty()) cout<<"ip address: "<<ip_address<<'\n';
    User Player(name[0], User_Status(type[0], level[0]));
    User Enemy(name[1], User_Status(type[1], level[1]));
    
    if(Player.is_multi_player()) Player.set_net_type(net_type, ip_address);

    Window* window=Window::Create();
    if(!Player.is_multi_player()){
        Window::run(Player, Enemy);
    }
    else Window::run(Player, true);
    delete window;

    return 0;
}
