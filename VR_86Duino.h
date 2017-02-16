//
// VR_86Duino.h
//
// programmed by George Andrews
//
// This is a library for use in some entry-level VR. It is
// designed on top of the UTFT library.
//
#ifndef VR_86Duino_h
#define VR_86Duino_h

#include "Arduino.h"
#include <UTFT.h>
#include <typeinfo>
#include <typeindex>

//
// An empty base class from which all drawable objects are
// derived. This class exists so that all drawable objects can
// be listed in one array in the Camera class.
//
class DrawableObject
{
  public:
  double Tuple[3];
};

class Vector;

class Point : public DrawableObject
{
  public:
  friend class Vector;
  
  // variables
  double Tuple[3];

  // functions
  Point(int x_pos, int y_pos, int z_pos);
  Point AddVectorToPoint(const Vector& vect_operand);
  Point SubtractVectorFromPoint(const Vector& vect_operand);
  Point SubtractPointFromPoint(const Point& point_operand);
  void DrawPoint(UTFT screen);
};

class Vector
{
  public:
  // variables
  double Tuple[3];

  // functions
  Vector(int x_mag, int y_mag, int z_mag);
  Vector AddVectorToVector(const Vector& vect_operand);
  Vector SubtractVectorFromVector(const Vector& vect_operand);
  Vector RotateXY(double degrees_val);
  Vector RotateXZ(double degrees_val);
  Vector RotateYZ(double degrees_val);
  Vector Scale(double scaling_tuple[3]);
};

class Math
{
  public:
  double ConvertDegreesToRadians(double degrees_val);
};

class Camera
{
  public:
  // variables
  
  // the following are the minimum and maximum bounds of X, Y,
  // and Z respectively
  int MinX;
  int MaxX;
  int MinY;
  int MaxY;
  int MinZ;
  int MaxZ;

  // array of all existent objects
  DrawableObject * ObjectsInWorld;
  int ObjectsInWorldSize;

  // functions
  void DrawScene(UTFT screen);
};

#endif
