import network
import picoweb

app = picoweb.WebApp(__name__)

@app.route('/')
def index(req, resp):
	yield from picoweb.start_response(resp)
	yield from resp.awrite("My name is Janus")


# set our access point up
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid="MONKEY_ISLAND_0", authmode=network.AUTH_OPEN)

app.run(debug=True, port=80)

# picoweb/picoweb -> lib/picoweb