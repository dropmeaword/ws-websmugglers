import network
import socket
import time

# set our access point up
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid="MONKEY_ISLAND_0", authmode=network.AUTH_OPEN)

# we open a listening socket and bind it on port 80 (HTTP)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind( ('0.0.0.0', 80) )
s.listen(0)

print("I am listening now...")

# wait forever
while True:
	# if an incoming connection arrives, deal with it
	conn, addr = s.accept()
	print( "Got a visitor from {0}".format(str(addr)) )

	# read the contents of the request
	request = conn.recv(4096)
	# print the incoming request
	request = str(request)
	print("Our visitor requested this: ")
	print(request)
	# send back to the browser the success HTTP headers
	conn.sendall('HTTP/1.1 200 OK\n')
	conn.sendall('Connection: close\n')
	conn.sendall('Server: smugglersrv\n')
	conn.sendall('Content-Type: text/html\n\n')

	# after the headers we can send something to render
	conn.sendall("My name is Janus")
	conn.sendall("\n")

	conn.close()

	# we sleep for a little bit
	time.sleep(0.01)
