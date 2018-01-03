#!/bin/sh

read -p "Enter your username : " -s username
echo "\n"
read -p "Enter your password : " -s password
echo "\n"

curl https://$HOST_TL:$PORT_TL  --data "$username|$password" -v --insecure
