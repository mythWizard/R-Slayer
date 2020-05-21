#include <cmath>
#include <vector>
#include <iostream>
//#include <Vector2.hpp>

#include "map.hpp"

Map::Map(){
	wall.loadFromFile("assets/Placeholder/BasicWall.png");
	ground.loadFromFile("assets/Placeholder/BasicTile.png");
	mossWall.loadFromFile("assets/Placeholder/MossyWall.png");
	mossGround.loadFromFile("assets/Placeholder/MossyTile.png");
	//coin.setSrgb(true);
	coin.loadFromFile("assets/Placeholder/Coin.png");
	bomb.loadFromFile("assets/Placeholder/Bomb.png");
	potion.loadFromFile("assets/Placeholder/Potion.png");
	shop.loadFromFile("assets/Placeholder/Shop.png");
	door.loadFromFile("assets/Placeholder/Door.png");
	stairUp.loadFromFile("assets/Placeholder/StairUp.png");
	stairDown.loadFromFile("assets/Placeholder/StairDown.png");
}

bool Map::checkRoom(int rx, int ry, int rw, int rh){

	for(int i = 0; i < rh; ++i){
		for(int j = 0; j < rw; ++j){
			if(floor[ry + i][rx + j] == '.' || floor[i + ry][j + rx] == 'X' || floor[i + ry][j + rx] == ',' || floor[i + ry][j + rx] == 'x'){
				return false;
			}
			if(rx > 0){
				if(floor[ry + i][rx + j - 1] == 'd'){
					return false;
				}
			}
			if(ry > 0){
				if(floor[ry + i - 1][rx + j] == 'd'){
					return false;
				}
			}
			if(ry + rh - 1 < floor.size()){
				if(floor[ry + i + 1][rx + j] == 'd'){
					return false;
				}
			}
			if(rx + rw - 1 < floor[rx].size()){
				if(floor[ry + i][rx + j + 1] == 'd'){
					return false;
				}
			}
		}
	}
	return true;
}

void Map::createRoom(int rx, int ry, int rw, int rh){
	for(int i = 0; i < rh; ++i){
		for(int j = 0; j < rw; ++j){
			int mossChance = rand() % 20;
			if(i == 0 || j == 0 || i == rh - 1 || j == rw - 1){
				if(mossChance == 0){
					floor[i + ry][j + rx] = 'x';
				}else{
					floor[i + ry][j + rx] = 'X';
				}
			} else {
				if(mossChance == 0){
					floor[i + ry][j + rx] = ',';
				}else{
					floor[i + ry][j + rx] = '.';
				}
			}
		}
	}

	bool oneDoor = false;

	while(!oneDoor){
		//Top side
		if(ry > 1){
			for(int i = 1; i < rw - 1; ++i){
				int dChance = rand() % (rw - 2);
				if(dChance == 0 && floor[ry][rx + i - 1] != 'd'){
					if(floor[ry - 1][rx + i] != '/'){
						floor[ry - 1][rx + i] = '.';
						if(inBounds(Position(rx + i, ry - 2))){
							if(!isValid(Position(ry - 2, rx + i))){
								floor[ry - 2][rx + i] = '.';
							}
						}
					}
					floor[ry][rx + i] = 'd';
					oneDoor = true;
				}
			}
		}

		//Bottom side
		if(ry + rh < floor.size() - 2){
			for(int i = 1; i < rw - 1; ++i){
				int dChance = rand() % (rw - 2);
				if(dChance == 0 && floor[ry + rh - 1][rx + i - 1] != 'd'){
					if(floor[ry + rh][rx + i] != '/'){
						floor[ry + rh][rx + i] = '.';
						if(inBounds(Position(rx + i, ry + rh + 1))){
							if(!isValid(Position(ry + rh + 1, rx + i))){
								floor[ry + rh + 1][rx + i] = '.';
							}
						}
					}
					floor[ry + rh - 1][rx + i] = 'd';
					oneDoor = true;
				}
			}
		}

		//Left side
		if(rx > 1){
			for(int i = 1; i < rh - 1; ++i){
				int dChance = rand() % (rh - 2);
				if(dChance == 0 && floor[ry + i - 1][rx] != 'd'){
					if(floor[ry + i][rx - 1] != '/'){
						floor[ry + i][rx - 1] = '.';
						if(inBounds(Position(rx - 1, ry + i))){
							if(!isValid(Position(ry + i, rx - 1))){
								floor[ry + i][rx - 1] = '.';
							}
						}
					}
					floor[ry + i][rx] = 'd';
					oneDoor = true;
				}
			}
		}

		//Right side
		if(rx + rw < floor[rx].size()){
			for(int i = 1; i < rh - 1; ++i){
				int dChance = rand() % (rh - 2);
				if(dChance == 0 && floor[ry + i - 1][rx + rw - 1] != 'd'){
					if(floor[ry + i][rx + rw] != '/'){
						floor[ry + i][rx + rw] = '.';
						if(inBounds(Position(rx + rw + 1, ry + i))){
							if(!isValid(Position(ry + i, rx + rw + 1))){
								floor[ry + i][rx + rw + 1] = '.';
							}
						}
					}
					floor[ry + i][rx + rw - 1] = 'd';
					oneDoor = true;
				}
			}
		}
	}
}

