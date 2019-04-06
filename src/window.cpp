#include"window.hpp"
#include"surface.hpp"
#include<unistd.h>

#define GAME_ON_EXIT 4

#define ENEMY_X 0
#define ENEMY_Y 0
#define MY_X    (FIELD_WIDTH+BORDER_WIDTH)
#define MY_Y    0

#define I2X(index)  (index-(index/MAX_ROW)*MAX_ROW)
#define I2Y(index)  (index/MAX_ROW)
#define P2I(x, y)   (MAX_COLUMN*(y/CELL_SIZE)+(x/CELL_SIZE))

#define CHECK_QUIT_STATUS(stat)             \
    if(stat==2){                            \
        std::cout<<"Quitting the game.\n";  \
        break;                              \
    }

#define LOAD_BMP(block, bmp)                        \
    if(!(block=Surface::on_load(bmp))){             \
        std::cout<<"Failed to load the image!\n";   \
    }

#define CHECK_DEFEAT_STATUS(user2, user1)   \
    if(user2.is_defeated()){                \
        std::cout<<user1.name()<<" won!\n"; \
        stat=2;                             \
        window->on_post_render();           \
        break;                              \
    }

Window* Window::window=nullptr;

Window::Window(){
    running=1;
    surface[0]=surface[1]=nullptr;
    block=nullptr;
    position=DEFAULT_POSITION;
    for(unsigned i=0;i<MAX_CELL;++i){
        cell_status[i]=my_cell_status[i]=0;
    }

    on_init();
}

void Window::reset(){
    status.reset();
    position=DEFAULT_POSITION;
}

Window* Window::Create(){
    if(!Window::window) Window::window=new Window();
    return Window::window;
}

int Window::run(User& user1, User& user2){
    unsigned stat=0;
    if(window->on_pre_game(user1)==2) return 2;
    if(window->on_pre_game(user2)==2) return 2;
    
    while(1){
        do{
            CHECK_DEFEAT_STATUS(user2, user1)
        }while((stat=window->on_execute(user1, user2))==3);
        CHECK_QUIT_STATUS(stat)
        do{
            CHECK_DEFEAT_STATUS(user1, user2)
        }while((stat=window->on_execute(user2, user1))==3);
        CHECK_QUIT_STATUS(stat)
    }
}

int Window::on_execute(User& user1, User& user2){
    std::cout<<user1.name()<<" is shooting.\n";
    running=1;
    
    if(user1.is_bot()){
        while(running==1) on_loop(user1, user2);
        return running;
    }

    SDL_Event event;
    while(running==1){
        while(SDL_PollEvent(&event)) on_event(&event);
        on_loop(user1, user2);
        on_render();
        if(running==0) sleep(1);
    }
    return running;
}

bool Window::on_init(){
    if(SDL_Init(SDL_INIT_VIDEO)<0) return false;
    if(!(surface[0]=SDL_SetVideoMode(2*FIELD_WIDTH+BORDER_WIDTH, FIELD_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))) return false;
    if(!(surface[1]=Surface::on_load(BACKGROUND))) return false;
    return true;
}

void Window::on_event(SDL_Event* event){
    Event::on_event(event);
}

void Window::on_exit(){
    running=2;
}

void Window::on_loop(User& user1, User& user2){
    if(position!=DEFAULT_POSITION || user1.is_bot()){
        if(user1.is_bot()){
            user2.copy_status(cell_status);
            // position=Field::generate(MAX_COLUMN, MAX_ROW, cell_status);
            position=Field::generate(Position(11, 11), user1.get_recent_succesful_shot(), cell_status);
        }
        std::cout<<"Position chose by bot : "<<position.x_<<' '<<position.y_<<'\n';
        unsigned stat=user2.fire(position);
        if(stat==1){
            std::cout<<user1.name()<<"| Succesful shot!\n";
            running=3;
            user1.set_recent_succesful_shot(position);
        } else if(stat==0){
            running=1;
            // user1.set_recent_succesful_shot(DEFAULT_POSITION);
        } else{
            running=0;
            // user1.set_recent_succesful_shot(DEFAULT_POSITION);
        }
        position=DEFAULT_POSITION;
    }
    user1.copy_status(my_cell_status);
    user2.copy_status(cell_status);
}

