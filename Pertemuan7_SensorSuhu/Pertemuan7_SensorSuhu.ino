// ==DHT11 Sensor Suhu==
#define BLYNK_TEMPLATE_ID "TMPL6uP6DQZVi"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "2noyz6dN_ln9whwMPgvoISd0nG3p3StZ"

#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <DHT.h>

// pin 13 khusus untuk device Ardutech
#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE); //inisialisasi sensor

int kelembaban, suhu; //inisialisasi variabel

// ini untuk konfigurasi token dan jaringan
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Abcde";
char pass[] = "qwertyuiopoo";
boolean status;

void cek_koneksi(){
  Blynk.begin(auth, ssid, pass);
  status=Blynk.connected();

  if (status == true) {
    lcd.print("Koneksi Sukses");
  } else {
    lcd.print("Koneksi Gagal");
  } 
}

void sensor_berjalan(){
  kelembaban = dht.readHumidity();
  suhu = dht.readTemperature();

  lcd.setCursor(3,1);
  lcd.print(suhu);
  lcd.setCursor(10,1);
  lcd.print(kelembaban);
 
  Blynk.virtualWrite(V1, suhu);  
  Blynk.virtualWrite(V2, kelembaban);
}

void setup() {
    // setting lcd
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // akhir setting lcd

  lcd.setCursor(0, 0);
  lcd.print("Tes Koneksi");
  lcd.setCursor(0, 1);
  
  cek_koneksi();

  dht.begin();
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("suhu&kelembaban");
  lcd.setCursor(0, 1);
  lcd.print("T=   C, H=   %");
}

void loop() {
  Blynk.run();
  delay(1000);
  sensor_berjalan();
}


