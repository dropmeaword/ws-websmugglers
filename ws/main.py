import network
import socket
import os

# set our wifi access point up
ap = network.WLAN(network.AP_IF)
ap.config(essid="MONKEY_ISLAND", authmode=network.AUTH_OPEN, channel=11)

def http_request_parse(raw):
    """
    Totally *NOT* RFC 2145 compliant
    """
    if raw:
        parts = raw.split()
    else:
        print("400 Bad request")

    if not parts[0] or not parts[1] or not parts[2]:
        print("400 Bad request")
        return None, None, None

    retval = None
    try:
        retval = (parts[0], parts[1], parts[2])
    except IndexError as e:
        print("400 Bad request")

    return retval


# open a socket on port 80 and listen
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('0.0.0.0', 80))
s.listen(0)

# serve forever
while True:
    conn, addr = s.accept()
    print("Got a connection from %s" % str(addr))
    request = conn.recv(4096)

    # parse request
    request = str(request)
    print("Our visitor requested %s" % str(request))

    command, path, version = http_request_parse(request)

    if path == '/':
        conn.sendall('HTTP/1.1 200 OK\n')
        conn.sendall('Connection: close')
        conn.sendall('Server: smugglesrv\n')
        conn.sendall('Content-Type: text/html\n\n')

        # send body
        conn.sendall('<h2>My name is Janus</h2>')
        conn.sendall('\n')
    else:
        try:
            with open(path, 'r') as html:
                # send response headers back to client
                conn.sendall('HTTP/1.1 200 OK\n')
                conn.sendall('Connection: close')
                conn.sendall('Server: smugglesrv\n')
                conn.sendall('Content-Type: text/html\n\n')
                for line in html:
                    conn.send(line)
                html.close()
        except OSError:
            conn.sendall('HTTP/1.1 404 Not Found\n')
            conn.sendall('Connection: close')
            conn.sendall('Server: smugglesrv\n')
            conn.sendall('Content-Type: text/html\n\n')
            conn.sendall('<h1>404 - you have entered the void</h1>')

    # close connection
    conn.close()

    # we keep no further information
    # HTTP is a stateless protocol
