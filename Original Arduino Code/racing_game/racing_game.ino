/*
Arduino Code for Racing Game, single player
*/
#include <Phpoc.h>
#include <PhpocClient.h>
#include <PhpocServer.h>

#include "SPI.h"
#include "Phpoc.h"

PhpocServer server(80);
int adcPin = A0;   
float adcVal = 0;  // variable to store the value coming from the sensor
int lastPos = -1;  
float adcMin = 512-2.5*100;
void setup() {
    Serial.begin(9600);
    while(!Serial)
        ;
    
    Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);

    server.beginWebSocket("game");

    Serial.print("WebSocket server address : ");
    Serial.println(Phpoc.localIP());   
}

void loop() {
    // when the client sends the first byte, say hello:
    PhpocClient client = server.available();
    
    if (client) {
        
        adcVal = 0;
        for(int i = 0; i < 50; i++)
            adcVal += analogRead(adcPin);
            
        adcVal /= 50;
        int pos = (int)((adcVal-adcMin) / 100);
        if (pos<0){
          pos = 0;
        }
        else 
          if (pos>4) pos =4;  
              
        if(lastPos != pos){
            String txtMsg = String(pos) + "\r\n";  
            char buf[txtMsg.length()];
            txtMsg.toCharArray(buf, txtMsg.length());
            server.write(buf, txtMsg.length());
            Serial.println(txtMsg);
            
            lastPos = pos;
            delayMicroseconds(50);

        }
 

    }

    
}
