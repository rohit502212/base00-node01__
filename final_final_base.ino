#include <RF24Network.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

int state=0;
int tx=1;  //////bluetooth module
int rx=0;
RF24 radio(10,9);

RF24Network network(radio);

int trig=3;
int echo=2;
long duration;
int distance;
int blData2=9;
int conData=0;

int container1=0;
int container2=0;
int container3=0;
const uint16_t this_node=00;
const uint16_t node01 = 01;
const uint16_t node02 = 02;

void setup() {
 
  SPI.begin();
  radio.begin();
  network.begin(90,this_node);
  radio.setDataRate(RF24_2MBPS);
  Serial.begin(9600);
  pinMode(trig,OUTPUT);///ultra sonic sensors
  pinMode(echo,INPUT);///ultra sonic sensors
  pinMode(tx,OUTPUT);
  pinMode(rx,INPUT);
}

void loop() {
//    delay(500); 
    network.update();                                        
    if (Serial.available() > 0) {             
       
         state=Serial.read();
         }
      
    if(state=='1'){
              //sending data to node 01
      RF24NetworkHeader header2(node01);//adress for sending data
      bool ok=network.write(header2,&blData2,sizeof(blData2));
      
      //sending data to node 02
      RF24NetworkHeader header3(node02);//adress for sending data
      bool ok2=network.write(header3,&blData2,sizeof(blData2));
      

        

           digitalWrite(trig,LOW);
          delayMicroseconds(2);
    
          digitalWrite(trig,HIGH);
          delayMicroseconds(10);
          digitalWrite(trig,LOW);
    
          duration=pulseIn(echo,HIGH);
          container1=duration*0.037/2;

 
        state=0;
      }
   
   while(network.available()){
  RF24NetworkHeader header;     
  network.read(header,&conData,sizeof(conData));
  if(header.from_node==1){
    container2=conData;
     }

       if(header.from_node==2){
    container3=conData;
     }
     
     }

     if(state=='2'){
//      for(int i=1;i<=2;i++){
        Serial.print((int)container1);
        Serial.print('|');
        Serial.print((int)container2);
        Serial.print('|');
        Serial.print((int)container3);
        Serial.println("");
//        delay(50);
//      }
        state=0;
      }

}
