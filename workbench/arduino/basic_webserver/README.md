Arduino-based webserver for the Wemos D1 mini pro.

Tried doing this in python without success as most webserver libraries crash the Wemos due to lack of RAM.I also tried this one [FSBrowserNG](https://github.com/gmag11/FSBrowserNG) without any luck, seems like a great library but didn't succeed at servicing files directly from SPIFFs.


### Compiling

###### Step 1
You will need ESP8266 support in your Arduino environment, you can use the *board manager* to install it by entering this url in your board manager: `http://arduino.esp8266.com/versions/2.3.0/package_esp8266com_index.json`

###### Step 2
Install the SPIFFs upload tool in your Arduino environment: https://github.com/esp8266/arduino-esp8266fs-plugin

Got this implementation from this documentation: https://tttapa.github.io/ESP8266/Chap11%20-%20SPIFFS.html

This might work as well but it ain't tested: https://github.com/esp8266/ESPWebServer/blob/master/examples/FSBrowser/FSBrowser.ino

