#!/usr/bin/python
x = ""
while x != "q":
    print "hello"
    x = raw_input("please input q for quit:")
    if not x:
        break
else:
    print "ending..."
