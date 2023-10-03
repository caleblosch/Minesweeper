//
// Created by caleb on 11/19/2022.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager {
    // static == one and only one of these will be in memory, ever
    static unordered_map<string, sf::Texture> textures; //since it is static, don't need to make any instances of it
    static void LoadTexture(string textureName); // LoadTexture("space");
    static void LoadTexture(string textureName, int rectDimensions);
public:
    static sf::Texture& GetTexture(string textureName); // GetTexture("space");
    static sf::Texture& GetTexture(string textureName, int digitNeeded);
    static void Clear(); // Call this once, at the end of main() to empty the unordered_map
};