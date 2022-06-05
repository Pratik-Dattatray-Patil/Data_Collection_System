#include "Hardware.h"

weighing_machine WeighingMachine;

bool weighing_machine::getWeight(float *weight)
{
  int i;
  char status;
  char *ptr_weight = (char *)weight;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x0B);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
//  delay(2420);
  delay(3000);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        status = vspi->transfer(0);
        if(status == 'S')
        {
        	*ptr_weight++ = vspi->transfer(0);
        	delay(1);
        	*ptr_weight++ = vspi->transfer(0);
        	delay(1);
        	*ptr_weight++ = vspi->transfer(0);
        	delay(1);
        	*ptr_weight   = vspi->transfer(0);
        }
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
