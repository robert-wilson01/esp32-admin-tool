


void settingResetWifi(){
    //Informacion general//
    strlcpy(id, "adminesp32", sizeof(id));//Nombre por defecto al rest y al inicio es adminesp32
    bootCount = 0;

    //Cliente//
    wifi_staticIP = false;
    strlcpy(wifi_ssid, "Totalplay-20A5_2.4Gnormal", sizeof(wifi_ssid));
    strlcpy(wifi_passw, "kEpLeR2014360507", sizeof(wifi_passw));
    strlcpy(wifi_ip_static, "192.168.100.1", sizeof(wifi_ip_static));
    strlcpy(wifi_gateway, "192.168.0.1", sizeof(wifi_gateway));
    strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
    strlcpy(wifi_primaryDNS, "8.8.4.4", sizeof(wifi_primaryDNS));
    strlcpy(wifi_secondaryDNS, "8.8.4.4", sizeof(wifi_secondaryDNS));
    //AP//
    ap_accessPoint = true;
    strlcpy(ap_nameap, deviceID().c_str(), sizeof(ap_nameap));
    strlcpy(ap_passwordap, "admin", sizeof(ap_passwordap));
    ap_canalap = 9;
    ap_hiddenap = false;
    ap_connetap = 4;


}