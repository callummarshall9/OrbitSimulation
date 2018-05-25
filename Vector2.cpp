#include <stdio.h>
#include <math.h>
#ifndef VECTOR2_HEADER_FILE
  #define VECTOR2_HEADER_FILE

class vector2 {
public:
  double x;
  double y;
  vector2 vector_subtract(vector2 vector);
  vector2 unit_vector();
  vector2 multiply_by_scalar_return_value(double scalar);
  double vector_norm();
  void set_x(double x);
  void set_y(double y);
  double get_x();
  double get_y();
  vector2(double x, double y);
  vector2();
};

vector2::vector2(double x, double y) {
  this->x = x;
  this->y = y;
}

vector2::vector2() {

}

vector2 vector2::vector_subtract(vector2 vector) {
  return vector2(vector.get_x() - this->get_x(), vector.get_y() - this->get_y());
}

double vector2::vector_norm() {
  return sqrt(pow(this->get_x(),2) + pow(this->get_y(),2));
}

vector2 vector2::unit_vector() {
  return vector2(this->get_x() / this->vector_norm(), this->get_y() / this->vector_norm());
}

vector2 vector2::multiply_by_scalar_return_value(double scalar) {
  double new_x = scalar * (double)this->get_x();
  double new_y = scalar * (double)this->get_y();
  return vector2(new_x, new_y);
}

void vector2::set_x(double x) {
  this->x = x;
}

double vector2::get_x() {
  return this->x;
}

double vector2::get_y() {
  return this->y;
}

void vector2::set_y(double y) {
  this->y = y;
}

#endif
