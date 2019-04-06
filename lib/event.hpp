
#include<SDL/SDL.h>
#include<string>

#pragma once

class Event{
    public:
    Event();
    virtual ~Event();

    virtual void on_event(SDL_Event* event);
    virtual void on_input_focus();
    virtual void on_input_blur();
    virtual void on_key_down(SDLKey stm, SDLMod mod, Uint16 unicode);
    virtual void on_key_up(SDLKey stm, SDLMod mod, Uint16 unicode);
    virtual void on_mouse_focus();
    virtual void on_mouse_blur();
    virtual void on_mouse_move(int mX, int mY, int relX, int relY, bool left, bool right, bool middle);
    virtual void on_mouse_motion(int x, int y);
    virtual void on_LButton_down(int mX, int mY);
    virtual void on_LButton_up(int mX, int mY);
    virtual void on_RButton_down(int mX, int mY);
    virtual void on_RButton_up(int mX, int mY);
    virtual void on_MButton_down(int mX, int mY);
    virtual void on_MButton_up(int mX, int mY);
    virtual void on_joy_axis(Uint8 which, Uint8 axis, Sint16 value);
    virtual void on_joy_button_down(Uint8 which, Uint8 button);
    virtual void on_joy_button_up(Uint8 which, Uint8 button);
    virtual void on_joy_hat(Uint8 which, Uint8 hat, Uint8 value);
    virtual void on_joy_ball(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
    virtual void on_minimize();
    virtual void on_restore();
    virtual void on_resize(int width, int height);
    virtual void on_expose();
    virtual void on_exit();
    virtual void on_user(Uint8 type, int code, void* data1, void* data2);
};
