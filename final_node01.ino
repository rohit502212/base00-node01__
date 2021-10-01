#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


RF24 radio(10,9);

RF24Network network(radio);

int trig=3;
int echo=2;
long duration;
int distance;    
const uint16_t this_node = 02;   
const uint16_t master00 = 00;    
int count=1;
int sum=0;
int container2;
  int mData=0;
void setup() {
  // put your setup code here, to run once:
   
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  Serial.begin(9600);  
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

}

void loop() {
  
   network.update();
  //===== Receiving =====//
 
   while(network.available()){
    RF24NetworkHeader header;
    network.read(header,&mData,sizeof(mData));
    Serial.println(mData);
   }

   if(mData==9){
//          for(count;count<=1;count++){
          digitalWrite(trig,LOW);
          delayMicroseconds(2);
    
          digitalWrite(trig,HIGH);
          delayMicroseconds(10);
          digitalWrite(trig,LOW);
    
          duration=pulseIn(echo,HIGH);
          container2=duration*0.037/2;
//          sum+=distance;
           Serial.println(distance);
           
//           }
//           container2=(sum/1);
           Serial.print("container2:  ");
           Serial.println(container2);
            mData=0;
//            count=1;
//            sum=0;
    }
   

  //   //====sending====//
 
  RF24NetworkHeader header5(master00);//adress for sending data
  bool ok=network.write(header5,&container2,sizeof(container2));
  
    

 delay(13);


}
