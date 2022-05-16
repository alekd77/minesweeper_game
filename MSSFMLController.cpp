#include "MSSFMLController.h"

MSSFMLController::MSSFMLController (MinesweeperBoard & boardSFML, TextureManager & texMgr,
                                    MSSFMLView & viewSFML) : board(boardSFML),
                                    textureManager(texMgr), view(viewSFML) {}

void MSSFMLController::SetCurrentMousePositions (
        sf::Event::MouseMoveEvent & mousePosition) {

    this->currentXMousePosition = mousePosition.x;
    this->currentYMousePosition = mousePosition.y;
}

int MSSFMLController::GetCurrentMouseXPosition() const {
    return currentXMousePosition;
}

int MSSFMLController::GetCurrentMouseYPosition() const {
    return currentYMousePosition;
}

void MSSFMLController::SetCurrentFieldPositions() {

    if (GetCurrentMouseYPosition() - view.GetHUDYSize() < 0)
        this->currentFieldRow = -1;

    this->currentFieldRow = (GetCurrentMouseYPosition() - view.GetHUDYSize())
                            / view.GetFieldSpriteYSize();
    this->currentFieldColumn = GetCurrentMouseXPosition()
                            / view.GetFieldSpriteXSize();
}

int MSSFMLController::GetCurrentFieldRow() const {
    return currentFieldRow;
}

int MSSFMLController::GetCurrentFieldColumn() const {
    return currentFieldColumn;
}


void MSSFMLController::HighlightField() {

    if (GetCurrentFieldRow() < 0 or
        GetCurrentFieldRow() > board.GetBoardHeight())
        return;

    if (GetCurrentFieldColumn() < 0 or
        GetCurrentFieldColumn() > board.GetBoardWidth())
        return;

    sf::Sprite field;

    field = this->textureManager.
            GetSpriteReference("blankField");
    field.setScale (view.GetSpriteScale(), view.GetSpriteScale());
    field.setPosition (GetCurrentFieldColumn() * view.GetFieldSpriteXSize(),
                       GetCurrentFieldRow() * view.GetFieldSpriteYSize()
                       + view.GetHUDYSize());
    field.setColor(sf::Color(255, 255, 255, 128));

    this->highlightedField = field;
}

void MSSFMLController::draw (sf::RenderTarget & target,
                             sf::RenderStates states) const {

    target.draw(this->highlightedField, states);
}


void MSSFMLController::HandlingEvents (sf::Event & event) {

    if (event.type == sf::Event::MouseMoved)
    {
        SetCurrentMousePositions(event.mouseMove);
        SetCurrentFieldPositions();
        HighlightField();
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (GetCurrentMouseYPosition() - view.GetHUDYSize() < 0)
            return;

        if (event.mouseButton.button == sf::Mouse::Left)
            board.RevealField(GetCurrentFieldRow(),
                              GetCurrentFieldColumn());
        else
        {
            if (!board.HasFlag(GetCurrentFieldRow(), GetCurrentFieldColumn()))
                board.ToggleFlag(GetCurrentFieldRow(),
                                 GetCurrentFieldColumn());
            else
                board.UntoggleFlag(GetCurrentFieldRow(),
                                   GetCurrentFieldColumn());
        }
    }
}