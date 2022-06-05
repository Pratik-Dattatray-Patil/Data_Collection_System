#include "Hardware.h"

keyboard Keyboard;

char keyboard::check_key(int opt)
{
  int i;
  char key;
  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  if(opt == ALPH)
    vspi->transfer(0x0C);
  else if(opt == NUM)
    vspi->transfer(0x0E);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(1985);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        key = vspi->transfer(0);
        delay(1);
        if(vspi->transfer(0) == '\r') {
          Serial.print("ACK received. Key = ");
          break;
        }
      }
    }
  }
  if(i >= 4)
    Serial.println("No ACK");
  else
    displayKey(key);
  
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();
  return key;
}

void keyboard::displayKey(char key) {
  switch(key) {
    case NO_KEY:
      Serial.println("No Input");
//      LCD.string(1, 1, "KEY:No Input");
      break;
    case NA:
      Serial.println("NA");
//      LCD.string(1, 1, "KEY:NA");
      break;
    case BACKSPACE:
      Serial.println("Backsapce");
//      LCD.string(1, 1, "KEY:Backsapce");
      break;
    case ENTER:
      Serial.println("Enter");
//      LCD.string(1, 1, "KEY:Enter");
      break;
    case CAPS_LOCK:
      Serial.println("Caps Lock");
//      LCD.string(1, 1, "KEY:Caps Lock");
      break;
    case ESCAPE:
      Serial.println("Escape");
//      LCD.string(1, 1, "KEY:Escape");
      break;
    case SPACE:
      Serial.println("Space");
//      LCD.string(1, 1, "KEY:Space");
      break;
    case F1:
      Serial.println("F1");
//      LCD.string(1, 1, "KEY:F1");
      break;
    case F2:
      Serial.println("F2");
//      LCD.string(1, 1, "KEY:F2");
      break;
    case F3:
      Serial.println("F3");
//      LCD.string(1, 1, "KEY:F3");
      break;
    case F4:
      Serial.println("F4");
//      LCD.string(1, 1, "KEY:F4");
      break;
    case F5:
      Serial.println("F5");
//      LCD.string(1, 1, "KEY:F5");
      break;
    default:
      Serial.println(key);
//      LCD.string(1, 1, "KEY:");
//      LCD.writeData(key);
  }
}
