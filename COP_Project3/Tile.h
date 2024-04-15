#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;
using namespace sf;



class Tile {
   // RenderWindow* window;
    Sprite baseTile; //revealed 
    Sprite topTile; //hidden
    bool isFlagged;
    bool isMined;
    bool isTileRevealed;
    vector <Tile*> neighbor;
    int mineCount;

public:
    Tile() {
        isTileRevealed = false;
        isFlagged = false;
        isMined = false;
        mineCount = 0;
    }
    void SetbaseTile(string name);
    Sprite& GetbaseTile();
    void SettopTile(string name);
    Sprite& GettopTile();
    
   
    bool GetFlagged();
    void updateFlag();
    void falseFlag() { isFlagged == false; }
    
    void SetMined(bool mine);
    bool GetMined();

    void pushNeighbor(Tile* newNeighbor);
    int GetMineCount();
    
    bool GetTileRevealed();
    void SetTileRevealed(bool revealTile, int mineNumber);

    void revealTile(Tile &tile);
    
    void tileRestart();

    vector<Tile*> GetNeighbor() { return neighbor; }

};














































/*

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Blue);

    sf::CircleShape shape2(30.f);
    shape2.setFillColor(sf::Color::Red);

    shape2.setPosition(200, 300);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // main function
        // 3 functions 
             // tile - bomb - empty 
             // main function - intialize code, flag 
            // controller 
        // 5 
          // main, header tile, texture for loadign

        // clear anything already drawn
        window.clear();
        //2. Draw the results of everything that was drawn

        window.draw(shape);
        for (int i = 0; i < 10; i++)
        {
            shape2.setPosition(100 * i, 50 * i);
            shape2.setRadius(10 * i);
            window.draw(shape2);
        }
        window.draw(shape2);
        //3. Present the result of everything that was drawn

        window.display();
    }
    // draw board  -> tile class -> store in 2D vectors -> game tile lot of fuctions 
    //   bg, hidden, flag, sprite 
    // implement button 
    // try right click first -> flag 
    // left click later - harder 
        // check neighbor 


    return 0;
}*/