#include<Servo.h>

// Created by Victor Valadez
// Youtube Video: https://youtube.com/shorts/bTavCQ-jaq0?feature=shared

Servo joint1;
Servo joint2;
Servo joint3;
Servo joint4;
Servo joint5;
Servo joint6;

int joint1Val;
int joint2Val;
int joint3Val;
int joint4Val;
int joint5Val;
int joint6Val;



const int stepPin = 3;
 int dirPin = 4; 
int dirButton = 2;
int state = HIGH;
int reading;
int previous = LOW;
int stepDelay=1000;



long time = 0;
long debounce = 200;

int customDelay,customDelayMapped;




void setup() {
  // put your setup code here, to run once:
  joint1.attach(8);
  joint2.attach(9);
  joint3.attach(10);
  joint4.attach(11);
  joint5.attach(12);
  joint6.attach(13);

  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(dirButton, INPUT_PULLUP);

  digitalWrite(dirPin,HIGH);
  
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  joint1Val = analogRead(0);
  joint1Val = map(joint1Val,0,1023,0,180);

  joint2Val = analogRead(1);
  joint2Val = map(joint2Val,0,1023,0,180);
  
  joint3Val = analogRead(2);
  joint3Val = map(joint3Val,0,1023,0,180);
  
  joint4Val = analogRead(3);
  joint4Val = map(joint4Val,0,1023,0,180);

  joint5Val = analogRead(4);
  joint5Val = map(joint5Val,0,1023,0,180);
  
  
  joint1.write(joint1Val);
  joint2.write(joint2Val);
  joint3.write(joint3Val);
  joint4.write(joint4Val);

  int revjoint5Val = joint5Val - 180;
  
  joint5.write(joint5Val);
  joint6.write(revjoint5Val);

    customDelayMapped = speedUp(); // Gets custom delay values from the custom speedUp function
  // Makes pules with custom delay, depending on the Potentiometer, from which the speed of the motor depends
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(customDelayMapped);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(customDelayMapped);



  reading = digitalRead(dirButton);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();

  
}

  digitalWrite(dirPin, state);

  previous = reading;
  
digitalWrite(stepPin, HIGH);
delayMicroseconds(stepDelay);
digitalWrite(stepPin, LOW);
delayMicroseconds(stepDelay);

}

  int speedUp() {
  int customDelay = analogRead(A5); // Reads the potentiometer
  int newCustom = map(customDelay, 0, 1023, 300,4000); // Convrests the read values of the potentiometer from 0 to 1023 into desireded delay values (300 to 4000)
  return newCustom;
}
