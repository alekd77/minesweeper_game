#ifndef MINESWEEPER_MSSFMLRENDERING_H
#define MINESWEEPER_MSSFMLRENDERING_H

#include "SFML/Graphics.hpp"
#include "Minesweeper.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"

class MSSFMLRendering {
private:
    MinesweeperBoard & board;
    MSSFMLView & view;
    MSSFMLController & controller;

public:
    MSSFMLRendering (MinesweeperBoard & boardSFML,
                     MSSFMLView & viewSFML,
                     MSSFMLController & controllerSFML);

    void Menu();

    void Game();
    void Update();

    void Leaderboard();
};

#endif