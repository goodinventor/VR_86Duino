//
// VR_Demo.ino
//
// programmed by George Andrews
//
// This is a demonstration program to test the features of the
// VR_86Duino library.
//
#include "VR_86Duino.h"
#include <UTFT.h>
#include <typeinfo>
#include <string>

#define RS_PIN 21
#define WR_PIN 22
#define CS_PIN 23
#define RST_PIN 24

UTFT vr_screen(SSD1289, RS_PIN, WR_PIN, CS_PIN, RST_PIN);

Point point1(1, 2, 1);
Point point2(0, 4, 4);
Vector vector1(2, 0, 0);
Vector vector2(0, 0, 0);

void setup()
{
  usePortMode();
  vr_screen.InitLCD();
  
  point1.DrawPoint(vr_screen);
  point2.DrawPoint(vr_screen);

  Point calc_point1(0, 0, 0);
  calc_point1 = point1.SubtractPointFromPoint(point2);
  for (int i = 0; i < 3; i++)
  {
    vector2.Tuple[i] = calc_point1.Tuple[i];
  }

  vector1 = vector1.AddVectorToVector(vector2);

  point1.AddVectorToPoint(vector1);
  point1.DrawPoint(vr_screen);

  point2.SubtractVectorFromPoint(vector2);
  point2.DrawPoint(vr_screen);
}

void loop()
{
}
