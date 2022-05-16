#ifndef MINESWEEPER_MSSFMLVIEW_H
#define MINESWEEPER_MSSFMLVIEW_H

#include "Minesweeper.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MSSFMLView : public sf::Drawable {
private:
    MinesweeperBoard & board;
    TextureManager & textureManager;

    // All dimensions are given in pixels.
    const double FIELD_TEXTURE_X_SIZE = 216;
    const double FIELD_TEXTURE_Y_SIZE = 216;
    const double INFO_TRAY_TEXTURE_X_SIZE = 386;
    const double INFO_TRAY_TEXTURE_Y_SIZE = 216;
    const double SPRITE_SCALE = 0.25;
    const double HUD_SPRITE_SCALE = 0.4;
    const double FIELD_SPRITE_X_SIZE =
            FIELD_TEXTURE_X_SIZE * SPRITE_SCALE;
    const double FIELD_SPRITE_Y_SIZE =
            FIELD_TEXTURE_Y_SIZE * SPRITE_SCALE;
    const double INFO_TRAY_SPRITE_X_SIZE =
            INFO_TRAY_TEXTURE_X_SIZE * HUD_SPRITE_SCALE;
    const double INFO_TRAY_SPRITE_Y_SIZE =
            INFO_TRAY_TEXTURE_Y_SIZE * HUD_SPRITE_SCALE;
    const double HUD_X_SIZE = screenWidth;
    const double HUD_Y_SIZE = 150;

    int fieldsInRow;
    int fieldsInColumn;

    double screenWidth;
    double screenHeight;

    sf::Font font_Comfortaa;

    sf::Clock clock;

    sf::Text flagCounter;
    sf::Text time;
    sf::Text gameStatusInfo;

    std::vector<std::vector<sf::Sprite>> boardFields;
    std::vector<sf::Sprite> HUDSprites;

public:
    MSSFMLView (MinesweeperBoard & boardToDisplay,
                TextureManager & textureManager);

    int GetFieldsInRowNumber() const;
    int GetFieldsInColumnNumber() const;
    double GetScreenWidth() const;
    double GetScreenHeight() const;
    double GetSpriteScale() const;
    double GetHUDSpriteScale() const;
    double GetFieldSpriteXSize() const;
    double GetFieldSpriteYSize() const;
    double GetInfoTraySpriteXSize() const;
    double GetInfoTraySpriteYSize() const;
    double GetHUDXSize() const;
    double GetHUDYSize() const;

    sf::Text FlagCounter() const;
    sf::Text Timer() const;

    void BoardFieldsSettings();

    void HUDSettings();

    void SetGameStatusInfo();

    void RevealMinesIfLost();

    void draw (sf::RenderTarget & target,
               sf::RenderStates states) const override;
};

#endif
