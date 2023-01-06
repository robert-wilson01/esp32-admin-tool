//Esn esta directiva se podrá hacer parpadear los leds indicadores de estado de cada área del dispositivo ESP32
//relacionado al estado de indicación de conexión, como el de un módem

#include <Arduino.h>
bool ioBlink = false;
unsigned long milOld;
int rndTemp = 0;

//Función para usar en Pestañeos simples para alarmas con tiempos variables 
void blinksingle(int speed, int _pin){
    if((milOld + speed) < millis()){
        milOld = millis();
        if(ioBlink == false){
            digitalWrite(_pin,HIGH);
            ioBlink = true;
        }
        else{
            digitalWrite(_pin,LOW);
            ioBlink = false;
        }

    }
}
//Función para usar en Pestañeos asíncronos en tiempos variables de ON y OFF
void blinksingleAsy(int timeHigh, int timeLow, int _pin){
    if(ioBlink == false){
        if((milOld + timeHigh) < millis()){
            milOld = millis();
            digitalWrite(_pin,LOW);
            ioBlink = true;
        }
    }
        else{
            if((milOld + timeLow) < millis()){
                milOld = millis();
                digitalWrite(_pin,HIGH);
                ioBlink = false;
            }
        }
}
//Función para usar en Pestañeos de retrasos aleatorios, usado en transferencias de datos TX/RX
void blinkRandomSingle(int minTime, int maxTime, int _pin){
    if((milOld + rndTemp) < millis()){
        milOld = millis();
        rndTemp = random(minTime,maxTime);
        if(ioBlink == false){
            digitalWrite(_pin,HIGH);
            ioBlink = true;
        }
        else{
            digitalWrite(_pin,HIGH);
            ioBlink = false;
        }

    }
}
//On para un LED
void setOnSingle(int _pin){
    digitalWrite(_pin,HIGH);
}
//OFF para un LED
void setOffSingle(int _pin){
    digitalWrite(_pin, LOW);
}