/* Arduino USB HID Keyboard Demo
*/
#include "HIDKeyboard.h"
#include "script.h"

HIDKeyboard keyboard; // Initialize HIDKeyboard object
char script[] = "test1234";
void setup()
{
  keyboard.begin();
  pinMode(LED_BUILTIN, OUTPUT); //allows for turning on the builtin LED
  delay(1000);
  run();
}

void loop()
{

}

void run(){
  keyboard.print(script);
  finished();
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
