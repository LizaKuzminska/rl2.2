#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Створюємо два об'єкти для датчиків
Adafruit_BMP280 bmp1; 
Adafruit_BMP280 bmp2; 

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println(F("Тест двох BMP280 через I2C"));

  // Запуск першого датчика на стандартній адресі 0x76
  if (!bmp1.begin(0x76)) {
    Serial.println(F("Не знайдено 1-й датчик (0x76)!"));
    while (1);
  }

  // Запуск другого датчика на зміненій адресі 0x77
  if (!bmp2.begin(0x77)) {
    Serial.println(F("Не знайдено 2-й датчик (0x77)! Перевірте пін SDO!"));
    while (1);    
  }

  Serial.println(F("Обидва датчики на зв'язку!"));
}

void loop() {
  // Зчитування даних
  float t1 = bmp1.readTemperature();
  float p1 = bmp1.readPressure() / 100.0F;

  float t2 = bmp2.readTemperature();
  float p2 = bmp2.readPressure() / 100.0F;

  // Вивід даних
  Serial.print("Датчик 1: ");
  Serial.print(t1); Serial.print(" C, ");
  Serial.print(p1); Serial.println(" hPa");

  Serial.print("Датчик 2: ");
  Serial.print(t2); Serial.print(" C, ");
  Serial.print(p2); Serial.println(" hPa");

  Serial.println("-----------------------");
  delay(2000);
}
