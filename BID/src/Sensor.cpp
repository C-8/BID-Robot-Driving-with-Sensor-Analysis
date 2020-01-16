#include<Sensor.h>


  Sensor::Sensor(uint8_t pin)
  {
    this->pin = pin;
    greyValue=analogRead(pin);
    whiteValue=greyValue+50;
    blackValue=greyValue-50;
    Serial.println(whiteValue);
    Serial.println(greyValue);
    Serial.println(blackValue);
  }

  void Sensor::addSample()
  {
    if (sampleIndex < 1000)
    {
      samples[sampleIndex] = analogRead(pin);
      //Serial.println(classifyValue(),DEC);
      sampleIndex++;
    if (sampleIndex % 10 == 0)
      clusterSamples();
    }
  }
  void Sensor::clusterSamples()
  {
    boolean changed = true;
    long blackSum=0;
    long greySum=0;
    long whiteSum=0;
    int blackCount = 0;
    int greyCount = 0;
    int whiteCount = 0;
    while (changed)
    {
      changed = false;
      for (int i = 0; i < sampleIndex; i++)
      {
        Feld classifiedValue = classifyValue(samples[i]);
        if (classifiedValue == BLACK)
        {
          blackSum += samples[i];
          blackCount++;
        }
        else if (classifiedValue == GREY)
        {
          greySum += samples[i];
          greyCount++;
        }
        else
        {
          whiteSum+= samples[i];
          whiteCount++;
        }
      }
      int tempBlack = blackValue;
      int tempGrey = greyValue;
      int tempWhite = whiteValue;
      if (blackCount > 0)
        blackValue = blackSum/blackCount;
      if (greyCount > 0)
        greyValue = greySum/greyCount;
      if (whiteCount > 0)
        whiteValue = whiteSum/whiteCount;
      if (tempBlack != blackValue || tempGrey != greyValue || tempWhite != whiteValue)
      {
        changed = true;
      }
    }
     //printValues();
  }

  Sensor::Feld Sensor::classifyValue(){
    return classifyValue(analogRead(pin));
  }

  Sensor::Feld Sensor::classifyValue(int value)
  {
    int blackDistance = abs(value - blackValue);
    int greyDistance = abs(value - greyValue);
    int whiteDistance = abs(value - whiteValue);

    if (blackDistance < min(greyDistance, whiteDistance))
    {
      return BLACK;
    }
    else if (greyDistance < whiteDistance)
    {
      return GREY;
    }
    else
    {
      return WHITE;
    }
  }

  void Sensor::printValues()
  {
    Serial.print("white: ");
    Serial.println(whiteValue, DEC);
    //Serial.print("grey: ");
    Serial.println(greyValue, DEC);
    //Serial.print("black: ");
    Serial.println(blackValue, DEC);
  };