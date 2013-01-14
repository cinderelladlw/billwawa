#!/usr/bin/python
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("", 8081))
while True:
    data, addr = s.recvfrom(1024)
    print "received", data, "from", addr
