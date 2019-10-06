#include "data.h"

using namespace std;


Vec2d& Vec2d::operator+=(const Vec2d &right){
	this->x += right.x;
	this->y += right.y;
	return *this;
}

Vec2d& Vec2d::operator-=(const Vec2d &right){
	this->x -= right.x;
	this->y -= right.y;
	return *this;
}

Vec2d operator+(Vec2d left, const Vec2d &right){
	left += right;
	return left;
}

Vec2d operator-(Vec2d left, const Vec2d &right){
	left -= right;
	return left;
}

ostream& operator<<(ostream &os, const Vec2d &v){
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}
/////////////////////////////////////////////////////////

//TODO dürfte memory leaken
bool Board::trySpawnNewTet(Tetro **t) const {
	Vec2d spawnPos = Vec2d(4, 4);
	
	if(*t ){
		delete *t;
	}
	
	Tetro *tet = new Tetro(rand() % 7 + 'a', spawnPos);
	*t = tet;
	
	Vec2d pos[4];
	(*t)->getPos(pos);
	return ! checkCollisions(*this, pos);
}


void Board::solidify(Tetro *t){
	Vec2d pos[4];
	t->getPos(pos);
	for(int i = 0; i < 4; i++){
		this->board[pos[i].x][pos[i].y] = t->getColor();
	}
}


Board::Board(){
	for(int i = 0; i < tXWidth; i++){
		for(int j = 0; j < tYHeight; j++){
			this->board[i][j] = tEMPTY;
		}
	}
}
///////////////////////////////////////////////////


