
CXX = g++
CXXFLAGS = -Wall -std=c++17 
LDFLAGS = -lX11

tetris: tetris.o data.o renderer.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o tetris tetris.o data.o renderer.o

tetris.o: tetris.cpp data.h renderer.h
	$(CXX) $(CXXFLAGS) -c tetris.cpp

data.o: data.h data.cpp

renderer.o: renderer.h renderer.cpp
	$(CXX) $(CXXFLAGS) -c renderer.cpp 

clean:
	@echo removing object files 
	@rm *.o
	@rm tetris