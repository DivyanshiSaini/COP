#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TextureManager.h"
#include <random>
mt19937 random_mt;

using namespace std;
using namespace sf;

Board:: Board(int _columns, int _rows, int _mines){
    columns = _columns;
    rows = _rows;
    mines = _mines; 
    defeat = false;
    victory = false;
    debug = false;
    flagcount = mines;
    testCases = false;

    int width = _columns * 32; //columns
    int height = _rows * 32 + 1;  //rows
    setHappyFace("face_happy");
    setDebugButton("debug");
    setTest1("test_1");
    setTest2("test_2");
    setTest3("test_3");
   

    for (int i = 0; i < rows; i++) //rows
    {
        //createte a vector
        vector<Tile> tileRows;
        // cout << "loop1";
        for (int j = 0; j < columns; j++)  //columns
        {
            Tile newTile;
            newTile.SetbaseTile("tile_revealed");
            newTile.SettopTile("tile_hidden");
            newTile.GetbaseTile().setPosition(j * 32, i * 32);
            newTile.GettopTile().setPosition(j * 32, i * 32);
            tileRows.push_back(newTile);
        }
        grid.push_back(tileRows);
    }
    generateMine();
    setNeighbor();
}

void Board::create(RenderWindow& window) {

    int width, height;

    width = columns * 32; //columns
    height = (rows * 32) + 100;  //rows

    smilyFace.setPosition((width - (32 * 2)) / 2, (height - 100) + 1);
    // happyFace.setPosition((width - (32 * 2)) / 2, (height - 100) + 1);
    victoryWin();
    if (defeat) {
        setHappyFace("face_lose");
    }
    else if (victory) {
        setHappyFace("face_win");
        flagcount = 0;
        
    }
    window.draw(GetHappyFace());



    test3.setPosition(width - (32 * 2), (height - 100) + 1);
    window.draw(test3);


    test2.setPosition(width - (32 * 4), (height - 100) + 1);
    window.draw(test2);


    test1.setPosition(width - (32 * 6), (height - 100) + 1);
    window.draw(test1);


    debugButton.setPosition(width - (32 * 8), (height - 100) + 1);
    window.draw(debugButton);

  //  mineCounter.setPosition(0, (height - 100) + 1);
  //  window.draw(mineCounter);

    for (int i = 0; i < rows; i++) //rows
    {
        for (int j = 0; j < columns; j++)  //columns
        {          
            window.draw(grid[i][j].GetbaseTile());
            if (grid[i][j].GetMined() && defeat && grid[i][j].GetFlagged())
            {
                
                grid[i][j].SetbaseTile("tile_revealed"); //here changed

                Sprite flagCase(TextureManager::GetTexture("flag"));
                flagCase.setPosition(j * 32, i * 32);
                window.draw(flagCase);
                
                grid[i][j].SettopTile("mine");            

            } else if (grid[i][j].GetMined() && defeat )
            {
                
                grid[i][j].SettopTile("mine");
                grid[i][j].SetbaseTile("tile_revealed");
              
            }
            window.draw(grid[i][j].GettopTile());
            //bool if hidden or not
        }
    }

//counter
    int mineCount = flagcount; // returns mines 
    if (mineCount < 0) {
        // -012 -> -
        Sprite numberFour(TextureManager::GetTexture("digits"));
        int fourPlaces = 10;
        numberFour.setTextureRect(IntRect(fourPlaces * 21, 0, 21, 32));
        numberFour.setPosition(0, (height - 100) + 1);
        window.draw(numberFour);
        mineCount = (-1) * mineCount;
    }
    // 058 -> 8 //works
    Sprite numberOne(TextureManager::GetTexture("digits"));
    
    int onePlaces = mineCount % 10;
    numberOne.setTextureRect(IntRect(onePlaces * 21, 0, 21, 32));
    numberOne.setPosition(0 + 21 * 3, (height - 100) + 1);
    window.draw(numberOne);
    
    // 058 -> 5
    Sprite numberTwo(TextureManager::GetTexture("digits"));
    int twoPlaces;
        if (mineCount > 99) {
            twoPlaces = ((mineCount % 100) / 10);
        }
        else {
            twoPlaces = (mineCount) / 10;
        }
    // best way to calc this?

    numberTwo.setTextureRect(IntRect(twoPlaces * 21, 0, 21, 32));
    numberTwo.setPosition(0 + (21 * 2), (height - 100) + 1);
    window.draw(numberTwo);
    //058-> 0 
    Sprite numberThree(TextureManager::GetTexture("digits"));
    int threePlaces = (mineCount) / 100;
    numberThree.setTextureRect(IntRect(threePlaces * 21, 0, 21, 32));
    numberThree.setPosition(21, (height - 100) + 1);
    window.draw(numberThree);

 }

