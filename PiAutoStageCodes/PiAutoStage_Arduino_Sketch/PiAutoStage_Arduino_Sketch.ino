
// zoomkat 11-22-10 serial servo (2) test
// Steiner-Rooney 01-29-2021 added in GoCode command to attach servos. 
// for writeMicroseconds, use a value like 1500
// for IDE 0019 and later
// Powering a servo from the arduino usually DOES NOT WORK.
// two servo setup with two servo commands
// send eight character string like 15001500 or 14501550


#include <Servo.h>
String readString, servo1, servo2;
Servo myservo1;  // create servo object to control myservo1 (X-motor)
Servo myservo2; // create servo object to control myservo2 (Y-motor)

void setup() {
 //initializes the servos to the neutral position. Prevents unwanted movement. 
 Serial.begin(9600);
 myservo1.write(90);
 delay(500);
 myservo2.write(90);
 delay(500);
}

void loop() {

 while (Serial.available()) {
   delay(10);  
   if (Serial.available() >0) {
     char c = Serial.read();  //gets one byte from serial buffer
     readString += c; //makes the string readString
   }
 }

 if (readString.length() >0) {
     //Serial.println(readString); //see what was received
     
     // expect a string like 07002100 containing the two servo positions      
     servo1 = readString.substring(0, 4); //get the first four characters, X-motor command
     servo2 = readString.substring(4, 8); //get the next four characters, Y-motor command
     
     int n1; //declare as number  
     int n2; //declare as number
     
     char carray1[6]; //magic needed to convert string to a number
     servo1.toCharArray(carray1, sizeof(carray1));
     n1 = atoi(carray1);
     
     char carray2[6];
     servo2.toCharArray(carray2, sizeof(carray2));
     n2 = atoi(carray2);
     if (n1 == 5555) {    //looks for the GoCode to attach the servo motors
      myservo1.attach(12);  //the pin for the servo control. Pin corresponds to X-motor. 
      myservo2.attach(13);  //the pin for the servo control. Pin corresponds to Y-motor.
      n1 = 1500;
     }
     
     myservo1.write(n1); //set X-motor position
     delay(500);
     myservo2.write(n2); //set Y-motor position
   readString="";
 }
}
