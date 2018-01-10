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
FIRMWARE=esp8266-20171101-v1.9.3.bin

erase:
	$(ESPTOOL) --port $(PORT) erase_flash

flash:
	# for Wemos D1 mini Lite
	#$(ESPTOOL) --port $(PORT) --baud 115200 write_flash --verify -fm dout -fs detect -ff 40m 0x00000 $(FIRMWARE)        
	
	# for Wemos D1 mini Pro
	$(ESPTOOL) -p  $(PORT) write_flash -fm dio -fs detect 0 $(FIRMWARE)
	@echo 'Power device again'
