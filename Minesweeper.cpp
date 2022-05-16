#include "Minesweeper.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

MinesweeperBoard::MinesweeperBoard (int width, int height, GameMode mode) {

    this->width = width;
    this->height = height;
    this->currentPlayerReveals = 0;
    this->isGameRunning = 0;
    this->currentGameMode = mode;
    this->currentPlayerActions = 0;

    if (mode == DEBUG)
    {
        for (int rowIdx = 0; rowIdx < GetBoardHeight(); ++rowIdx)
        {
            for (int columnIdx = 0; columnIdx < GetBoardWidth(); ++columnIdx)
            {
                if (rowIdx == columnIdx)
                    board[rowIdx][columnIdx].hasMine = true;

                if (rowIdx == 0)
                    board[rowIdx][columnIdx].hasMine = true;

                if (columnIdx == 0 and rowIdx % 2 == 0)
                    board[rowIdx][columnIdx].hasMine = true;
            }
        }

        return;
    }

    int maxMinesNumber = GetBoardHeight() * GetBoardWidth();

    if (mode == EASY)
        maxMinesNumber *= 0.1;

    if (mode == NORMAL)
        maxMinesNumber *= 0.2;

    if (mode == HARD)
        maxMinesNumber *= 0.3;

    this->currentMinesNumber = maxMinesNumber;
    this->currentFlagNumber = GetBoardMinesNumber();

    CreateBoard();
}


bool MinesweeperBoard::IsFieldOnBoard (int row, int column) const {

    if (row < 0 or row > GetBoardHeight() - 1)
        return false;

    if (column < 0 or column > GetBoardWidth() - 1)
        return false;

    return true;
}

bool MinesweeperBoard::IsRevealed (int row, int column) const {

    if (!IsFieldOnBoard(row, column))
        return false;

    return board[row][column].isRevealed;
}

bool MinesweeperBoard::HasMine (int row, int column) const {

    if (!IsFieldOnBoard(row, column))
        return false;

    return board[row][column].hasMine;
}

bool MinesweeperBoard::HasFlag (int row, int column) const {

    if (!IsFieldOnBoard(row, column))
        return false;

    if (IsRevealed(row, column))
        return false;

    return board[row][column].hasFlag;
}


int MinesweeperBoard::GetBoardHeight() const {
    return height;
}

int MinesweeperBoard::GetBoardWidth() const {
    return width;
}

int MinesweeperBoard::GetBoardMinesNumber() const {
    return currentMinesNumber;
}

int MinesweeperBoard::GetCurrentPlayerActions() const {
    return currentPlayerActions;
}

int MinesweeperBoard::GetFlagNumber() const {
    return currentFlagNumber;
}

int MinesweeperBoard::GetMinesAroundFieldNumber (int row, int column) const {

    if (!IsRevealed(row, column))
        return -1;

    if (!IsFieldOnBoard(row, column))
        return -1;

    int countMines = 0;

    for (int rowIdx = row - 1; rowIdx <= row + 1; ++rowIdx)
    {
        for (int columnIdx = column - 1; columnIdx <= column + 1;
             ++columnIdx)
        {
            if (IsFieldOnBoard(rowIdx, columnIdx))
            {
                if (HasMine(rowIdx, columnIdx))
                    ++countMines;
            }
        }
    }

    return countMines;
}

GameState MinesweeperBoard::GetGameState() const {

    if (isGameRunning == 1)
        return FINISHED_LOSS;

    if (isGameRunning == 2)
        return FINISHED_WIN;

    return RUNNING;
}

char MinesweeperBoard::GetFieldInfo (int row, int column) const {

    if (!IsFieldOnBoard(row, column))
        return '#';

    if (!IsRevealed(row, column) and HasFlag(row, column))
        return 'F';

    if (!IsRevealed(row, column) and !HasFlag(row, column))
        return '_';

    if (IsRevealed(row, column) and HasMine(row, column))
        return 'x';

    if (IsRevealed(row, column) and GetMinesAroundFieldNumber(row, column) == 0)
        return ' ';

    return '0' + GetMinesAroundFieldNumber(row, column);
}


int MinesweeperBoard::RandomNumberGenerator() const {

    return rand() % RANDOM_NUMBER_GENERATOR_INTERVAL;
}

void MinesweeperBoard::CreateBoard() {

    // Generates default board and fills it with random numbers.
    std::vector<std::vector<int>> defaultBoard;
    std::vector<int> tempDefaultBoardRow;

    for (int rowIdx = 0; rowIdx < GetBoardHeight(); ++rowIdx)
    {
        tempDefaultBoardRow.clear();

        for (int columnIdx = 0; columnIdx < GetBoardWidth(); ++columnIdx)
        {
            tempDefaultBoardRow.push_back (RandomNumberGenerator());
        }

        defaultBoard.push_back(tempDefaultBoardRow);
    }


    // Calculates how many common randomly generated numbers
    // the default board is consisted of.
    std::vector<std::pair<int,int>> countCommonRandomNumbers;
    std::pair<int,int> tempCommonRandomNumbers;

    for (int randomNumberIdx = 0; randomNumberIdx < RANDOM_NUMBER_GENERATOR_INTERVAL;
         ++randomNumberIdx)
    {
        tempCommonRandomNumbers.first = randomNumberIdx;
        tempCommonRandomNumbers.second = 0;

        for (int rowIdx = 0; rowIdx < GetBoardHeight(); ++rowIdx)
        {
            for (int columnIdx = 0; columnIdx < GetBoardWidth(); ++columnIdx)
            {
                if (defaultBoard[rowIdx][columnIdx] == randomNumberIdx)
                    ++tempCommonRandomNumbers.second;
            }
        }

        countCommonRandomNumbers.push_back(tempCommonRandomNumbers);
    }


    // Counts which random number will be define as a limit number
    // (every under number will be set as field with bomb).
    int currentMinesSet = 0;
    int maxRandNumberToSet = 0;

    for (int randomNumberIdx = 0; randomNumberIdx < RANDOM_NUMBER_GENERATOR_INTERVAL;
         ++randomNumberIdx)
    {
        if (currentMinesSet + countCommonRandomNumbers
            [randomNumberIdx].second > GetBoardMinesNumber())
            break;

        currentMinesSet += countCommonRandomNumbers
        [randomNumberIdx].second;
        ++maxRandNumberToSet;
    }

    // Sets settings of generated board.
    for (int rowIdx = 0; rowIdx < GetBoardHeight(); ++rowIdx)
    {
        for (int columnIdx = 0; columnIdx < GetBoardWidth(); ++columnIdx)
        {
            board[rowIdx][columnIdx].hasMine = false;
            if (defaultBoard[rowIdx][columnIdx] < maxRandNumberToSet)
                board[rowIdx][columnIdx].hasMine = true;

            board[rowIdx][columnIdx].hasFlag = false;
            board[rowIdx][columnIdx].isRevealed = false;
        }
    }
}


