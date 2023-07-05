const int trigPin = 2;
const int echoPin = 4;
const int sensorPin=A0;
const int buzzerPin= 13;
const int enA = 9;
const int in1 = 8;
const int in2 = 7;
const int enB = 3;
const int in3 = 5;
const int in4 = 6;
int incomingByte = 0; // assign pin for bluetooth module
int smoke_level;

void setup() {
  
Serial.begin(9600);//sets the baud rate for data transfer in bits/second
pinMode(sensorPin, INPUT);//the smoke sensor will be an input to the arduino
pinMode(buzzerPin, OUTPUT);//the buzzer serves an output in the circuit
pinMode(enA, OUTPUT);// Set all the motor control pins to outputs
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
digitalWrite(in1, LOW);// Turn off motors - Initial state
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}


void loop()
{
if (Serial.available() > 0) {
incomingByte = Serial.read();
}
switch(incomingByte)
{
case 'S':
digitalWrite(in1, LOW); // control for stop
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
Serial.println("Stop\n");
incomingByte='*';
break;

case 'R':
digitalWrite(in1, HIGH); // control for right
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
Serial.println("right\n");
incomingByte='*';
break;

case 'L':
digitalWrite(in1, LOW); // control for left
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
Serial.println("left\n");
incomingByte='*';
break;

case 'F':
digitalWrite(in1, HIGH); // control for forward
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
Serial.println("forward\n");
incomingByte='*';
break;

case 'B':
digitalWrite(in1, LOW); // control for backward
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
Serial.println("backwards\n");
incomingByte='*';
break;

case 'f':
digitalWrite(in1, LOW); // control for stop
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
Serial.println("Stop\n");
incomingByte='*';
break;

case 'd':
digitalWrite(in1, HIGH); // control for right
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
Serial.println("right\n");
incomingByte='*';
break;

case 'a':
digitalWrite(in1, LOW); // control for left
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
Serial.println("left\n");
incomingByte='*';
break;

case 'w':
digitalWrite(in1, HIGH); // control for forward
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
Serial.println("forward\n");
incomingByte='*';
break;

case 's':
digitalWrite(in1, LOW); // control for backward
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
Serial.println("backwards\n");
incomingByte='*';
break;

  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
 
long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
pinMode(trigPin, OUTPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 
pinMode(echoPin, INPUT); 
duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance

inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
smoke_level= analogRead(sensorPin); //arduino reads the value from the smoke sensor
Serial.println(smoke_level);//prints just for debugging purposes, to see what values the sensor is picking up
Serial.print(inches);
Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();

if(smoke_level >170){ //if smoke level is greater than 170, the buzzer will go off
digitalWrite(buzzerPin, HIGH);
}
else{
digitalWrite(buzzerPin, LOW);
}
delay(150);

directionControl();
delay(1000);
speedControl();
delay(1000);
}

void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);
  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);
  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void speedControl() {// This function lets you control speed of the motors
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}



/////////////////////////////////////////// FUNCTIONS ////////////////////////////////////////


long microsecondsToInches(long microseconds)

{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf--
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
