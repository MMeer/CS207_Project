//header files
/*
Mode Selection






*/
#include <SPI.h>
#include <Phpoc.h>
#include <PhpocClient.h>
#include <PhpocServer.h>

//setting the proxi port to port 80
PhpocServer server(80);

//variable declarations
boolean alreadyConnected = false; 
const int potPin = A0;
int pot_value;
int mode = 0;

void setup() {
    Serial.begin(9600); //Begin Serial
    while(!Serial)
        ;

    Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);

    server.beginWebSocket("game");

    Serial.print("WebSocket server address : ");
    Serial.println(Phpoc.localIP());
    
    pinMode(6, INPUT); //Set pins for buttons
    pinMode(7, INPUT); 
    pinMode(8, INPUT); 
    pinMode(9, INPUT); 
    
}

int value_6 = digitalRead(6); //Read initial values for buttons
int value_7 = digitalRead(7);
int value_8 = digitalRead(8);
int value_9 = digitalRead(9);
int pre_dir_1 = 0;
int pre_dir_2 = 0;
int dir_1 = 0; //Assign zero as initial value
int dir_2 = 0;


//loop function
void loop() {
    // when the client sends the first byte, say hello:
    PhpocClient client = server.available();
    
    pot_value = analogRead(potPin); //Read potentiometer value
    mode = map(pot_value, 0, 1024, 1, 2); //Map potentiometer value to a 1 or 2
    Serial.println(mode); //Print mode
    
    if(mode == 1){ //If mode is 1 execute code for two player game
      if (client) {
          value_6 = digitalRead(6); //Read values for buttons
          value_7 = digitalRead(7);
          value_8 = digitalRead(8);
          value_9 = digitalRead(9);
          dir_1 = value_7 - value_6; //Get direction by subtracting both values
          dir_2 = value_9 - value_8;
  
          if(dir_1 != pre_dir_1 || dir_2 != pre_dir_2) //If direction is diffrent send new values to server
          {
              pre_dir_1 = dir_1;
              pre_dir_2 = dir_2;
              
              String txtMsg = "[" + String(dir_1) + ", " + String(dir_2) + "]\r\n";  
              char buf[txtMsg.length()+ 1];
              txtMsg.toCharArray(buf, txtMsg.length() + 1);
              server.write(buf, txtMsg.length());
          }         
      }
    }

    if(mode == 2){ //If mode is 2 execute code for single player racing game
         if (client) {       
          value_6 = digitalRead(6); //Read values from buttons
          value_7 = digitalRead(7);
          dir_1 = value_7 - value_6; //Get direction from difference of button values
          if(pre_dir_1 != dir_1){ //If value is different from last time send new value to server
              String txtMsg = String(dir_1) + "\r\n";  
              char buf[txtMsg.length()];
              txtMsg.toCharArray(buf, txtMsg.length());
              server.write(buf, txtMsg.length());
              Serial.println(txtMsg);
              
              pre_dir_1 = dir_1;
              delayMicroseconds(50);
  
          }
      }
    }
}
