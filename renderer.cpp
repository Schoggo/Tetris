#include "renderer.h"

using namespace std;
namespace rend{



void initRender(const Board &b, Tetro *t, GraphicsState &gs){
	cout << &gs << " : " << sizeof(gs) <<endl;
	gs.wSize = Vec2d(tXWidth * gs.squareSize + tXWidth - 1, 
	tYHeight * gs.squareSize + tYHeight - 1);
	
	
	
	for(int i = 1; i < tXWidth; i++){
		gs.vLines[i - 1].x1 = i * gs.squareSize + i - 1;
		gs.vLines[i - 1].x2 = i * gs.squareSize + i - 1;
		gs.vLines[i - 1].y1 = 0;
		gs.vLines[i - 1].y2 = gs.wSize.y;
	}
	for(int i = 1; i < tYHeight; i++){
		gs.hLines[i - 1].y1 = i * gs.squareSize + i - 1;
		gs.hLines[i - 1].y2 = i * gs.squareSize + i - 1;
		gs.hLines[i - 1].x1 = 0;
		gs.hLines[i - 1].x2 = gs.wSize.x;
	}
	
	
	
	gs.disp = XOpenDisplay(NULL);
	if(!gs.disp){
		cout << "Error opening gs.display" << endl;
		exit(1);
	}
	
	gs.screen = DefaultScreen(gs.disp);
	
	
	gs.wind = XCreateSimpleWindow(gs.disp, RootWindow(gs.disp, gs.screen), 0, 100, gs.wSize.x,
		gs.wSize.y, 0, BlackPixel(gs.disp, gs.screen), BlackPixel(gs.disp, gs.screen));
		
	XStoreName(gs.disp, gs.wind, "My Little Tetris");
	
	#if 1
	
	gs.cmap = XCreateColormap(gs.disp, gs.wind,
	DefaultVisual(gs.disp, gs.screen), AllocNone);
	
	XParseColor(gs.disp, gs.cmap, "rgb:bb/bb/bb", &gs.lGrey);
	XParseColor(gs.disp, gs.cmap, "rgb:20/20/20", &gs.bGrey);
	XParseColor(gs.disp, gs.cmap, "rgb:ff/00/00", &gs.red);
	XParseColor(gs.disp, gs.cmap, "rgb:cc/cc/00", &gs.yellow);
	XParseColor(gs.disp, gs.cmap, "rgb:00/00/88", &gs.dblue);
	XParseColor(gs.disp, gs.cmap, "rgb:00/ff/00", &gs.green);
	XParseColor(gs.disp, gs.cmap, "rgb:ff/aa/00", &gs.orange);
	XParseColor(gs.disp, gs.cmap, "rgb:10/10/ff", &gs.lblue);
	XParseColor(gs.disp, gs.cmap, "rgb:cc/00/77", &gs.pink);
	
	XAllocColor(gs.disp, gs.cmap, &gs.bGrey);
	XAllocColor(gs.disp, gs.cmap, &gs.lGrey);
	XAllocColor(gs.disp, gs.cmap, &gs.red);
	XAllocColor(gs.disp, gs.cmap, &gs.yellow);
	XAllocColor(gs.disp, gs.cmap, &gs.dblue);
	XAllocColor(gs.disp, gs.cmap, &gs.green);
	XAllocColor(gs.disp, gs.cmap, &gs.orange);
	XAllocColor(gs.disp, gs.cmap, &gs.lblue);
	XAllocColor(gs.disp, gs.cmap, &gs.pink);
	
	gs.lValues.foreground = gs.lGrey.pixel;
	gs.lValues.line_width = 1;
	gs.lValues.line_style = LineSolid;
	gs.lineGC = XCreateGC(gs.disp, gs.wind, 
		GCForeground | GCLineWidth | GCLineStyle, &gs.lValues);
	
	gs.bgValues.foreground = gs.bGrey.pixel;
	gs.bgValues.fill_style = FillSolid;
	gs.bgGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.bgValues);
	gs.redValues.foreground = gs.red.pixel;
	gs.redValues.fill_style = FillSolid;
	gs.redGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.redValues);
	gs.yellowValues.foreground = gs.yellow.pixel;
	gs.yellowValues.fill_style = FillSolid;
	gs.yellowGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.yellowValues);
	gs.dblueValues.foreground = gs.dblue.pixel;
	gs.dblueValues.fill_style = FillSolid;
	gs.dblueGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.dblueValues);
	gs.greenValues.foreground = gs.green.pixel;
	gs.greenValues.fill_style = FillSolid;
	gs.greenGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.greenValues);
	gs.orangeValues.foreground = gs.orange.pixel;
	gs.orangeValues.fill_style = FillSolid;
	gs.orangeGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.orangeValues);
	gs.lblueValues.foreground = gs.lblue.pixel;
	gs.lblueValues.fill_style = FillSolid;
	gs.lblueGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.lblueValues);
	gs.pinkValues.foreground = gs.pink.pixel;
	gs.pinkValues.fill_style = FillSolid;
	gs.pinkGC = XCreateGC(gs.disp, gs.wind, GCForeground | GCFillStyle, &gs.pinkValues);
	
	
	XSetWindowBackground(gs.disp, gs.wind, gs.bGrey.pixel);
	
	#endif
	
	XSelectInput(gs.disp, gs.wind, ExposureMask |  KeyPressMask );
	
	
	
	
	XMapWindow(gs.disp, gs.wind);
	cout << "mapped window- " << gs.screen << ", " << endl;
	XFlush(gs.disp);
}


