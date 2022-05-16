#include "MSTextController.h"
#include <iostream>

using namespace std;

MSTextController:: MSTextController (MinesweeperBoard & boardToDisplay,
                                     MSBoardTextView & boardTextView)
                                     : board(boardToDisplay), textView(boardTextView) {}

void MSTextController::Play() {
    int userRowChoice, userColumnChoice;
    bool userAction;      // 'false' = toggle flag, 'true' = reveal field
    bool untoggle;


    cout << "\nEnter row: "; cin >> userRowChoice;
    cout << "Enter column: "; cin >> userColumnChoice;

    cout << "\nChoose action ('0' = toggle flag, '1' = reveal field): ";
    cin >> userAction;

    if (userAction)
        board.RevealField(userRowChoice - 1, userColumnChoice - 1);
    else
    {
        if (board.HasFlag(userRowChoice - 1, userColumnChoice - 1))
        {
            cout << "\nField with entered coordinates has already been toggled.\n"
                    "Do you want to untoggle? Press '0' for no or '1' for yes: ";
            cin >> untoggle;

            if (untoggle)
                board.UntoggleFlag(userRowChoice - 1, userColumnChoice - 1);

            return;
        }

        board.ToggleFlag(userRowChoice - 1, userColumnChoice - 1);
    }
}