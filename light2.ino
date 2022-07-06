#include <SoftwareSerial.h>

//255 least bright 0 highest brightness

SoftwareSerial mySerial(2, 3); // RX, TX

#define r_pin 5
#define g_pin 10
#define b_pin 11

#define warm 12

char *input_code;
uint8_t r=0,g=0,b=0;
uint8_t r1=0,g1=0,b1=0;
String incs;

void setup() {
  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600); // Default communication rate of the Bluetooth module is 9600 faster rate 38400
  // change baud rate rate from 9600 to 38400 in HC05, as we want high speed transmissions.
  // Follow this link to change it: https://www.instructables.com/Changing-Baud-Rate-of-HC-05-Bluetooth/
}

void blin(){
  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
}

void brightness(uint8_t bright){
//  Serial.println(r);
//  Serial.println(g);
//  Serial.println(b);
  
  r1 = map(bright,0,100,255,r);
  g1 = map(bright,0,100,255,g);
  b1 = map(bright,0,100,255,b);

//  if(bright!=0){
//    r1 = 0;
//    g1 = 0;
//    b1 = 0;
//  }
  
  analogWrite(r_pin,r1);
  analogWrite(g_pin,g1);
  analogWrite(b_pin,b1);
  
//  Serial.println(r1);
//  Serial.println(g1);
//  Serial.println(b1);
}

void colour(String in){
  r = uint8_t(strtol(in.substring(0,in.indexOf(',')).c_str(),NULL,10));
  in = in.substring(in.indexOf(',')+1);
  g = uint8_t(strtol(in.substring(0,in.indexOf(',')).c_str(),NULL,10));
  in = in.substring(in.indexOf(',')+1);
  b = uint8_t(strtol(in.c_str(),NULL,10));
//
//  Serial.println(r);
//  Serial.println(g);
//  Serial.println(b);
  
  r = 255-r;g = 255-g;b = 255-b;

  analogWrite(r_pin,r);
  analogWrite(g_pin,g);
  analogWrite(b_pin,b);

//  Serial.println(r);
//  Serial.println(g);
//  Serial.println(b);
}

void loop() {
  //if(Serial.available() > 0){ // Checks whether data is comming from the serial port
  if(mySerial.available() > 0){
    blin();
    incs = mySerial.readStringUntil('\0'); // Reads the data from the serial port
//    Serial.println(incs);
    if(incs.charAt(0) == 'C'){
      incs = incs.substring(incs.lastIndexOf("C")+1);
      colour(incs);
    }
    if(incs.charAt(0) == 'B'||incs.charAt(incs.length()-4) == 'B'||incs.charAt(incs.length()-3) == 'B'){
      incs = incs.substring(incs.lastIndexOf("B")+1);
      input_code = incs.c_str();
      brightness(uint8_t(strtol(input_code,NULL,10)));
    }
    if(incs.charAt(0) == 'W'){
      if(incs.charAt(1) == '1')
      digitalWrite(warm,HIGH);
      else if(incs.charAt(1) == '0')
      digitalWrite(warm,LOW);
    }
//    else if(incs.charAt(0) == 'O'){
//      on_off(incs.charAt(1));
//    }
  }
  
}