void renderTetro(Tetro *t, bool isNew, GraphicsState &gs){
	cout <<"rendering tetro\n";
	
	static Vec2d old[4] = {};
	//if this is the same tetro as last call, make its last position background again
	//if(!isNew){
		//cout <<"old\n";
		for(int i = 0; i < 4; i++){
			XFillRectangle(gs.disp, gs.wind, gs.bgGC, 
				old[i].x * (gs.squareSize + 1), old[i].y * (gs.squareSize + 1),
				gs.squareSize, gs.squareSize);
		}
	//}
	
	
	Vec2d pos[4] = {Vec2d(-1, -1), Vec2d(0, -1), Vec2d(-1, 0), Vec2d(0, 0)};
	//cout << "a\n";
	t->getPos(pos);
	//cout << "b\n";
	t->getPos(old);
	
	for(int i = 0; i < 4; i++){
		switch(t->getColor()){
			case tRED:
					XFillRectangle(gs.disp, gs.wind, gs.redGC, 
						//t->position.x * (gs.squareSize + 1), t->position.y * (gs.squareSize + 1), 
						pos[i].x * (gs.squareSize + 1), pos[i].y * (gs.squareSize + 1),
						gs.squareSize, gs.squareSize);
					break;
				case tYELLOW:
					XFillRectangle(gs.disp, gs.wind, gs.yellowGC, 
						//t->position.x * (gs.squareSize + 1), t->position.y * (gs.squareSize + 1), 
						pos[i].x * (gs.squareSize + 1), pos[i].y * (gs.squareSize + 1),
						gs.squareSize, gs.squareSize);
					break;
				case tDBLUE:
					XFillRectangle(gs.disp, gs.wind, gs.dblueGC, 
						//t->position.x * (gs.squareSize + 1), t->position.y * (gs.squareSize + 1), 
						pos[i].x * (gs.squareSize + 1), pos[i].y * (gs.squareSize + 1),
						gs.squareSize, gs.squareSize);
					break;
				case tGREEN:
					XFillRectangle(gs.disp, gs.wind, gs.greenGC, 
						//t->position.x * (gs.squareSize + 1), t->position.y * (gs.squareSize + 1), 
						pos[i].x * (gs.squareSize + 1), pos[i].y * (gs.squareSize + 1),
						gs.squareSize, gs.squareSize);
					break;
				case tORANGE:
					XFillRectangle(gs.disp, gs.wind, gs.orangeGC, 
						//t->position.x * (gs.squareSize + 1), t->position.y * (gs.squareSize + 1), 
						pos[i].x * (gs.squareSize + 1), pos[i].y * (gs.squareSize + 1),
						gs.squareSize, gs.squareSize);
					break;
				case tLBLUE:
					XFillRectangle(gs.disp, gs.wind, gs.lblueGC, 
						//t->position.x * (gs.squareSize + 1), t->position.y * (gs.squareSize + 1), 
						pos[i].x * (gs.squareSize + 1), pos[i].y * (gs.squareSize + 1),
						gs.squareSize, gs.squareSize);
					break;
				case tPINK:
					XFillRectangle(gs.disp, gs.wind, gs.pinkGC, 
						//t->position.x * (gs.squareSize + 1), t->position.y * (gs.squareSize + 1), 
						pos[i].x * (gs.squareSize + 1), pos[i].y * (gs.squareSize + 1),
						gs.squareSize, gs.squareSize);
					break;
		}
	}
	
	
	//cout << t.color <<endl;
}

