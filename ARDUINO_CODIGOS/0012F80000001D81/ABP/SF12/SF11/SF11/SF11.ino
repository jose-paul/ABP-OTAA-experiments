/* Includes */

#include <LoRaWAN.h>
#include <SoftwareSerial.h>
#include <stdint.h>

/* SoftwareSerial handles */

SoftwareSerial* hSerialCommands = NULL;

/* Variables */

char str_counter[128];
int counter = 0;
int aux_count = 0;
/* Setup */

void setup()
{
Serial.begin(9600);
delay(1000);
Serial.println("Initializing…");

/* Initialize SoftwareSerial */
hSerialCommands = SerialCommandsInit(7, 6, 9600);

Serial.println("Reset…");
SendRaw("ATZ\r\n");
delay(5000);

Serial.println("Configurando ABP no device 8214…");
SendRaw("AT+NJM=0\r\n");
delay(1000);

SendRaw("AT+DR=1\r\n");
Serial.println("Configurando ADR para 1 = SF11");
delay(1000);

Serial.println("Configurando DADDR…");
SendRaw("AT+DADDR=00:8C:32:73\r\n");
delay(1000);

/* Configurando EndDevice como ABP */

Serial.println("Sending Nwk Key…");
SendRaw("AT+NWKSKEY=30:AA:2F:D0:5C:65:3B:EC:49:E2:06:C8:F5:1D:92:63");
delay(1000);

Serial.println("Sending App Key…");
SendRaw("AT+APPSKEY=61:19:DF:C0:8C:D5:EA:DB:79:52:B7:B7:25:8E:43:54");
delay(1000);

Serial.println("Sending Channel Mask…");
SendRaw("AT+CHMASK=FF00:0000:0000:0000:0002:0000"); // TTN
delay(1000);

Serial.println("Sending JOIN…");
SendRaw("AT+JOIN");
delay(1000);

Serial.println("Aguardando 30 segundos apos JOIN…");
delay(30000);
}

/* Loop ---------------------- */

void loop()
{
  sprintf(str_counter, "AT+TXCFM=83:1:3:{\"Contador\":\"contador\",\"value\":%d} \r\n\0", counter++);
  SendRaw(str_counter);
  Serial.println(str_counter);
  Serial.println("Aguardando 10 segundos apara proximo envio…");
  delay(10000);

}
