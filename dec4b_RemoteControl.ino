//Include the IR remote Library
#include <IRremote.hpp>

// Standby pin
int STBY = 3;

// Pins on the Arduino that belong to the motors' of the wheels // 

//Motor A
int PWMA = 5;    
int AIN1 = 8;    

//Motor B
int PWMB = 6;    
int BIN1 = 7;
  
// Recieving Pin for Infra Red
int IR_PIN = 9;
 
// Remote Direction Buttons
int FRONT = 70;
int BACK = 21;
int RIGHT = 68;
int LEFT = 67;
int OK = 64;

// Available Speeds //  
int MaxSPEED= 250;   
int MinSPEED= 50;    
int NormSPEED= 100;    
int DontMOVE= 0;  

// Available Times //
int Stop = 0; 
int Time = 1000;  
int IRResponseTime = 0; 



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



void setup(){

  Serial.begin(9600);

  // Turn the Motors pins into Outputs
  pinMode(AIN1, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);
  digitalWrite(STBY, 1);

  // Start the InfraRed Receiver
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK); 
}



void loop() {

  if (IrReceiver.decode()) {

   Serial.println(IrReceiver.decodedIRData.command); // Print raw data

   if(IrReceiver.decodedIRData.command == OK){
     Standby();
    }
   else if(IrReceiver.decodedIRData.command == FRONT){
     Forward(IRResponseTime,NormSPEED);
    }
   else if(IrReceiver.decodedIRData.command == BACK){
     Backward(IRResponseTime,NormSPEED);
    }
   else if(IrReceiver.decodedIRData.command == RIGHT){
     Right(IRResponseTime,NormSPEED);
     //delay(450);
    // Standby();
    }
    else if(IrReceiver.decodedIRData.command == LEFT){
     Left(IRResponseTime,NormSPEED);
    // delay(450);
     //Standby();
    }

    IrReceiver.resume(); // Enable receiving of the next value
  }
}
