
//-------------------------------------------------------------------//
//Función devolverá cierto o falso dependiendo las configuraciones WiFi
//Dependiendo de lo que leerá en los parámetros puestos en el WiFi
//Creará un archivo JSON de 500 Bytes con dicha información
//-------------------------------------------------------------------//
boolean settingsReadWifi(){
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