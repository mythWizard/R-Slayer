#ifndef ENEMY__HPP
#define ENEMY__HPP

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "position.hpp"

class Enemy{
	public:
		Enemy();
		void move(string dir, Player* hero);
		void setType(string t){type = t;}
		void setHealth(int h){health = h;}
		void takeDamage(int d){health -= d;}
		void draw(sf::RenderWindow& window, Player hero);
		void setPos(Position newPos){pos = newPos;}
		//void die();
		Position getPos(){return pos;}
		string getType(){return type;}
		int getHealth(){return health;}
	private:
		Position pos;
		int health;
		string type;
		sf::Texture rat;
		sf::Texture slime;
		sf::Texture snake;
		//TODO MIMICS - PAST FIRST BOSS?
		//TODO BOSSES - EVERY FIFTH LEVEL
};

#endif