bool Map::isValid(Position loc){
	if(loc.x < floor[loc.x].size() && loc.x > 0 && loc.y > 0 && loc.y < floor.size()){
		if(floor[loc.y][loc.x] == '/'){
			return true;
		}
	}
	return false;
}

bool Map::inBounds(Position loc){
	if(loc.x < floor[0].size() - 1 && loc.x > 0 && loc.y > 0 && loc.y < floor.size() - 1){
		return true;
	}
	return false;
}

bool Map::checkWall(Position loc){
	if(floor[loc.y][loc.x] == 'X' || floor[loc.y][loc.x] == 'x'){
		return true;
	}
	return false;
}

void Map::create(int a, int b){

	srand(time(NULL));

	if(a % 2 == 0)
		a++;

	if(b % 2 == 0)
		b++;

	//making a vector for editing
	floor = vector<string>(a);
	for(int i = 0; i < a; ++i){
		for(int j = 0; j < b; ++j){
			if(i % 2 == 0){
				floor[i] += "#";
			}else{
				if(j%2 == 0){
					floor[i] += "#";
				}else{
					floor[i] += "/";
				}
			}
		}
	}
}

void Map::generate(int a, int b, int level){

	create(a, b);

	int roomAttempts = (a * b) / 4;

	for(int i = 0; i < roomAttempts; ++i){
		int rx = rand() % b;
		if(rx % 2 == 1)
			++rx;
		int ry = rand() % a;
		if(ry % 2 == 1)
			++ry;
		int rw = 4 + (rand() % (b / 2));
		int rh = 4 + (rand() % (a / 2));
		if(rw % 2 == 0)
			++rw;
		if(rh % 2 == 0)
			++rh;
		if(rx + rw < b && ry + rh < a){
			if(checkRoom(rx, ry, rw, rh)){
				createRoom(rx, ry, rw, rh);
			}
		}
	}

	bool upPlaced = false;
	bool downPlaced = false;

	if(level > 1){
		while(!(upPlaced && downPlaced)){
			for(int i = 0; i < floor.size(); ++i){
				for(int j = 0; j < floor[i].size(); ++j){
					int stairChance = rand() % (a * b / 4);
					if(stairChance == 0 && !upPlaced && (floor[i][j] == ',' || floor[i][j] == '.')){
						floor[i][j] = '^';
						upPlaced = true;
					}else if(stairChance == 1 && !downPlaced && (floor[i][j] == ',' || floor[i][j] == '.')){
						floor[i][j] = 'v';
						downPlaced = true;
					}
				}
			}
		}
	}else{
		while(!upPlaced){
			for(int i = 0; i < floor.size(); ++i){
				for(int j = 0; j < floor[i].size(); ++j){
					int stairChance = rand() % (a * b / 4);
					if(stairChance == 0 && !upPlaced && (floor[i][j] == ',' || floor[i][j] == '.')){
						floor[i][j] = '^';
						upPlaced = true;
					}
				}
			}
		}
	}

	//setting the number of coins and shops
	int numshop = a*b/200 + 1;
	int numcoins = a*b/5 + 10;
	int numpotions = a*b/5;
	int numbombs = a*b/10;

	while(true){
		bool firstfound = false;
		vector<Position> spots;
		for(int a = 0; a < floor.size(); ++a){
			for(int b = 0; b < floor[a].size(); ++b){
				if(floor[a][b] == '/'){
					spots.push_back(Position(b,a));
					floor[a][b] = '.';
					firstfound = true;
					//cout << b << " " << a << endl;
					break;
				}
			}
			if(firstfound){
				break;
			}
		}

		if(firstfound == false){
			break;
		}

		//cout << "Starting Map Building" << endl;

		while(spots.size() != 0){

			Position loc = spots[spots.size()-1];

			vector<Position> nbs = vector<Position>();
			Position nba = Position(loc.x+2, loc.y);
			Position nbb = Position(loc.x-2, loc.y);
			Position nbc = Position(loc.x, loc.y-2);
			Position nbd = Position(loc.x, loc.y+2);
			//finding the valid spots
			if(isValid(nba)){
				nbs.push_back(nba);
			}
			if(isValid(nbb)){
				nbs.push_back(nbb);
			}
			if(isValid(nbc)){
				nbs.push_back(nbc);
			}
			if(isValid(nbd)){
				nbs.push_back(nbd);
			}

			if(nbs.size() == 0){
				spots.pop_back();
			} else {
				//choosing the random neighbor
				int num = rand() % nbs.size();
				int mossChance = rand() % 20;
				int mossChance2 = rand() % 20;
				//marking the spots as visited and removing the wall
				if(num == 0){
					spots.push_back(nbs[0]);
					if(mossChance == 0){
						floor[nbs[0].y][nbs[0].x] = ',';
					}else{
						floor[nbs[0].y][nbs[0].x] = '.';
					}
					Position mid = (loc + nbs[0])/2; 
					if(mossChance2 == 0){
						floor[mid.y][mid.x] = ',';
					}else{
						floor[mid.y][mid.x] = '.';
					}
				}else if(num == 1){
					spots.push_back(nbs[1]);
					if(mossChance == 0){
						floor[nbs[1].y][nbs[1].x] = ',';
					}else{
						floor[nbs[1].y][nbs[1].x] = '.';
					}
					Position mid = (loc + nbs[1])/2; 
					if(mossChance2 == 0){
						floor[mid.y][mid.x] = ',';
					}else{
						floor[mid.y][mid.x] = '.';
					}
				}else if(num == 2){
					spots.push_back(nbs[2]);
					if(mossChance == 0){
						floor[nbs[2].y][nbs[2].x] = ',';
					}else{
						floor[nbs[2].y][nbs[2].x] = '.';
					}
					Position mid = (loc + nbs[2])/2; 
					if(mossChance2 == 0){
						floor[mid.y][mid.x] = ',';
					}else{
						floor[mid.y][mid.x] = '.';
					}
				}else if(num == 3){
					spots.push_back(nbs[3]);
					if(mossChance == 0){
						floor[nbs[3].y][nbs[3].x] = ',';
					}else{
						floor[nbs[3].y][nbs[3].x] = '.';
					}
					Position mid = (loc + nbs[3])/2; 
					if(mossChance2 == 0){
						floor[mid.y][mid.x] = ',';
					}else{
						floor[mid.y][mid.x] = '.';
					}
				}

			}
		}
	}

	//replacing any remaining placeholder symbols
	for(int i = 0; i < floor.size(); ++i){
		for(int j = 0; j < floor[i].size(); ++j){
			int mossChance = rand() % 20;
			if(floor[i][j] == '#'){				
				if(mossChance == 0){
					floor[i][j] = 'x';
				}else{
					floor[i][j] = 'X';
				}
			}else if(floor[i][j] == '/'){
				if(mossChance == 0){
					floor[i][j] = ',';
				}else{
					floor[i][j] = '.';
				}
			}
		}
	}

	//generating coins
	for(int i = 0; i < floor.size(); ++i){
		for(int j = 0; j < floor[i].size(); ++j){
			if(rand() % (a * b / 4) == 0){
				if(floor[i][j] == '.' || floor[i][j] == ','){
					floor[i][j] = 'o';
					--numcoins;
				}
			}
		}
	}
	for(int i = 0; i < floor.size(); ++i){
		for(int j = 0; j < floor[i].size(); ++j){
			if(rand() % (a * b / 4) == 0){
				if(floor[i][j] == '.' || floor[i][j] == ','){
					floor[i][j] = 'b';
					--numbombs;
				}
			}
		}
	}
	for(int i = 0; i < floor.size(); ++i){
		for(int j = 0; j < floor[i].size(); ++j){
			if(rand() % (a * b / 4) == 0){
				if(floor[i][j] == '.' || floor[i][j] == ','){
					floor[i][j] = 'p';
					--numpotions;
				}
			}
		}
	}
	//generating shops
	for(int i = 0; i < floor.size(); ++i){
		for(int j = 0; j < floor[i].size(); ++j){
			if(rand() % (a * b / 2) == 0){
				if(floor[i][j] == '.'){
					floor[i][j] = '$';
					numshop--;
				}
			}
		}
	}

	for(int i = 0; i < floor.size(); ++i){
		for(int j = 0; j < floor[i].size(); ++j){
			cout << floor[i][j];
		}
		cout << endl;
	}
}