Tetro::Tetro(char c, Vec2d pos): position(pos), color(c) {
	//Tetro t;
	//t.position = pos;
	rotation = 0;
	//t.color = c;
	
	switch(c){
		case OTetro:
			offsets[0][0] = Vec2d(-1, -1);
			offsets[0][1] = Vec2d(0, -1);
			offsets[0][2] = Vec2d(-1, 0);
			offsets[0][3] = Vec2d(0, 0);
			offsets[1][0] = Vec2d(-1, -1);
			offsets[1][1] = Vec2d(0, -1);
			offsets[1][2] = Vec2d(-1, 0);
			offsets[1][3] = Vec2d(0, 0);
			offsets[2][0] = Vec2d(-1, -1);
			offsets[2][1] = Vec2d(0, -1);
			offsets[2][2] = Vec2d(-1, 0);
			offsets[2][3] = Vec2d(0, 0);
			offsets[3][0] = Vec2d(-1, -1);
			offsets[3][1] = Vec2d(0, -1);
			offsets[3][2] = Vec2d(-1, 0);
			offsets[3][3] = Vec2d(0, 0);
			break;
		
		case TTetro:
			//  #
			// ###
			offsets[0][0] = Vec2d(1, 0);
			offsets[0][1] = Vec2d(0, 0); 
			offsets[0][2] = Vec2d(-1, 0);
			offsets[0][3] = Vec2d(0, -1);
			// #
			// ##
			// #
			offsets[1][0] = Vec2d(0, -1); 
			offsets[1][1] = Vec2d(0, 0); 
			offsets[1][2] = Vec2d(0, 1); 
			offsets[1][3] = Vec2d(1, 0);
			// ###
			//  #
			offsets[2][0] = Vec2d(-1, 0); 
			offsets[2][1] = Vec2d(0, 0); 
			offsets[2][2] = Vec2d(1, 0); 
			offsets[2][3] = Vec2d(0, 1);
			//  #
			// ##
			//  #
			offsets[3][0] = Vec2d(0, -1); 
			offsets[3][1] = Vec2d(0, 0); 
			offsets[3][2] = Vec2d(0, 1); 
			offsets[3][3] = Vec2d(-1, 0);
			break;
			
		case ITetro:
			offsets[0][0] = Vec2d(-2, -1); 
			offsets[0][1] = Vec2d(-1, -1); 
			offsets[0][2] = Vec2d(0, -1); 
			offsets[0][3] = Vec2d(1, -1);
			offsets[1][0] = Vec2d(0, -2); 
			offsets[1][1] = Vec2d(0, -1); 
			offsets[1][2] = Vec2d(0, 0); 
			offsets[1][3] = Vec2d(0, 1);
			offsets[2][0] = Vec2d(-2, 0); 
			offsets[2][1] = Vec2d(-1, 0); 
			offsets[2][2] = Vec2d(0, 0); 
			offsets[2][3] = Vec2d(1, 0);
			offsets[3][0] = Vec2d(-1, -2); 
			offsets[3][1] = Vec2d(-1, -1); 
			offsets[3][2] = Vec2d(-1, 0); 
			offsets[3][3] = Vec2d(-1, 1);
			break;
		
		case STetro:
			offsets[0][0] = Vec2d(-1, 0);
			offsets[0][1] = Vec2d(0, 0); 
			offsets[0][2] = Vec2d(0, -1); 
			offsets[0][3] = Vec2d(1, -1);
			offsets[1][0] = Vec2d(0, -1); 
			offsets[1][1] = Vec2d(0, 0); 
			offsets[1][2] = Vec2d(1, 0); 
			offsets[1][3] = Vec2d(1, 1);
			offsets[2][0] = Vec2d(0, 0);
			offsets[2][1] = Vec2d(1, 0); 
			offsets[2][2] = Vec2d(-1, 1); 
			offsets[2][3] = Vec2d(0, 1);
			offsets[3][0] = Vec2d(-1, -1); 
			offsets[3][1] = Vec2d(-1, 0); 
			offsets[3][2] = Vec2d(0, 0); 
			offsets[3][3] = Vec2d(0, 1);
			break;
		
		case ZTetro:
			offsets[0][0] = Vec2d(-1, -1); 
			offsets[0][1] = Vec2d(0, -1); 
			offsets[0][2] = Vec2d(0, 0); 
			offsets[0][3] = Vec2d(1, 0);
			offsets[1][0] = Vec2d(0, 0); 
			offsets[1][1] = Vec2d(0, 1); 
			offsets[1][2] = Vec2d(1, -1); 
			offsets[1][3] = Vec2d(1, 0);
			offsets[2][0] = Vec2d(-1, 0); 
			offsets[2][1] = Vec2d(0, 0); 
			offsets[2][2] = Vec2d(0, 1); 
			offsets[2][3] = Vec2d(1, 1);
			offsets[3][0] = Vec2d(-1, 0); 
			offsets[3][1] = Vec2d(-1, 1); 
			offsets[3][2] = Vec2d(0, -1); 
			offsets[3][3] = Vec2d(0, 0);
			break;
			
		case LTetro:
			offsets[0][0] = Vec2d(-1, 0);
			offsets[0][1] = Vec2d(0, 0); 
			offsets[0][2] = Vec2d(1, 0); 
			offsets[0][3] = Vec2d(1, -1);
			offsets[1][0] = Vec2d(0, -1); 
			offsets[1][1] = Vec2d(0, 0); 
			offsets[1][2] = Vec2d(0, 1); 
			offsets[1][3] = Vec2d(1, 1);
			offsets[2][0] = Vec2d(-1, 0); 
			offsets[2][1] = Vec2d(0, 0); 
			offsets[2][2] = Vec2d(1, 0); 
			offsets[2][3] = Vec2d(-1, 1);
			offsets[3][0] = Vec2d(-1, -1); 
			offsets[3][1] = Vec2d(0, -1); 
			offsets[3][2] = Vec2d(0, 0); 
			offsets[3][3] = Vec2d(0, 1);
			break;
		
		case JTetro://x, y
			offsets[0][0] = Vec2d(-1, -1); 
			offsets[0][1] = Vec2d(-1, 0); 
			offsets[0][2] = Vec2d(0, 0); 
			offsets[0][3] = Vec2d(1, 0);
			
			offsets[1][0] = Vec2d(0, -1); 
			offsets[1][1] = Vec2d(1, -1); 
			offsets[1][2] = Vec2d(0, 0); 
			offsets[1][3] = Vec2d(0, 1);
			
			offsets[2][0] = Vec2d(-1, 0); 
			offsets[2][1] = Vec2d(0, 0); 
			offsets[2][2] = Vec2d(1, 0); 
			offsets[2][3] = Vec2d(1, 1);
			
			offsets[3][0] = Vec2d(0, -1); 
			offsets[3][1] = Vec2d(0, 0); 
			offsets[3][2] = Vec2d(0, 1); 
			offsets[3][3] = Vec2d(-1, 1);
			break;
	}
	
	//return t;
}


