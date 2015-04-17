
from thebutton import TheButton
#import gatt
import math
import serial
import time
import threading


class ButtonApp():
    def __init__(self):
        # connect to your Arduino via serial
        # Arduino can be found with ls /dev/tty* in LXTerminal
        self.ser = serial.Serial('/dev/ttyACM0',9600)
        self.the_button = TheButton()

        self.last_lowest = 60.0


    def run(self):
        # The WebSocketApp loop runs in it's own thread,
        # so make sure you call TheButton.close() when you're done with it!
        self.the_button.start()

        try:
            while True:
                #tmnw=round(self.the_button.current_time*10)
                tmnw=round((math.floor(self.the_button.current_time) + (1-((self.the_button.current_time-math.floor(self.the_button.current_time))/0.36)))*10) # weird calculation because of time.clock
                print tmnw
                tmnw2=str(round(tmnw)).rstrip('0').rstrip('.') # strip decimal places
                #print time.clock()
                self.ser.write(bytearray(tmnw2,'ascii')) # write deciseconds to serial
                #self.ser.write(tmnw)
                time.sleep(0.5) # necessary, or else serial will collapse. however this makes tmnw round to seconds, deciseconds get lost.
        except (KeyboardInterrupt,SystemExit):
            pass
        self.close()

    def close(self):
        # The Button WebSocketApp runs in it's own thread, so make sure it's closed. This also closes the socket
        self.the_button.close()


if __name__ == "__main__":
    button_app = ButtonApp()
    button_app.run()
