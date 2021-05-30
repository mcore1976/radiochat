// RADIOCHAT - DIGISPARK + FS1000A + MX-PM-5V
// ALLOWS UNENCRYPTED 2 WAY (HALF DUPLEX) 
// COMMUNICATION ON ISM BAND
// DEVICE APPEARS AS CDC USB-TO-SERIAL PORT
// IN OPERATING SYSTEM 
// connections to be made 
// (transmitter) FS1000A DATA PIN to PIN P2 Digispark - 2
// (receiver)   MX-PM-5V DATA PIN to PIN P0 Digispark - 0


#include <DigiCDC.h>
#include <VirtualWire.h>
#define LEDPIN  1
#define RADIO_TX_PIN  2
#define RADIO_RX_PIN  0
#define RADIO_SPEED   1200

void setup() {                
  // initialize the digital pin as an output.
  SerialUSB.begin();
  // initialize VirtualWire RX and TX pins, the speed
  // Port 0 is RX pin from 433MHz module 
  vw_set_rx_pin(RADIO_RX_PIN);
  // Port 2 is TX pin from FS1000A 433MHz module
  vw_set_tx_pin(RADIO_TX_PIN);
  // set the radio transmission speed 
  vw_setup(RADIO_SPEED);
  // initialize built in Digispark LED for diagnostics
  pinMode(LEDPIN, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {

  // buffer for receiving radio data 
   uint8_t buf[8];
   uint8_t buflen = 8;
 
  if (SerialUSB.available()) {
    uint8_t usbinput = SerialUSB.read();         // read character from USB serial port
     digitalWrite(LEDPIN, HIGH);                 // LED ON
     vw_send(&usbinput, 2);                      // send single character with FS1000A module
     vw_wait_tx();                               // wait for sending character over radio       
     SerialUSB.write(usbinput);                  // write an ECHO on terminal   
     if (usbinput == 13)  SerialUSB.write(10);   // send CRLF in terminal
     digitalWrite(LEDPIN, LOW);   // LED OFF
  }
  
   // activate radio for receiving packets 
   vw_rx_start();

  // vw_wait_rx_max(50);                          // wait 50miliseconds for radio reception
   if (vw_get_message(buf, &buflen)) 
      {
        // if there is anything received over radio then...
        digitalWrite(LEDPIN, HIGH);               // LED ON
        SerialUSB.write(buf[0]);                  // send it over USB to the terminal 
        if (buf[0] == 13)  SerialUSB.write(10);   // send CRLF in terminal
        digitalWrite(LEDPIN, LOW);                // LED OFF
      }
  
   SerialUSB.refresh();               // keep usb alive can also use SerialUSB.delay();
}
