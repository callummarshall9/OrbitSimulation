sf::Color handle_colour(std::string colour) {
  if(colour == "red") {
    return sf::Color::Red;
  } else if (colour == "blue") {
    return sf::Color::Blue;
  } else if (colour == "green") {
    return sf::Color::Green;
  } else if(colour == "yellow") {
    return sf::Color::Yellow;
  } else if(colour == "orange") {
    return sf::Color(255,165,0);
  } else if(colour == "lightblue") {
    return sf::Color(30,144,255);
  } else if(colour == "grey") {
    return sf::Color(169,169,169);
  }
  return sf::Color(255,255,255);
}
