#include "Hardware.h"

SPIClass * vspi = NULL;
const int spiClk = 500000; // 500 kHz

void hardware::begin()
{
  vspi = new SPIClass(VSPI);
	vspi->begin();
	pinMode(VSPI_SS, OUTPUT); //VSPI SS
	digitalWrite(VSPI_SS, HIGH);
  
  delay(1500);
  LCD.clear();
  LCD.writeCommand(0x0C);
  
  if(!SD.begin(SD_SS)){
      Serial.println("Card Mount Failed");
      return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
      Serial.println("No SD card attached");
      return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
      Serial.println("MMC");
  } else if(cardType == CARD_SD){
      Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void hardware::send_header()
{
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
	digitalWrite(VSPI_SS, LOW);
	for(int i = 0; i < 2; i++) 
	{
  	vspi->transfer(header[i]);
    Serial.print(header[i], HEX);
    Serial.print(" | ");
	}
  Serial.println(' ');
	digitalWrite(VSPI_SS, HIGH);
	vspi->endTransaction();
}
