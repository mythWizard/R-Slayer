#include <iostream>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "enemy.hpp"
#include "position.hpp"
#include "map.hpp"
#include "item.hpp"

#define width 1280
#define height 720

using namespace std;

int gamemode = 2;
// Set game mode
// 1 = Play
// 2 = Main Menu
// 3 = New Floor
// 4 = Lose
// 5 = Win
// 6 = Instructions
// 7 = Credits
// 8 = Pause
// 9 = Shop

int main(){

	sf::RenderWindow window(sf::VideoMode(width, height), "R@ Slayer");//, sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	Player hero;
	Position heroPos;
	vector<Map> floors;
	vector<Enemy> enemies;
	Map m;
	bool moved;
	int eChance;
	vector<vector<string>> eTypes;

	vector<string> floorTypes;
	floorTypes.push_back("RAT");
	floorTypes.push_back("SLIME");
	floorTypes.push_back("SNAKE");
	eTypes.push_back(floorTypes);

	int currentFloor = 0;

	m.generate(30, 30, floors.size() + 1);
	floors.push_back(m);

	bool placed = false;

	for(int i = 0; i < m.floor.size(); ++i){
		for(int j = 0; j < m.floor[i].size(); ++j){
			if(m.floor[i][j] == '.'){
				hero.setPos(Position(j, i));
				placed = true;
				break;
			}
		}
		if(placed){
			break;
		}
	}

	//window.setKeyRepeatEnabled(false);

	while(window.isOpen()){
		sf::Event ev;
		while(window.pollEvent(ev)){
			if (ev.type == sf::Event::Closed){
				window.close();
			}
			window.clear(sf::Color::Black);

			switch(gamemode){
				case 1:
					window.setKeyRepeatEnabled(true);

					//window.clear(sf::Color::Red);
					if(ev.type == sf::Event::KeyPressed){
						Position next = hero.getPos();
						if(ev.key.code == sf::Keyboard::Escape){
							gamemode = 8;
							break;
						}else if(ev.key.code == sf::Keyboard::W){
							next = next + Position(0, -1);
							if(m.inBounds(next)){
								if(!m.checkWall(next)){
									int en = m.checkEnemy(enemies, next);
									if(en == -1){
										hero.move("UP");
										moved = true;
									}else{
										enemies[en].takeDamage(5);
										if(enemies[en].getHealth() <= 0){
											enemies.erase(enemies.begin() + en);
											hero.gainExp(5);
										}
									}
								}
							}
						}else if(ev.key.code == sf::Keyboard::S){
							next = next + Position(0, 1);
							if(m.inBounds(next)){
								if(!m.checkWall(next)){
									int en = m.checkEnemy(enemies, next);
									if(en == -1){
										hero.move("DOWN");
										moved = true;
									}else{
										enemies[en].takeDamage(5);
										if(enemies[en].getHealth() <= 0){
											enemies.erase(enemies.begin() + en);
											hero.gainExp(5);
										}
									}
								}
							}
						}else if(ev.key.code == sf::Keyboard::A){
							next = next + Position(-1, 0);
							if(m.inBounds(next)){
								if(!m.checkWall(next)){
									int en = m.checkEnemy(enemies, next);
									if(en == -1){
										hero.move("LEFT");
										moved = true;
									}else{
										enemies[en].takeDamage(5);
										if(enemies[en].getHealth() <= 0){
											enemies.erase(enemies.begin() + en);
											hero.gainExp(5);

										}
									}
								}
							}
						}else if(ev.key.code == sf::Keyboard::D){
							next = next + Position(1, 0);
							if(m.inBounds(next)){
								if(!m.checkWall(next)){
									int en = m.checkEnemy(enemies, next);
									if(en == -1){
										hero.move("RIGHT");
										moved = true;
									}else{
										enemies[en].takeDamage(5);
										if(enemies[en].getHealth() <= 0){
											enemies.erase(enemies.begin() + en);
											hero.gainExp(5);
										}
									}
								}
							}
						}else if(ev.key.code == sf::Keyboard::Space){
							if(m.floor[heroPos.y][heroPos.x] == '^'){
								gamemode = 3;
							}else if(m.floor[heroPos.y][heroPos.x] == 'v'){
								floors[currentFloor] = m;
								--currentFloor;
								m = floors[currentFloor];
								m.spawn(hero, "DOWN");
							}else if(m.floor[heroPos.y][heroPos.x] == '$'){
								gamemode = 9;
							}else{
								continue;
							}
						}else if(ev.key.code == sf::Keyboard::Num1){
							hero.use(0);
							if(hero.getItemType(0) == "BOMB"){
								m.explode(hero.getPos());
							}
						}else if(ev.key.code == sf::Keyboard::Num2){
							hero.use(1);
							if(hero.getItemType(1) == "BOMB"){
								m.explode(hero.getPos());
							}
						}else if(ev.key.code == sf::Keyboard::Num3){
							hero.use(2);
							if(hero.getItemType(2) == "BOMB"){
								m.explode(hero.getPos());
							}
						}
						
						//cout << "PLAYER MOVED" << endl;

						for(int i = 0; i < enemies.size(); ++i){
							//cout << enemies[i].getType() << endl;
							//cout << enemies[i].getPos().x << " " << enemies[i].getPos().y << endl;
							Position enow = enemies[i].getPos();
							//cout << enow.x << " " << enow.y << endl;
							if(enow + Position(0, -1) == heroPos){
								enemies[i].move("UP", &hero);
							} else if(enow + Position(0, 1) == heroPos){
								enemies[i].move("DOWN", &hero);
							} else if(enow + Position(-1, 0) == heroPos){
								enemies[i].move("LEFT", &hero);
							} else if(enow + Position(1, 0) == heroPos){
								enemies[i].move("RIGHT", &hero);
							} else {
								bool eMoved = false;
								while(!eMoved){
									int eDir = rand() % 4;
									//cout << eDir << endl;
									if(eDir == 0){
										Position enext = enow + Position(0, -1);
										if(m.inBounds(enext)){
											if(!m.checkWall(enext)){
												//cout << m.checkWall(enext) << endl;
												enemies[i].move("UP", &hero);
												eMoved = true;
											}
										}
									}else if(eDir == 1){
										Position enext = enow + Position(0, 1);
										if(m.inBounds(enext)){
											if(!m.checkWall(enext)){
												//cout << m.checkWall(enext) << endl;
												enemies[i].move("DOWN", &hero);
												eMoved = true;
											}
										}
									}else if(eDir == 2){
										Position enext = enow + Position(-1, 0);
										if(m.inBounds(enext)){
											if(!m.checkWall(enext)){
												//cout << m.checkWall(enext) << endl;
												enemies[i].move("LEFT", &hero);
												eMoved = true;
											}
										}
									}else if(eDir == 3){
										Position enext = enow + Position(1, 0);
										if(m.inBounds(enext)){
											if(!m.checkWall(enext)){
												//cout << m.checkWall(enext) << endl;
												enemies[i].move("RIGHT", &hero);
												eMoved = true;
											}
										}
									}
								}
							}
						}
						
						//cout << "ENEMIES MOVED" << endl;

						if(enemies.size() < 10){
							eChance = rand() % 26;
							if(eChance == 0){
								Enemy e;
								int cLevel = currentFloor / 5;
								int eType = rand() % eTypes[cLevel].size();
								e.setType(eTypes[cLevel][eType]);
								e.setHealth(10);
								Position newPos(0, 0);
								while(m.checkWall(newPos)){
									int posx = rand() % m.floor[0].size();
									int posy = rand() % m.floor.size();
									newPos.x = posx;
									newPos.y = posy;
								}
								e.setPos(newPos);
								enemies.push_back(e);
							}
						}
					}

					//cout << "ENEMIES SPAWNED" << endl;

					heroPos = hero.getPos();
					if(moved){
						if(m.floor[heroPos.y][heroPos.x] == 'o'){
							int amt = (rand() % 20) + 1;
							Item c;
							c.type = "COIN";
							c.amt = amt;
							hero.pickup(c);
							m.floor[heroPos.y][heroPos.x] = '.';
						}else if(m.floor[heroPos.y][heroPos.x] == 'b'){
							Item c;
							c.type = "BOMB";
							c.amt = 1;
							hero.pickup(c);
							m.floor[heroPos.y][heroPos.x] = '.';
						}else if(m.floor[heroPos.y][heroPos.x] == 'p'){
							Item c;
							c.type = "POTION";
							c.amt = 1;
							hero.pickup(c);
							m.floor[heroPos.y][heroPos.x] = '.';
						}
					}
					moved = false;

					//cout << "ITEMS PICKED UP" << endl;

					m.draw(window, hero);
					for(Enemy e : enemies){
						e.draw(window, hero);
					}
					hero.draw(window);

					//cout << "ENTITIES DRAWN" << endl;

					break;

				case 2:
					window.setKeyRepeatEnabled(false);
					window.clear(sf::Color::White);
					if(ev.type == sf::Event::KeyPressed){
						if(ev.key.code == sf::Keyboard::Escape){
							gamemode = -1;
						}else if(ev.key.code == sf::Keyboard::Space){
							gamemode = 1;
						}
					}
					break;
				case 3:
					floors[currentFloor] = m;
					if(currentFloor + 1 == floors.size()){
						m.generate(30, 30, floors.size() + 1);
						floors.push_back(m);
						++currentFloor;
					}else{
						++currentFloor;
						m = floors[currentFloor];
					}
					m.spawn(hero, "UP");
					gamemode = 1;
					enemies.clear();
					window.clear(sf::Color::Black);
					m.draw(window, hero);
					hero.draw(window);
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					window.setKeyRepeatEnabled(false);
					window.clear(sf::Color::Blue);
					if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
						gamemode = -1;
					}
					break;
				case 9:
					window.setKeyRepeatEnabled(false);
					window.clear(sf::Color::Magenta);
					if(ev.type == sf::Event::KeyPressed){
						if(ev.key.code == sf::Keyboard::Space){
							gamemode = 1;
						}
					}
					break;
				case -1:
					window.close();
				default:
					break;
			}

		}

		window.display();
	}

	return 0;
}
