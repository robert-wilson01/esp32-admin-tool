//Directiva relacionada con el conexion al broker MQTT
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttclient(espClient); 

char topico[150];
String mqtt_data ="";
long lastReconnectAttempt = 0;
long lastMqttReconnectAttempt = 0;
long lastMsg = 0;

void callback(char *topic, byte *payload, unsigned int length);
String Json();

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------Conexión al MQTT---------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
boolean mqtt_connect(){  
  
  mqttclient.setServer(mqtt_server, mqtt_port);
  mqttclient.setCallback(callback);
  log("Info: Intentando conexión al Broker MQTT...");

  // Conexion al Servidor MQTT , ClienteID, Usuario, Password.
  // Ver documentación del servicio utilizado en https://pubsubclient.knolleary.net/api.html  

  if (mqttclient.connect(mqtt_id, mqtt_user, mqtt_passw)) {  // Attempt to connect
    log("Info: Conectado al Broker MQTT");
    // ********************¡¡¡¡MUY IMPORTANTE ROBERTO!!!!: Nos suscribimos a comandos Topico: usuario/dispositivo/comando******************
    String topico_subscribe = String(mqtt_user)+"/"+mqtt_id+"/command"; //Concatenacion de la suscripcion
    topico_subscribe.toCharArray(topico, 150); //Crea variable char para el topic MQTT, un topic por cada cliente o estacion
    mqttclient.subscribe(topico); 

    topico_subscribe.toCharArray(topico, 25);
    mqttclient.publish(topico, "ok"); //Publicar respuesta ok por MQTT

  } else {
    log("Error: failed, rc= " + mqttclient.state());
    return(0);
  }

  return (1);

}
//--------------------------------------------------------------------------------------------------//
//--------------------------------Manejo de los mensajes entrantes al broker---------------------------
//-----------------------------------------------------------------------------------------------------//
void callback(char *topic, byte *payload, unsigned int length){
String mensaje = "";
String str_topic(topic);

for(uint16_t i=0; i < length; i++){
  mensaje += (char)payload[i];
  mqttRX();
}

mensaje.trim();
DynamicJsonDocument jsonDoc(300); //Se cra un documento json de 300

deserializeJson(jsonDoc, mensaje); //el mensaje entrante al broker se convierte en un json doc

//TODO: REALIZAR MANEJO DE ACCIONES AL LLEGAR UN DATO JSON
if(jsonDoc["RELAY1"] == "on"){
setOnSingle(RELAY1);
Relay01_status = HIGH;
settingsSaveRelays(); //Se guarda estatus de los RELAYS en el documento json
}else if (jsonDoc["RELAY1"] == "off"){
setOffSingle(RELAY1);
Relay01_status = LOW;
settingsSaveRelays(); //Se guarda estatus de los RELAYS en el documento json
}else if(jsonDoc["RELAY2"] == "on"){
setOnSingle(RELAY2);
Relay02_status = HIGH;
settingsSaveRelays(); //Se guarda estatus de los RELAYS en el documento json
}else if (jsonDoc["RELAY2"] == "off"){
setOffSingle(RELAY2);
Relay02_status = LOW;
settingsSaveRelays(); //Se guarda estatus de los RELAYS en el documento json
}

log("Info: Topico -->" + str_topic); //FUNCION PARA RECIBIR DATOS DEL BROKER, EL TOPICO DE SUSCRIPCION
log("Info: Mensaje -->" + mensaje); //FUNCION PARA RECIBIR DATOS DEL BROKER, MENSAJE ENVIADO

serializeJsonPretty(jsonDoc, Serial);


}

//------------------------------------------------------------------------------------------------------//
// -------------------------------Manejo de los Mensajes Salientes del broker---------------------------//
//-------------------------------------------------------------------------------------------------------//
void mqtt_publish(){
  
  String topic = String(mqtt_user)+"/"+mqtt_id+"/values"; //Concatenación del topic para suscribirse
  mqtt_data = Json();
  mqttclient.publish(topic.c_str(), mqtt_data.c_str());
  mqtt_data = "";

  mqttTX();

}
//------------------------------------------------------------------------------------------
// --------------------------JSON con informacion de envio por MQTT-----------------------
// ----------------------------------------------------------------------------------------
String Json(){

   String response;
   DynamicJsonDocument jsonDoc(3000);
   jsonDoc["WFDBM"] = WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0");
   jsonDoc["WFPRC"] = WiFi.status() == WL_CONNECTED ? String(getRSSIasQuality(WiFi.RSSI())) : F("0"); 
   jsonDoc["TempCPU"] = String(TempCPUValue()); 
   jsonDoc["RAMD"] = String(ESP.getFreeHeap() * 100 / ESP.getHeapSize()); 
   jsonDoc["FLASHU"] = String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()), 0);

   serializeJson(jsonDoc, response);   //Funcion de la libreria JSON de Arduino
   return response;

}
//----------------------------------------------------------------------------------------------
// -------------------------------------MQTT Loop Principal---------------------------------------
// -----------------------------------------------------------------------------------------------------
void mqttLoop(){
  if(mqtt_enable){                      //Si el MQTT está habiliado a los dispositivos, proceder
      
      if (!mqttclient.connected()) {    //Si el cliente esta conectado al MQTT, proceder, SINO, proceder a lo que sigue
        long now = millis();
        // try and reconnect continuously for first 60s then try again once every 120s
        if ( (now < 60000) || ((now - lastMqttReconnectAttempt)  > 120000) ) {
          lastMqttReconnectAttempt = now;
          if (mqtt_connect()) { // Intentar una reconección cada minuto y por cada falla, aumentar el minuto
            lastMqttReconnectAttempt = 0;
          }                   
          // Poner en ON el Led del MQTT, esto indica que esta intentando reconectar
          setOnSingle(MQTTLED);          
        }
      } else {
        // En caso de que la conexión al MQTT haya sido exitosa, proceder
        mqttclient.loop();
        // Poner en OFF el Led del MQTT, este apagado del LED permitirá una mejor visualización del parpadeo cuando haya transmisión
        //de los datos
        setOffSingle(MQTTLED);
      }
         
    }
}
