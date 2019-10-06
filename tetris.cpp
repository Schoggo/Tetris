#include "data.h"
#include "renderer.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;


bool handleInput(Display *disp, Board &b, Tetro *t, const ControlScheme &ctrl){
	bool didSomething = 0;
	XEvent event;
	while(XCheckMaskEvent(disp, KeyPressMask, &event)){
		if(event.xkey.keycode == ctrl.mvD){
			while(t->tryMoveDown(b, t)){}
		}
		if(event.xkey.keycode == ctrl.mvL){
			t->tryLMove(b, t);
		}
		if(event.xkey.keycode == ctrl.mvR){
			t->tryRMove(b, t);
		}
		if(event.xkey.keycode == ctrl.tnL){
			t->tryLTurn(b, t);
		}
		if(event.xkey.keycode == ctrl.tnR){
			t->tryRTurn(b, t);
		}
		
		
		cout << "key pressed: " << event.xkey.keycode << endl;
		didSomething = 1;
	}
	return didSomething;
}

bool needBGRedraw(Display *disp){
	XEvent event;
	return XCheckMaskEvent(disp, ExposureMask, &event);
}


void clearLines(Board &b, int &score){
	int cleared = 0;
	bool full;
	bool foundOne = true;
	while(foundOne){
		foundOne = false;
		//go through all lines from bottom to top
		for(int i = tYHeight - 1; i >= 0; i--){
			full = 1;
			//check if line is full
			for(int j = 0; j < tXWidth; j++){
				if(b.board[j][i] == '_'){
					full = 0;
					break;
				}
			}
			//if line is full increment cleared lines
			if(full){
				cleared++;
				foundOne = 1;
				/*
				for(int j = 0; j < tXWidth; j++){
					b.board[j][i] = '_';
				}
				*/
				//go through all lines above the full line
				for(int j = i - 1; j >= 0; j--){
					//and push them one donw
					for(int k = 0; k < tXWidth; k++){
						//cout << b.board[k][j + 1] << " becomes " << b.board[k][j] <<endl;
						b.board[k][j + 1] = b.board[k][j];
						//b.board[k][j + 1] = '_';
					}
				}
			}
		}
	}
}



int main(){
	
	ControlScheme ctrlSch = ControlScheme(38, 40, 39, 24, 26);
	
	srand(time(NULL));
	
	Board board = Board();
	//board.board[1][1] = tRED;
	Tetro *currT = NULL;
	board.trySpawnNewTet(&currT);
	rend::GraphicsState gs = rend::GraphicsState();
	rend::initRender(board, currT, gs);
	rend::renderBase(gs);
		cout << "irender" <<endl;
	
	std::chrono::_V2::system_clock::time_point lastFall
		= chrono::high_resolution_clock::now();
	std::chrono::_V2::system_clock::time_point now;
	const std::chrono::seconds oneSec(1);
	const std::chrono::milliseconds shortInterval(150);
	
	bool shutdown = false;
	
	bool needBoardRender = true;
	bool needTetroRender = true;
	bool newTetro = false;
	
	int score = 0;
	
	while(!shutdown){
		//cout<<"inloop"<<endl;
		//if >= 1 second has passed, try moving the tetro down.
#if 1
		if((now = chrono::high_resolution_clock::now()) - lastFall >= oneSec){
			cout << "tick" <<endl;
			lastFall = now;
			needTetroRender = 1;
			//if it can't be moved down, try spawning a new one
#if 1
			if(!currT->tryMoveDown(board, currT)){
				cout <<"cant move down" <<endl;
				board.solidify(currT);
				needBoardRender = 1;
				newTetro = 1;
				clearLines(board, score);
				//if no new tetro can be spawned, the game ends
				if(!board.trySpawnNewTet(&currT)){
					cout <<"cant spawn new" <<endl;
					//game over
					shutdown = 1;
					break;
				}
			}
#endif
		}
#endif
		#if 1
		if(handleInput(gs.disp, board, currT, ctrlSch)){
			needTetroRender = 1;
		}
		#endif
		#if 1
		if(needBGRedraw(gs.disp)){
			rend::renderBase(gs);
			rend::renderTetro(currT, newTetro, gs);
			rend::renderBoard(board, gs);
			needTetroRender = 0;
			newTetro = false;
			needBoardRender = 0;
		}
		#endif
		#if 1
		if(needTetroRender){
			rend::renderTetro(currT, newTetro, gs);
			newTetro = false;
			needTetroRender = 0;
		}
		#endif
		#if 1
		if(needBoardRender){
			rend::renderBase(gs);
			rend::renderBoard(board, gs);
			needBoardRender = 0;
		}
		#endif
		
		//cout << currT->getColor() <<endl;
		//rend::render(board, currT);
		//chrono::milliseconds sl(50);
		//this_thread::sleep_for(sl);
	}
	
	cout << score << endl;
	chrono::seconds sl(10);
	this_thread::sleep_for(sl);
	
	
	//delete currT;
	return 0;
}