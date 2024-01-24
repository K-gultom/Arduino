// ==Koneksi ke wifi==
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const char* ssid = "Galaxy";
const char* password = "sandi43210";

void setKoneksi() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("tes koneksi...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("connecting...");
  lcd.setCursor(0, 1);

  lcd.print(ssid);
  WiFi.begin(ssid,password);
  // untuk cek apakah sudah join atau tidak
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  }

  lcd.clear();
  lcd.print("Wifi Connected");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
}

void runKoneksi(){
    lcd.setCursor(8, 1);
    lcd.print(WiFi.RSSI());
    lcd.setCursor(12, 1);
    // dBm satuan untuk menghitung sinyal
    lcd.print("dBm");
    delay(2000);
}