void Board::rightClickFlag(Vector2f mousePos) {
    if (!victory) {
        int x = mousePos.x / 32;
        int y = mousePos.y / 32;
        //int flagCount = GetFlagCount();
        for (int i = 0; i < rows; i++) //rows
        {
            for (int j = 0; j < columns; j++)  //columns
            {
                if (j == x && i == y && !defeat) {
                    //cout << i << "\n" << j;
                    if (!grid[i][j].GetTileRevealed()) {
                        grid[i][j].updateFlag();
                    }

                    //if statement 
                    // flag count never > mineCount
                    // flag cout never < 0
                    if (grid[i][j].GetFlagged()) {
                        flagcount--;
                    }
                    else if (!(grid[i][j].GetFlagged()))
                    {
                       /* if (flagcount + 1 > mines) {
                            flagcount = mines;
                        }
                        else {*/
                            flagcount++;
                        //}

                    }
                }
            }

        }
        //cout << endl << "flagcount" << flagcount << endl;
        // her non mined tile is revealed;
    }
}

void Board::leftClick(sf::Vector2f mousePos) {
    if(!victory){
    int x = mousePos.x / 32;
    int y = mousePos.y / 32;
    //clicking on tiles
    for (int i = 0; i < rows; i++) //rows
    {
        for (int j = 0; j < columns; j++)  //columns
        {
            if (((j == x && i == y) && !grid[i][j].GetFlagged()) && !defeat) {
                if (grid[i][j].GetMined())
                {
                    grid[i][j].SetTileRevealed(true, -1);
                    defeat = true;
                }
                else {
                    grid[i][j].revealTile(grid[i][j]);
                }
            }
        }

    }



    if (debugButton.getGlobalBounds().contains(mousePos)) {
        if (!debug) { debug = true; }
        else if (debug) { debug = false; }

        for (int i = 0; i < rows; i++) //rows
        {
            for (int j = 0; j < columns; j++)  //columns
            {
                if (debug) { // when button is clicked 
                    if (grid[i][j].GetMined()) // if a mine exsists 
                    {
                        
                        grid[i][j].SetbaseTile("tile_revealed");
                        grid[i][j].SettopTile("mine");
                    }
                }
                else {

                    if (grid[i][j].GetMined()) {
                        if (grid[i][j].GetFlagged()) {
                            grid[i][j].SetbaseTile("tile_hidden");
                            grid[i][j].SettopTile("flag");
                        }
                        else {
                            grid[i][j].SetbaseTile("tile_revealed");
                            grid[i][j].SettopTile("tile_hidden");
                        }

                    }
                }
            }
        }
    }
    }
    if (smilyFace.getGlobalBounds().contains(mousePos)) {
        restartBoard();
        flagcount = mines;
    }
    if (test1.getGlobalBounds().contains(mousePos)) {
        runTestCase(1);
    }
    if (test2.getGlobalBounds().contains(mousePos)) {
        runTestCase(2);
    }
    if (test3.getGlobalBounds().contains(mousePos)) {
        runTestCase(3);       
    }       
}

void Board::generateMine() {
    int mineCounter = 0;
   // int randomSeed = 0;
    random_mt.seed(time(NULL));
    //srand(time(NULL));
    while(mines > mineCounter) //rows
    { 
        uniform_int_distribution<int> mineRow(0, rows-1);
        int randomRow = mineRow(random_mt);

        uniform_int_distribution<int> mineColumns(0, columns-1);
        int randomColumns = mineColumns(random_mt);
        
        if (grid[randomRow][randomColumns].GetMined() == false) {
            grid[randomRow][randomColumns].SetMined(true);
            mineCounter++;
       }
    }

    /*cout << mineCounter << " is euqal to 50?" << endl;
    if (mineCounter == mines) {
        cout << "Yes! It is " << mines << endl;
    }*/
}