void Tetro::getPos(Vec2d pos[4]) const{
	for(int i = 0; i < 4; i++){
		pos[i] = this->offsets[this->rotation][i] + this->position;
	}
}


void Tetro::getLTurn(Vec2d pos[4], const Tetro* t) const{
	for(int i = 0; i < 4; i++){
		pos[i] = t->offsets[(t->rotation + 3) % 4][i] + t->position;
	}
}

void Tetro::getRTurn(Vec2d pos[4], const Tetro* t) const{
	for(int i = 0; i < 4; i++){
		pos[i] = t->offsets[(t->rotation + 1) % 4][i] + t->position;
	}
}

void Tetro::getOneDown(Vec2d pos[4], const Tetro* t) const{
	t->getPos(pos);
	//cout <<"tcolor: " << t->getColor() <<endl;
	for(int i = 0; i < 4; i++){
	//	pos[i] = t->getOffsets()[t->rotation][i] + t->position;
		pos[i].y ++;
	//	cout << pos[i] << " getonedown" <<endl;
	}
}

void Tetro::getRight(Vec2d pos[4], const Tetro* t) const{
	t->getPos(pos);
	for(int i = 0; i < 4; i++){
	//	pos[i] = t->getOffsets()[t->rotation][i] + t->position;
		pos[i].x ++;
	}
}

void Tetro::getLeft(Vec2d pos[4], const Tetro* t) const{
	t->getPos(pos);
	for(int i = 0; i < 4; i++){
	//	pos[i] = t->getOffsets()[t->rotation][i] + t->position;
		pos[i].x --;
	}
}

bool checkCollisions(const Board &b, const Vec2d pos[4]){
	for(int i = 0; i < 4; i++){
		if(pos[i].x < 0 || pos[i].x >= tXWidth || pos[i].y < 0 || pos[i].y >= tYHeight){
			cout << "out of bounds" << endl;
			return true;
		}
		if(b.board[pos[i].x][pos[i].y] != tEMPTY){
			cout << "not free" << endl;
			return true;
		}
	}
	return false;
}

bool Tetro::tryLTurn(const Board &b, Tetro *t){
	Vec2d pos[4];
	getLTurn(pos, t);
	if(checkCollisions(b, pos)){
		return false;
	}
	t->rotation += 3;
	t->rotation %= 4;
	return true;
}

bool Tetro::tryRTurn(const Board &b, Tetro *t){
	Vec2d pos[4];
	getRTurn(pos, t);
	if(checkCollisions(b, pos)){
		return false;
	}
	t->rotation ++;
	t->rotation %= 4;
	return true;
}


bool Tetro::tryMoveDown(const Board &b, Tetro *t){
	Vec2d pos[4];
	getOneDown(pos, t);
	if(checkCollisions(b, pos)){
		return false;
	}
	t->position.y ++;
	return true;
}

bool Tetro::tryRMove(const Board &b, Tetro *t){
	Vec2d pos[4];
	getRight(pos, t);
	if(checkCollisions(b, pos)){
		return false;
	}
	t->position.x ++;
	return true;
}

bool Tetro::tryLMove(const Board &b, Tetro *t){
	Vec2d pos[4];
	getLeft(pos, t);
	if(checkCollisions(b, pos)){
		return false;
	}
	t->position.x --;
	return true;
}