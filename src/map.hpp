#ifndef MAP__HPP
#define MAP__HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "position.hpp"
#include "player.hpp"
#include "enemy.hpp"

using namespace std;

class Map{
	public:
		Map();
		vector<string> floor;
		bool isValid(Position loc);
		bool inBounds(Position loc);
		bool checkWall(Position loc);
		bool checkRoom(int rx, int ry, int rw, int rh);
		void createRoom(int rx, int ry, int rw, int rh);
		void create(int a, int b);
		void generate(int a, int b, int level);
		void draw(sf::RenderWindow& window, Player hero);
		void spawn(Player& hero, string dir);
		void explode(Position b);
		int checkEnemy(vector<Enemy> e, Position newPos);

	private:
		sf::Texture wall;
		sf::Texture ground;
		sf::Texture mossWall;
		sf::Texture mossGround;
		sf::Texture coin;
		sf::Texture bomb;
		sf::Texture potion;
		sf::Texture shop;
		sf::Texture door;
		sf::Texture stairUp;
		sf::Texture stairDown;
};

#endif