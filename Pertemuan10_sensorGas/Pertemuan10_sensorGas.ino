//  sensor gas mq_2
#define BLYNK_TEMPLATE_ID "TMPL65iCGyAm2"
#define BLYNK_TEMPLATE_NAME "coba iot"
#define BLYNK_AUTH_TOKEN "pYy8hfeZSrspR4UcT1Ak1Aqe5yunPTrH"

#define MQ2_SENSOR 15

#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy";
char pass[] = "sandi43210";

LiquidCrystal_I2C lcd(0x27, 16, 2);

int MQ2_SENSOR_Value = 0;
boolean status;

void cek_koneksi(){ 
  Blynk.begin(auth, ssid, pass);
  if(Blynk.connected() == true){    
    lcd.print("Koneksi Sukses");
  }
  else{  
    lcd.print("Koneksi Gagal");
  }
}

void cek_MQ(){
  
   MQ2_SENSOR_Value = digitalRead(MQ2_SENSOR);

    if ((MQ2_SENSOR_Value==0)&&(status==0)) 
    {       
      // awas yang pertama, dapat dari blynk event, sesuai nama event yang dibuat
      Blynk.logEvent("awas", "Gas bocor terdeteksi!, AWAS!!!!!!!!!!");
      status=1;   
      lcd.setCursor(3, 1);
      lcd.print("AWAS");      
      delay(5000);
    }
    else if((MQ2_SENSOR_Value==1)&&(status==1)) 
    {              
    status=0;
    lcd.setCursor(3, 1);
      lcd.print("AMAN");  
    delay(1000); 
    }
 }

void lcd_setup(){
    lcd.begin(16,2);
    lcd.init(); 
    lcd.backlight();
}

void setup() {
  lcd_setup();
  lcd.setCursor(0, 0);
  lcd.print("=Sensor Gas=");
  lcd.setCursor(0, 1);   
  lcd.print("   Blynk IoT");
  delay(2000); //tunggu 2s
  lcd.clear(); //hapus tampilan LCD     
  lcd.print("Tunggu Koneksi..");//tulis LCD 
  lcd.setCursor(0,1);
  cek_koneksi();
  lcd.clear(); 
  lcd.setCursor(0, 0);  
  lcd.print("MQ:Aktif");
  lcd.setCursor(0, 1);  
  lcd.print("MQ:");

}

void loop() {
  for(int u = 0; u < 500; u++){
  Blynk.run();  
  }
  cek_MQ();
  delay(5);
}