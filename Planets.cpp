#include "Vector2.cpp"
#include "math.h"
double TIMESTEP = 24 * 3600;

class planet {
public:
  double mass;
  vector2 position;
  vector2 velocity;
  char* name;
  std::string color;
  vector2 calculate_acceleration(std::vector<planet> &planets);
  vector2 calculate_new_position(vector2 acceleration);
  vector2 calculate_new_velocity(vector2 acceleration);
  void update_position(std::vector<planet> &planets);
  planet(double radius, double velocity_y, double mass, char* name, std::string color);
};

planet::planet(double radius, double velocity_y, double mass, char* name, std::string color) {
  this->position.set_x(radius);
  this->position.set_y(0);
  this->velocity.set_x(0);
  this->velocity.set_y(velocity_y);
  this->mass = mass;
  this->name = name;
  this->color = color;
}

vector2 planet::calculate_acceleration(std::vector<planet> &planets) {
  double G = 6.67e-11;//G constant in Newton's law of gravitation.
  vector2 acceleration(0,0);
  for(int i = 0; i < planets.size(); i++) {
    if(planets[i].name == this->name) { continue; }
    double mass_one = this->mass;
    double mass_two = planets[i].mass;
    /*double delta_y = planets[i].position.get_y() - this->position.get_y();
    double delta_x = planets[i].position.get_x() - this->position.get_x();
    double theta = atan2(delta_y,delta_x);
    double distance = sqrt(pow(delta_x,2) + pow(delta_y,2));
    double force = G * mass_one * mass_two / pow(distance,2);
    acceleration.set_x(acceleration.get_x() + force / mass_one * cos(theta));
    acceleration.set_y(acceleration.get_y() + force / mass_one * sin(theta));*/
    vector2 two_to_one = this->position.vector_subtract(planets[i].position);
    vector2 unit_vector = two_to_one.unit_vector();
    vector2 force = unit_vector.multiply_by_scalar_return_value(G * mass_one * mass_two / pow(two_to_one.vector_norm(),2));//F=-GMm/(r_12)^2*(r_12 unit vector)
    acceleration.set_x(acceleration.get_x() + force.get_x() / mass_one);
    acceleration.set_y(acceleration.get_y() + force.get_y() / mass_one);

  }
  return acceleration;
}

vector2 planet::calculate_new_position(vector2 acceleration) {
  vector2 ut = this->velocity.multiply_by_scalar_return_value(TIMESTEP);//BUG HERE
  double scalar_value = 0.5 * pow(TIMESTEP, 2);
  vector2 half_at_two_squared = acceleration.multiply_by_scalar_return_value(scalar_value);
  double new_x_value = this->position.get_x() + ut.get_x() + half_at_two_squared.get_x();
  double new_y_value = this->position.get_y() + ut.get_y() + half_at_two_squared.get_y();
  return vector2(new_x_value, new_y_value);
}

vector2 planet::calculate_new_velocity(vector2 acceleration) {
  return vector2(this->velocity.get_x() + acceleration.get_x() * TIMESTEP, this->velocity.get_y() + acceleration.get_y() * TIMESTEP);
}

void planet::update_position(std::vector<planet> &planets) {
  vector2 acceleration = this->calculate_acceleration(planets);
  vector2 new_velocity = calculate_new_velocity(acceleration);
  vector2 new_pos = calculate_new_position(acceleration);
  this->position.set_x(new_pos.get_x());
  this->position.set_y(new_pos.get_y());
  this->velocity.set_x(new_velocity.get_x());
  this->velocity.set_y(new_velocity.get_y());
}
