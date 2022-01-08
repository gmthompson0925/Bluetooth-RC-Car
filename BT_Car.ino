//Arduino Bluetooth Controlled Car
//Before uploading the code you have to install the necessary library
//Note - Disconnect the Bluetooth Module before hiting the upload button otherwise you'll get compilation error message.
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install 
//After downloading the library open Arduino IDE >> go to sketch >> Include Libray >> ADD. ZIP Libray >> Select the downloaded 
//ZIP File >> Open it >> Done
//Now You Can Upload the Code without any problem but make sure the bt module isn't connected with Arduino while uploading code

// Necessary library for the movement classes to operate
#include <AFMotor.h>

// Initialize light sensor and piezo
int ldrPin = A0;
int siren = 8;

//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

char command; 

void setup() 
{       
// declare the LED pins as outputs
pinMode(3, OUTPUT);
pinMode(6, OUTPUT);

// declare the piezo as an output 
pinMode(siren, OUTPUT);

// declare the light sensor as an input
pinMode(ldrPin, INPUT);


Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop(){
  
 MotorAction();
  
}

// Motor Function
void MotorAction() {
  
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous. These are the case/movement commands. 
    //Serial.println(command);
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    }
  }
}

// 
void PoliceAction() {
  
// Initialize variable to read the light status
   int ldrStatus = analogRead(ldrPin);

// if the light threshhold is below 100, start looping the piezo and lights
if (ldrStatus <= 100) {
  
   tone(siren, 1000);
    delay(250);
    tone(siren, 250);
    digitalWrite(3, LOW);  
  digitalWrite(6, HIGH);  
  // wait for a quarter second before changing the light
  delay(250);
  digitalWrite(3, HIGH); 
  digitalWrite(6, LOW); 
  // wait for a quarter second before changing the light
  delay(250);
}

// if it is still light outside, keep everything off
else {
  
    noTone(siren);
  digitalWrite(3, LOW); 
  digitalWrite(6, LOW); 
} 
}

void forward()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(255);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(255);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
} 

void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}
