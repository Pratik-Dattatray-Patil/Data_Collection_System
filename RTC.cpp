#include "Hardware.h"

rtc RTC;

void rtc::setDateTime(byte day, byte month, byte year, byte dow, byte hour, byte minutes, byte seconds)
{
  int i;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);
  
  // send the request
  vspi->transfer(0x1A);
  vspi->transfer(day);
  vspi->transfer(month);
  vspi->transfer(year);
  vspi->transfer(dow);
  vspi->transfer(hour);
  vspi->transfer(minutes);
  vspi->transfer(seconds);
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

void rtc::setCompilationDateTime(char *date, char *time)
{
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  
  /* Extract day, month, year */
  byte year = atoi(date + 9);
  date[6] = 0;
  byte day = atoi(date + 4);
  date[3] = 0;
  byte month;
  for(int i = 0; i < 12; i++) {
    if(strcmp(date, months[i]) == 0) {
      month = i + 1;
      break;
    }
  }

  /* Extract hour, minutes, seconds */
  byte seconds = atoi(time + 6);
  time[5] = 0;
  byte minutes = atoi(time + 3);
  time[2] = 0;
  byte hour = atoi(time);

  /* Find the day of week from the date */
  int k, m, c = 20, y;
  byte w;
  k = day;
  if(month < 3)
    m = month + 10;
  else
    m = month - 2;
  y = year - (month < 3)*1;
  w = (k + (int)floor((2.6 * m) - 0.2) - (2 * c) + y + (y/4) + (c/4)) % 7;

  setDateTime(day, month, year, w + 1, hour, minutes, seconds);
}

void rtc::getDate(byte &day, byte &month, byte &year, byte &dow)
{
  int i;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x1B);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        day = vspi->transfer(0);
        delay(1);
        month = vspi->transfer(0);
        delay(1);
        year = vspi->transfer(0);
        delay(1);
        dow = vspi->transfer(0);
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

void rtc::getTime(byte &hour, byte &minutes, byte &seconds)
{
  int i;
  Hardware.send_header();
  
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);

  // send the request
  vspi->transfer(0x1C);
  vspi->transfer('\r');
  
  // wait for the response with a timeout
  delay(2);
  for(i = 0; i < 5; i++){
    if(vspi->transfer(0) == '>') {
      delay(1);
      if(vspi->transfer(0) == '>') {
        delay(1);
        hour = vspi->transfer(0);
        delay(1);
        minutes = vspi->transfer(0);
        delay(1);
        seconds = vspi->transfer(0);
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
