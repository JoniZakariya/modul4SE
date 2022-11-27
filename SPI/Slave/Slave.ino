/*program Slave*/
#include <SPI.h>

#define L1 4 //pin arduino
#define L2 5 //pin arduino
#define L3 6 //pin arduino
#define L4 7 //pin arduino
#define NUM_LEDS 4 //jumlah led

int leds[NUM_LEDS] = {L1, L2, L3, L4};

volatile uint8_t val = 0; //variable ini disimpan di ram

void setup (void) {
  Serial.begin (9600);
  for (int z = 0; z < 4; z++) {
    pinMode(leds[z], OUTPUT);
  }
  pinMode(MISO, OUTPUT); //output untk mengirim data dari slave to master
  SPCR |= 0b0000001 << 6; //SPI activated
  SPI.attachInterrupt(); //interrupt activated
  Serial.println("welcome to module 4");
  Serial.println("device SLave");
}
ISR (SPI_STC_vect) //dipanggil ketika ada interrupt dari SPI
{
  val = SPDR; //SPI Data Register
  SPDR = val; //manyimpan nilai dari variable val
}

void loop (void) {
  Serial.print("data Input = ");
  Serial.println(val);

  if (val > 0 && val <= NUM_LEDS) {
    Serial.print("LED1 = ");
    Serial.print((0x01 >> (val - 1)) & 1);
    Serial.print("\t LED2 = ");
    Serial.print((0x02 >> (val - 1)) & 1);
    Serial.print("\t LED3 = ");
    Serial.print((0x04 >> (val - 1)) & 1);
    Serial.print("\t LED4 = ");
    Serial.println((0x08 >> (val - 1)) & 1);
    // ============== KONDISI LED ===============
    digitalWrite(leds[0], (0x01 >> (val - 1)) & 1);
    digitalWrite(leds[1], (0x02 >> (val - 1)) & 1);
    digitalWrite(leds[2], (0x04 >> (val - 1)) & 1);
    digitalWrite(leds[3], (0x08 >> (val - 1)) & 1);
  }
  else {
    for (int x = 0; x < NUM_LEDS; x++) {
      digitalWrite(leds[x], LOW);
    }
    Serial.println("data tidak sesuai");
  }
  delay(250);
}
