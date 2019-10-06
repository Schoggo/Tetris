#ifndef tetrisdata
#define tetrisdata

#include <iostream>
#include <X11/keysymdef.h>

#define tEMPTY '_'
#define tRED 'a'
#define tYELLOW 'b'
#define tDBLUE 'c'
#define tGREEN 'd'
#define tORANGE 'e'
#define tLBLUE 'f'
#define tPINK 'g'
#define tXWidth 10
#define tYHeight 20


#include <ostream>

enum Forms{TTetro = tPINK, OTetro = tYELLOW, ITetro = tLBLUE, JTetro = tDBLUE, 
	LTetro = tORANGE, STetro = tGREEN, ZTetro = tRED};

class Tetro;

class Vec2d{
	public:
		int x;
		int y;
		
		Vec2d() {};
		Vec2d(int a, int b) : x(a), y(b) {};
		Vec2d(const Vec2d &param) : x(param.x), y(param.y){};
		Vec2d& operator -=(const Vec2d&);
		Vec2d& operator +=(const Vec2d&);
		friend std::ostream& operator<<(std::ostream&, const Vec2d&);
};
Vec2d operator+(Vec2d l, const Vec2d &r);
Vec2d operator-(Vec2d l, const Vec2d &r);


class Board{
	public:
		char board[tXWidth][tYHeight];
		//bool success
		bool trySpawnNewTet(Tetro**) const;
		void solidify(Tetro*);
		
		Board();
};


class Tetro{
	public:
		Vec2d position;
		 Vec2d offsets[4][4];
		int rotation;
		 char color;
		
	public:
		//bool success
		bool tryRTurn(const Board&, Tetro*);
		bool tryLTurn(const Board&, Tetro*);
		bool tryMoveDown(const Board&, Tetro*);
		bool tryRMove(const Board&, Tetro*);
		bool tryLMove(const Board&, Tetro*);
		
		Tetro(char, Vec2d);
		
		char getColor() const {return this->color;}
		
				
		//Vec2d** getOffsets() const {return (Vec2d**)this->offsets;}
		
		void getRTurn(Vec2d pos[4], const Tetro*) const;
		void getLTurn(Vec2d pos[4], const Tetro*) const;
		void getPos(Vec2d pos[4]) const;
		void getOneDown(Vec2d pos[4], const Tetro*) const;
		void getRight(Vec2d pos[4], const Tetro*) const;
		void getLeft(Vec2d pos[4], const Tetro*) const;
};

//true == collision occured
bool checkCollisions(const Board &b, const Vec2d pos[4]);


struct ControlScheme{
	public:
	
		unsigned int mvL;
		unsigned int mvR;
		unsigned int mvD;
		unsigned int tnL;
		unsigned int tnR;
		
		ControlScheme(unsigned int moveLeft, unsigned int moveRight, 
			unsigned int moveDown, unsigned int turnLeft, unsigned int turnRight):
			mvL(moveLeft), mvR(moveRight), mvD(moveDown), tnL(turnLeft), 
			tnR(turnRight) {}
};

#endif