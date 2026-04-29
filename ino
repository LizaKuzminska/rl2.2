#include <Wire.h>
// Бібліотека для I2C (шина, по якій підключені датчики)

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
// Бібліотеки для роботи з BMP280


// ---------------- ДВА ДАТЧИКИ ----------------

// Створюємо ДВА окремих об'єкти.
// Це як дві "копії" датчика, але з різними адресами.
Adafruit_BMP280 bmp1; 
Adafruit_BMP280 bmp2; 


void setup() {

  Serial.begin(115200);
  while (!Serial);
  // Чекаємо поки Serial підключиться (корисно для деяких плат)

  Serial.println(F("Тест двох BMP280 через I2C"));


  // ---------- ПЕРШИЙ ДАТЧИК ----------

  // Запускаємо датчик на адресі 0x76 (стандартна)
  if (!bmp1.begin(0x76)) {
    Serial.println(F("Не знайдено 1-й датчик (0x76)!"));
    while (1);
    // Якщо датчик не знайдений — зависаємо
  }


  // ---------- ДРУГИЙ ДАТЧИК ----------

  // Запускаємо другий датчик на адресі 0x77
  // Це та сама модель, але з іншою адресою!
  if (!bmp2.begin(0x77)) {
    Serial.println(F("Не знайдено 2-й датчик (0x77)! Перевірте пін SDO!"));
    while (1);    
  }

  Serial.println(F("Обидва датчики на зв'язку!"));
}


void loop() {

  // ---------- ЗЧИТУВАННЯ З ПЕРШОГО ----------

  float t1 = bmp1.readTemperature();
  // температура в °C

  float p1 = bmp1.readPressure() / 100.0F;
  // тиск в hPa (бо за замовчуванням Pa)


  // ---------- ЗЧИТУВАННЯ З ДРУГОГО ----------

  float t2 = bmp2.readTemperature();

  float p2 = bmp2.readPressure() / 100.0F;


  // ---------- ВИВІД ----------

  Serial.print("Датчик 1: ");
  Serial.print(t1); 
  Serial.print(" C, ");
  Serial.print(p1); 
  Serial.println(" hPa");

  Serial.print("Датчик 2: ");
  Serial.print(t2); 
  Serial.print(" C, ");
  Serial.print(p2); 
  Serial.println(" hPa");

  Serial.println("-----------------------");

  delay(2000);
  // оновлення кожні 2 секунди
}
