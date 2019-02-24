/* Arduino USB HID Keyboard Demo
 */
#include "keycodes.h"
uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */
int loopcount = 0;

String attackcode = "test";
int stringlength = attackcode.length();

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT); //allows for turning on the builtin LED
  
  Serial.begin(9600);
  delay(200);
  /*
  String attackcode = "test";
  int stringlength = 10;
  int loopcount = 0;
  */
}

void loop() 
{

  delay(10);
  if( loopcount < stringlength ) {
    typeKey(KEY_A);
    digitalWrite(LED_BUILTIN, HIGH);
    loopcount = loopcount+1;
  }
  else {
    flashLight(); }
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}
void typeKey(int key){
  buf[2] = key;
  Serial.write(buf, 8);
  releaseKey();
  
  
}

void flashLight() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}
