#!/usr/bin/python
from SocketServer import TCPServer, ThreadingMixIn, StreamRequestHandler
class Server(ThreadingMixIn, TCPServer):pass

class Handler(StreamRequestHandler):
    def handle(self):
        addr = self.request.getpeername()
        print 'get connection from', addr
        self.wfile.write('thanks for connecting')

server = Server(('', 1234), Handler)
server.serve_forever()
