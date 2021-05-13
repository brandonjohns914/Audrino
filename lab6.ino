void setup()
{

  /// Worked in collaboration with Kevin La 
  Serial.begin(9600);


  ///Brandon Lab 4
  int ad[8] = {38, 40, 42, 44, 46, 48, 50, 52};
  int ale = 49;
  int address = 0;

  byte data1;
  byte data2; 
  pinMode(43, OUTPUT); //read
  pinMode(45, OUTPUT); //write
  pinMode(49, OUTPUT);// ale
  pinMode(51, OUTPUT); //M_IO
  for (int i = 0; i < 8; i++) {
    pinMode(ad[i], INPUT);
  }



  // set all address pins to outputs
  for (int i = 0; i < 8; i++) {
    pinMode(ad[i], OUTPUT);
  }


  digitalWrite(49, LOW);//ale
  digitalWrite(43,HIGH); //Read blue
  digitalWrite(45,HIGH); // write // orange
  digitalWrite(51, HIGH);// green M_io


  digitalWrite(52, HIGH); //orange = AD7
  digitalWrite(50, HIGH); // blue = AD6
  digitalWrite(48, HIGH); // white = AD5
  digitalWrite(46, HIGH); // green = AD4
  digitalWrite(44, HIGH); //yellow = AD3
  digitalWrite(42, HIGH); //purple = AD2
  digitalWrite(40, HIGH); //pink = AD1
  digitalWrite(38, HIGH); //red = AD0


  MemWrite(0b00110010, 0b00010110);
  MemWrite(0b01010101, 0b11110000);
  data1 = MemRead(0b00110010);
  data2 = MemRead(0b01010101);

  
}

// Done by Kevin La
void MemWrite(byte address, byte data)
{
  setADtoOUTput();
  setAD(address);
  LatchALE();

  Serial.print('\n');
  Serial.print("Writing to Address: ");
  
  for (int i = 7; i >= 0; i = i - 1)
    Serial.print(bitRead(address, i));
    
  
  setAD(data);
  
  Serial.print('\n');
  Serial.print("Data Written: ");
  
  for (int i = 7; i >= 0; i = i - 1)
    Serial.print(bitRead(data, i));
    //write
  digitalWrite(45, LOW);
  
  delay(2000); //write
  digitalWrite(45, HIGH);
}
// done by Kevin La 
byte MemRead(byte address)
{
  setADtoOUTput();
  setAD(address);
  LatchALE();

  byte data;
  int val = 0;
  int counter = 7;
  Serial.print('\n');
  Serial.print("reading from Address: ");
  for(int i = 7; i>= 0; i = i-1)
    Serial.print(bitRead(address,i));

    //READ SRAM
    setADtoINput();
    digitalWrite(43, LOW);
    delay(2000); 
    Serial.print("    ");

    if(bitRead(address, 7) == 1 && bitRead(address, 6) == 1)
      {
        Serial.println("");
        Serial.print("Data read from SRAM2 is: ");
        Serial.println("");
      }
    else 
      {
        Serial.println("");
        Serial.print("Data read from SRAM1 is: ");
        Serial.println("");
      }
      


/// sram to AD0-AD7
   for(int i =52; i>= 38; i= i-2)
   {
    val = digitalRead(i);
    bitWrite(data, counter, val);
    counter--;
   }

      // print
for(int i =7; i >=0; i = i-1)
  Serial.print(bitRead(data,i));

  Serial.print(" decimal: ");
  Serial.print(data);

  Serial.println("");
//rd
  digitalWrite(43, HIGH);

  return data; 
      
}
// Done by Brandon Johns
void setADtoOUTput()
{
  for (int i = 38; i <= 52; i = i + 2)
    pinMode(i, INPUT);
}

// Done by Brandon Johns 
void setADtoINput()
{
  for (int i = 38; i <= 52; i = i + 2)
    pinMode(i, OUTPUT);
}

// Done by Brandon Johns 
void setAD(byte in)
{
  int count = 0;
  for (int i = 38; i <= 52; i = i + 2)
  {
    digitalWrite(i, bitRead(in, count));
    count = count + 1;
  }
  delay(1000);
}

// Done by Brandon Johns 
void LatchALE()
{
  digitalWrite(49, HIGH);
  delay(1000);
  digitalWrite(49, LOW);
  delay(1000);
}
void loop()
{




}
