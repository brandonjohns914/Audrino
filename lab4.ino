void setup()
{

int ad[8] = {38,40,42,44,46,48,50,52};
int ale = 49;
int address = 0; 
pinMode(49, OUTPUT);
for (int i = 0; i < 8; i++) {
      pinMode(ad[i], INPUT);
  }

 

  // set all address pins to outputs
  for (int i = 0; i < 8; i++) {
      pinMode(ad[i], OUTPUT);
  }
 

 digitalWrite(49,HIGH);
 
 digitalWrite(52,HIGH); 
 digitalWrite(50,HIGH); //AD6 BLUE
 digitalWrite(48,HIGH); // orange/yellow = AD5
 digitalWrite(46,HIGH); // PINK = AD4
 digitalWrite(44,HIGH); //ORANGE = AD3
 digitalWrite(42,HIGH); //RED = AD2
 digitalWrite(40,HIGH); //red = AD1
 digitalWrite(38,HIGH); //Green = AD0

 digitalWrite(43,HIGH); //purple = AD0


  digitalWrite(43,HIGH); //Read blue
  digitalWrite(45,HIGH); // write // orange
  digitalWrite(51, HIGH);// green M_io
 
 // it works
}

void loop()
{


 

}
