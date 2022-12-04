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
  for (uint8_t indx = 0; indx < NUM_LEDS; indx++) {
    pinMode(leds[indx], OUTPUT);
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
    uint8_t bin[NUM_LEDS] = {0b0001, 0b0010, 0b0100, 0b1000};
    --data;
    // ============== KONDISI LED ===============
    for (uint8_t j = 0; j < NUM_LEDS; j++) {
      uint8_t val = (bin[j] >> data) & 1;
      Serial.print("LED" + String(j + 1) + " = " + String(val) + " \t");
      digitalWrite(leds[j], val);
    }
    Serial.println();
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
