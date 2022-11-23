/*
   program device1
   percobaan komunikasi digital UART dan led sebagai tanda keberhasilan
*/
#include <SoftwareSerial.h>

SoftwareSerial SerialExternal(2, 3);

int data = 0;
bool state1 = 0;
bool state2 = 0;

void setup() {
  SerialExternal.begin(9600);
  Serial.begin(9600);
  Serial.println("Welcome to module 4");
  Serial.println("device1 is running");
}

void loop() {
  if (Serial.available()) {
    data = Serial.read(); // baca data (max 1 byte)
    data -= 48;//lihat kode ascii, tentang karakter dan desimal
    state1 = 1;
  }
  if (state1) {
    SerialExternal.write(data); // kirim data(max 1 byte)
    state1 = 0;
  }
  int d_device2 = 0;
  if (SerialExternal.available()) {
    d_device2 = SerialExternal.read();
    state2 = 1;
  }
  if (state2) {
    Serial.println("data dari device2 = " + String(d_device2));
    state2 = 0;
  }
  delay(250);
}
