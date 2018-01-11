# micropython snippets

board diagnostics:

```
import port_diag
```

## WiFi (mode: STATION)
Connecting to WiFi:

minimal:
```
import network

station = network.WLAN(network.STA_IF)
station.active(True)
station.connect("SSID", "password")
station.isconnected()
```

scan for visible WiFi networks:

```
import network

station = network.WLAN(network.STA_IF)
station.scan()
```

wrapped:

```
import network
 
def connect():
  ssid = "SSID"
  password =  "password"
 
  station = network.WLAN(network.STA_IF)
 
  if station.isconnected() == True:
      print("Already connected")
      return
 
  station.active(True)
  station.connect(ssid, password)
 
  while station.isconnected() == False:
      pass
 
  print("Connection successful")
  print(station.ifconfig())
```

### Getting network configuration:

```
ap.ifconfig()
```

Will show us our device's IP, netmask, gateway IP and DNS address.

To get the device's MAC address:

```
import network
import ubinascii
mac = ubinascii.hexlify(network.WLAN().config('mac'),':').decode()
print(mac)
```



## WiFi (mode: AP)

Creating an AP:

```
import network

ap = network.WLAN(network.AP_IF)
ap.config(essid="MONKEY_ISLAND", authmode=network.AUTH_OPEN, channel=11)
print(ap.config('essid'))
print(ap.config('channel'))
```

## Libraries

Installing libraries:

```
import upip
upip.install('picoweb')
```

This might throw an error because some of the dependencies will fail to install, it will complain that install might be incomplete. We can verify the install by typing:

```
import os
os.listdir('lib')
```


### Picoweb webserver


```
import picoweb
import uasyncio
import pkg_resources

app = picoweb.WebApp(__name__)

@app.route("/")
def index(req, resp):
    yield from picoweb.start_response(resp)
    yield from resp.awrite("Hello world from picoweb running on the ESP32")

app.run(debug=True, host = "192.168.1.87", port="80")
```

The port defaults to 8081, if we don’t pass this argument. The host defaults to 127.0.0.1 if we don’t specify it. In our case, we will not specify the port, and thus use the default 8081.


## DNS

https://github.com/jczic/MicroDNSSrv
https://github.com/jczic/MicroWebSrv

https://github.com/yschaeff/ICantBelieveItsNotDNS


## Web server

Simplest possible:

```
import network
import socket

# set our wifi access point up
ap = network.WLAN(network.AP_IF)
ap.config(essid="MONKEY_ISLAND", authmode=network.AUTH_OPEN, channel=11)

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

    # send response headers back to client
    conn.sendall('HTTP/1.1 200 OK\n')
    conn.sendall('Connection: close')
    conn.sendall('Server: smugglesrv\n')
    conn.sendall('Content-Type: text/html\n\n')

    # send body
    conn.sendall('My name is Janus')
    conn.sendall('\n')

    # close connection
    conn.close()

    # we keep no further information
    # HTTP is a stateless protocol
```

A simple request parser:

```
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
```

Modify our server:

```
    [...]

    # send response headers back to client
    conn.sendall('HTTP/1.1 200 OK\n')
    conn.sendall('Connection: close')
    conn.sendall('Server: smugglesrv\n')
    conn.sendall('Content-Type: text/html\n\n')

    command, path, version = http_request_parse(request)

    # send body
    conn.sendall('<h2>My name is Janus</h2>')
    conn.sendall("path: {0}".format(path))
    conn.sendall('\n')

    [...]
```

serving actual HTML files, change send body:

```
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
        
```

complete minimal web server:

```
import network
import socket
import os

# set our wifi access point up
#ap = network.WLAN(network.AP_IF)
#ap.config(essid="MONKEY_ISLAND", authmode=network.AUTH_OPEN, channel=11)

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
```

Send HTTP status codes:

```
def send_200_ok(conn):
    conn.sendall('HTTP/1.1 200 OK\n')
    conn.sendall('Connection: close')
    conn.sendall('Server: smugglesrv\n')
    conn.sendall('Content-Type: text/html\n\n')

def send_400_not_found(conn):
    conn.sendall('HTTP/1.1 404 Not Found\n')
    conn.sendall('Connection: close')
    conn.sendall('Server: smugglesrv\n')
    conn.sendall('Content-Type: text/html\n\n')
    conn.sendall('<h1>404 - you have entered the void</h1>')
```

See: https://httpstat.us/

