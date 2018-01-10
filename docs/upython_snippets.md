## Create AP

```
import network

ap_if = network.WLAN(network.AP_IF)
ap_if.config(essid="MONKEY_ISLAND", authmode=network.AUTH_OPEN)
```

