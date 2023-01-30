//**Archivos guaradados los estados

//---------------------------------------------------------------------------------
//------------Guardar los estados de los Relays-----------------------------------
//------------------------------------------------------------------------
boolean settingsSaveRelays(){
    // Guarda configuración de los Relays
    StaticJsonDocument<200> jsonConfig;
    File file = SPIFFS.open(F("/settingrelays.json"), "w+"); //Se abre el ARCHIVO EN MODO LECTURA 
    if (file){ //Sie l archivo esta abierto, se le guardan los parametros de los relays
        jsonConfig["Relay01_status"] = Relay01_status;
        jsonConfig["Relay02_status"] = Relay02_status;
        serializeJsonPretty(jsonConfig, file);
        file.close();
        log(F("Info: Estado de los Relay guardado")); //Se imprime en el puerto serial el guardado exitoso de los relays
        serializeJsonPretty(jsonConfig, Serial);
        return true; //Retorna un verdadero porque es una funcion booleana
    }else{ //De otro modo, implica un problrma en el guardado de los parametros de los relay e indica en consola un fallo
        log(F("Error: Falló el guardado del estado de los Relay"));
        return false;
    }
}