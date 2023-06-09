#include "SPI.h"      // библиотека для протокола SPI
#include "nRF24L01.h" // библиотека для nRF24L01+
#include "RF24.h"     // библиотека для радио модуля

const uint64_t pipe = 0xF0F1F2F3F4LL; // идентификатор передачи
RF24 radio(9,10); // Для MEGA2560 замените на RF24 radio(9,53);

void setup() {
  Serial.begin(9600);  // запускаем последовательный порт
  radio.begin();       // включаем радио модуль
  radio.setChannel(0); // выбираем канал (от 0 до 127)

    // скорость: RF24_250KBPS, RF24_1MBPS или RF24_2MBPS
  radio.setDataRate(RF24_1MBPS);
    // мощность: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM
  radio.setPALevel(RF24_PA_HIGH);

  radio.openReadingPipe(1, pipe);    // открываем первую трубу
  radio.startListening();            // начинаем слушать трубу
}

void loop() {
  int data;
  
  if (radio.available())             // проверяем буфер обмена
  {
    radio.read(&data, sizeof(data)); // читаем данные
    Serial.print("data: ");
    Serial.println(data);            // выводим данные на монитор порта
  }
}