//* Line Tracking *//

//This code uses the ITR20001 Sensor to track changes in color.//
//Here it is used to track a line and make the Elegoo Car      //
//change directions accordingly.                               //


// Analog pins responsible for the line tracking //  
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
 
// Available Speeds //    These will be the the Y variables when a command is called
int MaxSPEED = 250;   
int MinSPEED = 50;    
int NormSPEED = 100;
int DontMOVE = 0;    
 
// Available Times //     These will be the the X variables when a command is called)
int Stop = 0; 
int Time = 1000;  
int LineTrkTime = 0;  



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

void Right(int x,int y){ //Right command  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,1);    //The comand of 1(HIGH) makes motor A move forward

  //Motor B    
  analogWrite(PWMB, y);     //Motor B is powered at speed y
  digitalWrite (BIN1,0);    //The comand of 0(LOW) makes motor B move backward

  // In the case of the Right command, Motor A is moving forward at full speed and Motor B is moving backwards at full speed
  // causing the Car to spin to the Right in the same spot.
}   

void Standby(){ //Standby command  
  //motor A     
  analogWrite (PWMA,0);     //Motor A is powered at speed 0

  //Motor B       
  analogWrite (PWMB,0);     //Motor B is powered at speed 0
}       

void Search(int x,int y){ //Search command. It turns left umtil it finds the line  
  //motor A    
  analogWrite (PWMA,y);     //Motor A is powered at speed y
  digitalWrite (AIN1,0);    //The comand of 0(LOW) makes motor A move backward

  //Motor B    
  analogWrite(PWMB, y);     //Motor B is powered at speed y
  digitalWrite (BIN1,1);    //The comand of 1(HIGH) makes motor B move forward

  //In the case of the Search command, it acts exactly as the Left command
}   



void setup() {    

  Serial.begin(9600);   // open the serial port at 9600 bps:

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

if(LT_L >=850 && LT_M >=850 && LT_R >=850){ //If all 3 sensors of the Line Tracker read values above or equal to 850, then it should run the lines of code inside curly bracket
  Standby();                                   //Run the Standby command
  Serial.println("STOP");                      //On serial monitor print a new line saying "STOP"
}  
else if(LT_M >=450) {                       //If the Middle sensor of the Line Tracker reads values above or equal to 450, then it should run the lines of code inside curly bracket
  Forward(LineTrkTime,NormSPEED);              //Run the Forward command, at 0 seconds, at 100 speed
  //Serial.println("GO FORWARD");              //On serial monitor print a new line saying "GO FORWARD"
}  
else if(LT_M <=450){                        //If the Middle sensor of the Line Tracker reads values below or equal to 450, then it should run the lines of code inside curly bracket
  if (LT_R >=600 ){                            //If the Right sensor of the Line Tracker reads values above or equal to 600, then it should run the lines of code inside curly bracket
    Right(LineTrkTime,MinSPEED);                  //Run the Right command, at 0 seconds, at 100 speed
    Serial.println("TURN RIGHT");                 //On serial monitor print a new line saying "TURN RIGHT"
  } 
  else if(LT_L >=600 ){                        //If the Left sensor of the Line Tracker reads values above or equal to 600, then it should run the lines of code inside curly bracket
   Left(LineTrkTime,MinSPEED);                    //Run the Left command, at 0 seconds, at 100 speed
   Serial.println("TURN LEFT");                   //On serial monitor print a new line saying "TURN LEFT"
  } 
  else if(LT_L <=70 && LT_M <=70 && LT_R <=70){//If all 3 sensors of the Line Tracker read values above or equal to 850, then it should run the lines of code inside curly bracket
   Serial.println("Searching...");                //On serial monitor print a new line saying "Searching..."
   Search(LineTrkTime,NormSPEED);                 //Run the Search command, at 0 seconds, at 100 speed
  } 
}

 

static unsigned long print_time = 500;    //Print time starts at 500

if (millis() - print_time > 1500) {       //If Internal Timer(millis) - Print time is more than 1500, run the code in the curly brackets
 print_time = millis();                   //The new printing time starts at the current Internal Timer(millis)
 Serial.print("LT_L = ");                 //Serial monitor print "LT_L = "
 Serial.println(LT_L);                    //Then print what the value detected by the left sensor
 Serial.print("LT_M = ");                 //Serial monitor print "LT_M = "
 Serial.println(LT_M);                    //Then print what the value detected by the middle sensor
 Serial.print("LT_R = ");                 //Serial monitor print "LT_R = "
 Serial.println(LT_R);                    //Then print what the value detected by the right sensor
 }  
}
