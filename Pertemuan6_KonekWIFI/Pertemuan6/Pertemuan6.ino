// stream data ke aplikasi blynk
#define BLYNK_TEMPLATE_ID "TMPL6a-nVdAkZ"
#define BLYNK_TEMPLATE_NAME "Pelatihan IOT Palcomtech"
#define BLYNK_AUTH_TOKEN "ynUXx47f8qaCbjgfN7tkX0nbPZFEvHlo"

#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define led1 16
#define led2 17
#define led3 18
#define led4 19


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Abcde";
char pass[] = "qwertyuiopoo";
boolean status;

BLYNK_WRITE(V0){
  int nilai1 = param.asInt();
  digitalWrite(led1, nilai1);
}

void cek_koneksi(){
  status=Blynk.connected();

  if (status == true) {
    // lcd.clear();
    lcd.print("Koneksi Sukses");
  } else {
    // lcd.clear();
    lcd.print("Koneksi Gagal");
  }
}

void setup(){
  pinMode(led1, OUTPUT);
  lcd.begin(16, 2);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("Tes Koneksi");
  lcd.setCursor(0, 1);
  Blynk.begin(auth, ssid, pass);
  cek_koneksi();
}

void loop(){
  Blynk.run();
}

