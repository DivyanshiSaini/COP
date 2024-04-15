#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include <vector>
using namespace std;
using namespace sf;


class Board
{
	int columns, rows, mines;
	bool victory, defeat, debug, testCases;
	vector<vector<Tile>> grid; 
	int flagcount, testCaseMineCount;

	
public:
	Sprite smilyFace, debugButton, test1, test2, test3;


    Board(int _columns, int _rows, int _mines);
	
	void create(RenderWindow &window);
	
	void rightClickFlag(Vector2f mousePos);
	void leftClick(Vector2f mousePos);
	void generateMine();

	void setBoardValue(int x, int y);
	void setNeighbor();
	
	void setHappyFace(string name);
	void setDebugButton(string name);
	void setTest1(string name);
	void setTest2(string name);
	void setTest3(string name);

	Sprite& GetHappyFace();
	void restartBoard();
	
	vector<String> testCase;
	void loadBrdFile(const char* filename);
	
	void restartBoard2();
	void runTestCase(int num);

	void printCounter();

	void victoryWin();
};




















