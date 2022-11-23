/*
   program device2
   percobaan komunikasi digital UART dan led sebagai tanda keberhasilan
*/
#include <SoftwareSerial.h> // library komunikasi UART

//========== Mendefinsikan konstanta ===========
#define L1 4 //pin arduino
#define L2 5 //pin arduino
#define L3 6 //pin arduino
#define L4 7 //pin arduino
#define NUM_LEDS 4 //jumlah led

#define MATI 0

//=========== member class ===========
SoftwareSerial SerialExternal(2/*rx*/, 3/*tx*/);
// SoftwareSerial = nama class
// SerialExternal = nama object class dari SoftwareSerial

int leds[NUM_LEDS] = {L1, L2, L3, L4}; // mengurutkan pin led dengan array
int data = 0; // deklarasi dan inisialisai
bool state = false;

void setup() {
  SerialExternal.begin(9600); // Mengatur kecepatan data dalam bit per detik (baud rate)
  Serial.begin(9600);
  for (int jn = 0; jn < 4; jn++) {
    pinMode(leds[jn], OUTPUT);
  }
  Serial.println("Welcome to module 4");
  Serial.println("device2 is running");
}
void loop() {
  if (SerialExternal.available()) {
    data = SerialExternal.read(); // membaca data yang masuk dari device1(max 1 byte)
    state = true;
  }

  Serial.println("data dari device1 = " + String(data));
  if (data > 0 && data <= NUM_LEDS) {
    Serial.print("LED1 = ");
    Serial.print((0x01 >> (data - 1)) & 1);
    Serial.print("\t LED2 = ");
    Serial.print((0x02 >> (data - 1)) & 1);
    Serial.print("\t LED3 = ");
    Serial.print((0x04 >> (data - 1)) & 1);
    Serial.print("\t LED4 = ");
    Serial.println((0x08 >> (data - 1)) & 1);
    // ============== KONDISI LED ===============
    digitalWrite(leds[0], (0x01 >> (data - 1)) & 1);
    digitalWrite(leds[1], (0x02 >> (data - 1)) & 1);
    digitalWrite(leds[2], (0x04 >> (data - 1)) & 1);
    digitalWrite(leds[3], (0x08 >> (data - 1)) & 1);
  }
  else {
    for (int z = 0; z < NUM_LEDS; z++) {
      digitalWrite(leds[z], MATI);
    }
    Serial.println("data tidak sesuai");
  }

  if (state) {
    state = false;
    SerialExternal.write(data); //kirim data(max 1 byte)
  }
  delay(250); // tunda program dalam mili detik
}
