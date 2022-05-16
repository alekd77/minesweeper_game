#ifndef MINESWEEPER_MSTEXTCONTROLLER_H
#define MINESWEEPER_MSTEXTCONTROLLER_H

#include "Minesweeper.h"
#include "MSBoardTextView.h"

class MSTextController {
private:
    MinesweeperBoard & board;
    MSBoardTextView & textView;

public:
    MSTextController (MinesweeperBoard & boardToDisplay,
                      MSBoardTextView & boardTextView);

    void Play();
};


#endif