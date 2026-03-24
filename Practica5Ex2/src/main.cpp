#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Alto de la pantalla (ajusta a 32 si tu pantalla es más delgada)

#define OLED_RESET    -1 // Pin de reset (usamos -1 si comparte el reset del ESP32)
#define SCREEN_ADDRESS 0x3C // Dirección I2C de la pantalla

// Declaración de la pantalla conectada por I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  // Pequeña pausa para dar tiempo a que se abra el monitor serie
  delay(1000); 
  
  Serial.println(F("\n--- Iniciando Ejercicio 2: Pantalla OLED ---"));
  Serial.print(F("Buscando pantalla SSD1306 en la direccion: 0x"));
  Serial.println(SCREEN_ADDRESS, HEX);

  // Genera el voltaje de la pantalla internamente
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("ERROR: Fallo al inicializar la pantalla OLED."));
    Serial.println(F("Por favor, revisa las conexiones SDA (GPIO 8) y SCL (GPIO 9)."));
    for(;;); // Bucle infinito para detener el programa si hay error
  }
  
  Serial.println(F("EXITO: Pantalla OLED inicializada correctamente."));

  Serial.println(F("Limpiando el buffer de la pantalla..."));
  display.clearDisplay(); 

  Serial.println(F("Configurando estilo de texto..."));
  display.setTextSize(1); // Escala del texto 1:1
  display.setTextColor(SSD1306_WHITE); // Dibujar texto en blanco
  display.setCursor(0,0); // Empezar en la esquina superior izquierda
  
  Serial.println(F("Escribiendo mensaje 'Hello, world!'..."));
  display.println(F("Hello, world!")); // Imprimir texto en el buffer
  
  Serial.println(F("Enviando los datos a la pantalla física..."));
  display.display(); 
  
  Serial.println(F("--- Proceso de inicializacion terminado ---"));
}

void loop() {
  // Bucle vacío
}