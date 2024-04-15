#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <unordered_map>
using namespace std;
using namespace sf;

class TextureManager
{
    
    // static == one and only of these in memory, ever
    static unordered_map<string,Texture> textures;
    static void LoadTexture(string textureName);// loadTexture("basetile")

public:    
    static Texture& GetTexture(string textureName);
    static void Clear(); // call this one at the end
};














/*TextureManager() {
       
        unordered_map<string,Texture> textures;
        textures["baseTile"].loadFromFile("images/tile_revealed.png");
        textures["topTile"].loadFromFile("images/tile_hidden.png");
        
        Sprite baseTileSprite(textures["baseTile"]);
        Sprite topTileSprite(textures["topTile"]);


        //new code 
        Sprite baseTileSprite(TextureManager::GetTexture["baseTile"]);
   }*/ 
