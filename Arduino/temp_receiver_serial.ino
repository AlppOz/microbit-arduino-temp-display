/*
Displays the temperature in the serial
Made for Uno R4 Wifi model but might work on other Arduino models idk
*/

#include <Wire.h>

//Modify these constants as you need before embedding
const int SENTINEL = -1; //choose a value that you never expect to recieve from the microbit
const int SERIAL_CHANNEL = 9600; //display the serial monitor on this channel
const int IC = 13; //I2C slave address

volatile int received_value = SENTINEL;
volatile bool new_data_status = false;

void youve_got_mail(int doesnt_matter); //I2C receive callback: triggered automatically when Microbit sends data

void setup() {
  Serial.begin(SERIAL_CHANNEL); 
  Wire.begin(IC);
  Wire.onReceive(youve_got_mail);
}

void loop() {
  if (new_data_status) { //entering this path signifies the function fired fully. i.e. the wire is available
    if (received_value == SENTINEL) { //here the function fired but the value from the microbit couldn't be recieved
      Serial.println("Wire available but reading failed. Abort! Abort!");
    }
    else { //everything's fine yippie:
      Serial.println(received_value);
    }
    new_data_status = false; //resetting for the next loop
  }
}

void youve_got_mail(int doesnt_matter) {
  if (Wire.available()) {
    received_value = Wire.read();
    new_data_status = true;
  }
}