void Map::draw(sf::RenderWindow& window, Player hero){
	sf::Vector2<unsigned int> dims = window.getSize();
	int cScreenX = dims.x / 2;
	int cScreenY = dims.y / 2;

	Position drawFrom = Position(cScreenX - (hero.getPos().x * 64) - 32, cScreenY - (hero.getPos().y * 64) - 32);

	for(int i = 0; i < floor.size(); ++i){
		for(int j = 0; j < floor[i].size(); ++j){
			sf::Sprite s;
			//rect.setSize(sf::Vector2f(64, 64));
			s.setPosition(drawFrom.x + (j * 64), drawFrom.y + (i * 64));
			if(floor[i][j] == 'X'){
				s.setTexture(wall);
			}else if(floor[i][j] == '.'){
				s.setTexture(ground);
				//rect.setFillColor(sf::Color::White);
			}else if(floor[i][j] == 'x'){
				s.setTexture(mossWall);
			}else if(floor[i][j] == ','){
				s.setTexture(mossGround);
			}else if(floor[i][j] == 'o'){
				s.setTexture(ground);
				window.draw(s);
				s.setTexture(coin);
				s.setScale(0.25, 0.25);
				//cout << coin.isSrgb() << endl;

				//rect.setFillColor(sf::Color::Yellow);
			}else if(floor[i][j] == '$'){
				s.setTexture(shop);
				//rect.setFillColor(sf::Color::Green);
			}else if(floor[i][j] == '^'){
				s.setTexture(ground);
				window.draw(s);
				s.setTexture(stairUp);
			}else if(floor[i][j] == 'v'){
				s.setTexture(ground);
				window.draw(s);
				s.setTexture(stairDown);
			}else if(floor[i][j] == 'd'){
				s.setTexture(ground);
				window.draw(s);
				s.setTexture(door);
			}else if(floor[i][j] == 'p'){
				s.setTexture(ground);
				window.draw(s);
				s.setTexture(potion);
			}else if(floor[i][j] == 'b'){
				s.setTexture(ground);
				window.draw(s);
				s.setTexture(bomb);
			}
			window.draw(s);
		}
	}
}

