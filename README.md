# thebuttonpixelstrip

### example.py
ALPSquid /r/thebutton Python client modified for Adafruit Neopixel Strip 144.

### requirements
Works with Python 2.7 and Raspbian (Wheezy) on Raspberry Pi B+.
Arduino connected via USB.

### how to install and run on Rasp Pi:

-sudo apt-get install python-serial
-[download https://bootstrap.pypa.io/get-pip.py ]
-sudo python get-pip.py
-sudo pip install enum34
-sudo pip install websocket-client
-python example.py

### Arduino/Neopixel: 

- compile and upload ino-file to arduino
- connect Ground to Ground on Powersupply
- connect PIN 6 to DATA on Neopixel Strip
- connect 5V Powersupply to V+ and V- on Strip


### to do

- print and send correct deciseconds over serial
- format and proofread this readme
- show last / lowest value
