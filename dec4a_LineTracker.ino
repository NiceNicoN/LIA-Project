// Analog pims responsible for the line tracking //  
#define LT_R analogRead(A0) //Analog pin A0 is responsible for Right Line Tracker  
#define LT_M analogRead(A1) //Analog pin A1 is responsible for Middle Line Tracker  
#define LT_L analogRead(A2) //Analog pin A2 is responsible for Left Line Tracker  


// Standby pin
int STBY = 3;

// Pins on the Arduino that belong to the motors' of the wheels // 

//Motor A
int PWMA = 5;    
int AIN1 = 8;    

//Motor B
int PWMB = 6;    
int BIN1 = 7;
 
// Available Speeds //  
int MaxSPEED = 250;   
int MinSPEED = 50;    
int NormSPEED = 100;
int DontMOVE = 0;    
 
// Available Times //
int Stop = 0; 
int Time = 1000;  
int LineTrkTime = 0;  



void Forward(int x,int y){  //Forward command  
  //motor A    
  analogWrite (PWMA,y);    
  digitalWrite (AIN1,1);    

  //Motor B      
  analogWrite(PWMB, y); 
  digitalWrite (BIN1,1);    
} 

void Backward(int x,int y){ //Backward command  
  //motor A    
  analogWrite (PWMA,y);    
  digitalWrite (AIN1,0);

  //Motor B
  analogWrite(PWMB, y);
  digitalWrite (BIN1,0);
}   

void Left(int x,int y){ //Left command  
  //motor A    
  analogWrite (PWMA,y);    
  digitalWrite (AIN1,1);

  //Motor B    
  analogWrite(PWMB, y);    
  digitalWrite (BIN1,0); 
}   

void Right(int x,int y){ //Right command  
  //motor A    
  analogWrite (PWMA,y);    
  digitalWrite (AIN1,0);    

  //Motor B    
  analogWrite(PWMB, y);    
  digitalWrite (BIN1,1);    
}   

void Standby(){ //Standby command  
  //motor A     
  analogWrite (PWMA,0); 
  digitalWrite (AIN1,1);     

  //Motor B       
  analogWrite(PWMB,0);     
  digitalWrite (BIN1,1);       
}     

void Search(int x,int y){ //Search command. It turns left umtil it finds the line  
  //motor A    
  analogWrite (PWMA,y);    
  digitalWrite (AIN1,1);

  //Motor B    
  analogWrite(PWMB, y);    
  digitalWrite (BIN1,0); 
}   



void setup() {    

  Serial.begin(9600);   

  // Turn the Motors pins into Outputs
  pinMode(AIN1, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);
  digitalWrite(STBY, 1);

  // Turn the ITR sensors' pins into Inputs
  pinMode(LT_R,INPUT);  
  pinMode(LT_M,INPUT);  
  pinMode(LT_L,INPUT);  
}    

 

void loop  () {    

if(LT_L >=850 && LT_M >=850 && LT_R >=850){ 
  Standby();   
  Serial.println("STOP"); 
}  
else if(LT_M >=450 && LT_M <=950) {  
  Forward(LineTrkTime,NormSPEED); 
  //Serial.println("GO FORWARD"); 
}  
else if(LT_M <=450){ 
  if (LT_R >=600 && LT_L <=100){ 
    Right(LineTrkTime,MinSPEED); 
    Serial.println("TURN RIGHT"); 
  } 
  else if(LT_L >=600 && LT_R <=100){  
   Left(LineTrkTime,MinSPEED); 
   Serial.println("TURN LEFT"); 
  } 
  else if(LT_L <=70 && LT_M <=70 && LT_R <=300){ 
   Serial.println("Searching...");  
   Search(LineTrkTime,NormSPEED);
  } 
}
delay (50);
Standby();  
 

static unsigned long print_time = 500;  

if (millis() - print_time > 1500) {  
 print_time = millis();  
 Serial.print("LT_L = ");  
 Serial.println(LT_L);  
 Serial.print("LT_M = ");  
 Serial.println(LT_M);   
 Serial.print("LT_R = ");  
 Serial.println(LT_R);  
 }  
}
