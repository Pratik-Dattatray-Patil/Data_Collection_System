#include "Hardware.h"

milk_analyzer MilkAnalyzer;

bool milk_analyzer::getAnalysis(int type)
{
  int i;
  char status;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  if(type == COW)
    vspi->transfer(0x02);
  else if(type == BUF)
    vspi->transfer(0x03);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(750);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        status = vspi->transfer(0);
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

  if(status == 'S')
  	return true;
  else if(status == 'F')
  	return false;
  return false;
}

float milk_analyzer::getFat()
{
  int i;
  float fat;
  char *ptr_fat = (char *)&fat;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x04);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        *ptr_fat++ = vspi->transfer(0);
        delay(1);
        *ptr_fat++ = vspi->transfer(0);
        delay(1);
        *ptr_fat++ = vspi->transfer(0);
        delay(1);
        *ptr_fat   = vspi->transfer(0);
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

  return fat;
}

float milk_analyzer::getSNF()
{
  int i;
  float snf;
  char *ptr_snf = (char *)&snf;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x05);
  vspi->transfer('\r');

  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        *ptr_snf++ = vspi->transfer(0);
        delay(1);
        *ptr_snf++ = vspi->transfer(0);
        delay(1);
        *ptr_snf++ = vspi->transfer(0);
        delay(1);
        *ptr_snf   = vspi->transfer(0);
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

  return snf;
}

float milk_analyzer::getCLR()
{
  int i;
  float clr;
  char *ptr_clr = (char *)&clr;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x06);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        *ptr_clr++ = vspi->transfer(0);
        delay(1);
        *ptr_clr++ = vspi->transfer(0);
        delay(1);
        *ptr_clr++ = vspi->transfer(0);
        delay(1);
        *ptr_clr   = vspi->transfer(0);
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

  return clr;
}

float milk_analyzer::getWater()
{
  int i;
  float water;
  char *ptr_water = (char *)&water;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x07);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        *ptr_water++ = vspi->transfer(0);
        delay(1);
        *ptr_water++ = vspi->transfer(0);
        delay(1);
        *ptr_water++ = vspi->transfer(0);
        delay(1);
        *ptr_water   = vspi->transfer(0);
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

  return water;
}

float milk_analyzer::getTemperature()
{
  int i;
  float temperature;
  char *ptr_temperature = (char *)&temperature;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x08);
  vspi->transfer('\r');

  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        *ptr_temperature++ = vspi->transfer(0);
        delay(1);
        *ptr_temperature++ = vspi->transfer(0);
        delay(1);
        *ptr_temperature++ = vspi->transfer(0);
        delay(1);
        *ptr_temperature   = vspi->transfer(0);
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

  return temperature;
}
