
#ifndef NETWORK_PACKAGE
#define NETWORK_PACKAGE

#include"network.h"
#include"package.h"

enum NET_TYPE{Client_Net=0, Server_Net};

struct Net_Pack{
    Network network;
    Package package;
    NET_TYPE type;

    Net_Pack()=default;
    Net_Pack(NET_TYPE net_type, const std::string& ip_address): 
        type(net_type) 
        {
            network.ip_addr=const_cast<char*>(ip_address.c_str());
        }
};

#endif
