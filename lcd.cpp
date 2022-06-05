#include "Hardware.h"

lcd LCD;

void lcd::clear()
{
  int i;
  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x14);
  vspi->transfer('\r');

  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        if(vspi->transfer(0) == '\r') {
          Serial.println("ACK received.");
          break;
        }
      }
    }
  }
  if(i >= 4)
    Serial.println("No ACK");
    
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();
}
	
void lcd::clearLine(int line)
{
  int i;
  unsigned char cmd = 0x40 | --line;
  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(cmd);
  vspi->transfer('\r');

  // wait for the response with a timeout
  delay(64);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        if(vspi->transfer(0) == '\r') {
          Serial.println("ACK received.");
          break;
        }
      }
    }
  }
  if(i >= 4)
    Serial.println("No ACK");
    
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();
}

void lcd::setCursor(int row, int col)
{
  int i;
  unsigned char cmd = 0x80 | (--row << 5) | --col;

  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);
  
  // send the request
  vspi->transfer(cmd);
  vspi->transfer('\r');

  // wait for the response with a timeout
  delay(28);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        if(vspi->transfer(0) == '\r') {
          Serial.println("ACK received.");
          break;
        }
      }
    }
  }
  if(i >= 4)
    Serial.println("No ACK");
    
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();
}

void lcd::writeCommand(unsigned char cmd)
{
  int i;
  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x15);
  vspi->transfer(cmd);
  vspi->transfer('\r');

  // wait for the response with a timeout
  delay(3);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        if(vspi->transfer(0) == '\r') {
          Serial.println("ACK received.");
          break;
        }
      }
    }
  }
  if(i >= 4)
    Serial.println("No ACK");
    
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();
}

void lcd::writeData(unsigned char val)
{
  int i;
  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x16);
  vspi->transfer(val);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(8);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        if(vspi->transfer(0) == '\r') {
          Serial.println("ACK received.");
          break;
        }
      }
    }
  }
  if(i >= 4)
    Serial.println("No ACK");
    
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();
}

void lcd::string(int row, int col, char *str)
{
  int i = 0;
  LCD.setCursor(row, col);
  delay(50);
  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);
  
  // send the request
  vspi->transfer(0x17);
  while(*str && (i++ < 20)) {
    vspi->transfer(*str);
    str++;
  }
  vspi->transfer('\r');

  // wait for the response with a timeout
  delay(108);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        if(vspi->transfer(0) == '\r') {
          Serial.println("ACK received.");
          break;
        }
      }
    }
  }
  if(i >= 4)
    Serial.println("No ACK");
    
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();
}
