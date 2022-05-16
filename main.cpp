#include "Minesweeper.h"
#include "TextureManager.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"
#include "MSSFMLRendering.h"

#include <iostream>
#include <ctime>

int main() {
    srand(time(NULL));

    MinesweeperBoard board(10, 10, EASY);
    TextureManager textureManager;
    MSSFMLView view (board, textureManager);
    MSSFMLController controller (board, textureManager, view);
    MSSFMLRendering rendering (board, view, controller);

    rendering.Game();
}