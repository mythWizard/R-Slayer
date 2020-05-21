#ifndef ITEM__HPP
#define ITEM__HPP

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Item{
	public:
		Item(){coin.loadFromFile("assets/Placeholder/Coin.png"); potion.loadFromFile("assets/Placeholder/Potion.png"); bomb.loadFromFile("assets/Placeholder/Bomb.png");}
		string type;
		int amt;
		sf::Texture coin;
		sf::Texture potion;
		sf::Texture bomb;
	private:
};

#endif