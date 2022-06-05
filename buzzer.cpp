#include "Hardware.h"

buzzer Buzzer;

void buzzer::on()
{
  int i;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);
  
  // send the request
  vspi->transfer(0x10);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(1);
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

void buzzer::off()
{
  int i;
  Hardware.send_header();

  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);
  // send the request
  vspi->transfer(0x11);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(1);
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
