#include <Arduino.h>
#include <Sensor.h>

Sensor sLeft(34);
Sensor sRight(35);
Sensor::Feld previousSampleLeft;
Sensor::Feld previousSampleRight;
int sampleTime = 5000;
enum driveStates
{
  FORWARD = 0,
  LEFT = 1,
  RIGHT = 2
};
driveStates driveState = FORWARD;
void drive();
void moveForward();
void rotateRight();
void rotateLeft();
boolean isCorrectTransition(Sensor::Feld oldval, Sensor::Feld newval);

void drive()
{
  //example
  Sensor::Feld sampleLeft = sLeft.classifyValue();
  Sensor::Feld sampleRight = sRight.classifyValue();
  if (driveState == FORWARD)
  {
    moveForward();
    if (sampleLeft != previousSampleLeft)
    {
      Serial.println("leftSensor turn");

      if (isCorrectTransition(previousSampleLeft, sampleLeft))
      {
        driveState = LEFT;
        Serial.println("turning left");
      }
      else
      {

        driveState = RIGHT;
        Serial.println("turning right");
      }
    }
    else if (sampleRight != previousSampleRight)
    {
      Serial.println("rightSensor turn");
      if (isCorrectTransition(previousSampleRight, sampleRight))
      {
        driveState = RIGHT;
        Serial.println("turning right");
      }
      else
      {
        driveState = LEFT;
        Serial.println("turning left");
      }
    }
  }
  else
  {
    if (driveState == LEFT){
      rotateLeft();}
    if (driveState == RIGHT){
      rotateRight();}
    if (sampleLeft == sampleRight)
    {
      Serial.println("driving forward again");
      driveState = FORWARD;
    }
  }
  previousSampleLeft=sampleLeft;
  previousSampleRight=sampleRight;
}
boolean isCorrectTransition(Sensor::Feld oldval, Sensor::Feld newval)
{
  // 0 = BLACK, 1 = GREY, 2 = WHITE
  if (newval > oldval)
  {
    if (!(oldval == 0 && newval == 2))
      return true;
  }
  else if (oldval == 2 && newval == 0)
    return true;

  return false;
}

void moveForward(){
  digitalWrite(32, HIGH);
  digitalWrite(33, HIGH);
}
void rotateLeft(){
  digitalWrite(32, LOW);
  digitalWrite(33, HIGH);
}
void rotateRight(){
  digitalWrite(32, HIGH);
  digitalWrite(33, LOW);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  sRight=Sensor(35);
  sLeft=Sensor(34);
  Serial.println("starting");
  previousSampleLeft = sLeft.classifyValue();
  previousSampleRight = sRight.classifyValue();
}

void loop()
{
  // put your main code here, to run repeatedly:
  sRight.addSample();
  sLeft.addSample();
  if (sampleTime > 0){
    moveForward();
    sampleTime -= 300;
  } else {
    drive();
  }
  
  Serial.print("Left: ");
  Serial.println(sLeft.classifyValue());
  Serial.print("Right: ");
  Serial.println(sRight.classifyValue());
  delay(300);
}