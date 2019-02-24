/* Arduino USB HID Keyboard Demo
*/
#include "keycodes.h"
#include "script.h"
#include "asciicodes.h"
uint8_t buf[8] = {
  0
};   /* Keyboard report buffer */
int loopcount = 0;

char attackcode[] = SCRIPT;
int stringlength = strlen(attackcode);

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

  delay(20);
  for (loopcount <= stringlength; ++loopcount;) {
    parse(loopcount - 1); //I use the -1 to fix it not printing the first character
    if (loopcount >= stringlength) {
      finished();
    }
  }

  /*
    if( loopcount < stringlength ) {
    typeKey(KEY_A);
    digitalWrite(LED_BUILTIN, HIGH);
    loopcount = loopcount+1;
    }
    else {
    flashLight(); }
  */
}

void parse(int i) {
  char currentKey = attackcode[i];
  if (currentKey >= 0x61 && currentKey <= 0x7a) { //if the ascii value is a lowercase letter
    typeKey(currentKey - 0x5d, false, false); //subtract hex(5d) from ascii value to get HID
  }
  else if (currentKey >= 0x41 && currentKey <= 0x5a) {
    typeKey(currentKey - 0x3d, true, false); //subtract hex(3d) from capital ascii value to get HID
  }
  else if (currentKey >= 0x30 && currentKey <= 0x39){
    typeKey(currentKey - 0x13,false,false);
  }
  else if (currentKey == 0x20) {
    typeKey(KEY_SPACE, false, false);
  }
  else if (currentKey == AS_SLASH) {
    typeKey(KEY_SLASH, false, false);
  }
  else if (currentKey == 0x5b) { //if its an open square bracket
    if (attackcode[i + 2] == 0x5d) { //if the char in two is "]"
      if (attackcode[i + 1] == 0x6e) { //if the next 1 is "n"
        typeKey(KEY_ENTER, false, false);
      }
      loopcount=loopcount+2;
    }
  }
}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;//Used for shift key
  buf[3] = 0; //Used for control key
  buf[4] = 0; //actual key
  Serial.write(buf, 8); // Release key
}
void typeKey(int key, bool isShift, bool isCtrl) { //Key should be the HID scancode
  if (isShift == true) {
    buf[2] = KEY_LEFTSHIFT;
  }
  if (isCtrl == true) {
    buf[3] = KEY_LEFTCTRL;
  }
  buf[4] = key;
  Serial.write(buf, 8);
  releaseKey();


}

void flashLight() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}

void finished() {
  for (int i = 1; i == 1;)
    flashLight();
}