void Board::setNeighbor() {
    
    // 8 conditons 
    for (int i = 0; i < rows; i++) //rows
    {
        for (int j = 0; j < columns; j++)  //columns
        {
            /*    x  x  x  x  x //top row
            *     x  x  x  x  x
                  x  x  x  x  x
                  x  x  x  x  x // bottom row

    */       
            // top row
            // top left
            if (j == 0 && i == 0) { //3 neighbor                
                grid[i][j].pushNeighbor(&grid[i + 1][j]);  // below it 
                grid[i][j].pushNeighbor(&grid[i + 1][j + 1]); // diagnoal to it
                grid[i][j].pushNeighbor(&grid[i][j + 1]); // right of it
            }
           else if (j < (columns - 1) && i == 0) { // 5 neighbors 
                grid[i][j].pushNeighbor(&grid[i + 1][j]);  // below it 
                grid[i][j].pushNeighbor(&grid[i][j + 1]); // right of it
                grid[i][j].pushNeighbor(&grid[i][j - 1]);  // left of it 
                grid[i][j].pushNeighbor(&grid[i + 1][j + 1]); // right bottom diagnoal to it 
                grid[i][j].pushNeighbor(&grid[i + 1][j - 1]); // left bottom diagnoal to it 
           }
            
                // last  column
                // top right
               
           else if (i == 0 && j == columns - 1) {
                grid[i][j].pushNeighbor(&grid[i + 1][j]);  // below it 
                grid[i][j].pushNeighbor(&grid[i + 1][j - 1]); // left bottom diagnoal to it 
                grid[i][j].pushNeighbor(&grid[i][j - 1]); // left of it
           }
           else if (i < (rows - 1) && j == columns - 1) {
                    grid[i][j].pushNeighbor(&grid[i + 1][j]);  // below it 
                    grid[i][j].pushNeighbor(&grid[i - 1][j]);  // above it
                    grid[i][j].pushNeighbor(&grid[i + 1][j - 1]); // left bottom diagnoal to it 
                    grid[i][j].pushNeighbor(&grid[i - 1][j - 1]); // left top diagonal to it
                    grid[i][j].pushNeighbor(&grid[i][j - 1]); // left of it
           }
            
                // bottom row
                //bottom right
           else if (j == columns - 1 && i == rows - 1) {
                grid[i][j].pushNeighbor(&grid[i - 1][j]);  // above it
                grid[i][j].pushNeighbor(&grid[i - 1][j - 1]); // left top diagonal to it
                grid[i][j].pushNeighbor(&grid[i][j - 1]); // left of it
                    
           }
           else if (j > 0 && i == rows - 1) {
                grid[i][j].pushNeighbor(&grid[i - 1][j]);  // above it
                grid[i][j].pushNeighbor(&grid[i - 1][j - 1]); // left top diagonal to it
                grid[i][j].pushNeighbor(&grid[i][j - 1]); // left of it
                grid[i][j].pushNeighbor(&grid[i][j + 1]);  // right of it
                grid[i][j].pushNeighbor(&grid[i - 1][j + 1]); // right top diagonal to it

           }
                //first columns
                //bottom left
           else if (j == 0 && i == (rows - 1)) {
                grid[i][j].pushNeighbor(&grid[i - 1][j]);  // above it
                grid[i][j].pushNeighbor(&grid[i - 1][j + 1]); // right top diagonal to it
                grid[i][j].pushNeighbor(&grid[i][j + 1]); // right of it
                }
           else if (i > 0 && j == 0) {
                grid[i][j].pushNeighbor(&grid[i - 1][j]);  // above it
                grid[i][j].pushNeighbor(&grid[i - 1][j + 1]); // right top diagonal to it
                grid[i][j].pushNeighbor(&grid[i][j + 1]); // right of it
                grid[i][j].pushNeighbor(&grid[i + 1][j]);  // below it
                grid[i][j].pushNeighbor(&grid[i + 1][j + 1]); // righ bottom diagonal to it

           }           
                // rest with 8 neighbors 
           else {
                grid[i][j].pushNeighbor(&grid[i - 1][j]);  // above it
                grid[i][j].pushNeighbor(&grid[i + 1][j]);  // below it
                grid[i][j].pushNeighbor(&grid[i][j + 1]); // right of it
                grid[i][j].pushNeighbor(&grid[i][j - 1]); // left of it
                grid[i][j].pushNeighbor(&grid[i - 1][j + 1]); // right top diagonal to it
                grid[i][j].pushNeighbor(&grid[i + 1][j + 1]); // righ bottom diagonal to it
                grid[i][j].pushNeighbor(&grid[i - 1][j - 1]); // left top diagonal to it
                grid[i][j].pushNeighbor(&grid[i + 1][j - 1]); // left bottom diagnoal to it 
           }
                cout << grid[i][j].GetMineCount();
        }
    }
}

