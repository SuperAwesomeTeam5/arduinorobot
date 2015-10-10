
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/

byte addresses[][6] = {"1Node","2Node"};

// Used to control whether this node is sending or receiving
bool role = 1; //Sender

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node")); 
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() {

  uint8_t readBuf[3]= {0,0,0};
  
  
/****************** Ping Out Role ***************************/  
 
    radio.stopListening();                                    // First, stop listening so we can talk.
    
    if(Serial.available() >= 3)
    {
        Serial.readBytes(readBuf,3);
        Serial.print(readBuf[0]);
        Serial.print(readBuf[1]);
        Serial.print(readBuf[2]);

        radio.write(readBuf, 3);              // Send the final one back. 
        Serial.println("Sent to radio");        
    }

//      readBuf[1] = 0;
//      readBuf[2] = 255;
//      readBuf[3] = 255;
//      radio.write( &readBuf, 3);              // Send the final one back. 



} // Loop

