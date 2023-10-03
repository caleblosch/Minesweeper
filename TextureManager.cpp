//
// Created by caleb on 11/19/2022.
//

#include "TextureManager.h"

// "redeclare" the variable, so that this file knows that it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName) {
    string path = "images/";
    path += textureName + ".png";

    // textureName == space
    // path == images/space.png

    textures[textureName].loadFromFile(path);
}

sf::Texture &TextureManager::GetTexture(string textureName) {
    // if the texture DOESN'T exist...
    if (textures.find(textureName) == textures.end()) // we didn't find it if this returns true
        LoadTexture(textureName);
    // load it first? and then return it?

    return textures[textureName];
}

void TextureManager::LoadTexture(std::string textureName, int rectDimensions) {
    string path = "images/";
    path += textureName + ".png";

    textures[textureName].loadFromFile(path, sf::IntRect(21*rectDimensions,0,21,32));
}

sf::Texture &TextureManager::GetTexture(std::string textureName, int digitNeeded) {
    LoadTexture(textureName, digitNeeded);

    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear(); // gets rid of all our stored objects
}