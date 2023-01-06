
//----------------------//
//Región para librerías//
//----------------------//
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
//----------------------//
//Región de archivos .hpp y fragmentación del código
//----------------------//
#include "settings.hpp" 
#include "functions.hpp" 
#include "settingsReset.hpp" 
#include "settingsRead.hpp"
#include "settingsSave.hpp" 
#include "esp32_wifi.hpp" 

//----------------------//
//Setup//
//----------------------//

void setup() {
  // put your setup code here, to run once:
  //Baudrate tasa de transferencia
  Serial.begin(115200);

  //Frecuemncia de CPU de ESP32
  setCpuFrequencyMhz(240);
  //Inicio del log por el puerto serial
  log("/nInfo: Iniciando setup");
  //Configuración de los pines
  settingPines();
// Inicio del SPIFFS. Primer filtro que asegura la correcta funcionalidad del chip                 
    if (!SPIFFS.begin()){
        log(F("Error: Falló la inicialización del SPIFFS"));
        while (true);
    }
  //lee configuraciones del WiFi
  settingsReadWifi();
   // Configuracion WIFI
  WiFi.disconnect(true);
  delay(1000);
  // Setup del WiFI
  wifi_setup(); 
}

void loop() {
  // put your main code here, to run repeatedly:
}