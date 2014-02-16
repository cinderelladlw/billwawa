#!/usr/bin/python
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
port = 8081
host = "127.0.0.1"

while True:
    msg = raw_input()
    s.sendto(msg, (host, port))
 
