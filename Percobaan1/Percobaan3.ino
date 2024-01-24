// pakai pin 26 dan 27

// ==case kontrol lampu==
#define led1 16
#define led2 17
#define tombol1 26
#define tombol2 27

int statusTombol1;

void setButton(){
 Serial.begin(9600);
 pinMode(led1, OUTPUT);
 pinMode(tombol1, INPUT_PULLUP);
}

void runButton(){
  statusTombol1=digitalRead(tombol1);
  digitalWrite(led1, !statusTombol1);
  Serial.println(statusTombol1);
}