void MinesweeperBoard::ToggleFlag (int row, int column) {

    if (IsRevealed(row, column))
        return;

    if (!IsFieldOnBoard(row, column))
        return;

    if (GetGameState() != RUNNING)
        return;

    if (HasFlag(row, column))
        return;

    board[row][column].hasFlag = true;
    --currentFlagNumber;
    ++currentPlayerActions;
}

void MinesweeperBoard::UntoggleFlag (int row, int column) {

    if (IsRevealed(row, column))
        return;

    if (!IsFieldOnBoard(row, column))
        return;

    if (GetGameState() != RUNNING)
        return;

    if (!HasFlag(row, column))
        return;

    board[row][column].hasFlag = false;
    ++currentFlagNumber;
}


void MinesweeperBoard::FloodFill (int startingRow, int startingColumn) {

    if (!IsFieldOnBoard(startingRow, startingColumn))
        return;

    if (IsRevealed(startingRow, startingColumn))
        return;

    if (GetGameState() != RUNNING)
        return;

    if (!IsRevealed(startingRow, startingColumn) and
        !HasMine(startingRow, startingColumn))
    {
        board[startingRow][startingColumn].isRevealed = true;
        ++currentPlayerReveals;

        if (GetMinesAroundFieldNumber(startingRow, startingColumn) == 0)
        {
            FloodFill(startingRow - 1, startingColumn + 0);
            FloodFill(startingRow + 1, startingColumn + 0);
            FloodFill(startingRow + 0, startingColumn - 1);
            FloodFill(startingRow + 0, startingColumn + 1);
            FloodFill(startingRow - 1, startingColumn + 1);
            FloodFill(startingRow + 1, startingColumn - 1);
            FloodFill(startingRow - 1, startingColumn - 1);
            FloodFill(startingRow + 1, startingColumn + 1);
        }
    }

    ++currentPlayerActions;
}

void MinesweeperBoard::RevealField (int row, int column) {

    if (IsRevealed(row, column))
        return;

    if (!IsFieldOnBoard(row, column))
        return;

    if (GetGameState() != RUNNING)
        return;

    if (HasFlag(row, column))
        return;

    if (currentPlayerReveals == 0 and currentGameMode != 0)
    {
        while (GetMinesAroundFieldNumber(row, column) != 0)
        {
            CreateBoard();
            FloodFill(row, column);
            this->currentFlagNumber = GetBoardMinesNumber();
        }
    }
    else
        FloodFill(row, column);


    if (HasMine(row, column))
    {
        board[row][column].isRevealed = true;
        isGameRunning = 1;  // Sets current GameState as 'FINISHED_LOSS'.
        return;
    }


    int unrevealedFieldsNumber = 0;

    for (int rowIdx = 0; rowIdx < GetBoardHeight(); ++rowIdx)
    {
        for (int columnIdx = 0; columnIdx < GetBoardWidth(); ++columnIdx)
        {
            if (!IsRevealed(rowIdx, columnIdx))
                ++unrevealedFieldsNumber;
        }
    }

    if (unrevealedFieldsNumber == GetBoardMinesNumber())
    {
        isGameRunning = 2;  // Sets current GameState as 'FINISHED_WIN'.
        return;
    }

    isGameRunning = 0;  // Sets current GameState as 'RUNNING'.
}


void MinesweeperBoard::RevealMinedField(int row, int column) {

    if (!IsFieldOnBoard(row, column))
        return;

    if (IsRevealed(row, column))
        return;

    if (GetGameState() != FINISHED_LOSS)
        return;

    if (!HasMine(row, column))
        return;

    board[row][column].isRevealed = true;
}


void MinesweeperBoard::DebugDisplay() const {

    for (int rowIdx = 0; rowIdx < GetBoardHeight(); ++rowIdx)
    {
        for (int columnIdx = 0; columnIdx < GetBoardWidth(); ++columnIdx)
        {
            std::string boardField;

            if (HasMine(rowIdx, columnIdx))
                boardField = "[M";
            else
                boardField = "[.";

            if (IsRevealed(rowIdx, columnIdx))
                boardField += "r";
            else
                boardField += ".";

            if (HasFlag(rowIdx, columnIdx))
                boardField += "f]";
            else
                boardField += ".]";

            std::cout << boardField;
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}