void Map::spawn(Player& hero, string dir){
	if(dir == "UP"){
		for(int i = 0; i < floor.size(); ++i){
			for(int j = 0; j < floor[i].size(); ++j){
				if(floor[i][j] == 'v'){
					hero.setPos(Position(j, i));
				}
			}
		}
	}else if(dir == "DOWN"){
		for(int i = 0; i < floor.size(); ++i){
			for(int j = 0; j < floor[i].size(); ++j){
				if(floor[i][j] == '^'){
					hero.setPos(Position(j, i));
				}
			}
		}
	}
}

void Map::explode(Position b){
	//Make sure it doesn't blow up the stairs

	Position up = Position(b.x, b.y - 1);
	Position up2 = Position(b.x, b.y - 2);
	Position down = Position(b.x, b.y + 1);
	Position down2 = Position(b.x, b.y + 2);
	Position left = Position(b.x - 1, b.y);
	Position left2 = Position(b.x - 2, b.y);
	Position right = Position(b.x + 1, b.y);
	Position right2 = Position(b.x + 2, b.y);
	Position upl = Position(b.x - 1, b.y - 1);
	Position upr = Position(b.x + 1, b.y - 1);
	Position dl = Position(b.x - 1, b.y + 1);
	Position dr = Position(b.x + 1, b.y + 1);

	floor[b.y][b.x] = '.';

	if(inBounds(up)){
		floor[up.y][up.x] = '.';
	}
	if(inBounds(up2)){
		floor[up2.y][up2.x] = '.';
	}
	if(inBounds(down)){
		floor[down.y][down.x] = '.';
	}
	if(inBounds(down2)){
		floor[down2.y][down2.x] = '.';
	}
	if(inBounds(left)){
		floor[left.y][left.x] = '.';
	}
	if(inBounds(left2)){
		floor[left2.y][left2.x] = '.';
	}
	if(inBounds(right)){
		floor[right.y][right.x] = '.';
	}
	if(inBounds(right2)){
		floor[right2.y][right2.x] = '.';
	}
	if(inBounds(upl)){
		floor[upl.y][upl.x] = '.';
	}
	if(inBounds(upr)){
		floor[upr.y][upr.x] = '.';
	}
	if(inBounds(dl)){
		floor[dl.y][dl.x] = '.';
	}
	if(inBounds(dr)){
		floor[dr.y][dr.x] = '.';
	}
}

int Map::checkEnemy(vector<Enemy> e, Position newPos){
	for(int i = 0; i < e.size(); ++i){
		if(e[i].getPos().x == newPos.x && e[i].getPos().y == newPos.y){
			return i;
		}
	}
	return -1;
}