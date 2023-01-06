//En esta directiva se crean las funciones para simplificar los codigos de escritura, lectura y edición de configuraciones de WiFi

#include "LedBlink.hpp"

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
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
    digitalWrite(MQTTLED, LOW);
    digitalWrite(WIFILED, LOW);
}

