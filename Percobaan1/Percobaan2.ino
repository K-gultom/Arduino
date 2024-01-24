// ==case led lampu==
#define led1 16
#define led2 17
#define led3 18
#define led4 19

void setLampu(){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void runLampu(){
  digitalWrite(led1, 1);
  digitalWrite(led2, 0);
  digitalWrite(led3, 0);
  digitalWrite(led4, 0);
  delay(500);
  
  digitalWrite(led1, 0);
  digitalWrite(led2, 1);
  digitalWrite(led3, 0);
  digitalWrite(led4, 0);
  delay(500);
  
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
  digitalWrite(led3, 1);
  digitalWrite(led4, 0);
  delay(500);
  
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
  digitalWrite(led3, 0);
  digitalWrite(led4, 1);
  delay(500);
  

}