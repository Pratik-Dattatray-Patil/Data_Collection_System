#include "Hardware.h"
hardware Hardware;

bool success;
char lcdbuff[21];
Analysis MilkData = {0, 0, 0, 0, 0};
float price = 0.0;
RTCData Date_Time;
char key;
char DateArr[11] = {0}, TimeArr[9] = {0};
String FileName, FilePath;
int entries = 0;

void setup() {
  Serial.begin(9600);
  Hardware.begin();
  delay(1000);
}

void loop() {
  
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}
