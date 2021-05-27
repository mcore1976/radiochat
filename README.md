# radiochat
This is simple 2 WAY radio chat device built from Digispark (ATTINY85) + FS1000A + MX-PM-5V modules. Allows "IRC" like radio communication between several PC connected to 433MHz/315MHz frequency. 

This device allows na SIMPLEX but 2 WAY radio communication on ISM band.  Digispark is connected to PC ( Linux / Windows) with CDC USB-to-Serial Port driver and allows to use Putty terminal for radio chatting. Characters from PuTTY are handled by DIGICDC library and further sent/received via FS1000A/MX-PM-5V modules with use of VirtualWire library. Allows for texting between group of people using same type of device. Remember that this communication is unencrypted.

connections 
- (transmitter module )  FS1000A DATA PIN <==> PIN P2 Digispark - #2
- (receiver module)   MX-PM-5V DATA PIN <==> PIN P0 Digispark - #0
- GND, 5V taken from Digispark pins have to be connected to both FS1000A/MX-PM-5V pins GND, VCC
- Please attach 17cm antenna to both transmitter and receiver modules

