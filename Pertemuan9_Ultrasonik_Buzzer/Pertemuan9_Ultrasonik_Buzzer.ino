// sensor ultrasonik di lengkapi buzzer peringatan
#define BLYNK_TEMPLATE_ID "TMPL65iCGyAm2"
#define BLYNK_TEMPLATE_NAME "coba iot"
#define BLYNK_AUTH_TOKEN "pYy8hfeZSrspR4UcT1Ak1Aqe5yunPTrH"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy";
char pass[] = "sandi43210";

#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>

#define Bell 4
#define echoP 13
#define trigP 12 

LiquidCrystal_I2C lcd(0x27, 16, 2);

boolean status,obyek;
long waktu;
int jarak;

void cek_koneksi(){ 
  status=Blynk.connected();
  if(status==true){
    lcd.print("Koneksi Sukses");
  }
  else{ 
    lcd.print("Koneksi Gagal");
  }
}

void run_ultrasonic(){
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW); 
  waktu = pulseIn(echoP, HIGH);   
  jarak= waktu*0.034/2;
  Blynk.virtualWrite(V3, jarak); 
  lcd.setCursor(6,0);
  lcd.print(jarak);
  lcd.print(" cm ");
    if((jarak<20)&&(obyek==0)) {
      Blynk.logEvent("awas", "Ada obyek terdeteksi !");
      digitalWrite(Bell,HIGH);
      // buat delayyy Suara, 2000 = 2 detik
      delay(2000);
      obyek=1;
    }
    else if((jarak>20)&&(obyek==1)){    
      obyek=0;
      digitalWrite(Bell,LOW);

    }
}
//==============================

//============================
void setup()
{  
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT); 

  pinMode(Bell, OUTPUT);
  
  lcd.begin(16,2); //set LCD ukuran 16x2
  lcd.init();  //inisialisasi LCD
  lcd.backlight(); //backlight LCD
  
  lcd.setCursor(0, 0); //set kursor di awal baris 1
  lcd.print("Sensor Ultrasonic");//tulis ke LCD

  lcd.setCursor(0, 1); //set kursos di awal baris 2     
  lcd.print("   Blynk IoT");//tulis ke LCD

  delay(2000); //tunggu 2s

  lcd.clear(); //hapus tampilan LCD     
  lcd.print("Tunggu Koneksi..");//tulis LCD 
  Blynk.begin(auth, ssid, pass);

  lcd.clear(); //hapus tampilan LCD     
  cek_koneksi(); //panggil fungsi cek koneksi 
  
  delay(3000);
  lcd.clear();   
  lcd.print("Range=");
  
}
//=============================
void loop()
{  
  for(int ulang=0;ulang<500;ulang++){
    Blynk.run();  
  }
  
  run_ultrasonic();
  delay(5);
  
}

