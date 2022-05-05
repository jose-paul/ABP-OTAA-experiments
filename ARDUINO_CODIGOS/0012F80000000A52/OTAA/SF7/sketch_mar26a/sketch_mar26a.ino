#include <LoRaWAN.h>

/* Includes ---------------------- */
#include <SoftwareSerial.h>
#include <stdint.h>

/* SoftwareSerial handles */
SoftwareSerial* hSerialCommands = NULL;

char APPKEY[] = "5D:D2:A3:A1:5A:1F:00:CC:16:2A:1B:B9:92:F6:F8:65";
char APPEUI[] = "01:01:01:01:01:01:01:01";
char CHMASK[] = "FF00:0000:0000:0000:0002:0000"; //máscara TTN
//00FF:0000:0000:0000:0000:0000;//everynet
char str_counter[128];
int counter = 0;

void setup() {
  Serial.begin(9600); /* Initialize monitor serial */
  Serial.println("Initializing...");
  delay(5000);

  /* Initialize SoftwareSerial */
  hSerialCommands = SerialCommandsInit(7, 6, 9600);

  SendRaw("ATZ\r\n");
  Serial.println("Reset");
  delay(5000);
 
  SendRaw("AT+AJOIN=1\r\n");
  Serial.println("Configurando Auto Join");
  delay(1000);

  SendRaw("AT+DR=5\r\n");
  Serial.println("Configurando ADR para 5 = SF7");
  delay(1000);
  /* Configure the EndDevice as OTAA */
  //InitializeOTAA(APPKEY, APPEUI);
  SendAtCommand(AT_CHMASK, AtSet, CHMASK);
  delay(1000);
  Serial.println("Sending JOIN.");
  SendAtCommand(AT_JOIN, AtGet, NULL);
  if(JoinNetwork(0) == RAD_OK)
  {
    Serial.println("EndDevice has joined sucessfully.");
  }
  else
  {
    Serial.println("Error joining the network.");
  }

  
}

void loop() {
  Serial.println(counter);
  sprintf(str_counter, "{\"variable_1\":\"solar\",\"value\":%d} \r\n\0", counter++);
  Serial.println(str_counter);
  SendString(str_counter, 2);
  delay(10000);
}
