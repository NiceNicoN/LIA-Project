//* Obstacle Avoidance *//

//This code uses the HC-SR04 Ultasonic Sensor to measure distance.//
//Here it is paired with a SG90 Servo Motor to help it detect     //
//obstacles in a field of 180°. This in turn helps the Elegoo Car //
//avoid collisions, avoid and back out of corners.                //


//Include the Servo Motor Library
#include <Servo.h>  //This library contains the codes necessary to use the SG90 Servo Moror

//Create the Servo Object to control the Servo Motor
Servo myservo;

// Analog pims responsible for the line tracking //  
#define LT_R analogRead(A0) //Analog pin A0 is responsible for Right Line Tracker  
#define LT_M analogRead(A1) //Analog pin A1 is responsible for Middle Line Tracker  
#define LT_L analogRead(A2) //Analog pin A2 is responsible for Left Line Tracker  

// Standby pin
int STBY = 3;

// Pins on the Arduino that belong to the motors' of the wheels // 

//Motor A  (Motors on the right side of the car)
int PWMA = 5;    // Pin 5 controls how fast Motor A is spinning
int AIN1 = 8;    // Pin 8 controls in which direction (forward or backward) Motor A is spinning

//Motor B  (Motors on the left side of the car)
int PWMB = 6;    // Pin 6 controls how fast Motor B is spinning
int BIN1 = 7;    // Pin 7 controls in which direction (forward or backward) Motor B is spinning
 
// Pins for the Ultrasonic Sensor
int trigPin = 13;           //Pin 13, the Trigger pin, is the one driven to send out the ultrasonic pulses
int echoPin = 12;           //Pin 12, the Echo in, is the one that produces a pulse when the reflected signal is received.

// Precise Variables
float duration, distance;   //With float, the duration and distace variables become precise to the decimal

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
  digitalWrite (AIN1,1);    //The comand of 1(HIGH) makes motor A move forward

  //Motor B      
  analogWrite (PWMB, y);    //Motor A is powered at speed y
  digitalWrite (BIN1,1);    //The comand of 1(HIGH) makes motor B move forward
} 

void Backward(int x,int y){ //Backward command  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,0);    //The comand of 0(LOW) makes motor A move backward

  //Motor B
  analogWrite (PWMB, y);    //Motor B is powered at speed y
  digitalWrite (BIN1,0);    //The comand of 0(LOW) makes motor B move backward
}   

void Left(int x,int y){ //Left command  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,0);    //The comand of 0(LOW) makes motor A move backward

  //Motor B    
  analogWrite(PWMB, y);     //Motor B is powered at speed y
  digitalWrite (BIN1,1);    //The comand of 1(HIGH) makes motor B move forward

  // In the case of the Left command, Motor A is moving backward at full speed and Motor B is moving forwards at full speed
  // causing the Car to spin to the Left in the same spot.
}   

void Right(int NormSPEED){ //Right command  
  //motor A    
  analogWrite (PWMA, NormSPEED);     
  digitalWrite (AIN1,1);    

  //Motor B    
  analogWrite(PWMB, NormSPEED);    
  digitalWrite (BIN1,0);
}

//void Right(int x,int y){ //Right command  
  //motor A    
  //analogWrite (PWMA,y);     //Motor A is powered at speed y
  //digitalWrite (AIN1,1);    //The comand of 1(HIGH) makes motor A move forward

  //Motor B    
  //analogWrite(PWMB, y);     //Motor B is powered at speed y
  //digitalWrite (BIN1,0);    //The comand of 0(LOW) makes motor B move backward

  // In the case of the Right command, Motor A is moving forward at full speed and Motor B is moving backwards at full speed
  // causing the Car to spin to the Right in the same spot.
//}   

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
  analogWrite (PWMA,0);     //Motor A is powered at speed 0

  //Motor B       
  analogWrite (PWMB,0);     //Motor B is powered at speed 0
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
  
  if (distance <= 20){   //if true that the object is less than 20 cm in front of the car, run next line of code.
    Standby();            ////Stop car
    myservo.write(0);     ////Servo turn Right
    delay(200);            ///for 0.2 seconds
    Ultrasonic();         ////Run Ultrasonic command
    delay(200);            ///for 0.2 seconds

    if (distance <= 20){   //if true that the object is less than 20 cm to the right of the car, run next line of code.
      Standby();            ////Car Stops

      myservo.write(180);   ////Servo turn Left
      delay(200);            ///for 0.2 seconds
      Ultrasonic();         ////Run Ultrasonic command
      delay(200);            ///for 0.2 seconds
    
      if (distance > 20){                  //if false that the object is less than 20 cm to the left of the car, run next line of code.
        Left(0,NormSPEED);    ////Car turns Left, at 100 speed
        delay(500);            ///for 0.5 seconds
        myservo.write(90);    ////Servo reajusts by turning Forward
      }

      else{   //if true that the object is less than 20 cm to the left of the car, run next line of code.
        Standby();
        delay(200);
        Backward(0,NormSPEED);////Car goes Backwards, at 100 speed
        delay(500);            ///for 0.5 seconds
        Left(0,NormSPEED);   ////Car turns Right, at 100 speed
        delay(500);           ///for 1 second
        
        myservo.write(90);    ////Servo reajusts by turning Forward
        delay(200);            ///for 0.2 seconds
        Ultrasonic();         ////Run Ultrasonic command
        delay(200);            ///for 0.2 seconds
      }
    }
    
    else{                  //if false that the object is less than 20 cm to the right of the car, run next line of code.
      Right(0,NormSPEED);   ////Car turns Right, at 100 speed
      delay(500);            ///for 0.5 seconds
      myservo.write(90);    ////Servo reajusts by turning Forward
    }
  }
  
  else{                  //if false that the object is less than 20 cm in front of the car, run next line of code.
    Forward(0,NormSPEED); ////Car goes Forward, at 100 speed
    myservo.write(90);    ////Servo reajusts by turning Forward
    Ultrasonic();         ////Run Ultrasonic command
    delay(100);            ///for 0.1 seconds
  }
}
