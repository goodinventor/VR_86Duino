//
// VR_86Duino.cpp
//
// programmed by George Andrews
//
// This is a library for use in some entry-level VR. It is
// designed on top of the UTFT library.
//
#include "Arduino.h"
#include "VR_86Duino.h"
#include <UTFT.h>
#include <typeinfo>
#include <typeindex>

//
// Point class constructor.
//
Point::Point(int x_pos, int y_pos, int z_pos)
{
  this->Tuple[0] = x_pos;
  this->Tuple[1] = y_pos;
  this->Tuple[2] = z_pos;
}

//
// Add a vector to the point and return the result as a point.
//
Point Point::AddVectorToPoint(const Vector& vect_operand)
{
  // loop through elements of tuple and add them together
  Point result(0, 0, 0);

  for (int i = 0; i < 3; i++)
  {
    result.Tuple[i] = this->Tuple[i] + vect_operand.Tuple[i];
  }
  
  return result;
}

//
// Subtract a vector from the point and return the result as a
// point.
//
Point Point::SubtractVectorFromPoint(const Vector& vect_operand)
{
  // loop through elements of tuple and subtract elements of the
  // vector from elements of the point
  Point result(0, 0, 0);

  for (int i = 0; i < 3; i++)
  {
    result.Tuple[i] = this->Tuple[i] - vect_operand.Tuple[i];
  }

  return result;
}

//
// Subtract a point from the point and return the result as a
// point.
//
Point Point::SubtractPointFromPoint(const Point& point_operand)
{
  // loop through elements of tuple and subtract elements of
  // point_operand from elements of the point
  Point result(0, 0, 0);

  for (int i = 0; i < 3; i++)
  {
    result.Tuple[i] = this->Tuple[i] - point_operand.Tuple[i];
  }

  return result;
}

//
// Draws point to the screen by converting the 3D coordinates
// into 2D ones and then displaying.
//
void Point::DrawPoint(UTFT screen)
{
  int half_screen_width = screen.getDisplayXSize() / 2;
  int half_screen_height = screen.getDisplayYSize() / 2;

  int x_screen = (int)round(((this->Tuple[0] / this->Tuple[2]) + half_screen_width) * half_screen_width);
  int y_screen = (int)round(((this->Tuple[1] / this->Tuple[2]) + half_screen_height) * half_screen_height);

  // make aspect ratio adjustments; for now, it is assumed that
  // the window is the full screen (adjustments will be made
  // later when a window class is up and running)
  float window_aspect = screen.getDisplayXSize() / screen.getDisplayYSize();

  if (window_aspect > 1.0)
  {
    x_screen /= window_aspect;
  }
  else
  {
    y_screen *= window_aspect;
  }

  screen.drawPixel(x_screen, y_screen);
}

//
// Vector class constructor.
//
Vector::Vector(int x_mag, int y_mag, int z_mag)
{
  this->Tuple[0] = x_mag;
  this->Tuple[1] = y_mag;
  this->Tuple[2] = z_mag;
}

//
// Add a vector to the vector and return the result as a vector.
//
Vector Vector::AddVectorToVector(const Vector& vect_operand)
{
  // loop through elements of tuple and add the vectors together
  Vector result(0, 0, 0);

  for (int i = 0; i < 3; i++)
  {
    result.Tuple[i] = this->Tuple[i] + vect_operand.Tuple[i];
  }

  return result;
}

//
// Subtract a vector from the vector and return the result as a
// vector.
//
Vector Vector::SubtractVectorFromVector(const Vector& vect_operand)
{
  // loop through the elements of tuple and subtract elements of
  // vect_operand from elements of the vector
  Vector result(0, 0, 0);

  for (int i = 0; i < 3; i++)
  {
    result.Tuple[i] = this->Tuple[i] - vect_operand.Tuple[i];
  }

  return result;
}

//
// Rotates a vector around the XY plane.
//
Vector Vector::RotateXY(double degrees_val)
{
  // declare the math object to use the functions
  Math math_obj;

  // convert the angle to radians
  double radians_val = math_obj.ConvertDegreesToRadians(degrees_val);
  Vector result(0, 0, 0);

  // calculate result vector
  result.Tuple[0] = cos(radians_val) * this->Tuple[0] - sin(radians_val) * this->Tuple[1];
  result.Tuple[1] = sin(radians_val) * this->Tuple[0] + cos(radians_val) * this->Tuple[1];
  result.Tuple[2] = this->Tuple[2];
  
  return result;
}

//
// Rotates a vector around the XZ plane.
//
Vector Vector::RotateXZ(double degrees_val)
{
  // declare the math object to use the functions
  Math math_obj;

  // convert the angle to radians
  double radians_val = math_obj.ConvertDegreesToRadians(degrees_val);
  Vector result(0, 0, 0);

  // calculate result vector
  result.Tuple[0] = cos(radians_val) * this->Tuple[0] + sin(radians_val) * this->Tuple[2];
  result.Tuple[1] = this->Tuple[1];
  result.Tuple[2] = -1 * sin(radians_val) * this->Tuple[0] + cos(radians_val) * this->Tuple[2];

  return result;
}

//
// Rotates a vector around the YZ plane.
//
Vector Vector::RotateYZ(double degrees_val)
{
  // declare the math object to use the functions
  Math math_obj;

  // convert the angle to radians
  double radians_val = math_obj.ConvertDegreesToRadians(degrees_val);
  Vector result(0, 0, 0);

  // calculate result vector
  result.Tuple[0] = this->Tuple[0];
  result.Tuple[1] = cos(radians_val) * this->Tuple[1] - sin(radians_val) * this->Tuple[2];
  result.Tuple[2] = sin(radians_val) * this->Tuple[1] + cos(radians_val) * this->Tuple[2];

  return result;
}

//
// Performs a scaling transformation on the vector.
//
Vector Vector::Scale(double scaling_tuple[3])
{
  Vector result(0, 0, 0);

  // calculate result vector
  result.Tuple[0] = this->Tuple[0] * scaling_tuple[0];
  result.Tuple[1] = this->Tuple[1] * scaling_tuple[1];
  result.Tuple[2] = this->Tuple[2] * scaling_tuple[2];

  return result;
}

//
// Converts degrees into radians.
//
double Math::ConvertDegreesToRadians(double degrees_val)
{
  double result = degrees_val * (PI / 180);
  return result;
}

//
// Camera class constructor.
//
Camera::Camera()
{
  this->ObjectsInWorldSize = 0;
}

//
// Camera class constructor.
//
Camera::Camera(int min_x, int max_x, int min_y, int max_y, int min_z, int max_z)
{
  this->MinX = min_x;
  this->MaxX = max_x;
  this->MinY = min_y;
  this->MaxY = max_y;
  this->MinZ = min_z;
  this->MaxZ = max_z;

  this->ObjectsInWorldSize = 0;
}

//
// Draws all objects in world.
//
void Camera::DrawScene(UTFT screen)
{
  // reference typeids
  const std::type_info& point_type = typeid(Point);

  // loop through the objects in world and check the typeid
  for (int i = 0; i < this->ObjectsInWorldSize; i++)
  {
    const std::type_info& object_type = typeid(this->ObjectsInWorld[i]);

    if (std::type_index(object_type) == std::type_index(point_type))
    {
      // reference point to print
      Point current_point(0, 0, 0);
      
      // copy values over
      for (int j = 0; j < 3; j++)
      {
        current_point.Tuple[i] = this->ObjectsInWorld[j].Tuple[j];
      }
      
      // draw the point
      current_point.DrawPoint(screen);
    }
  }
}
