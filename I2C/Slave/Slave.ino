/*program Slave*/
#include <Wire.h>

#define SLAVE_ADDR 35 //NIM 2 digit dari belakang
#define L1 4 //pin arduino
#define L2 5 //pin arduino
#define L3 6 //pin arduino
#define L4 7 //pin arduino
#define NUM_LEDS 4 //jumlah led

int leds[NUM_LEDS] = {L1, L2, L3, L4};

int data = 0;

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
  for (int x = 0; x < 4; x++) {
    pinMode(leds[x], OUTPUT);
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
    for (int x = 0; x < NUM_LEDS; x++) {
      digitalWrite(leds[x], LOW);
    }
    Serial.println("data tidak sesuai");
  }
  delay(250);
}
