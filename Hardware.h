#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <Arduino.h>
#include <SPI.h>
#include "FS.h"
#include "SD.h"

#define VSPI_MISO   MISO
#define VSPI_MOSI   MOSI
#define VSPI_SCLK   SCK
#define VSPI_SS     SS
#define SD_SS       4

extern const int spiClk;
extern SPIClass * vspi;

class hardware
{
private:
	char header[3] = "~#";
public:
	void begin();
	void send_header();
};
extern hardware Hardware;

class buzzer
{
public:
	void on();
	void off();
};
extern buzzer Buzzer;

#define ALPH 0
#define NUM 1

#define NO_KEY      0x05
#define NA 			    0x07
#define BACKSPACE 	0x08
#define ENTER     	0x0A
#define CAPS_LOCK 	0x14
#define ESCAPE    	0x1B
#define SPACE     	0x20
#define LEFT      	0x25
#define UP        	0x26
#define RIGHT     	0x27
#define DOWN      	0x28
#define F1        	0x70
#define F2        	0x71
#define F3        	0x72
#define F4        	0x73
#define F5        	0x74

class keyboard
{
public:
	char check_key(int opt);
	void displayKey(char key);
};
extern keyboard Keyboard;

class lcd
{
public:
	void clear();
	void clearLine(int line);
	void setCursor(int row, int col);
	void writeCommand(unsigned char cmd);
	void writeData(unsigned char val);
	void string(int row, int col, char *str);
};
extern lcd LCD;

#define COW 0
#define BUF 1

class milk_analyzer
{
public:
	bool getAnalysis(int type);
	float getFat();
	float getSNF();
	float getCLR();
	float getWater();
	float getTemperature();
};
extern milk_analyzer MilkAnalyzer;

class weighing_machine
{
public:
	bool getWeight(float *weight);
};
extern weighing_machine WeighingMachine;

typedef struct analysis
{
  float fat, SNF, CLR, water, temp, weight;
} Analysis;

class rtc
{
public:
	void setDateTime(byte day, byte month, byte year, byte dow, byte hour, byte minutes, byte seconds);
  void setCompilationDateTime(char *date, char *time);
	void getDate(byte &day, byte &month, byte &year, byte &dow);
	void getTime(byte &hour, byte &minutes, byte &seconds);
};
extern rtc RTC;

typedef struct rtcdata
{
  byte Day, Month, Year, DOW, Hour, Minutes, Seconds;
} RTCData;

#endif
