#include"window.hpp"
#include"surface.hpp"
#include<unistd.h>

int Window::on_execute(User& user1, User& user2){
    std::cout<<"On execute.\n";
    std::cout<<user1.name()<<" is shooting.\n";
    running=1;
    on_loop(user1, user2);
    on_render();
    SDL_Event event;
    while(running==1){
        while(SDL_PollEvent(&event)) on_event(&event);
        on_loop(user1, user2);
        on_render();
        if(running!=1) sleep(1);
    }
    return 0;
}

bool Window::on_init(){
    std::cout<<"On init.\n";
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
    // std::cout<<"On loop.\n";
    if(position!=Position(-1, -1)){
        unsigned stat=user2.fire(position);
        if(stat==1){
            std::cout<<user1.name()<<"| Succesful shot!\n";
            running=0;
        } else if(stat==0){
            running=1;
        } else{
            running=0;
        }
        // user1.copy_status(my_cell_status);
        // user2.copy_status(cell_status);
        std::cout<<"Copied!\n";
        position.init(-1, -1);
    }
    user1.copy_status(my_cell_status);
    user2.copy_status(cell_status);
}

void Window::on_render(){
    Surface::on_draw(surface[0], test, 0, 0);
    Surface::on_draw(surface[0], surface[1], 560, 0);
    for(unsigned i=0;i<121;++i){
        if(cell_status[i]==1){
            if(!(block=Surface::on_load("resource/shotShip.bmp"))){
                std::cout<<"Failed to load the image!\n";
            }
            Surface::on_draw(surface[0], block, 50*(i-(i/11)*11)+1, 50*(i/11)+1);
            SDL_FreeSurface(block);
        } else if(cell_status[i]==2){
            if(!(block=Surface::on_load("resource/shotSea.bmp"))){
                std::cout<<"Failed to load the image!\n";
            }
            Surface::on_draw(surface[0], block, 50*(i-(i/11)*11)+1, 50*(i/11)+1);
            SDL_FreeSurface(block);
        }
        if(my_cell_status[i]==1){
            if(!(block=Surface::on_load("resource/lostShip.bmp"))){
                std::cout<<"Failed to load the image!\n";
            }
            Surface::on_draw(surface[0], block, 560+50*(i-(i/11)*11)+1, 50*(i/11)+1);
            SDL_FreeSurface(block);
        } else if(my_cell_status[i]==2){
            if(!(block=Surface::on_load("resource/lostSea.bmp"))){
                std::cout<<"Failed to load the image!\n";
            }
            Surface::on_draw(surface[0], block, 560+50*(i-(i/11)*11)+1, 50*(i/11)+1);
            SDL_FreeSurface(block);
        } else if(my_cell_status[i]==3){
            if(!(block=Surface::on_load("resource/ship.bmp"))){
                std::cout<<"Failed to load the image!\n";
            }
            Surface::on_draw(surface[0], block, 560+50*(i-(i/11)*11)+1, 50*(i/11)+1);
            SDL_FreeSurface(block);
        }
    }
    SDL_Flip(surface[0]);
}

void Window::on_quit(){
    SDL_FreeSurface(test);
    SDL_FreeSurface(surface[1]);
    SDL_FreeSurface(surface[0]);
    SDL_Quit();
}

void Window::on_LButton_down(int x, int y){
    position.init(x/50, y/50);
    std::cout<<"Position : "<<position.x_<<" "<<position.y_<<'\n';
}