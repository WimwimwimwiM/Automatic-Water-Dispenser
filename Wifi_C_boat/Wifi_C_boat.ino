
//Change the WiFi_SSID, WiFi_PASS, BLYNK_TEMPLATE_ID, and BLYNK_AUTH_TOKEN in the code file to your own credentials.

/*#define BLYNK_AUTH_TOKEN 
#define WIFI_SSID 
#define WIFI_PASS 
#define BLYNK_TEMPLATE_ID 
#define BLYNK_TEMPLATE_NAME */


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Motor A Pins
#define EN_motorA   25
#define IN1_motorA  26
#define IN2_motorA  27

// Motor B Pins
#define EN_motorB   32
#define IN1_motorB  33
#define IN2_motorB  14  

int Speed_SA = 220;
int Speed_SB = 220;
int Speed_LA = 150;
int Speed_LB = 150;
int Speed_BW = 200;

HardwareSerial mySerial(2);

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi Connected!");
  Blynk.begin(BLYNK_AUTH_TOKEN,WIFI_SSID, WIFI_PASS);
  Serial.println(WiFi.localIP());

  pinMode(EN_motorA, OUTPUT);
  pinMode(IN1_motorA, OUTPUT);
  pinMode(IN2_motorA, OUTPUT);
  pinMode(EN_motorB, OUTPUT);
  pinMode(IN1_motorB, OUTPUT);
  pinMode(IN2_motorB, OUTPUT);

  digitalWrite(IN1_motorA, LOW);
  digitalWrite(IN2_motorA, LOW);
  digitalWrite(IN1_motorB, LOW);
  digitalWrite(IN2_motorB, LOW);

}

BLYNK_WRITE(V5) {
  Speed_SA = param.asInt();  
  Serial.print("Speed_SA : ");
  Serial.println(Speed_SA);  
}
BLYNK_WRITE(V6) {
  Speed_SB = param.asInt();  
  Serial.print("Speed_SB : ");
  Serial.println(Speed_SB); 
}
BLYNK_WRITE(V7) {
  Speed_LA = param.asInt();  
  Serial.print(" Speed_LA : ");
  Serial.println(Speed_LA);  
}
BLYNK_WRITE(V8) {
  Speed_LB = param.asInt();  
  Serial.print("Speed_LB : ");
  Serial.println(Speed_LB);  
}
BLYNK_WRITE(V9) {
  Speed_BW = param.asInt();  
  Serial.print("Speed_BW : ");
  Serial.println(Speed_BW);  
}
BLYNK_WRITE(V0) { //SA
  int buttonValue = param.asInt(); 
  Serial.println(Speed_SA); 
  if (buttonValue == 1) {
    Serial.println("Forward_motor_A");
    digitalWrite(IN1_motorA, HIGH);
    digitalWrite(IN2_motorA, LOW);
    analogWrite(EN_motorA, Speed_SA);
  } else {
    Serial.println("Stop_motor_A");
    digitalWrite(IN1_motorA, LOW);
    digitalWrite(IN2_motorA, LOW);    
    analogWrite(EN_motorA, 0);   
  }
}
BLYNK_WRITE(V1) {//SB
  int buttonValue = param.asInt(); 
  Serial.println(Speed_SB); 
  if (buttonValue == 1) {
    Serial.println("Forward_motor_B");
    digitalWrite(IN1_motorB, HIGH);
    digitalWrite(IN2_motorB, LOW);
    analogWrite(EN_motorB, Speed_SB);
  } else {
    Serial.println("Stop_motor_B");
    digitalWrite(IN1_motorB, LOW);
    digitalWrite(IN2_motorB, LOW);    
    analogWrite(EN_motorB, 0);   
  }
}
BLYNK_WRITE(V2) {//LA
  int buttonValue = param.asInt(); 
  Serial.println(Speed_LA);
  if (buttonValue == 1) {
    Serial.println("Forward_motor_B");
    digitalWrite(IN1_motorA, HIGH);
    digitalWrite(IN2_motorA, LOW);
    analogWrite(EN_motorA, Speed_LA);
  } else {
    Serial.println("Stop_motor_B");
    digitalWrite(IN1_motorA, LOW);
    digitalWrite(IN2_motorA, LOW);    
    analogWrite(EN_motorA, 0);   
  }
}
BLYNK_WRITE(V3) {//LB
  int buttonValue = param.asInt(); 
  Serial.println(Speed_LB); 
  if (buttonValue == 1) {
    Serial.println("Forward_motor_B");
    digitalWrite(IN1_motorB, HIGH);
    digitalWrite(IN2_motorB, LOW);
    analogWrite(EN_motorB,Speed_LB);
  } else {
    Serial.println("Stop_motor_B");
    digitalWrite(IN1_motorB, LOW);
    digitalWrite(IN2_motorB, LOW);    
    analogWrite(EN_motorB, 0);   
  }
}
BLYNK_WRITE(V4) {//BW
  int buttonValue = param.asInt(); 
  if (buttonValue == 1) {
    Serial.println("Backward_motor");
    digitalWrite(IN1_motorA, LOW);
    digitalWrite(IN2_motorA, HIGH);
    analogWrite(EN_motorA, Speed_BW);
    digitalWrite(IN1_motorB, LOW);
    digitalWrite(IN2_motorB, HIGH);
    analogWrite(EN_motorB, Speed_BW);
  } else {
    Serial.println("Stop_motor");
    digitalWrite(IN1_motorB, LOW);
    digitalWrite(IN2_motorB, LOW); 
    digitalWrite(IN1_motorA, LOW);
    digitalWrite(IN2_motorA, LOW);
    analogWrite(EN_motorA, 0);    
    analogWrite(EN_motorB, 0);   
  }
}
void loop() {
  int check = 0;
  Blynk.run();
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    check = 1;
  }
  if (check == 1) { 
    Serial.println("WiFi Connected!");
    Blynk.begin(BLYNK_AUTH_TOKEN,WIFI_SSID, WIFI_PASS);
  }
}

