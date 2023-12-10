// Analog pims responsible for the line tracking //  
#define LT_R analogRead(A0) //Analog pin A0 is responsible for Right Line Tracker  
#define LT_M analogRead(A1) //Analog pin A1 is responsible for Middle Line Tracker  
#define LT_L analogRead(A2) //Analog pin A2 is responsible for Left Line Tracker  


// Available Speeds //  
int MaxSPEED = 250;   
int MinSPEED = 50;    
int NormSPEED = 100;
int DontMOVE = 0;    
 
// Available Times //
int Stop = 0; 
int Time = 1000;  
int LineTrkTime = 0; 


void setup() {    

  Serial.begin(9600);   
 
 // Turn the ITR sensors' pins into Inputs
  pinMode(LT_R,INPUT);  
  pinMode(LT_M,INPUT);  
  pinMode(LT_L,INPUT);  
}    


void loop  () {    
  


static unsigned long print_time = 500;  

if (millis() - print_time > 1000) {  
 print_time = millis();  
 Serial.print("LT_L = ");  
 Serial.println(LT_L);  
 Serial.print("LT_M = ");  
 Serial.println(LT_M);   
 Serial.print("LT_R = ");  
 Serial.println(LT_R);  
 }  
}
