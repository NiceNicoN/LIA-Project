//Include the Servo Motor Library
#include <Servo.h>

//Create the Servo Object to control the Servo Motor
Servo myservo;

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
  
// Recieving Pin for Infra Red
int IR_PIN = 9;
 
// Pins for the Ultrasonic Sensor
int trigPin = 13; 
int echoPin = 12;

float duration, distance;

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
  analogWrite (PWMA,100);    
  digitalWrite (AIN1,1);    

  //Motor B      
  analogWrite(PWMB, 100); 
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

void LeftForward(int x,int y){   //Left Forward command
  //motor A  
  analogWrite (PWMA,y);  
  digitalWrite (AIN1,1);  
 
  //Motor B  
  analogWrite(PWMB, y/2);  
  digitalWrite (BIN1,1);  
} 

void RightForward(int x,int y){   //Right Forward command
  //motor A   
  analogWrite (PWMA,y/2);   
  digitalWrite (AIN1,1);

  //Motor B   
  analogWrite(PWMB, y);   
  digitalWrite (BIN1,1);    
}  

void LeftBackward(int x,int y){   //Left Backward command  
 //motor A   
  analogWrite (PWMA,y);   
  digitalWrite (AIN1,0);   
  
  //Motor B   
  analogWrite(PWMB, y/2);   
  digitalWrite (BIN1,0);     
}

void RightBackward(int x,int y){  //Right Backward command
  //motor A   
  analogWrite (PWMA,y/2);   
  digitalWrite (AIN1,0);   

  //Motor B   
  analogWrite(PWMB, y);   
  digitalWrite (BIN1,0);     
}   

void Standby(){ //Standby command  
  //motor A     
  analogWrite (PWMA,0); 
  digitalWrite (AIN1,1);     

  //Motor B       
  analogWrite(PWMB,0);     
  digitalWrite (BIN1,1);       
}  

void Ultrasonic(){  //Ultrasonic command
  // Write a pulse to the HC-SR04 Trigger Pin 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(echoPin, HIGH);

  // Determine distance from duration  
  // Use 343 meters per second as speed of sound
  distance = (duration / 2) * 0.0343; 
  return(int)distance;
}



void setup(){

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

  // Declare the pupose of each Ultrasonic pin
  pinMode(trigPin, OUTPUT);  // trig pin outputs sonic signals
  pinMode(echoPin, INPUT);   // trig pin recieves sonic signals that bounced back

  // Attaches the servo on pin 10 to the Servo Object
  myservo.attach(10);
}



void loop() {

  //if(LT_L >=1000 && LT_M >=1000 && LT_R >=1000){ 
   // Standby();   
    //Serial.println("STOP");
 // }
  
  if (distance > 20){
    Forward(0,NormSPEED);
    myservo.write(90);
    Ultrasonic();
  }

  else if (distance < 20){
    Standby();
    delay(1000);
    myservo.write(0);
    delay(1000);
    Ultrasonic();

    if (distance < 20){
     Right(3000,NormSPEED);
     myservo.write(90);
    }
    
    else if (distance < 20){
     Standby();
     delay(1000);
     myservo.write(180);
     delay(100);
     Ultrasonic();
     delay(250);
     Ultrasonic();
     
      if (distance > 20){
       Left (750,NormSPEED);
       myservo.write(90);
      }
      else if( distance < 20){
       Backward (500,NormSPEED);
       Left(1400,NormSPEED);
       myservo.write(90);
      }
     }
  }
  
}
  