//geht mit XNextEvent == Exposure
void renderBase(GraphicsState &gs){
	cout << "rendering bg" <<endl;
	//draw clean board
	XFillRectangle(gs.disp, gs.wind, gs.bgGC, 0, 0, (gs.squareSize + 1) * tXWidth, 
		(gs.squareSize + 1) * tYHeight);
	
	//draw grid
	XDrawSegments(gs.disp, gs.wind, gs.lineGC, gs.vLines, tXWidth -1 );
	XDrawSegments(gs.disp, gs.wind, gs.lineGC, gs.hLines, tYHeight -1 );
	XFlush(gs.disp);
}



void renderBoard(const Board &b, GraphicsState &gs){
	cout << "rendering board"<<endl;
	//draw squares on board
	for(int i = 0; i < tXWidth; i++){
		for(int j = 0; j < tYHeight; j++){
			switch(b.board[i][j]){
				case tRED:
					XFillRectangle(gs.disp, gs.wind, gs.redGC, 
						i * (gs.squareSize + 1), j * (gs.squareSize + 1), 
						gs.squareSize, gs.squareSize);
					break;
				case tYELLOW:
					XFillRectangle(gs.disp, gs.wind, gs.yellowGC, 
						i * (gs.squareSize + 1), j * (gs.squareSize + 1), 
						gs.squareSize, gs.squareSize);
					break;
				case tDBLUE:
					XFillRectangle(gs.disp, gs.wind, gs.dblueGC, 
						i * (gs.squareSize + 1), j * (gs.squareSize + 1), 
						gs.squareSize, gs.squareSize);
					break;
				case tGREEN:
					XFillRectangle(gs.disp, gs.wind, gs.greenGC, 
						i * (gs.squareSize + 1), j * (gs.squareSize + 1), 
						gs.squareSize, gs.squareSize);
					break;
				case tORANGE:
					XFillRectangle(gs.disp, gs.wind, gs.orangeGC, 
						i * (gs.squareSize + 1), j * (gs.squareSize + 1), 
						gs.squareSize, gs.squareSize);
					break;
				case tLBLUE:
					XFillRectangle(gs.disp, gs.wind, gs.lblueGC, 
						i * (gs.squareSize + 1), j * (gs.squareSize + 1), 
						gs.squareSize, gs.squareSize);
					break;
				case tPINK:
					XFillRectangle(gs.disp, gs.wind, gs.pinkGC, 
						i * (gs.squareSize + 1), j * (gs.squareSize + 1), 
						gs.squareSize, gs.squareSize);
					break;
				
			}
		}
	}
}


}//namespace