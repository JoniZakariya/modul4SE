/* program Master */
#include <SPI.h>
#define SS 10 //Select Slave

int data = 0;
boolean state = false;

void setup (void) {
  Serial.begin(9600);
  SPI.begin(); //menyetel SCK, MOSI, dan SS ke output, menarik SCK dan MOSI LOW, dan SS HIGH.
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH); /*pin (enable slave) aktif ketika LOW */
  SPI.setClockDivider(SPI_CLOCK_DIV4);//mengatur clock SPI dari 1/4 frekuensi sistem (frekuensi sistem 16MHz).
  Serial.println("welcome to module 4");
  Serial.println("device Master");
}

void loop (void) {
  //========= Mengambil nilai dari Serial Monitor ==============
  if (Serial.available()) {
    data = Serial.read();
    data = data - 48;
    state = true;
  }
  //========= Mengirim data ke slave ==============
  if (state) {
    int dataFromMISO = sendDataSPI(data);//mengirim nilai dari master, dan mengambil nilai dari slave
    if (dataFromMISO) Serial.println("data dari slave = " + String (dataFromMISO));
    else Serial.println("slave gagal ngirim");
    state = false;
  }
  delay(250);
}
//======= fungsi write and read data SPI =========
int sendDataSPI(int _val) {
  digitalWrite(SS, LOW); //aktifkan pin enable slave
  int data_receive = SPI.transfer(_val); // mengirim data ke slave, dan mengambil data dari slave
  digitalWrite(SS, HIGH); // matikan pin enable slave
  delay(1);
  return data_receive;
}
