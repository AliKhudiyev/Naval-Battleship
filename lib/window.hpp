
#include<SDL/SDL.h>

#pragma once

#include"event.hpp"
#include"user.hpp"

class Window: public Event{
    private:
    unsigned running;
    SDL_Surface* surface[2], *test;
    SDL_Surface* block;
    Position position;
    unsigned cell_status[121], my_cell_status[121];

    private:
    Window();

    public:
    static Window* Create();
    int on_execute(User& user1, User& user2);

    bool on_init();
    void on_event(SDL_Event* event);
    void on_exit();
    void on_loop(User& user1, User& user2);
    void on_render();
    void on_quit();

    void on_LButton_down(int x, int y);
    ~Window(){
        on_quit();
    }

    private:
    static Window* window;
};
