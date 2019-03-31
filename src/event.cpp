#include"event.hpp"

Event::Event(){}

Event::~Event(){}

void Event::on_event(SDL_Event* event){
    switch(event->type){
        case SDL_ACTIVEEVENT:{
            switch(event->active.state){
                case SDL_APPMOUSEFOCUS:{
                    if(event->active.gain) on_mouse_focus();
                    else on_mouse_blur();
                    break;
                }
                case SDL_APPINPUTFOCUS:{
                    if(event->active.gain) on_input_focus();
                    else on_input_blur();
                    break;
                }
                case SDL_APPACTIVE:{
                    if(event->active.gain) on_restore();
                    else on_minimize();
                    break;
                }
            }
            break;
        }
        case SDL_KEYDOWN:{
            on_key_down(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.unicode);
            break;
        }
        case SDL_KEYUP:{
            on_key_up(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.unicode);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:{
            switch(event->button.button){
                case SDL_BUTTON_LEFT:{
                    on_LButton_down(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:{
                    on_RButton_down(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:{
                    on_MButton_down(event->button.x, event->button.y);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:{
            switch(event->button.button){
                case SDL_BUTTON_LEFT:{
                    on_LButton_up(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:{
                    on_RButton_up(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:{
                    on_MButton_up(event->button.x, event->button.y);
                    break;
                }
            }
            break;
        }
        case SDL_JOYAXISMOTION:{
            on_joy_axis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
            break;
        }
        case SDL_JOYBALLMOTION:{
            on_joy_ball(event->jball.which, event->jball.ball, event->jball.xrel, event->jball.yrel);
            break;
        }
        case SDL_JOYHATMOTION:{
            on_joy_hat(event->jhat.which, event->jhat.hat, event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN:{
            on_joy_button_down(event->jbutton.which, event->jbutton.button);
            break;
        }
        case SDL_JOYBUTTONUP:{
            on_joy_button_up(event->jbutton.which, event->jbutton.button);
            break;
        }
        case SDL_QUIT:{
            on_exit();
            break;
        }
        case SDL_SYSWMEVENT:{
            break;
        }
        case SDL_VIDEORESIZE:{
            on_resize(event->resize.w, event->resize.h);
            break;
        }
        case SDL_VIDEOEXPOSE:{
            on_expose();
            break;
        }
        default:{
            on_user(event->user.type, event->user.code, event->user.data1, event->user.data2);
            break;
        }
    }
}

void Event::on_input_focus(){}

void Event::on_input_blur(){}

void Event::on_key_down(SDLKey stm, SDLMod mod, Uint16 unicode){}

void Event::on_key_up(SDLKey stm, SDLMod mod, Uint16 unicode){}

void Event::on_mouse_focus(){}

void Event::on_mouse_blur(){}

void Event::on_mouse_move(int mX, int mY, int relX, int relY, bool left, bool right, bool middle){}

void Event::on_LButton_down(int mX, int mY){}

void Event::on_LButton_up(int mX, int mY){}

void Event::on_RButton_down(int mX, int mY){}

void Event::on_RButton_up(int mX, int mY){}

void Event::on_MButton_down(int mX, int mY){}

void Event::on_MButton_up(int mX, int mY){}

void Event::on_joy_axis(Uint8 which, Uint8 axis, Sint16 value){}

void Event::on_joy_button_down(Uint8 which, Uint8 button){}

void Event::on_joy_button_up(Uint8 which, Uint8 button){}

void Event::on_joy_hat(Uint8 which, Uint8 hat, Uint8 value){}

void Event::on_joy_ball(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel){}

void Event::on_minimize(){}

void Event::on_restore(){}

void Event::on_resize(int width, int height){}

void Event::on_expose(){}

void Event::on_exit(){}

void Event::on_user(Uint8 type, int code, void* data1, void* data2){}