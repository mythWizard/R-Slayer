#include <iostream>
#include <sstream>

#include "player.hpp"

Player::Player(){
	tex.loadFromFile("assets/Placeholder/Player.png");
	panel.loadFromFile("assets/Placeholder/Panel.png");
	panelTop.loadFromFile("assets/Placeholder/PanelTop.png");
	alagard.loadFromFile("assets/Fonts/alagard.ttf");
	health = 20;
	healthmax = 20;
	exp = 0;
	expnext = 20;
}

void Player::move(string dir){
	if(dir == "UP"){
		setPos(getPos() + Position(0, -1));
	}else if(dir == "DOWN"){
		setPos(getPos() + Position(0, 1));
	}else if(dir == "LEFT"){
		setPos(getPos() + Position(-1, 0));
	}else if(dir == "RIGHT"){
		setPos(getPos() + Position(1, 0));
	}
}

void Player::draw(sf::RenderWindow& window){
	sf::Vector2<unsigned int> dims = window.getSize();
	int cScreenX = dims.x / 2;
	int cScreenY = dims.y / 2;
	Position drawFrom = Position(cScreenX - 32, cScreenY - 32);

	sf::Sprite s;
	s.setPosition(drawFrom.x, drawFrom.y);
	s.setTexture(tex);
	window.draw(s); 

	sf::RectangleShape rect(sf::Vector2f(1024, 96));
	rect.setPosition(cScreenX - (8 * 64), dims.y - 96);
	rect.setFillColor(sf::Color::White);
	window.draw(rect);

	rect.setSize(sf::Vector2f(128, 24));
	rect.setPosition(cScreenX - (7 * 64) - 16, dims.y - 60);
	rect.setFillColor(sf::Color::Black);
	window.draw(rect);

	rect.setSize(sf::Vector2f((124 * (health / healthmax)), 20));
	rect.setPosition(cScreenX - (7 * 64) - 14, dims.y - 58);
	rect.setFillColor(sf::Color::Red);
	window.draw(rect);

	rect.setSize(sf::Vector2f(128, 24));
	rect.setPosition(cScreenX - (7 * 64) - 16, dims.y - 28);
	rect.setFillColor(sf::Color::Black);
	window.draw(rect);

	rect.setSize(sf::Vector2f((124 * (exp / expnext)), 20));
	rect.setPosition(cScreenX - (7 * 64) - 14, dims.y - 26);
	rect.setFillColor(sf::Color::Blue);
	window.draw(rect);

	for(int i = 0; i < 10; ++i){
		Position drawSpot = Position((cScreenX - (5 * 64)) + (i * 64), dims.y - 64);
		s.setPosition(drawSpot.x, drawSpot.y);
		s.setTexture(panel);
		window.draw(s); 
		s.setTexture(panelTop);
		window.draw(s);
		if(inventory.size() > i){
			if(inventory[i].type == "COIN"){
				s.setTexture(inventory[i].coin);
				//s.scale(0.25, 0.25);
				window.draw(s);
				//s.scale(4, 4);
				stringstream sout;
				sout << inventory[i].amt;
				sf::Text textAmt(sout.str(), alagard, 16);
				textAmt.setPosition(drawSpot.x + 6, drawSpot.y + 42);
				window.draw(textAmt);
			}else if(inventory[i].type == "BOMB"){
				s.setTexture(inventory[i].bomb);
				window.draw(s);
				stringstream sout;
				sout << inventory[i].amt;
				sf::Text textAmt(sout.str(), alagard, 16);
				textAmt.setPosition(drawSpot.x + 6, drawSpot.y + 42);
				window.draw(textAmt);
			}else if(inventory[i].type == "POTION"){
				s.setTexture(inventory[i].potion);
				window.draw(s);
				stringstream sout;
				sout << inventory[i].amt;
				sf::Text textAmt(sout.str(), alagard, 16);
				textAmt.setPosition(drawSpot.x + 6, drawSpot.y + 42);
				window.draw(textAmt);
			}
		}
	}
}

void Player::pickup(Item it){
	for(int i = 0; i < inventory.size(); ++i){
		if(inventory[i].type == it.type){
			inventory[i].amt += it.amt;
			return;
		}
	}
	if(inventory.size() < 10){
		inventory.push_back(it);
	}
}

bool Player::pay(int amt){
	for(int i = 0; i < inventory.size(); ++i){
		if(inventory[i].type == "COIN"){
			if(inventory[i].amt - amt >= 0){
				inventory[i].amt -= amt;
				return true;
			}
			return false;
		}
	}
	return false;
}

void Player::use(int item){
	if(inventory.size() <= item){
		return;
	}

	if(inventory[item].type == "COIN"){
		return;
	}

	if(inventory[item].amt > 0){
		inventory[item].amt -= 1;
	}

	if(inventory[item].type == "POTION"){
		health += 5;
		if(health > healthmax){
			health = healthmax;
		}
	}
}

string Player::getItemType(int item){
	if(inventory.size() <= item){
		return "";
	}
	return inventory[item].type;
}

void Player::gainExp(int amt){
	exp += amt;
	if(exp >= expnext){
		exp = int(exp) % int(expnext);
		expnext *= 2;
	}
}

/*
void Player::attack(Enemy e){
	e.takeDamage(3);
	if(e.getHealth() <= 0){
		exp += 3;
	}else{
		health -= 3;
	}
}
*/