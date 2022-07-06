//255 least bright 0 highest brightness

#define r_pin 9
#define g_pin 10
#define b_pin 11
char *input_code;
uint8_t r,g,b;
String incs;
int state = 0;

void setup() {
  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  Serial.begin(9600); // Default communication rate of the Bluetooth module is 9600 faster rate 38400
  // change baud rate rate from 9600 to 38400 in HC05, as we want high speed transmissions.
  // Follow this link to change it: https://www.instructables.com/Changing-Baud-Rate-of-HC-05-Bluetooth/
}

void on_off(char on_off_state){
  if(on_off_state == '1'){
    //EF9A9A
    //starting light colour
    analogWrite(255-239, r_pin);
    analogWrite(255-154, g_pin);
    analogWrite(255-154, b_pin);
    state = 1;
  }
  else if(on_off_state == '0'){
  analogWrite(r_pin,255);
  analogWrite(g_pin,255);
  analogWrite(b_pin,255);
    state = 0;
  }
      digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
}

void brightness(uint8_t bright){
  r = map(bright,0,100,r,0);
  g = map(bright,0,100,g,0);
  b = map(bright,0,100,b,0);

  analogWrite(r_pin,r);
  analogWrite(g_pin,g);
  analogWrite(b_pin,b);

  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

void colour(String in){
  in = in.substring(1);
  //long int col = strtol(in, NULL, 16);
  r = uint8_t(strtol(in.substring(0,in.indexOf(',')).c_str(),NULL,10));
  r = 255-r;
  in = in.substring(in.indexOf(',')+1);
  g = uint8_t(strtol(in.substring(0,in.indexOf(',')).c_str(),NULL,10));
  g = 255-g;
  in = in.substring(in.indexOf(',')+1);
  b = uint8_t(strtol(in.c_str(),NULL,10));
  b = 255-b;

  analogWrite(r_pin,r);
  analogWrite(g_pin,g);
  analogWrite(b_pin,b);

  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

void loop() {
  //if(Serial.available() > 0){ // Checks whether data is comming from the serial port
  if(Serial.available() > 0){
    incs = Serial.readStringUntil('\0'); // Reads the data from the serial port
    incs = incs.substring(0,incs.indexOf(" "));
    //input_code = incs.c_str();
    if(state==1&&incs.charAt(0) == 'C'){
      colour(incs);
    }
    else if(state==1&&incs.charAt(0) == 'B'){
      incs = incs.substring(incs.lastIndexOf("B")+1);
      input_code = incs.c_str();
      brightness(uint8_t(strtol(input_code,NULL,10)));
    }
    else if(incs.charAt(0) == 'O'){
      on_off(incs.charAt(1));
    }
  }
}
