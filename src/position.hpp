#ifndef POSITION__HPP
#define POSITION__HPP

class Position{
	public:
		Position(){x = 0; y = 0;}
		Position(int b, int a){x = b; y = a;}
		Position operator/(int rhs){
		Position rv = Position(x,y);
			rv.x /= rhs;
			rv.y /= rhs;
			return rv;
		}

		Position operator+(const Position& rhs){
			Position rv = Position(x,y);
			rv.x += rhs.x;
			rv.y += rhs.y;
			return rv;
		}

		Position operator-(const Position& rhs){
			Position rv = Position(x,y);
			rv.x -= rhs.x;
			rv.y -= rhs.y;
			return rv;
		}

		bool operator==(const Position& rhs){
			return(this->x == rhs.x && this->y == rhs.y);
		}
		int x;
		int y;
};

#endif