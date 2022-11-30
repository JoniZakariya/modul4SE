/*program Slave*/
#include <SPI.h>

#define L1 4 //pin arduino
#define L2 5 //pin arduino
#define L3 6 //pin arduino
#define L4 7 //pin arduino
#define NUM_LEDS 4 //jumlah led

int leds[NUM_LEDS] = {L1, L2, L3, L4};

volatile uint8_t data = 0; //variable ini disimpan di RAM

void setup (void) {
  Serial.begin (9600);
  for (uint8_t indx = 0; indx < NUM_LEDS; indx++) {
    pinMode(leds[indx], OUTPUT);
  }
  pinMode(MISO, OUTPUT); //output untk mengirim data dari slave to master
  SPCR |= 0b0000001 << 6; //SPI activated
  SPI.attachInterrupt(); //interrupt activated
  Serial.println("welcome to module 4");
  Serial.println("device SLave");
}
ISR (SPI_STC_vect) //(Interrupt Service Routine) dipanggil ketika ada interrupt dari SPI
{
  data = SPDR; //SPI Data Register
  SPDR = data;
}

void loop (void) {
  Serial.print("data Input = ");
  Serial.println(data);

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
      digitalWrite(leds[j], LOW);
    }
    Serial.println("data tidak sesuai");
  }
  delay(250);
}
