#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Tile.h"
#include "Board.h"
#include "TextureManager.h"
#include <unordered_map>
#include <vector>
using namespace std;
using namespace sf;

class fileVariable {
   public :
     int rows, columns, mines;
    void loadFile(const char* filename) {
        fstream inFile(filename);
        vector <string> fileStore;

        if (inFile.is_open()) {
            string value;
            //getline(inFile, value);
            while (getline(inFile, value)) {
                fileStore.push_back(value);
            }
        }
        columns = stoi(fileStore[0]);
        rows = stoi(fileStore[1]);
        mines = stoi(fileStore[2]);
   }
};


int main()
{
    //Render window step 1
    fileVariable load;
    load.loadFile("boards/config.cfg");

    int rows = load.rows, columns=load.columns, mines= load.mines;
    int width, height;
    int x, y;

    width = columns * 32; //columns
    height = (rows * 32) + 100;  //rows
    RenderWindow window(VideoMode(width, height), "MineSweeper works!");   
    Board board(columns, rows, mines);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                //check left or right 
                //getposition -> compare with tile position -> add a flag
                //left click -> mine loose ->1 is a numer(noneighbors) ->1 it is a blank tile(itself and all neighbors)
                // flag should never be revealed ulse right click 
                // already revealed shouldn't do anything

                    if (event.mouseButton.button == Mouse::Right)
                    {
                        Vector2f mousePos(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
                        x = event.mouseButton.x / 32;
                        y = event.mouseButton.y / 32;
                       // board.rightClickFlag(x,y);
                        board.rightClickFlag(mousePos);
                    } else if (event.mouseButton.button == Mouse::Left)
                    {
                        //cout << event.mouseButton.x / 32 << endl;
                       // cout << event.mouseButton.y / 32 << endl;
                        Vector2f mousePos( Mouse::getPosition(window).x,Mouse::getPosition(window).y);   
                       // x = event.mouseButton.x / 32;
                      //  y = event.mouseButton.y / 32;
                        board.leftClick(mousePos);
                    }  
                cout << "Button pressed" << endl;
            }
        }
        window.clear((Color::White));
        //create function 
        board.create(window);
        window.display();
    }
    return 0;
};

