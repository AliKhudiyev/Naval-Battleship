
#include<string>

#pragma once

enum ERROR_T{
    ERR_Default=0,
    ERR_Warning,
    ERR_LIGTH,
    ERR_Info,
    ERR_File,
    ERR_Memory,
    ERR_Fatal
};

class Exception{
    private:
    std::string msg_;
    ERROR_T error_;

    public:
    Exception(const std::string& msg, ERROR_T error=ERR_Default): 
        msg_(msg), error_(error) {}
    std::string what(int line=-1) const;
};
