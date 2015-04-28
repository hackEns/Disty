#!/usr/bin/env python

'''
A WebSocket server that echos back whatever it receives from the client.
Copyright 2010 Joel Martin
Licensed under LGPL version 3 (see docs/LICENSE.LGPL-3)

You can make a cert/key with openssl using:
openssl req -new -x509 -days 365 -nodes -out self.pem -keyout self.pem
as taken from http://docs.python.org/dev/library/ssl.html#certificates
'''

import os, socket, select, sys
sys.path.insert(0,os.path.join(os.path.dirname(__file__), ".."))
from websocket import WebSocketServer, WebSocketRequestHandler


def sendUDP(ip, port, message):
    try:
        sock = socket.socket(socket.AF_INET, # Internet
                             socket.SOCK_DGRAM) # UDP
        sock.sendto(message, (ip, port))
        sock.close()
    except:
        pass


class WebSocketEcho(WebSocketRequestHandler):
    """
    WebSockets server that echos back whatever is received from the
    client.  """
    buffer_size = 8096

    def new_websocket_client(self):
        """
        Echo back whatever is received.
        """

        cqueue = []
        c_pend = 0
        cpartial = ""
        rlist = [self.request]

        while True:
            wlist = []

            if cqueue or c_pend: wlist.append(self.request)
            ins, outs, excepts = select.select(rlist, wlist, [], 1)
            if excepts: raise Exception("Socket exception")

            if self.request in outs:
                # Send queued target data to the client
                c_pend = self.send_frames(cqueue)
                cqueue = []

            if self.request in ins:
                # Receive client data, decode it, and send it back
                frames, closed = self.recv_frames()
                print("Received: "+frames[0].decode('utf-8'))
                sendUDP("localhost", 4242, frames[0].decode('utf-8'))

                if closed:
                    self.send_close()

if __name__ == '__main__':
    opts = {"listen_port": 80, "web": "."}

    try:
        server = WebSocketServer(WebSocketEcho, **opts)
        server.start_server()
    except:
        pass
