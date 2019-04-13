#include"exception.hpp"

std::string Exception::what(int line) const{
    std::string msg="", str_line="";
    if(line>=0) str_line=" "+std::to_string(line);
    switch(error_){
        case ERR_Default:{
            msg="DEFAULT ERROR: "+msg_+str_line;
            break;
        }
        case ERR_Warning:{
            msg="WARNING: "+msg_+str_line;
            break;
        }
        case ERR_LIGTH:{
            msg="LIGHT ERROR: "+msg_+str_line;
            break;
        }
        case ERR_Info:{
            msg="INFO ERROR: "+msg_+str_line;
            break;
        }
        case ERR_File:{
            msg="FILE ERROR: "+msg_+str_line;
            break;
        }
        case ERR_Memory:{
            msg="MEMORY ERROR: "+msg_+str_line;
            break;
        }
        case ERR_Fatal:{
            msg="FATAL ERROR: "+msg_+str_line;
            break;
        }
    }
    return msg;
}