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

SendRaw("AT+DR=0\r\n");
Serial.println("Configurando ADR para 0= SF12");
delay(1000);

Serial.println("Configurando DADDR…");
SendRaw("AT+DADDR=01:AE:F4:9E\r\n");
delay(1000);

/* Configurando EndDevice como ABP */

Serial.println("Sending Nwk Key…");
SendRaw("AT+NWKSKEY=12:E3:E0:9A:5E:40:0D:56:6B:5B:F9:D2:36:37:A4:0E");
delay(1000);

Serial.println("Sending App Key…");
SendRaw("AT+APPSKEY=C3:D3:10:09:0F:30:3C:C5:1B:4B:28:41:E7:28:D4:7E");
delay(1000);

Serial.println("Sending Channel Mask…");
SendRaw("AT+CHMASK=FF00:0000:0000:0000:0002:0000"); // TTN
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
