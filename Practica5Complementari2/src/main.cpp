#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_AHTX0.h>
#include <RTClib.h>

// --- Credenciales Wi-Fi ---
const char* ssid = "Nautilus";
const char* password = "20000Leguas";

// --- Instancias de Servidor y Sensores ---
WebServer server(80); // Servidor web en el puerto estándar 80
Adafruit_AHTX0 aht;
RTC_DS3231 rtc;

// --- Función que genera y envía la página Web ---
void handleRoot() {
  // 1. Leer los sensores
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  DateTime now = rtc.now();

  // 2. Construir la respuesta HTML
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<meta http-equiv=\"refresh\" content=\"5\">"; // La página se recarga sola cada 5 segundos
  html += "<title>Estación ESP32-S3</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f9; color: #333; margin-top: 50px; }";
  html += "h1 { color: #0056b3; }";
  html += ".caja { background: white; border-radius: 10px; padding: 20px; box-shadow: 0 4px 8px rgba(0,0,0,0.2); display: inline-block; }";
  html += ".dato { font-size: 24px; font-weight: bold; margin: 10px 0; }";
  html += "</style></head><body>";
  
  html += "<h1>Panel de Sensores I2C</h1>";
  html += "<div class=\"caja\">";
  
  // Formatear la hora
  html += "<p class=\"dato\">Hora actual: ";
  if(now.hour() < 10) html += "0";
  html += String(now.hour()) + ":";
  if(now.minute() < 10) html += "0";
  html += String(now.minute()) + ":";
  if(now.second() < 10) html += "0";
  html += String(now.second()) + "</p>";

  // Mostrar Temperatura y Humedad
  html += "<p class=\"dato\">Temperatura: " + String(temp.temperature, 1) + " &deg;C</p>";
  html += "<p class=\"dato\">Humedad: " + String(humidity.relative_humidity, 1) + " %</p>";
  
  html += "</div>";
  html += "</body></html>";

  // 3. Enviar el HTML al navegador del usuario
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- Iniciando Servidor Web I2C ---");

  // Iniciar Sensores I2C (usarán GPIO 8 y 9 por defecto en el S3)
  if (!aht.begin()) {
    Serial.println("Error al iniciar el sensor AHT20.");
  }
  if (!rtc.begin()) {
    Serial.println("Error al iniciar el RTC.");
  }

  // Conectar al Wi-Fi
  Serial.print("Conectando a la red Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Esperar hasta que se conecte
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("¡Conectado al Wi-Fi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP()); // IMPRESCINDIBLE: Aquí verás qué IP poner en el navegador

  // Configurar las rutas del servidor web
  server.on("/", handleRoot); // Cuando alguien entre a la raíz ("/"), ejecuta handleRoot

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor Web iniciado. Esperando clientes...");
}

void loop() {
  // El ESP32 debe estar constantemente "escuchando" si algún cliente pide la web
  server.handleClient();
}