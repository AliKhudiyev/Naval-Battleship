#include"window.hpp"
#include"surface.hpp"
#include<unistd.h>

void Window::draw_at(const Position& position, unsigned stat){
    cells[11*position.y_+position.x_].x=50*position.x_;
    cells[11*position.y_+position.x_].y=50*position.y_;
    if(stat==1){
        cells[11*position.y_+position.x_].image="resource/shotShip.bmp";
    } else if(stat==2){
        cells[11*position.y_+position.x_].image="resource/shotSea.bmp";
    }
}

int Window::on_execute(Field* fld){
    if(!on_init()) return -1;
    
    field=fld;
    
    SDL_Event event;
    while(running==1){
        while(SDL_PollEvent(&event)) on_event(&event);
        on_loop();
        on_render();
        if(running!=1) sleep(1);
    }
    on_quit();
    return running;
}

bool Window::on_init(){
    // SDL_INIT_EVERYTHING;
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

void Window::on_loop(){
    ;
}

void Window::on_render(){
    Surface::on_draw(surface[0], test, 0, 0);
    Surface::on_draw(surface[0], surface[1], 560, 0);
    for(unsigned i=0;i<121;++i){
        if((*my_field)[i]==3){
            if((block=Surface::on_load("resource/ship.bmp"))==NULL){
                std::cout<<"Failed to load!\n";
            }
            Surface::on_draw(surface[0], block, 560+50*(i-11*(i/11))+1, 50*(i/11)+1);
            SDL_FreeSurface(block);
        }
        if(!cells[i].image.empty()){
            // std::cout<<"i : "<<i<<'\n';
            if((block=Surface::on_load(cells[i].image.c_str()))==NULL){
                std::cout<<"Failed to load!\n";
            }
            Surface::on_draw(surface[0], block, cells[i].x+1, cells[i].y+1);
            SDL_FreeSurface(block);
        }
        unsigned stat=(*my_field)[i];
        if(stat==1){
            if((block=Surface::on_load("resource/lostShip.bmp"))==NULL){
                std::cout<<"Failed to load!\n";
            }
            Surface::on_draw(surface[0], block, 560+50*(i-11*(i/11))+1, 50*(i/11)+1);
            SDL_FreeSurface(block);
        } else if(stat==2){
            if((block=Surface::on_load("resource/lostSea.bmp"))==NULL){
                std::cout<<"Failed to load!\n";
            }
            Surface::on_draw(surface[0], block, 560+50*(i-11*(i/11))+1, 50*(i/11)+1);
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
    Position position(x/50, y/50);
    std::cout<<"Position: "<<position.x_<<" "<<position.y_<<'\n';
    unsigned stat;
    for(stat=0;!stat;){
        if((stat=field->fire(position))==1){
            draw_at(position, stat);
            std::cout<<"Successful shot.\n";
        }
    }
    draw_at(position, stat);
    if(field->is_defeated()){
        std::cout<<" won!\n";
        running=2;
    }
    else running=0;
    // std::cout<<"Mouse clicked at "<<x/50<<" "<<y/50<<'\n';
}