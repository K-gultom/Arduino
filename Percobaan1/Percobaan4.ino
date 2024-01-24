// LCD

// ==Case Cetak ke Lcd==
#include <LiquidCrystal_I2C.h>
// kalau mau pakai library harus include
LiquidCrystal_I2C lcd(0x27,16,2);

void setLcd(){
  // ini perintah setup
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.print("Yehezkiel Gultom");
  
  //kolom ke 0, baris ke 1
  lcd.setCursor(0,1);
  lcd.print("Belajar IOT");
}
