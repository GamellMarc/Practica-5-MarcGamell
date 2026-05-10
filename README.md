# Pràctica 5 - Processadors Digitals: Busos de Comunicació (I2C)

Aquest repositori conté els codis font i la memòria corresponents a la **Pràctica 5** de l'assignatura de Processadors Digitals. L'objectiu d'aquest projecte és l'aprenentatge, configuració i ús del protocol de comunicació síncron **I2C (*Inter-Integrated Circuit*)** per connectar múltiples perifèrics a un microcontrolador ESP32-S3.

## 📂 Estructura del Repositori

El repositori està dividit en les següents carpetes i fitxers, reflectint l'evolució de la pràctica des de la detecció bàsica de maquinari fins a la creació d'una estació IoT completa:

* **`Practica5Ex1/`** (Escàner I2C): 
  * Eina de diagnòstic de maquinari. 
  * Codi encarregat de rastrejar el bus I2C (adreces de 1 a 127) per detectar qualsevol dispositiu físic connectat i retornar la seva adreça hexadecimal (ACK) pel terminal sèrie.

* **`Practica5Ex2/`** (Display OLED I2C): 
  * Control gràfic mitjançant I2C. 
  * Programa per inicialitzar una pantalla OLED SSD1306 i enviar de forma massiva un *buffer* de dades des de la RAM de l'ESP32 per dibuixar geometries i text ("Hello, world!").

* **`Practica5Complementari1/`** (Estació Meteorològica i Rellotge OLED): 
  * Gestió multidispositiu (Mestre i 3 Esclaus). 
  * Projecte on l'ESP32 conviu al mateix bus I2C amb una pantalla OLED (`0x3C`), un sensor de temperatura/humitat AHT20 (`0x38`) i un rellotge RTC DS3231 (`0x68`). Llegeix dades atmosfèriques i temporals i les representa visualment en temps real.

* **`Practica5Complementari2/`** (Servidor Web I2C): 
  * Integració IoT (I2C + Wi-Fi). 
  * El projecte definitiu on l'ESP32 actua de servidor web asíncron. En rebre una petició HTTP, llegeix els sensors AHT20 i RTC pel bus I2C i serveix els valors encapsulats en una pàgina web HTML interactiva amb refresc automàtic.

* **`InformePràctica5PD.pdf`**: 
  * Memòria completa i detallada de la pràctica. Inclou l'explicació de l'arquitectura de codi de cada exercici, els diagrames de flux, l'anàlisi de temps de la CPU (explicant l'alliberament del bus) i les sortides obtingudes.

## 🛠️ Tecnologies i Maquinari Utilitzat

* **Microcontrolador:** Placa de desenvolupament ESP32-S3 (Mestre I2C)
* **Dispositius I2C (Esclaus):** * Pantalla OLED 128x64 (Controlador SSD1306)
  * Sensor de Temperatura i Humitat relatiu (AHT20)
  * Mòdul de Rellotge de Temps Real (RTC DS3231)
* **Entorn de desenvolupament:** Visual Studio Code amb l'extensió PlatformIO.
* **Llenguatge:** C++ (Framework d'Arduino)
* **Llibreries principals:** `Wire.h`, `WebServer.h`, `Adafruit SSD1306`, `Adafruit GFX`, `Adafruit AHTX0`, `RTClib`.

## 👤 Autor
**Marc Gamell**