void Window::on_render(){
    Surface::on_draw(surface[0], surface[1], ENEMY_X, ENEMY_Y);
    Surface::on_draw(surface[0], surface[1], MY_X, MY_Y);
    for(unsigned i=0;i<MAX_CELL;++i){
        if(cell_status[i]==1){
            LOAD_BMP(block, SHOT_SHIP)
            Surface::on_draw(surface[0], block, CELL_SIZE*I2X(i)+1, CELL_SIZE*I2Y(i)+1);
            SDL_FreeSurface(block);
        } else if(cell_status[i]==2){
            LOAD_BMP(block, SHOT_SEA)
            Surface::on_draw(surface[0], block, CELL_SIZE*I2X(i)+1, CELL_SIZE*I2Y(i)+1);
            SDL_FreeSurface(block);
        }
        /**
        else if(cell_status[i]==3){
            LOAD_BMP(block, SHIP)
            Surface::on_draw(surface[0], block, CELL_SIZE*I2X(i)+1, CELL_SIZE*I2Y(i)+1);
            SDL_FreeSurface(block);
        }
        /**/
        if(my_cell_status[i]==1){
            LOAD_BMP(block, LOST_SHIP)
            Surface::on_draw(surface[0], block, MY_X+CELL_SIZE*I2X(i)+1, CELL_SIZE*I2Y(i)+1);
            SDL_FreeSurface(block);
        } else if(my_cell_status[i]==2){
            LOAD_BMP(block, LOST_SEA)
            Surface::on_draw(surface[0], block, MY_X+CELL_SIZE*I2X(i)+1, CELL_SIZE*I2Y(i)+1);
            SDL_FreeSurface(block);
        } else if(my_cell_status[i]==3){
            LOAD_BMP(block, SHIP)
            Surface::on_draw(surface[0], block, MY_X+CELL_SIZE*I2X(i)+1, CELL_SIZE*I2Y(i)+1);
            SDL_FreeSurface(block);
        }
    }
    if(status.mod==INIT_MODE){
        on_pre_render();
    }
    SDL_Flip(surface[0]);
}

void Window::on_pre_render(){
    LOAD_BMP(block, WELCOME)
    Surface::on_draw(surface[0], block, 0, 0);
    SDL_FreeSurface(block);
    for(unsigned j=0;j<4;++j){
        if(status.ship_size==0){
            LOAD_BMP(block, SHIP)
        } else{
            if(j!=status.ship_size-2){
                LOAD_BMP(block, SHIP)
            } else{
                LOAD_BMP(block, SELECTED_SHIP)
            }
        }
        Surface::on_draw(surface[0], block, 100+100*j, 50*6);
        SDL_FreeSurface(block);
    }
}

void Window::on_post_render(){
    LOAD_BMP(block, WIN)
    Surface::on_draw(surface[0], block, 0, 0);
    SDL_FreeSurface(block);
    SDL_Flip(surface[0]);
    sleep(3);
}

void Window::on_quit(){
    SDL_FreeSurface(surface[1]);
    SDL_FreeSurface(surface[0]);
    SDL_Quit();
}

void Window::on_LButton_down(int x, int y){
    if(status.mod==PLAY_MODE) position.init(x/CELL_SIZE, y/CELL_SIZE);
    else{
        if(x<FIELD_WIDTH && !status.CHOOSED){
            unsigned index=P2I(x, y);
            status.CHOOSED=true;
            if(index==68 && status.n_available_ships[0]) status.ship_size=2;
            else if(index==70 && status.n_available_ships[1]) status.ship_size=3;
            else if(index==72 && status.n_available_ships[2]) status.ship_size=4;
            else if(index==74 && status.n_available_ships[3]) status.ship_size=5;
            else status.CHOOSED=false;
        }
        on_pre_render();
        if(x>MY_X && status.CHOOSED){    
            status.SET=true;
            position.init((x-MY_X)/CELL_SIZE, y/CELL_SIZE);
        }
    }
}

void Window::on_RButton_down(int x, int y){
    if(status.mod==INIT_MODE){
        status.orientation=!status.orientation;
    }
}

void Window::on_mouse_motion(int x, int y){
    if(status.mod==INIT_MODE){
        for(unsigned i=0;i<MAX_CELL;++i) my_cell_status[i]=0;
        for(unsigned i=0;i<status.ship_size;++i){
            if(x<MY_X || !status.ship_size) break;
            if(status.orientation){
                if(y/CELL_SIZE+status.ship_size<=MAX_ROW) my_cell_status[P2I((x-MY_X), (y))+MAX_COLUMN*i]=3;

            } else{
                if((x-MY_X)/CELL_SIZE+status.ship_size<=MAX_COLUMN) my_cell_status[P2I((x-MY_X), (y))+i]=3;
            }
        }
    }
}

int Window::on_pre_game(User& user){
    if(user.is_bot()){
        user.place_ships();
        status.mod=PLAY_MODE;
        return 1;
    }
    status.mod=INIT_MODE;
    running=1;
    unsigned index=0;
    bool is_set=false;

    SDL_Event event;
    while(running==1){
        while(SDL_PollEvent(&event)) on_event(&event);
        if(status.SET && status.ship_size){
            is_set=user.set_ship(index, position, status.ship_size, status.orientation);
            if(is_set){
                ++index;
                --status.n_available_ships[status.ship_size-2];
                status.ship_size=0;
                status.CHOOSED=false;
            }
            status.SET=false;
        }
        user.copy_only_ship_status(my_cell_status);
        on_render();
        bool pass=true;
        for(unsigned i=0;i<MAX_SHIPS-1;++i){
            if(status.n_available_ships[i]!=0){
                pass=false;
                break;
            }
        }
        if(pass){
            running=0;
            sleep(1);
        }
    }
    status.mod=PLAY_MODE;
    reset();
    return running;
}