void Board::setHappyFace(string name) {
    smilyFace.setTexture(TextureManager::GetTexture(name));
}

void Board::setDebugButton(string name) {
    debugButton.setTexture(TextureManager::GetTexture(name));
}

void Board::setTest1(string name) {
    test1.setTexture(TextureManager::GetTexture(name));
}

void Board::setTest2(string name) {
    test2.setTexture(TextureManager::GetTexture(name));
}

void Board::setTest3(string name) {
    test3.setTexture(TextureManager::GetTexture(name));
}

Sprite& Board::GetHappyFace() {
    return smilyFace;
}

void Board::restartBoard() {
    defeat = false;
    victory = false;
    testCases = false;
    
    setHappyFace("face_happy");

    for (int i = 0; i < rows; i++) //rows
    {
        for (int j = 0; j < columns; j++)  //columns
        {
                grid[i][j].tileRestart();
        }

    }
    generateMine();
    setNeighbor();
}
void Board::loadBrdFile(const char* filename) {
    fstream inFile(filename);
   // vector <string> fileStore;
    testCase.clear();
    if (inFile.is_open()) {
        
        string value;
        //getline(inFile, value);
        while (getline(inFile, value)) {
            testCase.push_back(value);
        }
    }
    
}
void Board::restartBoard2() {
    defeat = false;
    victory = false;
    testCases = false;

    setHappyFace("face_happy");

    for (int i = 0; i < rows; i++) //rows
    {
        for (int j = 0; j < columns; j++)  //columns
        {
            grid[i][j].tileRestart();
        }

    }
}
void Board::runTestCase(int num){
    restartBoard2();
    int mineCount = 0;
    
    //char* name = fileName[0];
    if (num == 1) {
        loadBrdFile("boards/testboard1.brd");
    }
    else if (num == 2) {
        loadBrdFile("boards/testboard2.brd");
    }
    else if (num == 3) {
        loadBrdFile("boards/testboard3.brd");
    }
    for (int i = 0; i < rows; i++) //rows
    {
        //cout << testCase.begin();
        for (int j = 0; j < columns; j++)  //columns
        {

            if ((testCase[i])[j] == '1') {
                grid[i][j].SetMined(true);
                mineCount++;
            }
            else {
                grid[i][j].SetMined(false);
            }
        }

    }
    flagcount = mineCount;
    testCaseMineCount = mineCount;
    //mines = mineCount;
    // setMineCount(mineCount);
    // cout << mines;
    testCases = true;
   setNeighbor();
}
void Board::victoryWin() {
    int victoryCounter = 0;

    for (int i = 0; i < rows; i++) //rows
    {
        for (int j = 0; j < columns; j++)  //columns
        {
            if (!grid[i][j].GetMined() && grid[i][j].GetTileRevealed()) { // if a tile is not mined an revealed 
                victoryCounter++;
            }
        }

    }
    int calc = 0;
    
    if (testCases) {
    calc = ((rows * columns) - testCaseMineCount);
    }
    else {
    calc = ((rows * columns) - mines);
    }
    
     
    
   
    //cout << "calc" << "\n\n\n" << calc;
    if (victoryCounter == calc) {
        victory = true;
    }

    if (victory) {
        for (int i = 0; i < rows; i++) //rows
        {
            for (int j = 0; j < columns; j++)  //columns
            {
                if (grid[i][j].GetMined() && !grid[i][j].GetTileRevealed()) { // if a tile is not mined an revealed 
                    grid[i][j].SetbaseTile("tile_hidden");
                    grid[i][j].SettopTile("flag");
                }
            }

        }
    }

}

