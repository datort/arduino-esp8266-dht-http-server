# Arduino ESP8266 DHT HTTP Server

## What's this about

This sketch was written to work on a NodeMCU V3.4 dev board. It reads temperature and humidity data from the wide-spread DHT sensors and serves this data via a HTTP server. 

## Prerequisites

In order to use this sketch, you'll have to install the required libraries to build it with your Arduino IDE: 

What you need besides the defaults: 

* DHT sensor library by Adafruit (v1.3.10)
* ArduinoJson by Benoit Blanchon (v6.16.1)

(All installed via the "Manage Libraries" menu)

To connect and use the NodeMCU board with it's ESP8266 chipset I used the Addional Board Manager URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`. That should bring some required libs, too. 


## Configuration

In order to get this thing connected to your Wifi you'll have to add your Wifi credentials. Checkout the `setup()` for this:

`wifiMulti.addAP("SSID1", "wifipassword1");`

The `addAP()` method enables you to supply multiple Wifi connections. This is useful if you have multiple access points around your house. The network with the best reception will automatically be choosen on startup. 


## Retrieve Data

After startup an IP address will be assigned by your DHCP server. You can see the address by opening the Arduino Serial Monitor. It should print something like this: 

```
Connected to YourWifiSSID
IP address:	192.168.178.48
mDNS responder started
HTTP server started
```

You can use this IP address to connect to the board. Besides that, the wifi client tries to setup mDNS to make the device available at `temp-sens-01.local`. But this may not work with all Wifi setups. Connecting using the IP is probably the safest way to do so. 


### Plain temperature (e.g. for Homebridge integration)

If you connect to the root of your device with your PCs browser over HTTP you'll get the current temperature in Celsius, e.g.

`GET http://device-ip/` -> `23.4`

### JSON data

A second option is to retrieve the data as a JSON object. It also returns the humdity value: 

`GET http://device-ip/json` -> `{"temperature":25.4,"humidity":42.2}`


### Additional info / License

This software is as is. It's written to my special requirements and may hopefully be useful for some one out there. It's featured in my little [YouTube Video](https://www.youtube.com/watch?v=fCwX3DTReXo). Feel free to do whatever you want with this piece of software.