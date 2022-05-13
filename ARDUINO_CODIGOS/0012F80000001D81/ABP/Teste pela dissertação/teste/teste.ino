#include <LoRaWAN.h>
#include <SoftwareSerial.h>
#include <stdint.h>

SoftwareSerial* hSerialCommands = NULL;

char APPSKEY[] = "61:19:DF:C0:8C:D5:EA:DB:79:52:B7:B7:25:8E:43:54";
char NWKSKEY[] = "30:AA:2F:D0:5C:65:3B:EC:49:E2:06:C8:F5:1D:92:63";
char DEVADDRESS[] = "00:8C:32:73";
char APPEUI[] = "01:01:01:01:01:01:01:01";
char CHMASK[] = "FF00:0000:0000:0000:0002:0000";

int counter = 0;
char str_counter[128];

void setup(){
  
  SendAtCommand(AT_CLASS, AtSet, "A");

  SendAtCommand(AT_NJM, AtSet, 0);

  SendAtCommand(AT_ADR, AtSet, 0);

  SendAtCommand(AT_DR, AtSet, 5);

  SendAtCommand(AT_CHMASK, AtSet, CHMASK);

  SendAtCommand(AT_APPEUI, AtSet, APPEUI);

  SendAtCommand(AT_APPSKEY, AtSet, APPSKEY);

  SendAtCommand(AT_NWKSKEY, AtSet, NWKSKEY);

  SendAtCommand(AT_DEVADDR, AtSet, DEVADDRESS);

  }

  void loop(){

    while(counter != 30){
        Serial.println(counter);
        sprintf(str_counter, "{\"variable_1\":\"solar\",\"value\":%d} \r\n\0", counter++);
        Serial.println(str_counter);
        SendString(str_counter, 2);
        delay(10000);
      }
    }
