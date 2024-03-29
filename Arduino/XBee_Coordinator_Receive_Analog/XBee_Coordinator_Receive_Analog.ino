// XBee_Coordinator_Receive_Analog.ino
// Author: Fosse Lin-Bianco
// Purpose: To receive analog data from a Coordinator XBee
//    and print DECIMAL value to Serial Monitor.
// Hardware: 1) XBee Series 3 + XBee Shield + Arduino RedBoard

#include <SoftwareSerial.h>

char startByte = 0x7E;
int dataCount = 0;
byte analog_MSB;
byte analog_LSB;
int analog_reading_Z;
int analog_reading_Y;
int analog_reading_X;

// * calibrated values - CHNAGE THESE VALUES BEFORE EACH TEST *
int Z_accel_at_rest = 550;
int Y_accel_at_rest = 547;
int X_accel_at_rest = 433;

// foot on wall position
//int Z_accel_at_rest = 518;
//int Y_accel_at_rest = 401;
//int X_accel_at_rest = 494;

SoftwareSerial XBee(2, 3); // XBee DOUT, IN - Arduino pin 2, 3 (RX, TX)

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
  establishContact();
}

void loop() {
  if (XBee.available()) {
    char current = XBee.read();
    if (current == 0x7E) {
//      Serial.println();
//      Serial.println();
//      Serial.println("Start:");
      dataCount = 0;
    }

    dataCount++;

// * to view entire package of bytes coming in *
//    Serial.print(current, HEX);
//    Serial.print(",");
    
// * to view parsed out analog data *
    if (dataCount == 12) {
      analog_MSB = current;
    } else if (dataCount == 13) {
      analog_LSB = current;
      analog_reading_Z = (analog_MSB * 256) + analog_LSB;
      analog_reading_Z -= Z_accel_at_rest;
      Serial.print(analog_reading_Z);
      Serial.print("\t");
    } else if (dataCount == 14) {
      analog_MSB = current;
    } else if (dataCount == 15) {
      analog_LSB = current;
      analog_reading_Y = (analog_MSB * 256) + analog_LSB;
      analog_reading_Y -= Y_accel_at_rest;
      Serial.print(analog_reading_Y);
      Serial.print("\t");
    } else if (dataCount == 16) {
      analog_MSB = current;
    } else if (dataCount == 17) {
      analog_LSB = current;
      analog_reading_X = (analog_MSB * 256) + analog_LSB;
      analog_reading_X -= X_accel_at_rest;
      Serial.print(analog_reading_X);
      Serial.print("\n");
    }
  } else {
    //sendRandomData();
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("A");
    delay(300);
  }
}

void sendRandomData() {
  Serial.print(int(random(0, 1024)));
  Serial.print("\t");
  Serial.print(int(random(0, 1024)));
  Serial.print("\t");
  Serial.print(int(random(0, 1024)));
  Serial.print("\n");
  delay(100);
}
