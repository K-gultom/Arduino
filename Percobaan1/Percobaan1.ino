#define ledPin 2
// pin 2 untuk mencari tahu rusak atau tidak nya dll, macam2 fungsi penggunaannya.
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // put your setup code here, to run once:
  // pinMode(ledPin, OUTPUT);
  // setLampu();
  // setButton();
  setKoneksi()
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(ledPin, HIGH);
  // delay(300);
  // digitalWrite(ledPin, LOW);
  // delay(300);

  // runLampu();
  // runButton();
  runKoneksi()
}