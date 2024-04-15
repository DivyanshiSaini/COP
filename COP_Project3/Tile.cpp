#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TextureManager.h"
using namespace std;
using namespace sf;

void Tile::SetbaseTile(string name) {
    baseTile.setTexture(TextureManager::GetTexture(name));
}

Sprite& Tile::GetbaseTile() {
    return baseTile;
}


void Tile::SettopTile(string name) {
    topTile.setTexture(TextureManager::GetTexture(name));
}
void Tile::SetMined(bool mine) {
    isMined = mine;
}


Sprite& Tile::GettopTile() {
    return topTile;
}

bool Tile::GetFlagged() {
    return isFlagged;
}
bool Tile::GetMined() {
    return isMined;
}


void Tile::updateFlag() {
    if (isFlagged) {
        isFlagged = false ;
        cout << "flag flase";
        SetbaseTile("tile_revealed");
        SettopTile("tile_hidden");

    }
    else if (!isFlagged) {
        isFlagged = true;
        cout << "flag true" << endl;
        SetbaseTile("tile_hidden");
        SettopTile("flag");
    }
}


void Tile::pushNeighbor(Tile* newNeighbor) {
    neighbor.push_back(newNeighbor);
    if (newNeighbor->isMined) {
         mineCount++;
    }
    
   
}


int Tile::GetMineCount() {
    return mineCount;
}

bool Tile::GetTileRevealed() {
    return isTileRevealed;
}

void Tile::SetTileRevealed(bool revealTile, int mineNumber) {
    isTileRevealed = revealTile;
    if (mineNumber == 0) {
        SettopTile("tile_revealed");
    }
    else if (mineNumber == 1) {
        SettopTile("number_1");
    }
    else if (mineNumber == 2) {
        SettopTile("number_2");
    }
    else if (mineNumber == 3) {
        SettopTile("number_3");
    }
    else if (mineNumber == 4) {
        SettopTile("number_4");
    }
    else if (mineNumber == 5) {
        SettopTile("number_5");
    }
    else if (mineNumber == 6) {
        SettopTile("number_6");
    }
    else if (mineNumber == 7) {
        SettopTile("number_7");
    }
    else if (mineNumber == 8) {
        SettopTile("number_8");
    }
    else if (mineNumber == -1) {
        SettopTile("mine");
        SetbaseTile("tile_revealed");
    }
}

void Tile::revealTile(Tile &tile) {
    if (tile.GetTileRevealed() != true) {
        if ((tile.GetFlagged() != true) && (tile.GetMined() != true)) {
            if (tile.mineCount == 0) {
                tile.SetTileRevealed(true, tile.GetMineCount());
                for (int i = 0; i < tile.neighbor.size(); i++) {
                    revealTile(*tile.neighbor[i]);
                }
            }
            else {
                tile.SetTileRevealed(true, tile.GetMineCount());
            }
        }
    }
}

void Tile::tileRestart() {
    isTileRevealed = false;
    isFlagged = false;
    isMined = false;
    mineCount = 0;

    SettopTile("tile_hidden");
    neighbor.clear();
}












