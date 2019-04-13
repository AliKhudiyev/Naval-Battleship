#!/bin/sh

INET_ADDRESS=$(ifconfig | grep "inet ")

IP_ADDRESS=$(echo $INET_ADDRESS | cut -c6-19)

echo "$IP_ADDRESS" > invitation.txt

if [ $# -gt 0 ]
then
    if [ $1 -eq 0 ]
    then
        echo "127.0.0.1" > invitation.txt
    fi
fi