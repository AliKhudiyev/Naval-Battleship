#include"window.hpp"
#include"surface.hpp"
#include<unistd.h>

int Window::on_execute(User& user1, User& user2){    
    SDL_Event event;
    while(running==1){
        while(SDL_PollEvent(&event)) on_event(&event);
        on_loop(user1, user2);
        on_render();
        if(running!=1) sleep(1);
    }
    return running;
}

bool Window::on_init(){
    if(SDL_Init(SDL_INIT_VIDEO)<0) return false;
    if(!(surface[0]=SDL_SetVideoMode(1110, 550, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))) return false;
    if(!(surface[1]=Surface::on_load("resource/background.bmp"))) return false;
    if(!(test=Surface::on_load("resource/enemyBackground.bmp"))) return false;
    return true;
}

void Window::on_event(SDL_Event* event){
    Event::on_event(event);
}

void Window::on_exit(){
    running=2;
}

void Window::on_loop(User& user1, User& user2){
    unsigned stat=user2.fire(position);
    if(stat==1){
        std::cout<<user1.name()<<"| Succesful shot!\n";
    }
}

void Window::on_render(){
    Surface::on_draw(surface[0], test, 0, 0);
    Surface::on_draw(surface[0], surface[1], 560, 0);
    
    SDL_Flip(surface[0]);
}

void Window::on_quit(){
    SDL_FreeSurface(test);
    SDL_FreeSurface(surface[1]);
    SDL_FreeSurface(surface[0]);
    SDL_Quit();
}

void Window::on_LButton_down(int x, int y){
    ;
}