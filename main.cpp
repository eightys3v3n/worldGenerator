#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "world.hpp"
#include "generator.hpp"
#include "window.hpp"

using namespace std;
using namespace sf;

int main()
{
  srand( 1337 );

  RenderWindow window( VideoMode(500,500), "game", Style::Close );
  window.setFramerateLimit(61);

  World world;
  world.size(50,50);

  cout << "world resized." << endl;

  generate( world );

  cout << "generated world." << endl;

  draw( window, world );

  cout << "drew world." << endl;

  cin.ignore( 255, '\n' );
  window.close();

  return false;
}