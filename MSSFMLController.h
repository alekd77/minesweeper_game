#ifndef MINESWEEPER_MSSFMLCONTROLLER_H
#define MINESWEEPER_MSSFMLCONTROLLER_H

#include "Minesweeper.h"
#include "MSSFMLView.h"
#include <SFML/Graphics.hpp>

class MSSFMLController : public sf::Drawable {
private:
    MinesweeperBoard & board;
    TextureManager & textureManager;
    MSSFMLView & view;

    int currentXMousePosition;
    int currentYMousePosition;

    int currentFieldRow;
    int currentFieldColumn;

    sf::Sprite highlightedField;

public:
    MSSFMLController (MinesweeperBoard & boardSFML,
                      TextureManager & textureManager,
                      MSSFMLView & viewSFML);

    void SetCurrentMousePositions (sf::Event::MouseMoveEvent & mousePosition);
    int GetCurrentMouseXPosition() const;
    int GetCurrentMouseYPosition() const;

    void SetCurrentFieldPositions();
    int GetCurrentFieldRow() const;
    int GetCurrentFieldColumn() const;

    void HighlightField();
    void draw (sf::RenderTarget & target,
               sf::RenderStates states) const override;

    void HandlingEvents (sf::Event & event);
};

#endif