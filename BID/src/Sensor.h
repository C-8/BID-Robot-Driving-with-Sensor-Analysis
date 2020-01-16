#include <Arduino.h>

class Sensor{
    private:
public:
enum Feld
{
  BLACK = 0,
  GREY = 1,
  WHITE = 2
};
  int samples[1000];
  int sampleIndex = 0;
  int blackValue;
  int greyValue;
  int whiteValue;
  uint8_t pin;
  Sensor(uint8_t pin);
  void addSample();
  void clusterSamples();
  Feld classifyValue();
  Feld classifyValue(int);
  void printValues();
};