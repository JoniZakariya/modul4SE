/*program Slave*/
#include <Wire.h>

#define SLAVE_ADDR 35 //NIM 2 digit dari belakang
#define L1 4 //pin arduino
#define L2 5 //pin arduino
#define L3 6 //pin arduino
#define L4 7 //pin arduino
#define NUM_LEDS 4 //jumlah led

int leds[NUM_LEDS] = {L1, L2, L3, L4};

volatile int data = 0;

/*== fungsi baca data yg diperoleh dari master ===*/
void receive(int wiresize) {
  if (Wire.available()) {
    data = Wire.read();
  }
}
/*== fungsi tulis data untuk dikirim ke master ===*/
void request() {
  Wire.write(data);
}

void setup() {
  Serial.begin(9600);
  for (uint8_t indx = 0; indx < NUM_LEDS; indx++) {
    pinMode(leds[indx], OUTPUT);
  }
  Wire.begin(SLAVE_ADDR); // memulai device(arduino) sebagai slave
  Serial.println("welcome to module 4");
  Serial.println("device slave");
  Wire.onReceive(receive);//fungsi yang dijalankan ketika master mengirim data to slave
  Wire.onRequest(request);//fungsi yang dijalankan ketika master meminta data to slave
}

void loop () {
  Serial.println("data dari master = " + String(data));
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
    for (uint8_t j = 0; j < NUM_LEDS; j++) {
      digitalWrite(leds[j], 0);
    }
    Serial.println("data tidak sesuai");
  }
  delay(250);
}
