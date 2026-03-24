#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>
#include <RTClib.h>

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Instancias de los sensores
Adafruit_AHTX0 aht; // Sensor Temp/Hum (0x38)
RTC_DS3231 rtc;     // Reloj RTC (0x68). Si usas DS1307, cambialo a RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println(F("\n--- Ejercicio Subida de Nota: Estacion + Reloj ---"));

  // 1. Inicializar Pantalla OLED
  Serial.print(F("Iniciando OLED... "));
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("ERROR"));
    for(;;);
  }
  Serial.println(F("OK"));
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // 2. Inicializar Sensor AHT (Temp/Hum)
  Serial.print(F("Iniciando Sensor AHT20 (0x38)... "));
  if (!aht.begin()) {
    Serial.println(F("ERROR"));
    for(;;);
  }
  Serial.println(F("OK"));

  // 3. Inicializar Reloj RTC
  Serial.print(F("Iniciando Reloj RTC (0x68)... "));
  if (!rtc.begin()) {
    Serial.println(F("ERROR"));
    for(;;);
  }
  Serial.println(F("OK"));

  // Si el reloj perdio la energia, lo ajustamos a la hora de compilacion del PC
  if (rtc.lostPower()) {
    Serial.println(F("RTC perdio energia, ajustando a la hora actual..."));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  Serial.println(F("--- Todo el hardware I2C inicializado correctamente ---"));
}

void loop() {
  // --- LECTURA DE DATOS ---
  // Leer Temperatura y Humedad
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  // Leer Hora del RTC
  DateTime now = rtc.now();

  // --- SALIDAS DE DEPURACIÓN (Puerto Serie) ---
  Serial.print(now.hour(), DEC); Serial.print(':');
  Serial.print(now.minute(), DEC); Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(F(" | Temp: "));
  Serial.print(temp.temperature);
  Serial.print(F("C | Hum: "));
  Serial.print(humidity.relative_humidity);
  Serial.println(F("%"));

  // --- ACTUALIZAR PANTALLA OLED ---
  display.clearDisplay();
  
  // Dibujar Hora (Grande)
  display.setTextSize(2);
  display.setCursor(0, 0);
  if(now.hour() < 10) display.print('0'); // Añadir 0 a la izquierda si es menor a 10
  display.print(now.hour(), DEC);
  display.print(':');
  if(now.minute() < 10) display.print('0');
  display.print(now.minute(), DEC);

  // Dibujar Temperatura y Humedad (Más pequeño)
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print(F("Temp: "));
  display.print(temp.temperature, 1); // 1 decimal
  display.print(F(" C"));

  display.setCursor(0, 45);
  display.print(F("Hum:  "));
  display.print(humidity.relative_humidity, 1);
  display.print(F(" %"));

  display.display();

  // Esperar 2 segundos antes de volver a leer
  delay(2000);
}