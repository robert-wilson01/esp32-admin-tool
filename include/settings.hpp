
//Archivo para definir configuraciones en general para el dispositivo ESP32

//----------------------//
//Definiciones
//----------------------//
#define RELAY1  27 //GPI027 como salida de Relay 1
#define RELAY2  26 //GPI026 como salida de Relay 2
#define WIFILED 12 //GPI012 como LED indicador del WiFi
#define MQTTLED 13 //GPI013 como LED indicador MQTT
//----------------------//
//Versión del Hardware
//----------------------//
#define HW "ADMINESP32 v1 00000000" //Versión del Hardware
//----------------------//
//Configuraciones generales
//----------------------//
char id[30];                   //ID del dispositivo
int  bootCount;                 //Número de resets
//----------------------//
//Variables para el WiFi
//----------------------//
boolean wifi_staticIP;            //Para el estado del uso de la IP Estática, sí o no
char    wifi_ssid[30];            //Nombre de Red WiFi
char    wifi_passw[30];           //Contraseña de Red WiFi
char    wifi_ip_static[15];       //IP Estático
char    wifi_gateway[15];         //Gateway
char    wifi_subnet[15];          //Subred
char    wifi_primaryDNS[15];      //DNS primario
char    wifi_secondaryDNS[15];    //DNS secundario
//----------------------//
//Variables para el Acces Point (AP) 
//----------------------//
boolean ap_accessPoint;     //Uso del modo AP
char    ap_nameap[31];      //SSID AP
char    ap_passwordap[63];  //Password AP
int     ap_canalap;         //Canal del AP
int     ap_hiddenap;        //Estado en que si es visible o no el AP (0 visible - 1 oculto)
int     ap_connetap;        // Numero de conexiones al AP
//----------------------//
//Zona de otras variables auxiliares
//----------------------//
uint8_t ip[4];             //Variable de la funcion que convierte los strings a cadena IP