
  // AD0 = 38 purple | AD1 = 40 blue | AD2 = 42 orange | AD3 = 44 yellow  |AD4 = 46 purple | AD5 = 48 yelloworange | AD6= 50 green | AD7 = 52 red
  // Control Signals ALE = 49 | RD = 43| WR = 45 | M_IO = 51 

  //ports 
  // A = 0b00000000 | B = 0b00000001 | C = 0b00000010 | CR = 0b00000011

  //rows
  // Row1 = 0b000000001 | Row2 = 0b000000010 | Row3 = 0b000000100 | Row4 0b000001000
void setup() 
{
  Serial.begin(9600);
 
  ControlSignal_ALE_RD_WR_MIO();
    
  // SET CR for A == OUT B== IN 
  Serial.println("SETTING CR: ");
  INput_OUTput_WRITE(0xE3, 0x82); 
  delay(100); 

  byte value = INput_OUTput_RD(0x01);
  Serial.print("READ value from B: ");
  Serial.println(value, HEX);
  INput_OUTput_WRITE(0xE0, 0x01);

}
 
void loop()
{
int i; 
  
  byte count_ROWs  = 0x01;
  
  for( i = 1; i <=4; i++)
  {
    INput_OUTput_WRITE(0xE0, count_ROWs);

    // active rows 
    count_ROWs = count_ROWs << 1;

    // Reads column pressed during loop
    byte columns = INput_OUTput_RD(0xE1);
  
    if(columns == 0)continue;
    else
      {
      Serial.println("keypad value");
      }
  } 
}

void ControlSignal_ALE_RD_WR_MIO()
{
  int i;  
  // starting outputing pins 43 - 51 
  for( i = 43; i <= 51; i = i + 2)
  {
    pinMode(i, OUTPUT);
  }
  
// 82C55 requires M_IO to start low 
  digitalWrite(51, LOW);  

  // ALE LOW = DATA
  // HIGH = ADDR 
  digitalWrite(49, LOW);
  
   // WR HIGH
  digitalWrite(45, HIGH);
  
  // RD HIGH
  digitalWrite(43, HIGH);
}

void INput_OUTput_WRITE(byte ADDR, byte DATA){
  
  // USING ALE to demultiplex the address to select the port 
  ALE_AD(ADDR);

  // setting the data 
  Setting_Address_DataPins(DATA); 

  // Starting WR active low
  digitalWrite(45, LOW); 
  delay(30);

  // ending WR making HIGH
  digitalWrite(45, HIGH); 
}

byte INput_OUTput_RD(byte ADDR)
{
  int i; 
  // using ALE to find ADDR for a port 
  ALE_AD(ADDR);

  // INputing RD 
  for (i = 38; i<=52; i = i+2)
  {
    pinMode(i, INPUT);
  }
  
  //  Starting RD Signal 
  digitalWrite(43, LOW); 
  delay(10); 
  
  int RD_value = 0;
  int bits = 7;
  byte byte_value; 
  for(i = 52; i>= 38; i=i-2)
  { 
    RD_value = digitalRead(i);
    bitWrite(byte_value, bits, RD_value);
    bits--;
  }

  // ending read
  digitalWrite(43, HIGH); 
  // returning value of the byte 
  return byte_value;
}

//setting the DATA pins 
void Setting_Address_DataPins(byte in) 
{
  
  int count_BIT = 0;
  int i; 
  // writing to AD0-AD7 data pins 
  for ( i = 38; i<=52; i = i+2)
  { 
   digitalWrite(i, bitRead(in, count_BIT)); 
   count_BIT++;
  }
  delay(10);
}

void ALE_AD(byte ADDR) 
{ 
  int i; 
  // Outputting AD0-AD7 
  for (i = 38; i<=52; i = i+2)
  {
    pinMode(i, OUTPUT);
  }

  int count_BIT = 0; 
  // writing to address of AD0-AD7 
  for ( i = 38; i<=52; i = i+2) 
  { 
   digitalWrite(i, bitRead(ADDR, count_BIT)); 
   count_BIT++; 
  }
  delay(10);

  // ALE =  ADO-AD7 = HIGH = ADDRESS
  digitalWrite(49, HIGH); // ALE H = Address, L = Data
  delay(20); 
  // ALE = AD0-AD7 =  LOW = DATA 
  digitalWrite(49, LOW); 
}
