#ifndef MINESWEEPER_TEXTUREMANAGER_H
#define MINESWEEPER_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

class TextureManager {
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Sprite> sprites;

public:
    TextureManager();

    void LoadTexture (const std::string & name, const std::string & filename);
    void SetTextures();
    sf::Texture& GetTextureReference (const std::string & texture);

    void LoadSprite (const std::string & spriteName);
    void SetSprites();
    sf::Sprite& GetSpriteReference (const std::string & sprite);
};

#endif
