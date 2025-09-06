
#include "ArduinoJson.h"
#include <OneWire.h>
#include <SFE_BMP180.h>
#include <Wire.h>

// Настройка датчиков
OneWire ds(10);          // Датчик температуры DS18B20 на пине 10
SFE_BMP180 pressure;     // Датчик давления BMP180
const int ANALOG_PIN = 1; // Аналоговый пин для дополнительных измерений

// Встроенный светодиод для индикации
const int STATUS_LED = LED_BUILTIN;

void setup() {
  // Инициализация порта
  Serial.begin(9600);
  while (!Serial); // Для плат с USB (Leonardo/Micro)
  
  // Инициализация датчиков
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);
  
  if (pressure.begin()) {
    // Короткое мигание при успешной инициализации
    digitalWrite(STATUS_LED, HIGH);
    delay(200);
    digitalWrite(STATUS_LED, LOW);
  }
}

void loop() {
  // 1. Проверка входящих команд (максимальный приоритет)
  if (checkForCommand()) {
    return; // Если была команда - пропускаем отправку данных в этом цикле
  }
  
  // 2. Отправка данных датчиков (если не было команд)
  sendSensorData();
  delay(1000); // Пауза между отправками данных
}

bool checkForCommand() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    
    if (cmd == "WHO_ARE_YOU") {
      // Очистка буфера перед ответом
      while (Serial.available()) Serial.read();
      
      // Визуальная индикация
      digitalWrite(STATUS_LED, HIGH);
      
      // Отправка ответа
      Serial.println("i im meteo");
      
      // Завершение обработки команды
      delay(100);
      digitalWrite(STATUS_LED, LOW);
      return true;
    }
  }
  return false;
}

void sendSensorData() {
  // Получение данных с датчиков
  float temperature = readTemperature();
  double pressureVal = getPressure();
  int analogVal = analogRead(ANALOG_PIN);

  // Формирование JSON
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["val"] = analogVal;
  doc["pressure"] = pressureVal;
  

  // Отправка данных
  String json;
  serializeJson(doc, json);
  Serial.println(json);
}

float readTemperature() {
  byte data[12];
  byte addr[8];
  

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // Начало измерения
  delay(100);       // Ожидание измерения
  
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);    // Чтение результатов

  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);
  
  // Коррекция точности
  if (cfg == 0x00) raw &= ~7;
  else if (cfg == 0x20) raw &= ~3;
  else if (cfg == 0x40) raw &= ~1;
  
  return (float)raw / 16.0;
}

double getPressure() {
  char status;
  double T, P;

  status = pressure.startTemperature();
  if (status == 0) return -1.0;
  
  delay(status);
  status = pressure.getTemperature(T);
  if (status == 0) return -1.0;
  
  status = pressure.startPressure(3);
  if (status == 0) return -1.0;
  
  delay(status);
  status = pressure.getPressure(P, T);
  if (status == 0) return -1.0;
  
  return P;
}