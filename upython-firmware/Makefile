# Serial port configuration
# Windows
#PORT=/dev/cu.SLAB_USBtoUART
# MAC
#PORT=/dev/ttyACM0
# Linux Debian/Ubuntu

#PORT=/dev/tty.wchusbserial1420
PORT=/dev/tty.SLAB_USBtoUART
SPEED=115200
ESPTOOL=esptool.py
#FIRMWARE=esp8266-20171101-v1.9.3.bin
FIRMWARE=esp8266-firmware-combined-with-picoweb.bin
FIRMWARE32=esp32-20180125-v1.9.3-240-ga275cb0f.bin

erase:
	$(ESPTOOL) --port $(PORT) erase_flash

flash:
# for Wemos D1 mini Lite
#$(ESPTOOL) --port $(PORT) --baud 115200 write_flash --verify -fm dout -fs detect -ff 40m 0x00000 $(FIRMWARE)        

# for Wemos D1 mini Pro
# anything other than `-fs 32m` doesn't work at all it seems
# the board has 16Mb of flash but only 4MB are usable
# this is a micropython limitation, as the ESP SDK
# seems to support 16Mb flash just fine

	@echo 'Flashing $(FIRMWARE)'
	$(ESPTOOL) -p  $(PORT) write_flash -fm dio -fs 32m 0 $(FIRMWARE)
	@echo 'Power device again'


flash32:
# for Wemos LOLIN based on ESP32
	@echo 'Flashing $(FIRMWARE32)'

	$(ESPTOOL) --chip esp32 --port $(PORT) write_flash -z 0x1000 $(FIRMWARE32)
	@echo 'Power device again'


