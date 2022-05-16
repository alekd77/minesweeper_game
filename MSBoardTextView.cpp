#include "MSBoardTextView.h"
#include <iostream>

MSBoardTextView::MSBoardTextView (MinesweeperBoard & boardToDisplay)
                                  : board(boardToDisplay) {}

void MSBoardTextView::Display() const {

    for (int rowIdx = 0; rowIdx < board.GetBoardHeight(); ++rowIdx)
    {
        for (int columnIdx = 0; columnIdx < board.GetBoardWidth(); ++columnIdx)
        {
            // The field is not revealed and does not have a flag.
            if (board.GetFieldInfo(rowIdx, columnIdx) == '_')
            {
                std::cout << "[_]";
                continue;
            }

            // The field is not revealed and has a flag.
            if (board.GetFieldInfo(rowIdx, columnIdx) == 'F')
            {
                std::cout << "[F]";
                continue;
            }

            // The field is revealed and has mine.
            if (board.GetFieldInfo(rowIdx, columnIdx) == 'x')
            {
                std::cout << "[M]";
                continue;
            }

            // The field is revealed and has 0 mines around.
            if (board.GetFieldInfo(rowIdx, columnIdx) == ' ')
            {
                std::cout << "[ ]";
                continue;
            }

            // The field is revealed and has some mines around
            // (from 1 to 8).
            if (board.GetFieldInfo(rowIdx, columnIdx) >= '1' and
                board.GetFieldInfo(rowIdx, columnIdx) <= '8')
            {
                switch (board.GetFieldInfo(rowIdx, columnIdx)) {
                    case '1': {
                        std::cout << "[1]";
                        break;
                    }
                    case '2': {
                        std::cout << "[2]";
                        break;
                    }
                    case '3': {
                        std::cout << "[3]";
                        break;
                    }
                    case '4': {
                        std::cout << "[4]";
                        break;
                    }
                    case '5': {
                        std::cout << "[5]";
                        break;
                    }
                    case '6': {
                        std::cout << "[6]";
                        break;
                    }
                    case '7': {
                        std::cout << "[7]";
                        break;
                    }
                    case '8': {
                        std::cout << "[8]";
                        break;
                    }
                }
            }
        }
        std::cout << "\n";
    }
}
