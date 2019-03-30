#include<iostream>
#include"user.hpp"

using namespace std;

int main(int argc, char* argv[]){

    User Ali("Ali");
    User Kanan("Kanan");
    
    while(1){
        if(Ali.play(Kanan)==2) break;
        if(Kanan.play(Ali)==2) break;
    }

    return 0;
}
