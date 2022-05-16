#include "MSSFMLView.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>

MSSFMLView::MSSFMLView (MinesweeperBoard & boardToDisplay, TextureManager & texMgr)
                        : board(boardToDisplay), textureManager(texMgr) {

    this->fieldsInRow = board.GetBoardWidth();
    this->fieldsInColumn = board.GetBoardHeight();
    this->screenWidth = GetFieldsInRowNumber() * GetFieldSpriteXSize();
    this->screenHeight = GetFieldsInColumnNumber() * GetFieldSpriteYSize()
                       + GetHUDYSize();


    if (!font_Comfortaa.loadFromFile ("../fonts/comfortaa/"
                                      "Comfortaa-Bold.ttf"))
        std::cerr << strerror(errno) << std::endl;

    BoardFieldsSettings();
    HUDSettings();
}


int MSSFMLView::GetFieldsInRowNumber() const {
    return fieldsInRow;
}

int MSSFMLView::GetFieldsInColumnNumber() const {
    return fieldsInColumn;
}

double MSSFMLView::GetScreenWidth() const {
    return screenWidth;
}

double MSSFMLView::GetScreenHeight() const {
    return screenHeight;
}

double MSSFMLView::GetSpriteScale() const {
    return SPRITE_SCALE;
}

double MSSFMLView::GetHUDSpriteScale() const {
    return HUD_SPRITE_SCALE;
}

double MSSFMLView::GetFieldSpriteXSize() const {
    return FIELD_SPRITE_X_SIZE;
}
double MSSFMLView::GetFieldSpriteYSize() const {
    return FIELD_SPRITE_Y_SIZE;
}

double MSSFMLView::GetInfoTraySpriteXSize() const {
    return INFO_TRAY_SPRITE_X_SIZE;
}

double MSSFMLView::GetInfoTraySpriteYSize() const {
    return INFO_TRAY_SPRITE_Y_SIZE;
}

double MSSFMLView::GetHUDXSize() const {
    return HUD_X_SIZE;
}

double MSSFMLView::GetHUDYSize() const {
    return HUD_Y_SIZE;
}

sf::Text MSSFMLView::FlagCounter() const {
    return flagCounter;
}

sf::Text MSSFMLView::Timer() const {
    return time;
}


void MSSFMLView::BoardFieldsSettings() {

    std::vector<std::vector<sf::Sprite>> tempMain;
    std::vector<sf::Sprite> tempRow;

    for (int rowIdx = 0; rowIdx < GetFieldsInColumnNumber(); ++rowIdx)
    {
        tempRow.clear();

        for (int columnIdx = 0; columnIdx < GetFieldsInRowNumber(); ++columnIdx)
        {
            sf::Sprite currentField;

            if (board.GetFieldInfo(rowIdx, columnIdx) == '_')
                currentField = this->textureManager.
                        GetSpriteReference("unrevealedField");

            if (board.GetFieldInfo(rowIdx, columnIdx) == 'F')
                currentField = this->textureManager.
                        GetSpriteReference("flaggedField");

            if (board.GetFieldInfo(rowIdx, columnIdx) == 'x')
                currentField = this->textureManager.
                        GetSpriteReference("minedField");

            if (board.GetFieldInfo(rowIdx, columnIdx) == ' ')
                currentField = this->textureManager.
                        GetSpriteReference("blankField");

            if (board.GetFieldInfo(rowIdx, columnIdx) >= '1' and
                board.GetFieldInfo(rowIdx, columnIdx) <= '8')
            {
                std::string str;
                str += board.GetFieldInfo(rowIdx, columnIdx);

                if (str == "1")
                    str += "MineAround";
                else
                    str += "MinesAround";

                currentField = this->textureManager.
                        GetSpriteReference(str);
            }

            currentField.setScale (GetSpriteScale(), GetSpriteScale());
            currentField.setPosition (columnIdx * GetFieldSpriteXSize(),
                                      rowIdx * GetFieldSpriteYSize() + GetHUDYSize());

            tempRow.push_back(currentField);
        }
        tempMain.push_back(tempRow);
    }

    this->boardFields = tempMain;
}


