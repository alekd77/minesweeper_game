#include "TextureManager.h"
#include <iostream>
#include <cstring>

TextureManager::TextureManager() {

    SetTextures();
    SetSprites();
}

void TextureManager::LoadTexture (const std::string & name,
                                  const std::string & filename) {

    sf::Texture textureToLoad;

    if (!textureToLoad.loadFromFile(filename))
        std::cerr << strerror(errno) << std::endl;

    this->textures[name] = textureToLoad;
}

void TextureManager::SetTextures() {

    std::string filePath = "../textures/";

    LoadTexture("infoTray", filePath + "MINESWEEPER_tray.png");
    LoadTexture("clock", filePath + "MINESWEEPER_C.png");
    LoadTexture("unrevealedField", filePath + "MINESWEEPER_X.png");
    LoadTexture("blankField", filePath + "MINESWEEPER_0.png");
    LoadTexture("minedField", filePath + "MINESWEEPER_M.png");
    LoadTexture("flaggedField", filePath + "MINESWEEPER_F.png");
    LoadTexture("1MineAround", filePath + "MINESWEEPER_1.png");
    LoadTexture("2MinesAround", filePath + "MINESWEEPER_2.png");
    LoadTexture("3MinesAround", filePath + "MINESWEEPER_3.png");
    LoadTexture("4MinesAround", filePath + "MINESWEEPER_4.png");
    LoadTexture("5MinesAround", filePath + "MINESWEEPER_5.png");
    LoadTexture("6MinesAround", filePath + "MINESWEEPER_6.png");
    LoadTexture("7MinesAround", filePath + "MINESWEEPER_7.png");
    LoadTexture("8MinesAround", filePath + "MINESWEEPER_8.png");
}

sf::Texture & TextureManager::GetTextureReference (
        const std::string & textureName) {

    return this->textures.at(textureName);
}



void TextureManager::LoadSprite (const std::string & spriteName) {

    sf::Sprite sprite;

    sprite.setTexture(textures[spriteName]);

    this->sprites[spriteName] = sprite;
}

void TextureManager::SetSprites() {

    LoadSprite("infoTray");
    LoadSprite("clock");
    LoadSprite("unrevealedField");
    LoadSprite("blankField");
    LoadSprite("minedField");
    LoadSprite("flaggedField");
    LoadSprite("1MineAround");
    LoadSprite("2MinesAround");
    LoadSprite("3MinesAround");
    LoadSprite("4MinesAround");
    LoadSprite("5MinesAround");
    LoadSprite("6MinesAround");
    LoadSprite("7MinesAround");
    LoadSprite("8MinesAround");
}

sf::Sprite& TextureManager::GetSpriteReference (
        const std::string & spriteName) {

    return this->sprites.at(spriteName);
}