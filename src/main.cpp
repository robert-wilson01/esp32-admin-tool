
//---------------------------------------------------------------//
//Región para librerías//
//--------------------------------------------------------------//
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
//-------------------------------------------------------------//
//Región de archivos .hpp y fragmentación del código
//-------------------------------------------------------------//
#include "settings.hpp" 
#include "functions.hpp" 
#include "settingsReset.hpp" 
#include "settingsRead.hpp"
#include "settingsSave.hpp" 
#include "esp32_wifi.hpp" 
#include "esp32_mqtt.hpp"
//-----------------------------------------------------------------------------//
//Setup principal del ESP32 al incicializarse//
//-----------------------------------------------------------------------------//

void setup() {
  // ------------------------------------------Setup de única lectura:
  //1.- Definición de la Baudrate tasa de transferencia
  Serial.begin(115200);

  //2.- Frecuencia de CPU de ESP32
  setCpuFrequencyMhz(240);
  //3.-Inicio del log por el puerto serial
  log("/nInfo: Iniciando setup");
  //4.-Configuración de los pines
  settingPines();
// 5.-Inicio del SPIFFS. Primer filtro que asegura la correcta funcionalidad del chip                 
    if (!SPIFFS.begin(true)){
        log(F("Error: Falló la inicialización del SPIFFS"));
        while (true);
    }
  //6.-Lee los estados de los Relays
  settingsReadRelays();
  //7.- Se colocan los estados a los Relays
  setOnOffSingle(RELAY1, Relay01_status);
  setOnOffSingle(RELAY2, Relay02_status);
  //7.-Lee configuraciones del WiFi
  settingsReadWiFi();
   //8.- Desconecta el WIFI 1 segundo suficiente para abandonar la conexion
  WiFi.disconnect(true);
  delay(1000);
  // Puesta en marcha de configuración Setup del WiFI
  wifi_setup();
  //Lectura de la configuración del MQTT a través de los json
  settingsReadMQTT();
}
//-------------------------------------------------------------------------------------------------//
//-----------------------------------------------Loop principal-------------------------------------//
//------------------------------------------------------------------------------------------------//
void loop() {
  
  yield();

  //------------------------------------------------------------------
  //WIFI, ejecuta ESP32 como cliente <estación> o AP
  //------------------------------------------------------------------
  if (wifi_mode == WIFI_STA){
  wifiLoop();
  }else if(wifi_mode == WIFI_AP){
  wifiAPLoop();
  }
  //------------------------------------------------------------------
  //MQTT, ejecuta conexión del ESP32 al MQTT
  //------------------------------------------------------------------
  //FIXME: Arreglar error
  
    if ((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA)){ //Aseguramiento de conexión exitosa a WiFi primero que nada
        if(mqtt_server != 0){                                        //Aseguramiento conexión al servidor exitoso 
            mqttLoop();
            if (mqttclient.connected()){                             //Asrguramiento conexión al broker exitoso 
                if (millis() - lastMsg > mqtt_time){
                    lastMsg = millis();                               //envio de mensaje a publicar al broker cada ciertos milisegundos
                    mqtt_publish();
                }
            }      
        }
    }

}
