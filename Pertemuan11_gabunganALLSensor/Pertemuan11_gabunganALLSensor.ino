// Smart Home
#define BLYNK_TEMPLATE_ID "TMPL6tWL2CDKt"
#define BLYNK_TEMPLATE_NAME "Smart Home IOT"
#define BLYNK_AUTH_TOKEN "BcDtQDTMj766xQzf5IsNKXLKp2gtPIRY"

#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 14 
#define DHTTYPE DHT11

#define Lampu_depan 16
#define Lampu_tidur 17

#define Bell 4 

#define MQ2_SENSOR  15 

#define echoP 13
#define trigP 12 

DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;
// nama ssid dan password hotspot
char ssid[] = "Galaxy";
char pass[] = "sandi43210";

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

boolean fg,fu;
int humi, temp,u; 
long duration;
int distance;
int MQ2_SENSOR_Value = 0;

void cek_koneksi(){ 
  Blynk.begin(auth, ssid, pass);
  boolean koneksi = Blynk.connected();

  if(koneksi==true){
    lcd.print("Koneksi Sukses");
  }
  else{    
    lcd.print("Koneksi Gagal");
  }

}

void read_DHT11(){
  humi = dht.readHumidity();  
  temp = dht.readTemperature(); 
      lcd.setCursor(3,0);
      lcd.print(temp);

      lcd.setCursor(10,0);
      lcd.print(humi);

      Blynk.virtualWrite(V3, temp);  
      Blynk.virtualWrite(V4, humi);   
}

BLYNK_WRITE(V0)
{ 
  int value1 = param.asInt();
  digitalWrite(Lampu_depan,value1);  
}

BLYNK_WRITE(V1)
{ 
  int value2 = param.asInt(); 
  ledcWrite(ledChannel, value2);
}

BLYNK_WRITE(V2)
{ 
  int value3 = param.asInt();
  digitalWrite(Bell,value3);  
}

void cek_US(){
  digitalWrite(trigP, LOW);   
  delayMicroseconds(2);        
  digitalWrite(trigP, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(trigP, LOW); 
  duration = pulseIn(echoP, HIGH);   
  distance= duration*0.034/2;
  
  if((distance<20)&&(fu==0)) {
    Blynk.logEvent("awas", "Ada obyek terdeteksi !");   
    lcd.setCursor(3, 1);
    lcd.print("AWAS");
    delay(20000);
    fu=1;
  }
  else if((distance>20)&&(fu==1)){    
    fu=0;
    lcd.setCursor(3, 1);
    lcd.print("aman");
  }
}
//==============================
void cek_MQ(){
   MQ2_SENSOR_Value = digitalRead(MQ2_SENSOR);
    if ((MQ2_SENSOR_Value==0)&&(fg==0)) 
       { 
         Blynk.logEvent("awas", "Gas bocor terdeteksi!");
         fg=1;   
         lcd.setCursor(12, 1);
         lcd.print("AWAS");      
         delay(5000);
        }
     else if((MQ2_SENSOR_Value==1)&&(fg==1)) 
       {              
        fg=0;
        lcd.setCursor(12, 1);
         lcd.print("aman");  
        delay(1000);
       }
 }


void setup()
{  
  pinMode(trigP, OUTPUT);  
  pinMode(echoP, INPUT); 
  pinMode(Lampu_depan, OUTPUT);
  pinMode(Lampu_tidur, OUTPUT);
  pinMode(Bell, OUTPUT);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(Lampu_tidur, ledChannel);

  lcd.begin(16,2); //set LCD ukuran 16x2
  lcd.init();  //inisialisasi LCD
  lcd.backlight(); //backlight LCD

  lcd.setCursor(0, 0); //set kursor di awal baris 1
  lcd.print(" = Smart Home = ");//tulis ke LCD
  lcd.setCursor(0, 1); //set kursos di awal baris 2     
  lcd.print("   Blynk IoT");//tulis ke LCD
  delay(2000); //tunggu 2s
  lcd.clear(); //hapus tampilan LCD   

  lcd.print("Tunggu Koneksi..");//tulis LCD 
  lcd.clear();
  cek_koneksi();

  dht.begin();  
  delay(3000);
  lcd.clear();

  lcd.print("T=   C, H=   %");
  lcd.setCursor(0, 1);  
  lcd.print("US:Aman, MQ:Aman");
}
//=============================
void loop()
{  
  for(u=0;u<500;u++){
  Blynk.run();  
  }
  read_DHT11();
  cek_MQ();
  cek_US();
  delay(5);
  
}

