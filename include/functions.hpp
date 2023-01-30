//En esta directiva se crean las funciones para simplificar los codigos de escritura, lectura y edición de configuraciones de WiFi
//Las funciones contienen mecanismos de actuacion en los GPIOS del ESP32
#include "LedBlink.hpp"

//Libreria especial del ESP32 para conocer su temperatura, sacada de su datasheet
#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

//-------------------------------------------------------------------//
//Generar un log en el puerto serial para tener que repetir los println
//-------------------------------------------------------------------//
void log(String s){
    Serial.println(s);
}
// -------------------------------------------------------------------
// Definir la Plataforma
// -------------------------------------------------------------------
String platform(){
// Optiene la plataforma de hardware
#ifdef ARDUINO_ESP32_DEV
    return "ESP32";
#endif
}

// -------------------------------------------------------------------
// Convierte un char a IP
// -------------------------------------------------------------------
IPAddress CharToIP(const char *str){
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}

// -------------------------------------------------------------------
// Retorna IPAddress en formato "n.n.n.n" de IP a conversion a String
// -------------------------------------------------------------------
String ipStr(const IPAddress &ip){    
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;
}


//-------------------------------------------------------------------//
//De HEX a String
//-------------------------------------------------------------------//
String hexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 -1);
    return s;
}
//-------------------------------------------------------------------//
//Crear un ID único desde la dirección MAC
//-------------------------------------------------------------------//
String idUnique(){
    //Retornará los ultimos 4 bytes del MAC cambiados//
    char idunique[15];
    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}
// -------------------------------------------------------------------
// ID del Dispositivo para La Base de Datos
// -------------------------------------------------------------------
String deviceID(){
    return String(platform()) + hexStr(ESP.getEfuseMac()) + String(idUnique());
}
// -------------------------------------------------------------------
// Configurar los Pines de Salida
// -------------------------------------------------------------------
void settingPines(){
    //dos pines de salida para relay y dos pines de salida para LED
    pinMode(WIFILED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    //Se inicializan en nivel bajo
    setOffSingle(RELAY1);
    setOffSingle(RELAY2);
    setOffSingle(WIFILED);
    setOffSingle(MQTTLED);
}
// -------------------------------------------------------------------
// Hacer parpadear LED MQTT de la Transmisión de datos al broker
// -------------------------------------------------------------------
void mqttTX(){ 
    for (int i = 0; i < 2; i++){
        setOnSingle(MQTTLED);
        delay(50);
        setOffSingle(MQTTLED);
        delay(10);
    }  
}

// -------------------------------------------------------------------
// Hacer parpadear LED MQTT de la Recepción de datos al broker
// -------------------------------------------------------------------
void mqttRX(){
    for (int i = 0; i < 1; i++){
        blinkRandomSingle(5,50,MQTTLED);
        delay(5);
    }
}
// -------------------------------------------------------------------
// Retorna información de la calidad de señal WIFI en %
// -------------------------------------------------------------------
int getRSSIasQuality(int RSSI){
    int quality = 0;
    if(RSSI <= -100){
        quality = 0;
    } else if(RSSI >= -50){
        quality = 100;
    } else{
       quality = 2 * (RSSI + 100); 
    }
    return quality;
}
// -------------------------------------------------------------------
// Retorna información de la temperatura del CPU
// -------------------------------------------------------------------
float TempCPUValue (){
    return TempCPU = (temprature_sens_read() - 32) / 1.8;
}