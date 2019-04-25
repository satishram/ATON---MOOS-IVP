#include <Servo.h>
Servo depth1;
Servo depth2;
Servo depth3;

Servo mt1;
Servo mt2;
int incomingByte = 0;   // for incoming serial data
int prv = 0;
int dec=0;
int rud=4,thu=0,nim=0,th=1,dp=0,dep=0;

void setup()

{

  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  depth1.attach(10);
  depth2.attach(11);
  depth3.attach(12);

  mt1.attach(6);
  mt2.attach(5);
//rudder.write(0);
     //thruster.write(0);
     mt1.writeMicroseconds(1500);
     mt2.writeMicroseconds(1500);


}



void

loop()

{

digitalWrite(13,HIGH);

  // send data only when you receive data:

  if (Serial.available() > 0)

    {
//82 R
//84 T
      // read the incoming byte:

      incomingByte = Serial.read();
      //Serial.println(Serial.read());
      incomingByte=incomingByte-48;
      if (incomingByte== (82-48))//for rudder
      {
        //Serial.println("in rudder");
      dec = 1;
      
      }
      else if (incomingByte == (84-48)) 
      {
        //Serial.println("in thruster");
      dec = 2;
      }   
     else if (incomingByte == (68-48)) 
      {
        //for depth
      dec = 3;
      }     
      else 
      {
      prv=incomingByte;
      }
     switch(dec)
     {
     case 1:
     {
       
     //int degree=map(prv,0,10,10,170);
     rud= prv;
     Serial.println("rud");
     Serial.println(rud);
      //rudder.write(degree);
      break;
     }
     case 2:
     {
       //Serial.println("in t set");
     //int degree=map(prv,0,10,45,70);
      th=prv;
      //thruster.write(degree);
      break;
     }
     case 3:
     {
     dp=prv;
     }
     default:
     {
     //rudder.write(0);
     //thruster.write(0);
     break;
     }
     
     
     }
     if (dp>5)
     {
     //upword or reverse menover
     Serial.println("depth rev");
     depth1.write(1500);
     depth2.write(1500);
     depth3.write(1500);
     }
     else
     {
     dep=map(dp,5,1,1501,1600);
     Serial.println("depth");
     Serial.println(dep);
     depth1.write(dep);
     depth2.write(dep);
     depth3.write(dep);
     }
     thu=map(th,0,9,1501,1600);
     Serial.println("thu");
     Serial.println(thu);
     dec=0;
     //op_rt=2+thu-rud;
     //op_lt;
     if (rud==4)
     {
     // it is equal
     Serial.println("in equal condition");
     
     mt1.writeMicroseconds(thu);
     mt2.writeMicroseconds(thu);
     }
     else if(rud>4)
     {
       Serial.println("in rt cond");
       nim=map(rud,4,9,1,200);
       Serial.println("mt1");
       Serial.println(thu-nim);
       Serial.println("mt2");
       Serial.println(thu+nim);
       mt1.writeMicroseconds(thu-nim);
     mt2.writeMicroseconds(thu+nim);
     // rt is fast
     }
     else if (rud<4)
     {
       nim=map(rud,4,0,1,200);
       Serial.println("in lt cond");
       Serial.println("mt1");
       Serial.println(thu+nim);
       Serial.println("mt2");
       Serial.println(thu-nim);
     
       mt1.writeMicroseconds(thu+nim);
     mt2.writeMicroseconds(thu-nim);
     }
      //int degree=map(incomingByte,0,10,10,170);
      //rudder.write(degree);// position of the rudder

      /*switch (incomingByte)

        {

      case '1':

        digitalWrite(13,HIGH);

        break;

      case '2':

        digitalWrite(13,LOW);

        break;
      default:

        digitalWrite(13,LOW);

        break;

        }



      

*/

      //Serial.println(incomingByte);

    }

}
