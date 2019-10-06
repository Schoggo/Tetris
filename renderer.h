#ifndef tetrisrenderer
#define tetrisrenderer

#include <X11/Xlib.h>
#include <iostream>
#include "data.h"

namespace rend{
	
	struct GraphicsState{
		Display *disp;
		int screen;
		Window wind;
		XEvent event;
		const int squareSize = 40;

		Vec2d wSize;

		XGCValues lValues;
		GC lineGC;
		XGCValues bgValues;
		GC bgGC;

		XGCValues redValues;
		GC redGC;
		XGCValues yellowValues;
		GC yellowGC;
		XGCValues dblueValues;
		GC dblueGC;
		XGCValues greenValues;
		GC greenGC;
		XGCValues orangeValues;
		GC orangeGC;
		XGCValues lblueValues;
		GC lblueGC;
		XGCValues pinkValues;
		GC pinkGC;

		Colormap cmap;
		XColor lGrey, bGrey, red, yellow, dblue, green, orange, lblue, pink;

		XSegment vLines[tXWidth - 1] = {};
		XSegment hLines[tYHeight - 1] = {};
	};
	
	
	
	void initRender(const Board&, Tetro*, GraphicsState&);
	void renderBase(GraphicsState&);
	void renderBoard(const Board &, GraphicsState&);
	void renderTetro(Tetro*, bool, GraphicsState&);
} // namespace rend



#endif