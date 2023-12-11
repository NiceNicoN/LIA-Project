//* Remote Control *//

//This code uses the InfraRed Remote Control to Control //
//the directions of Elegoo Car                          //

//Include the IR remote Library
#include <IRremote.hpp>   //This library contains the codes necessary to use the InfraRed Remote Control

// Standby pin
int STBY = 3;

// Pins on the Arduino that belong to the motors' of the wheels // 

//Motor A  (Motors on the right side of the car)
int PWMA = 5;    // Pin 5 controls how fast Motor A is spinning
int AIN1 = 8;    // Pin 8 controls in which direction (forward or backward) Motor A is spinning

//Motor B  (Motors on the left side of the car)
int PWMB = 6;    // Pin 6 controls how fast Motor B is spinning
int BIN1 = 7;    // Pin 7 controls in which direction (forward or backward) Motor B is spinning
  
// Pin recieving commands from Infra Red remote
int IR_PIN = 9;
 
// Remote Direction Buttons
int FRONT = 70;  // The IR sensor detects number 70 from the button designated front
int BACK = 21;   // The IR sensor detects number 21 from the button designated back
int RIGHT = 68;  // The IR sensor detects number 68 from the button designated right
int LEFT = 67;   // The IR sensor detects number 67 from the button designated left
int OK = 64;     // The IR sensor detects number 64 from the button designated ok

// Available Speeds //    These will be the the Y variables when a command is called
int MaxSPEED= 250;   
int MinSPEED= 50;    
int NormSPEED= 100;    
int DontMOVE= 0;  

// Available Times //     These will be the the X variables when a command is called)
int Stop = 0; 
int Time = 1000;  
int IRResponseTime = 0; 



void Forward(int x,int y){  //Forward command  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,1);    //The comand of 1(HIGH) makes the motor move forward

  //Motor B      
  analogWrite (PWMB, y);    //Motor A is powered at speed y
  digitalWrite (BIN1,1);    //The comand of 1(HIGH) makes the motor move forward
} 

void Backward(int x,int y){ //Backward command  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,0);    //The comand of 0(LOW) makes the motor move backward

  //Motor B
  analogWrite (PWMB, y);    //Motor B is powered at speed y
  digitalWrite (BIN1,0);    //The comand of 0(LOW) makes the motor move backward
}   

void Left(int x,int y){ //Left command  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,1);    //The comand of 1(HIGH) makes the motor move forward

  //Motor B    
  analogWrite (PWMB, y);    //Motor B is powered at speed y
  digitalWrite (BIN1,0);    //The comand of 0(LOW) makes the motor move backward

 // In the case of the Left command, Motor A is moving forward at full speed and Motor B is moving backwards at full speed
 // causing the Car to spin to the Left in the same spot.
}

void Right(int x,int y){ //Right command  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,0);    //The comand of 0(LOW) makes the motor move backward

  //Motor B    
  analogWrite (PWMB, y);    //Motor B is powered at speed y  
  digitalWrite (BIN1,1);    //The comand of 1(HIGH) makes the motor move forward
  
 // In the case of the Right command, Motor A is moving backward at full speed and Motor B is moving forwards at full speed
 // causing the Car to spin to the Right in the same spot.
}   

void Standby(){ //Standby command  
  //motor A     
  analogWrite (PWMA,0);     //Motor A is powered at speed 0

  //Motor B       
  analogWrite (PWMB,0);     //Motor B is powered at speed 0
}       



void setup(){

  Serial.begin(9600);// open the serial port at 9600 bps:

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
  
  if (IrReceiver.decode()) {    // If IR Sensor recieves a command, it should decode it and run this loop
   
   Serial.println(IrReceiver.decodedIRData.command);     // The Serial Monitor should display the value of the decoded IR signal

   if(IrReceiver.decodedIRData.command == OK){           //If the the recieved value is equal to the to the value representd by "OK", run the next line of code
     Standby();                                          //Run the Standby command
    }
   else if(IrReceiver.decodedIRData.command == FRONT){   //If the the recieved value is equal to the to the value representd by "FRONT", run the next line of code
     Forward(IRResponseTime,NormSPEED);                  //Run the Forward command, at 0 seconds, at 100 speed
    }
   else if(IrReceiver.decodedIRData.command == BACK){    //If the the recieved value is equal to the to the value representd by "BACK", run the next line of code
     Backward(IRResponseTime,NormSPEED);                 //Run the Backward command, at 0 seconds, at 100 speed
    }
   else if(IrReceiver.decodedIRData.command == RIGHT){   //If the the recieved value is equal to the to the value representd by "RIGHT", run the next line of code
     Right(IRResponseTime,NormSPEED);                    //Run the Right command, at 0 seconds, at 100 speed
    }
   else if(IrReceiver.decodedIRData.command == LEFT){    //If the the recieved value is equal to the to the value representd by "LEFT", run the next line of code
     Left(IRResponseTime,NormSPEED);                     //Run the Left command, at 0 seconds, at 100 speed
    }

    IrReceiver.resume(); // Enables the receiving of the next value
  }
}
