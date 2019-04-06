
#include<SDL/SDL.h>

#pragma once

#include"event.hpp"
#include"user.hpp"
#include"window_stat.hpp"

class Window: public Event{
    private:
    unsigned running;
    Window_Status status;
    SDL_Surface* surface[2], *test;
    SDL_Surface* block;
    Position position;
    unsigned cell_status[121], my_cell_status[121];

    private:
    Window();
    void reset();

    public:
    static Window* Create();
    static int run(User& user1, User& user2);
    int on_execute(User& user1, User& user2);

    bool on_init();
    int on_pre_game(User& user);
    void on_event(SDL_Event* event);
    void on_exit();
    void on_loop(User& user1, User& user2);
    void on_render();
    void on_pre_render();
    void on_post_render();
    void on_quit();

    void on_LButton_down(int x, int y);
    void on_RButton_down(int x, int y);
    void on_mouse_motion(int x, int y);
    ~Window(){
        on_quit();
    }

    private:
    static Window* window;
};
