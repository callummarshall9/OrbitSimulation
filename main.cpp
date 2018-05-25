#include <SFML/Graphics.hpp>
#include "Planets.cpp"
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "colour_utils.cpp"
#include "string_utils.cpp"
#include <thread>

using namespace std;


std::vector<planet> load_model() {
  std::vector<planet> planets;
  float AU = 149597870700;//1 AU = 149597870700m
  std::ifstream input_file("model_data.csv");
  for( std::string line; getline( input_file, line ); ) {
    vector<string> tokens = split(line, ",");
    const char* name = tokens[1].c_str();
    double mass = stod(tokens[2].c_str()) * pow(10,stod(tokens[3].c_str()));
    double position_x = stod(tokens[4].c_str()) * AU;
    double velocity_y = stod(tokens[5]) * pow(10,stod(tokens[6].c_str()));
    planet new_planet(position_x, velocity_y, mass, strdup(name), tokens[0]);
    planets.push_back(new_planet);
  }
  return planets;
}

void planet_display(std::vector<planet> &planets) {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
  sf::Font font;
  font.loadFromFile("LiberationSerif-Regular.ttf");
  std::vector<sf::Text> planet_text;
  std::vector<sf::CircleShape> planet_shapes;
  float scale = 0.001 * 150 * pow(10,9);
  float center_x = 1280 / 2;
  float center_y = 720 / 2;
  bool debug = false;
  for(int i = 0; i < planets.size(); i = i + 1) {
    sf::CircleShape planet_shape(5);
    float planet_x_coordinate = center_x + planets[i].position.get_x() / scale;
    float planet_y_coordinate = center_y + planets[i].position.get_y() / scale;
    planet_shape.setPosition(planet_x_coordinate, planet_y_coordinate);
    planet_shape.setFillColor(handle_colour(planets[i].color));
    planet_shapes.push_back(planet_shape);
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setPosition(planet_x_coordinate,planet_y_coordinate + 20);
    planet_text.push_back(text);
  }
  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed) {
            window.close();
          }
          if(event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
              scale = scale * 0.5;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
              scale = scale * 1.5;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
              TIMESTEP = TIMESTEP + 3600;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
              TIMESTEP = TIMESTEP - 3600;
            } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
              debug = (debug) ? false : true;
            }
          }
      }
      window.clear();
      for(int j = 0; j < planet_shapes.size(); j++) {
        float planet_x_coordinate = center_x + planets[j].position.x / scale;
        float planet_y_coordinate = center_y + planets[j].position.y / scale;
        planet_shapes[j].setPosition(planet_x_coordinate,planet_y_coordinate);
        planet_text[j].setPosition(planet_x_coordinate, planet_y_coordinate + 20);
        window.draw(planet_shapes[j]);
        if(debug == 0) {
          planet_text[j].setString(std::string(planets[j].name));
        } else {
          planet_text[j].setString(std::string(planets[j].name) +
            "\n (" + std::string(to_string(planets[j].position.get_x())) +
            ","  + std::string(to_string(planets[j].position.get_y())) +
            ")"
          );
        }
        window.draw(planet_text[j]);
      }
      sf::Text text;
      text.setFont(font);
      text.setString("Timestep: " + to_string(TIMESTEP / 3600) + " hours "  +
      "\n Scale: " + to_string(scale / (150 * pow(10,9))) + "AU (approximately 150x10^9m)" +
      "\n Debug: " + to_string(debug)
      );
      text.setCharacterSize(20);
      text.setPosition(0,0);
      window.draw(text);
      window.display();
  }
}

void planet_math(std::vector<planet> &planets) {
  while(true) {
    for(int i = 0; i < planets.size(); i = i + 1) {
      planets[i].update_position(planets);
    }
    std::this_thread::sleep_for(1s);
  }
}

int main()
{
    std::vector<planet> planets = load_model();
    thread planet_manipulator(planet_math, std::ref(planets));
    planet_display(planets);
    return 0;
}
