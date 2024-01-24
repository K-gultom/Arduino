// sensor ultrasonik
#define BLYNK_TEMPLATE_ID "TMPL6uP6DQZVi"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "2noyz6dN_ln9whwMPgvoISd0nG3p3StZ"

#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>
const int trigP = 12;
const int echoP = 13;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Abcde";
char pass[] = "qwertyuiopoo";

LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
int distance;

boolean st;
void cek_koneksi(){ 
  st=Blynk.connected();
  if(st==true){
    lcd.clear();   
    lcd.print("Koneksi Sukses");
  }
  else{
    lcd.clear();     
    lcd.print("Koneksi Gagal");
  }
}
// 
//=============================
void read_ultrasonic(){
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW); 
  duration = pulseIn(echoP, HIGH); //pulseIn untuk menghitung jarak tempuh suara
  //v = 340m/s --.0.34 cm/us
  distance= duration*0.034/2;
  
  
  lcd.setCursor(6,0);
  lcd.print(distance);  
  lcd.print(" cm  ");    
  // v4 dapat dari data stream blynk
    Blynk.virtualWrite(V4, distance); 
}

//============
void setup()
{    
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT); 
  lcd.begin(16,2); //set LCD ukuran 16x2
  lcd.init();  //inisialisasi LCD
  lcd.backlight(); //backlight LCD
  lcd.setCursor(0, 0); //set kursor di awal baris 1
  lcd.print("   Ultrasonic  ");//tulis ke LCD
  lcd.setCursor(0, 1); //set kursos di awal baris 2     
  lcd.print("  Range Meter ");//tulis ke LCD
  Blynk.begin(auth, ssid, pass);
  cek_koneksi(); //panggil fungsi cek koneksi 
  delay(2000); //tunggu 2s
  lcd.clear(); //hapus tampilan LCD        
  lcd.print("Jarak = ");//tulis ke LCD  

}
//=============================
void loop()
{
  read_ultrasonic();
  delay(1000);
  Blynk.run();
}

