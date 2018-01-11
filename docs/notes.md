## Uploading files to the board

`ampy` will allow you to upload files, run scripts and transfer your website to the MCU. To use `ampy` you will have to install it first, like this:

```
pip install adafruit-ampy
```

see (ampy tutorial)[https://learn.adafruit.com/micropython-basics-load-files-and-run-code?view=all]

By default the run command will wait for the script to finish running on the board before printing its output.  In some cases you don't want this behavior--for example if your script has a main or infinite loop that never returns you don't want ampy to sit around waiting forever for it to finish.  In this case add the --no-output option to the run command.  This flag tells ampy not to wait for any output and instead just start running the script and return.

## uPython REPL

*REPL stands for Read Evaluate Print Loop* it is an interactive programming environment, many languages offer this way of interfacing with their runtime.

One of the great things of micropython is that it provides a REPL by default on the device you load it on and you can pretty much do everything you need from that REPL, however if you want your work to persist in between boots the REPL is not the right workflow.

Luckily micropython has an internal filesystem where we can upload our code sketches and store them in the device's flash memory along with other non-code files, this will allow us to build our webserver little by little.

## A REPL over the web

Let's use the serial interface to access the board's REPL and enabled the WebREPL feature so that we can use our browser to type in our code instead of the terminal.

```
import webrepl_setup
```


Since the ESP8266 is a WiFi enabled board that means that is capable of networking out of the box and is capable of acting as a Wifi access point. When you flash the board fresh, you will see that after resetting it will create an access point with name `MicroPython-<something>` where something is the unique ID of the board.

You can connect your computer to that Wifi network and when asked for a password you can enter `micropythoN`, with a capital *N*.

Now that you are connected to the board via Wifi, you can use the webrepl tool, to interface with the little Wemos board.

For more info [Adafruit WebREPL tutorial](https://learn.adafruit.com/micropython-basics-esp8266-webrepl/access-webrepl)

What is cool about having a REPL over the web is that you can program a microcontroller that literally sits on another country.

http://micropython.org/live/

```
# LCD output
import pyb
from pyb import Servo

lcd = pyb.LCD('Y')
lcd.light(True)
lcd.write('\n\n  YEAH HAMBURG!\n')

#s1 = Servo(1)
s2 = Servo(2)

# move to -60 degrees over 1.5 seconds
# speed up to a speed of 20 over 2 seconds
s2.speed(20, 1000)
pyb.delay(1000)
# speed up to a speed of 20 over 2 seconds
s2.speed(0)
```

## How to transfer files to my ESP8266?

The official way is by using the WebREPL file transfer tool: http://docs.micropython.org/en/latest/e ... ive-prompt . File transfers also supported directly by WebREPL HTML client. If WebREPL file transfer doesn't work [well] for you, or you just want to try other options, there're few community-supported alternatives:
- rshell
- mpfshell, http://forum.micropython.org/viewtopic.php?f=16&t=1652
- ampy
- ESPlorer, http://forum.micropython.org/viewtopic.php?f=16&t=1817 (may support file transfer in future versions)

## micropython documentation

http://docs.micropython.org/en/v1.9.3/esp8266/

## Boards

https://learn.adafruit.com/micropython-basics-what-is-micropython/overview?view=all#faq-9

## IDEs

* [ESPlorer](https://esp8266.ru/esplorer/)


## Materials list

|item|units|url|
|---|---|---|
|5x LIR2032 coin cell pack|25|https://www.knoopcelgigant.nl/knoopcel-batterijen/cr2032/camelion-cr2032-blister-5.html|
|Battery holder with switch|25|https://www.aliexpress.com/item/2x3V-CR2032-Coin-Cell-Button-Battery-Holder-Case-Black-Wire-Lead-With-ON-OFF-Switch/32829655213.html?spm=2114.search0104.3.47.mvY1Zi&ws_ab_test=searchweb0_0,searchweb201602_4_10152_10151_10065_10344_10068_10342_10343_10059_10340_10314_10341_10534_100031_10084_10604_10083_10103_10304_10307_10301_10142,searchweb201603_36,ppcSwitch_5&algo_expid=0a188b7b-6df2-4ae9-b25b-3ec1bb0efda0-7&algo_pvid=0a188b7b-6df2-4ae9-b25b-3ec1bb0efda0&priceBeautifyAB=0|
|Battery holder with switch (opt #2)|25|https://www.banggood.com/3V-ONOFF-Switch-Cover-CR2032-Button-Battery-Holder-Case-Box-p-960984.html|
|Wemos D1 mini v3|25|https://opencircuit.nl/Product/12095/WeMos-D1-mini-V3-Wifi-Module or https://www.tinytronics.nl/shop/nl/arduino/wemos/wemos-d1-mini-v2-esp8266-12f-ch340?search=Wemos|
|USB data cable|25|n.a.|

Where to buy:

Pro: 
https://paradisetronic.com/de/nodemcu/wemos-d1-mini-pro-esp8266ex
https://eckstein-shop.de/WeMos-D1-mini-Pro-WiFi-Board-ESP8266-NodeMcu-CP2104-mit-IPEX-Stecker

NodeMCU:
https://paradisetronic.com/de/nodemcu/wemos-d1-mini-nodemcu-esp8266
??? http://www.watterott.com/de/NodeMcu-Lua-WIFI-Board-Based-on-ESP8266-CP2102-Module
http://www.watterott.com/de/NodeMcu-Lua-WIFI-Board-Based-on-ESP8266-CP2102-Module


Battery holder:
https://www.reichelt.de/Batteriehalter-fuer-Knopfzellen/2/index.html?ACTION=2&GROUPID=4260;SID=94Wk7D%40KwQAT8AAGcXyDkc4d14bbc4cb2fa0f11c0cacdffe7b854


CH340G driver:
https://paradisetronic.com/de/treiber

### Getting my computer ready to work with the Wemos

During this workshop we will use various tools to be able to write and upload software into our microcontroller, but let's start with the basics. At first we will use a command line utility called `esptool`, this might seem a bit tricky to use at first but it will give us an understanding of how to operating system talks to our board. To install `esptool` run:

```
$ pip install esptool
```

Once it installs successfully run it and read the help text that it presents to you as a default output. It will probably look something like this:

```
usage: esptool [-h] [--chip {auto,esp8266,esp32}] [--port PORT] [--baud BAUD]
               [--before {default_reset,no_reset}]
               [--after {hard_reset,soft_reset,no_reset}] [--no-stub]
               [--trace]

               {dump_mem,chip_id,write_mem,run,load_ram,make_image,write_flash_status,flash_id,version,read_mac,read_flash,read_mem,erase_region,image_info,read_flash_status,elf2image,erase_flash,verify_flash,write_flash}
               ...
esptool: error: too few arguments
```

As you can see, the last line reads: `esptool: error: too few arguments` this tells us that we didn't provide this `esptool` with the parameters it needs to do its job. It probably doesn't know how to find our board and what to put in it.

### DRY: use a Makefile

Software people do not like typing and they do not like to repeat things over and over. If you see yourself doing the same thing many times there's probably a shortcut or an easier, less repetitive way of doing it. We call this the *DRY principle* for _"Don't Repeat Yourself"_. In this case we are going to use one of the many ways of scripting that is available to us, the _Makefile_. Makefiles are to programming what binding glue is to bookmaking.

```
# tested on a Wemos D1 mini lite 1.0.0
# (cc) zilog <root@derfunke.net>
#
# @note -fm dout .:. must be dout, any other flashing_mode will not work on the Wemos :/

# Serial port configuration
# Windows
#PORT=/dev/cu.SLAB_USBtoUART
# MAC
#PORT=/dev/ttyACM0
# Linux Debian/Ubuntu
PORT=/dev/tty.wchusbserial1420
BAUDRATE=115200
ESPTOOL=esptool.py
FIRMWARE=esp8266-20171101-v1.9.3.bin

erase:
	$(ESPTOOL) --port $(PORT) erase_flash

flash:
	@echo "Be sure about MEMORY SIZE"
	$(ESPTOOL) --port $(PORT) --baud $(BAUDRATE) write_flash --verify -fm dout -fs detect -ff 40m 0x00000 $(FIRMWARE)        
	@echo 'Power device again'
```

This makefile can automate two tasks for us: `erase` which will wipe out the memory of our little Wemos and `flash` which will upload our python-compatible firmware into the board.

### What is flashing?

Devices that have and embedded software called firmware are often "flashed", for example if you have ADSL internet at home you probably have a router, a router is basically a computer running the firmware of its manufacturer. When we update that firmware we are essentially flashing its chip. Flashing is a persistent operation, that means that if we remove power from the device and power it back up again it will run the latest firmware we flashed.

### Where is your microcontroller?

Most microcontrollers that come in prototyping platforms have a chip on them that interfaces to your computer through a protocol called `serial`. If your operating system has the appropriate drivers to speak to the device in question, it will *mount* a serial device as a *COM port*, on Windows or as part of the `/dev` filesystem in Unix derivatives (Linux or OSX). This so-called mountpoint is the way the system represents the device to make it accessible in *user space*.

Try to find your microcontroller's representation in the system now.

### Making my Wemos speak python

To be able to program the Wemos in the python language we need to flash the MCU with a teeny version of python called [micropython](http://micropython.org). You can flash other things into the Wemos too, you can even write your own software from scratch and flash that too if you like. The ESP8266 inside of the Wemos is a general computation device and it can run pretty much anything you through at it as long as it can run within the (very) constrained limitations of such teeny device.

Back to python.

You will need to download a binary file from the [micropython downloads area](http://micropython.org/download/) named `esp8266-20171101-v1.9.3.bin`. This file contains a new firmware for the ESP8266 chipset that implements python.

If the flashing process terminated ok, we will need to power-cycle our Wemos. You can use the reboot button on the side for that.

### How to know if we succeeded?

###### Linux/OSX
To look _inside_ of our wemos we need to use a serial terminal emulator, if you run OSX or linux you can use the program called `screen` from your command line, like this:

```
$ screen /dev/tty.SLAB_USBtoUART 115200
```

Where the part that says `/dev/tty.SLAB_USBtoUART` is just the location of the Wemos as your computer sees it. In Unix-family systems serial devices normally hide somewhere in `/dev/tty...`.

The `screen` command is very powerful but is fairly awkward to use and has a steep learning curve. For now we just need to know how to open a session using the command above and how to quit to quit you can use <kbd>ctrl</kbd> + <kbd>a</kbd> and then <kbd>ctrl</kbd> + <kbd>k</kbd>, then it will ask you if you want to kill the window. You can use this moment to ponder about the meaning of *kill* in this context, or you can just press <kbd>y</kbd> to exit.

###### Windows

Windows lacks a terminal emulation program so you need a third party program like PuTTY. You can download it from (PuTTY's homepage)[https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html].

Using your serial program you must connect to the COM port that you found in the previous step. With PuTTY, click on “Session” in the left-hand panel, then click the “Serial” radio button on the right, then enter you COM port (eg COM4) in the “Serial Line” box. Finally, click the “Open” button.

## Powering your project

 Regular CR2032 will not be quite enough, these batteries operate at 3V and can't really deal with peaks very well, which we need for a MCU. There is another chemistry called LIR2032 (for Li-Ion Rechargeable) which comes in the same package and has an operating voltage of 3.6V these will be able to power your MCU for about 1h in full use.

#### Saving battery life

In wearable applications you want to be able to run your project with as little power consumption as possible, the ESP8266 chipset has a bunch of power-saving features.

![ESP power saving modes](https://www.losant.com/hs-fs/hubfs/Blog/deep_sleep/esp8266_sleep_options.png?t=1515102772300&width=1280&name=esp8266_sleep_options.png)


## Some references
* [Getting started with uPython on the Wemos](http://garybake.com/getting-started-with-the-wemos-d1-and-micropython.html)
