

//---------------------------------VALORES POR DEFECTO DE TODO EL SISTEMA----------------------------------
// Valores por defecto Parametros WIFI
// -------------------------------------------------------------------
void settingResetWifi(){
    //Informacion general//
    strlcpy(id, "adminesp32", sizeof(id));//Nombre por defecto al rest y al inicio es adminesp32
    bootCount = 0;

    //ESP32 como Cliente de MI RED PRIVADA//
    wifi_staticIP = false;
    strlcpy(wifi_ssid, "Totalplay-20A5_2.4Gnormal", sizeof(wifi_ssid)); //Nombre de mi RED PRIVADA
    strlcpy(wifi_passw, "kEpLeR2014360507", sizeof(wifi_passw)); //Contraseña de mi RED PRIVADA
    strlcpy(wifi_ip_static, "192.168.100.1", sizeof(wifi_ip_static)); //IP estática de mi RED PRIVADA 
    strlcpy(wifi_gateway, "192.168.0.1", sizeof(wifi_gateway)); 
    strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
    strlcpy(wifi_primaryDNS, "8.8.4.4", sizeof(wifi_primaryDNS));
    strlcpy(wifi_secondaryDNS, "8.8.4.4", sizeof(wifi_secondaryDNS));
    //ESP32 como AP//
    ap_accessPoint = false; //Access Pointe INHABILITADO, true para habilitarlo
    strlcpy(ap_nameap, deviceID().c_str(), sizeof(ap_nameap));
    strlcpy(ap_passwordap, "admin", sizeof(ap_passwordap)); //Contraseña definida para el AP
    ap_canalap = 9;
    ap_hiddenap = false;
    ap_connetap = 4;
}
// Valores por defecto Parametros del MQTT al efecturar el Reset
// -------------------------------------------------------------------
void settingsResetMQTT(){
    // Define configuración por defecto del equipo conexión MQTT
    strlcpy(mqtt_user, "robertowilson", sizeof(mqtt_user));
    strlcpy(mqtt_passw, "1234", sizeof(mqtt_passw));
    strlcpy(mqtt_server, "cubaelectronica.com", sizeof(mqtt_server));
    strlcpy(mqtt_id, deviceID().c_str(), sizeof(mqtt_id));
    mqtt_time = 60000;  // Un Minuto
    mqtt_port = 1883; //Puerto no muy seguro que digamos
    mqtt_enable = true;
}
//-------------------------------------------------------------------
// Valores por defecto Relays, es decir, apagador
// -------------------------------------------------------------------
void settingsResetRelays(){
    Relay01_status = LOW;
    Relay02_status = LOW;
}