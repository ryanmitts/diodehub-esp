<p align="center">
  <img src="img/diodehub.png" alt="DiodeHub Logo"/>
</p>

# DiodeHub ESP32 Firmware

[DiodeHub](https://diodehub.com) ESP32 firmware.

Firmware to run on an ESP32 WiFi module to drive individually addressable light strips, like the WS2812B, that can be controlled over the internet.

The ESP32 chip connects using HTTPS to a WebSocket server where light control messages can be sent from the internet.

I am making this to work specifically with my site, [DiodeHub](https://diodehub.com), but the source code is here that you could setup your own server solution to have the lights connect to if you follow the API to talk to the ESP module over the socket.

## Motivation

I wanted to have these light strips in my basement after seeing them online. Originally I used just a standard Arduino UNO to drive the lights, but going into the ceiling to flash a new sketch to change how the lights look was inconvenient. I wanted a way I could control them from the couch to any effect I wanted.

## What You Need

### Light Strip

You will need a WS2812B light strip. I buy mine off Amazon if I need just one, or off Alibaba or Aliexpress if ordering more than one and can wait weeks.

I only have ever used the WS2812B light strips since they seem to be the easiest to get a hold of and use. Since I am using the [FastLED](http://fastled.io/) library to drive the lights, I'm sure this firmware could be modified to control other light sets too.

I have the LED color buffer set to hold up to 2096 LEDs worth of colors to drive, but I have not hooked up this many lights. I don't think driving this many would be reasonable in this setup as the time to write out that many lights would likely make most effects too slow to be enjoyable, and the amount of power that would consume you would need to have multiple power supplies along the light run. Driving multiple strings at once independently would probably be more feasible, but I have not tried that.


### Power Supply

You must have an adequate 5V power supply to power the light set. The WS2812B addressable lights use RGB 5050 LED modules. Each color (RGB) can draw at full power 20mA. Thus each light on full brightness would draw 60mA. If you had a 4 meter strip of 240 lights, this would mean the potential current draw is 14.4A. Much higher than most household 5V power supplies I have seen are able to provide.

I find the full brightness to be extremely bright and unnecessary for my usual use, so I have set lights to only output at half brightness in the FastLED library. This allows you to specify your RGB colors in the usual 0-255 range, and have the brightness automatically scale as the control signals for the lights are generated.

The human high does not perceive brightness linearly, so I find this change not very noticeable and can reduce my current draw by about half. Granted, this is if the lights are displaying solid white -- at half brightness as described, and displaying the rotating rainbow effect, my 240 light strip appears to draw 4.5A roughly from the supply.

So I bought a 10A 5v power supply for my use case. Just please keep this in mind if adjusting the brightness and you have a large light strip.

Most of the supplied that meet these specs look something like [this](https://www.amazon.com/Aiposen-Transformer-Security-Computer-Project/dp/B01B1QKLR8/ref=sr_1_2_sspa?crid=35EZ0OVPPORZS&keywords=5v+10a+power+supply&qid=1551851169&s=gateway&sprefix=5v+10a%2Caps%2C194&sr=8-2-spons&psc=1). You have to hookup an AC power cord yourself and run the wire output of your lights to the output terminals.

### ESP32 Module

You will need an ESP32 module on which you can flash the firmware to operate the light strip.

I use and have been developing with the [ESP32-DevKitC V4](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/get-started-devkitc.html). I buy mine from [Mouser](https://www.mouser.com/) as they are only $10 each, but you have to pay for shipping, or you can buy them on Amazon.

I'm sure other development boards for the ESP32 that you can find will also work. I soon will have a WROOVER one to test on as well.

I am also working to make my own PCB with the ESP32 module to have this run on too. The draft schematics and Gerber files are in this repository.

### A Way to Control The Lights

The firmware on this chip connects to a server over a WebSocket, and light control messages in JSON format are sent to the lights to instruct a light effect to display.

I am working on a website for this, [DiodeHub](https://diodehub.com) where you can sign up, add a device to register, setup your device, and use the interface to create preset effects to send to your lights.

I am also working on an example NodeJS server you can run to test locally with your light setup.

## Installation

If you wish to install the firmware onto an ESP32 device without setting up the entire build environment to do so.

### Install ESPTool

This is the flashing utility provided by the chip manufacturer, Esprissif, to be able to flash the chips.

The tool is [here](https://github.com/espressif/esptool), and following the "Easy Installation" works well, just make sure you have Python installed first.

You should be able to run `esptool.py` from your terminal after installing this.

### Download Firmware

From the releases page of this repository, download the four `.bin` files that need to be flashed onto your chip.

Place these all into one folder.

### Get Ready to Flash

If you are using the DevKit ESP32, plug the USB cable into your computer and identify the port for which it was assigned. On Windows this will be a `COMX` value, and on OSX/Linux it will be `/dev/ttyUSB0` or something.

### Flash

Run the following command, replacing the portion noted with your port.

`esptool.py --chip esp32 --port {your port, COM5, /dev/ttyUSB1, etc.} --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0xe000 ota_data_initial.bin 0x1000 bootloader.bin 0x10000 diodehub-esp.bin 0x8000 default.bin`

## Setup

Once the firmware is on the chip you must set up the chip to communicate with the WebSocket server. To do so you must:

1. Enter your home WiFi SSID and password.
2. Enter the `clientId` and `clientSecret` that the lights will register with the server with. This acts as the devices username and password.
3. How many LEDS the module is controlling.

The chip, by default will communicate with DiodeHub, and if you login you can generate a clientId and clientSecret for your account. You can use this in the device setup.

When the device is done flashing, it should enter configuration mode. If not, trying powering the chip off and on again.

Using your computer, you can connect to the chip using WiFi. The chip will have an SSID of `DiodeHub-x`. Once connected, you may be prompted automatically to the configuration page, if not, you can browser to `192.168.4.1`.

On this page, you can configure the device.

Once configured, the device will restart and be ready to-go. You can now reconnect your your normal WiFi connection.

## Control

Now the device is ready to receive control from DiodeHub, or your own server if you are using the device in that way.
