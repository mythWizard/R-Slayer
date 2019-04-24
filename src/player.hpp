#ifndef PLAYER__HPP
#define PLAYER__HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "item.hpp"
#include "position.hpp"
//#include "enemy.hpp"

using namespace std;

class Player{
	public:
		Player();
		//~Player();
		void move(string dir);
		void setPos(Position newPos){pos = newPos;}
		void setHealth(int amt){health = amt;}
		void draw(sf::RenderWindow& window);
		void setClass(string c){classification = c;}
		void pickup(Item it);
		void use(int item);
		void gainExp(int amt);
		bool pay(int amt);
		int inventorySize(){return inventory.size();}
		int getHealth(){return health;}
		string getItemType(int item);
		Position getPos(){return pos;}
		//void attack(Enemy e);

	private:
		string classification;
		Position pos;
		vector<Item> inventory;
		double health;
		double healthmax;
		double exp;
		double expnext;
		int level;
		sf::Texture tex;
		sf::Texture panel;
		sf::Texture panelTop;
		sf::Font alagard;
};

#endif