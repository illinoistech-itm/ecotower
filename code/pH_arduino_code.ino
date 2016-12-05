
#include <SoftwareSerial.h>                       
#define rx 0                                          
#define tx 1

SoftwareSerial myserial(rx, tx);                 


String inputstring = "";                        
String sensorstring = "";                          
boolean input_stringcomplete = false;            
boolean sensor_stringcomplete = false;             
float ph;                                         



void setup() {                                        
  Serial.begin(9600);                              
  myserial.begin(9600);                         
  inputstring.reserve(10);                       
  sensorstring.reserve(30);                           
}


void serialEvent() {                                 
  char inchar = (char)Serial.read();               
  inputstring += inchar;                        
  if (inchar == '\r') {                               
    input_stringcomplete = true;             
  }
}

void loop() {                                      

  if (input_stringcomplete) {                                       
    myserial.print(inputstring);                      
    inputstring = "";                          
    input_stringcomplete = false;                  
  }

  if (myserial.available() > 0) {                    
    char inchar = (char)myserial.read();             
    sensorstring += inchar;
    if (inchar == '\r') {
      sensor_stringcomplete = true;                
    }
  }


  if (sensor_stringcomplete) {                       
    Serial.println(sensorstring);                   
    ph = sensorstring.toFloat();                     

    if (ph >= 5.5 && ph<=6.2) {                     
                                                     
      Serial.println("Ideal");                    
    }

    if (ph <= 5.499) {                              
      Serial.println("Too Acidic");                      
    }

    if(ph >= 6.201){
      Serial.println("Too Basic");
    }


    sensorstring = "";                          
    sensor_stringcomplete = false;                  
  }
}
