
//Lecturas de archivos json que contienen información relevante a las confoguraciones siguientes:
// 1.- Lectura con configuraciones WIFI
//2.-Lectura con configuraciones MQTT
//3.- Lectura con configuraciones Relays
//-------------------------------------------------------------------//
//Función devolverá cierto o falso dependiendo las configuraciones WiFi
//Dependiendo de lo que leerá en los parámetros puestos en el WiFi
//Creará un archivo JSON de 500 Bytes con dicha información
//-------------------------------------------------------------------//
//Inicia función de configuraciones de lectura del WIFI
boolean settingsReadWiFi(){
StaticJsonDocument<500> jsonConfig;
File file = SPIFFS.open("/SettingWifi.json", "r"); //se abre en modo lectura (r, read) y se guarda en una variable tipo archivo (File)//
   if(deserializeJson(jsonConfig, file)){
    //Si falla la lectura, inicia valores por defecto
    settingResetWifi();
    log("Error: Falló la lectura de la configuración WiFi. Se tomarán los valores por defecto");
    return false;

       } else {
//Información general//
strlcpy(id, jsonConfig["id"], sizeof(id));
bootCount = jsonConfig["boot"];
//Cliente
wifi_staticIP = jsonConfig["wifi_staticIP"];
strlcpy(wifi_ssid, jsonConfig["wifi_ssid"], sizeof(wifi_ssid));
strlcpy(wifi_passw, jsonConfig["wifi_passw"], sizeof(wifi_passw));
strlcpy(wifi_ip_static, jsonConfig["wifi_ip_static"], sizeof(wifi_ip_static));
strlcpy(wifi_gateway, jsonConfig["wifi_gateway"], sizeof(wifi_gateway));
strlcpy(wifi_subnet, jsonConfig["wifi_subnet"], sizeof(wifi_subnet));
strlcpy(wifi_primaryDNS, jsonConfig["wifi_primaryDNS"], sizeof(wifi_primaryDNS));
strlcpy(wifi_secondaryDNS, jsonConfig["wifi_secondaryDNS"], sizeof(wifi_secondaryDNS));
//AP 
ap_accessPoint = jsonConfig["ap_accessPoint"];
strlcpy(ap_nameap, jsonConfig["ap_nameap"], sizeof(ap_nameap));
strlcpy(ap_passwordap, jsonConfig["ap_passwordap"], sizeof(ap_passwordap));
ap_canalap = jsonConfig["ap_canalap"];
ap_hiddenap = jsonConfig["ap_hiddenap"];
ap_connetap = jsonConfig["ap_connetap"];
file.close();
log("Info: Lectura de configuración WiFi correcta");
return true;
         }
} 
// -------------------------------------------------------------------
// Inicia función de lectura de configuraciones de los Parametros MQTT
//---------------------------------------------------------------------
boolean settingsReadMQTT(){
    // Lee la configuración MQTT
    StaticJsonDocument<500> jsonConfig;

    File file = SPIFFS.open(F("/settingmqtt.json"), "r"); //json en modo 'r' de lectura
    if (deserializeJson(jsonConfig, file)){
        // Si falla la lectura al deserealizarse, toma los valores por defecto
        settingsResetMQTT();
        log(F("Error: Falló la lectura de la configuración MQTT, tomando valores por defecto"));
        return false;
    }else{
        // Si lee el archivo
        strlcpy(mqtt_user, jsonConfig["mqtt_user"], sizeof(mqtt_user));
        strlcpy(mqtt_passw, jsonConfig["mqtt_passw"], sizeof(mqtt_passw));
        strlcpy(mqtt_server, jsonConfig["mqtt_server"], sizeof(mqtt_server));
        strlcpy(mqtt_id, jsonConfig["mqtt_id"], sizeof(mqtt_id));
        mqtt_time = jsonConfig["mqtt_time"];
        mqtt_port = jsonConfig["mqtt_port"];
        mqtt_enable = jsonConfig["mqtt_enable"];
        file.close();
        log(F("Info: Lectura de configuración MQTT correcta"));
        return true;
    }
}
// -------------------------------------------------------------------
// Inicia función de lectura de los estados de los Relays
// -------------------------------------------------------------------
boolean settingsReadRelays(){
    StaticJsonDocument<200> jsonConfig;
    File file = SPIFFS.open("/settingrelays.json", "r"); //json en modo 'r' de lectura
    if (deserializeJson(jsonConfig, file)){
        // Si falla la lectura al deserealizarse, inicia valores por defecto
        settingsResetRelays();
        log("Error: Falló la lectura del estados de los Relays, tomando valores por defecto");
        return false;
    }else{        
        Relay01_status = jsonConfig["Relay01_status"];
        Relay02_status = jsonConfig["Relay02_status"];
        file.close();
        log("Info: Lectura de los Relay correcta");
        return true;
}
}