void MSSFMLView::HUDSettings() {

    sf::Sprite clockTraySprite;
    sf::Sprite clockSprite;
    sf::Sprite flagTraySprite;
    sf::Sprite flagSprite;

    clockTraySprite.setTexture(textureManager.
                GetTextureReference("infoTray"));
    clockTraySprite.setScale(GetHUDSpriteScale(),
                             GetHUDSpriteScale());
    clockTraySprite.setPosition(25, 25);
    HUDSprites.push_back(clockTraySprite);

    clockSprite.setTexture(textureManager.
                GetTextureReference("clock"));
    clockSprite.setScale(GetSpriteScale(),
                         GetSpriteScale());
    clockSprite.setPosition(40, 40);
    HUDSprites.push_back(clockSprite);

    flagTraySprite.setTexture(textureManager.
                GetTextureReference("infoTray"));
    flagTraySprite.setScale(GetHUDSpriteScale(),
                            GetHUDSpriteScale());
    flagTraySprite.setPosition(GetScreenWidth() - 25
                                - GetInfoTraySpriteXSize(), 25);
    HUDSprites.push_back(flagTraySprite);

    flagSprite.setTexture(textureManager.
                GetTextureReference("flaggedField"));
    flagSprite.setScale(GetSpriteScale(),
                        GetSpriteScale());
    flagSprite.setPosition(GetScreenWidth() - 10
                        - GetInfoTraySpriteXSize(), 40);
    HUDSprites.push_back(flagSprite);
}


void MSSFMLView::SetGameStatusInfo() {

    sf::Text timer;
    std::stringstream ss;
    ss << std::ceil(clock.getElapsedTime().asSeconds());
    timer.setString(ss.str());
    timer.setFont(font_Comfortaa);
    timer.setFillColor(sf::Color::Blue);
    timer.setScale(1.2, 1.2);
    timer.setPosition(115, 45);

    if (board.GetCurrentPlayerActions() == 0)
    {
        timer.setString("0");
        this->time = timer;
        clock.restart();
    }
    else
    {
        if (board.GetGameState() == RUNNING)
            this->time = timer;
    }

    sf::Text flagCount;
    std::stringstream ss2;
    ss2 << board.GetFlagNumber();
    flagCount.setString(ss2.str());
    flagCount.setFont(font_Comfortaa);
    flagCount.setFillColor(sf::Color::Blue);
    flagCount.setScale(1.2, 1.2);
    flagCount.setPosition(GetScreenWidth() - 90, 45);
    this->flagCounter = flagCount;


    if (board.GetGameState() == RUNNING)
        return;

    sf::Text status;
    status.setFont(font_Comfortaa);
    status.setFillColor(sf::Color::White);
    status.setPosition(195, 50);

    if (board.GetGameState() == FINISHED_LOSS)
    {
        status.setString("You lost!");
        this->gameStatusInfo = status;
        return;
    }

    status.setString("You won!");
    this->gameStatusInfo = status;
}


void MSSFMLView::RevealMinesIfLost() {

    std::vector<std::pair<int, int>> minedFieldPositions;
    std::pair<int, int> tempFieldPositions;

    for (int rowIdx = 0; rowIdx < board.GetBoardHeight(); ++rowIdx)
    {
        for (int columnIdx = 0; columnIdx < board.GetBoardWidth(); ++columnIdx)
        {
            if (board.HasMine(rowIdx, columnIdx))
            {
                tempFieldPositions.first = rowIdx;
                tempFieldPositions.second = columnIdx;
            }

            minedFieldPositions.push_back(tempFieldPositions);
        }

    }


    while (!minedFieldPositions.empty())
    {
        int fieldIdx = rand() % minedFieldPositions.size();

        board.RevealMinedField(minedFieldPositions[fieldIdx].first,
                               minedFieldPositions[fieldIdx].second);

        minedFieldPositions.erase(minedFieldPositions.begin() + fieldIdx);
    }
}


void MSSFMLView::draw (sf::RenderTarget & target, sf::RenderStates states) const {

    for (int columnIdx = 0; columnIdx < GetFieldsInRowNumber(); ++columnIdx)
    {
        for (int rowIdx = 0; rowIdx < GetFieldsInColumnNumber(); ++rowIdx)
        {
            target.draw(boardFields[rowIdx][columnIdx], states);
        }
    }

    for (const auto & HUDSprite : HUDSprites)
    {
        target.draw(HUDSprite);
    }

    target.draw(time, states);
    target.draw(flagCounter, states);
    target.draw(gameStatusInfo, states);
}
