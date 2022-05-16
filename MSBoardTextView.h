#ifndef MINESWEEPER_MSBOARDTEXTVIEW_H
#define MINESWEEPER_MSBOARDTEXTVIEW_H

#include "Minesweeper.h"

class MSBoardTextView {
private:
    MinesweeperBoard & board;

public:
    explicit MSBoardTextView (MinesweeperBoard & boardToDisplay);

    void Display() const;
};


#endif