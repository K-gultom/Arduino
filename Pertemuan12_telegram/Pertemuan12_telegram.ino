#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> 
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

// GANTI DG WiFi dan Password
const char* ssid = "Galaxy";
const char* password = "sandi43210";

// GANTI DG TOKEN & ID CHAT
#define BOTtoken "6559806944:AAFeeGL8DtP-BHwZiITHuvizY1SGnNDB4yo" 
#define CHAT_ID "1279980068"

#define L1 16
#define L2 17
#define L3 18
#define L4 19

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin = 2;

bool l1State = LOW;
bool l2State = LOW;
bool l3State = LOW;
bool l4State = LOW;

//===========================================
void handleNewMessages(int numNewMessages) {
  // Iterasi melalui semua pesan baru yang diterima
  for (int i=0; i<numNewMessages; i++) { 
    // Ambil ID chat dari pesan dan konversi menjadi String
    String chat_id = String(bot.messages[i].chat_id);
     // Periksa apakah ID chat tidak sesuai dengan ID yang diizinkan
    if (chat_id != CHAT_ID){
      // Kirim pesan ke pengguna yang tidak diizinkan dan lanjutkan ke pesan berikutnya
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }  
    // Ambil teks pesan dan nama pengirim
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    
    if (text == "/start") {
      bot.sendMessage(chat_id, "Kontrol LED Ready...", "");
    }
    
    if (text == "/l1_on") {
      bot.sendMessage(chat_id, "LED 1 ON", "");
      l1State = HIGH;
      digitalWrite(L1, l1State);
    }
    
    if (text == "/l1_off") {
      bot.sendMessage(chat_id, "LED 1 OFF", "");
      l1State = LOW;
      digitalWrite(L1, l1State);
    }
    
    if (text == "/cek_1") {
      if (digitalRead(L1)){
        bot.sendMessage(chat_id, "LED 1 kondisi ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED 1 kondisi OFF", "");
      }
    }
    
    if (text == "/l2_on") {
      bot.sendMessage(chat_id, "LED 2 ON", "");
      l2State = HIGH;
      digitalWrite(L2, l2State);
    }
    
    if (text == "/l2_off") {
      bot.sendMessage(chat_id, "LED 2 OFF", "");
      l2State = LOW;
      digitalWrite(L1, l2State);
    }
    
    if (text == "/cek_2") {
      if (digitalRead(L2)){
        bot.sendMessage(chat_id, "LED 2 kondisi ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED 2 kondisi OFF", "");
      }
    }
 
    if (text == "/l3_on") {
      bot.sendMessage(chat_id, "LED 3 ON", "");
      l3State = HIGH;
      digitalWrite(L3, l3State);
    }
    
    if (text == "/l3_off") {
      bot.sendMessage(chat_id, "LED 3 OFF", "");
      l3State = LOW;
      digitalWrite(L3, l3State);
    }
    
    if (text == "/cek_3") {
      if (digitalRead(L3)){
        bot.sendMessage(chat_id, "LED 3 kondisi ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED 3 kondisi OFF", "");
      }
    }
    
    if (text == "/l4_on") {
      bot.sendMessage(chat_id, "LED 4 ON", "");
      l4State = HIGH;
      digitalWrite(L4, l4State);
    }
    
    if (text == "/l4_off") {
      bot.sendMessage(chat_id, "LED 4 OFF", "");
      l4State = LOW;
      digitalWrite(L4, l4State);
    }
    
    if (text == "/cek_4") {
      if (digitalRead(L4)){
        bot.sendMessage(chat_id, "LED 4 kondisi ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED 4 kondisi OFF", "");
      }
    }
    
    if (text == "/all_on") {
      bot.sendMessage(chat_id, "LED 1-4 ON", "");     
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,HIGH);
    }
    
    if (text == "/all_off") {
      bot.sendMessage(chat_id, "LED 1-4 OFF", "");     
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
    }
  }
}

void setup() {
  
  lcd.begin(16,2); //set LCD ukuran 16x2
  lcd.init();  //inisialisasi LCD
  lcd.backlight(); //backlight LCD
  lcd.setCursor(0, 0); //set kursor di awal baris 1
  lcd.print("Kontrol Telegram");//tulis ke LCD  
  lcd.setCursor(0,1);
  lcd.print("Tunggu Koneksi...");
  
  pinMode(16, OUTPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
    
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  lcd.setCursor(0,1);
  lcd.print("Connected.....");
  delay(1000);
  bot.sendMessage(CHAT_ID, "ESP32 Kontrol LED ready ....", "");
}
//=================================================
void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}



