#include "enemy.hpp"

Enemy::Enemy(){
	rat.loadFromFile("assets/Placeholder/Rat.png");
	slime.loadFromFile("assets/Placeholder/Slime.png");
	snake.loadFromFile("assets/Placeholder/Snake.png");
}

void Enemy::move(string dir, Player* hero){
	Position ppos = hero->getPos();
	Position newpos = pos;
	if(dir == "UP"){
		newpos.y -= 1;
		if(newpos == ppos){
			hero->setHealth(hero->getHealth() - 3);
		}else{
			pos = newpos;
		}
	}else if(dir == "DOWN"){
		newpos.y += 1;
		if(newpos == ppos){
			hero->setHealth(hero->getHealth() - 3);
		}else{
			pos = newpos;
		}
	}else if(dir == "LEFT"){
		newpos.x -= 1;
		if(newpos == ppos){
			hero->setHealth(hero->getHealth() - 3);
		}else{
			pos = newpos;
		}
	}else if(dir == "RIGHT"){
		newpos.x += 1;
		if(newpos == ppos){
			hero->setHealth(hero->getHealth() - 3);
		}else{
			pos = newpos;
		}
	}
}

void Enemy::draw(sf::RenderWindow& window, Player hero){
	sf::Vector2<unsigned int> dims = window.getSize();
	int cScreenX = dims.x / 2;
	int cScreenY = dims.y / 2;

	Position drawFrom = Position(cScreenX - (hero.getPos().x * 64) - 32, cScreenY - (hero.getPos().y * 64) - 32);
	Position drawSpot = Position(drawFrom.x + (pos.x * 64), drawFrom.y + (pos.y * 64));
	sf::Sprite s;
	s.setPosition(drawSpot.x, drawSpot.y);
	if(type == "RAT"){
		s.setTexture(rat);
	}else if(type == "SLIME"){
		s.setTexture(slime);
	}else if(type == "SNAKE"){
		s.setTexture(snake);
	}
	window.draw(s);
}