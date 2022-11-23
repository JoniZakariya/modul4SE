/*program Master*/
#include <Wire.h>

#define SLAVE_ADDR 35 // NIM 2 digit dari belakang

int data = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(); //inisialiasi arduino sebagai master
  Serial.println("welcome to module 4");
  Serial.println("device master");
}

void loop () {
  if (Serial.available()) {
    data = Serial.read(); // baca data serial(1 byte)
    data -= 48; // lihat kode ascii
  }
  //=====send data from master======
  Wire.beginTransmission(SLAVE_ADDR);//menentukan alamat yang dituju
  Wire.write(data); //menulis data untuk dikirim.
  Wire.endTransmission(); //mengakhiri transmisi dengan mengirim address dan data

  //====request data from slave=====
  Wire.requestFrom(SLAVE_ADDR/*alamat tujuan*/, 1/*request berapa byte*/);// melakukan request data from slave
  if (Wire.available()) { // jumlah byte data yang diterima
    int dataFromSlave = Wire.read(); // membaca data dalam 1 byte
    Serial.println("data dari slave = " + String(dataFromSlave));
  }
  delay(250);
}
