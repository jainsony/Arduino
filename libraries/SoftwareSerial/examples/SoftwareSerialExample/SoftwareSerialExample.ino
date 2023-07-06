#include <Arduino.h>
#include "wiring_private.h"

Uart mySerial (&sercom0, 5, 6, SERCOM_RX_PAD_1, UART_TX_PAD_0);

// Attach the interrupt handler to the SERCOM
void SERCOM0_Handler()
{
    mySerial.IrqHandler();
}

void setup() {
  // Reassign pins 5 and 6 to SERCOM alt
  pinPeripheral(5, PIO_SERCOM_ALT);
  pinPeripheral(6, PIO_SERCOM_ALT);

  // Start my new hardware serial
  mySerial.begin(9600);
}

void loop() {
  // Do something with mySerial...
  Serial.println("Data from port two:");
}