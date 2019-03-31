
#include<SDL/SDL.h>
#include<iostream>

#pragma once

#include"event.hpp"
#include"cell.hpp"
#include"field.hpp"

class Window: public Event{
    private:
    unsigned running;
    SDL_Surface* surface[2];
    SDL_Surface* test, *block;
    Field *field, *my_field;
    Cell cells[121];

    public:
    Window(){
        running=1;
        surface[0]=NULL;
        surface[1]=NULL;
        test=NULL;
        block=NULL;
        field=nullptr;

        for(unsigned i=0;i<11;++i){
            for(unsigned j=0;j<11;++j){
                cells[11*i+j].x=j*50;
                cells[11*i+j].y=i*50;
                cells[11*i+j].image="";
            }
        }
        my_field=new Field();
    }

    int on_execute(Field* fld);
    void set(unsigned state){
        running=state;
    }
    void draw_at(const Position& position, unsigned stat);
    Field* get_field(){ return my_field; }

    bool on_init();
    void on_event(SDL_Event* event);
    void on_exit();
    void on_loop();
    void on_render();
    void on_quit();

    void on_LButton_down(int x, int y);
    ~Window(){
        delete my_field;
    }
};
