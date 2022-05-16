#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

enum GameMode {DEBUG, EASY, NORMAL, HARD};
enum GameState {RUNNING, FINISHED_LOSS, FINISHED_WIN};

struct Field {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard {
private:
    const int RANDOM_NUMBER_GENERATOR_INTERVAL = 1000;

    Field board[100][100];
    int width;
    int height;
    int isGameRunning;    // '0' = RUNNING, '1' = FINISHED_LOSS, '2' = FINISHED_WIN
    int currentPlayerReveals;
    int currentGameMode;    // '0' = DEBUG, '1' = EASY, '2' = NORMAL, '3' = HARD
    int currentMinesNumber;
    int currentFlagNumber;
    int currentPlayerActions;

    bool IsFieldOnBoard (int row, int column) const;

    int RandomNumberGenerator() const;

    void CreateBoard();

    void FloodFill (int startingRow, int startingColumn);

public:
    MinesweeperBoard (int width, int height, GameMode mode);

    bool IsRevealed (int row, int column) const;
    bool HasMine (int row, int column) const;
    bool HasFlag (int row, int column) const;

    int GetBoardHeight() const;
    int GetBoardWidth() const;
    int GetBoardMinesNumber() const;
    int GetCurrentPlayerActions() const;
    int GetFlagNumber() const;
    int GetMinesAroundFieldNumber (int row, int column) const;
    GameState GetGameState() const;
    char GetFieldInfo (int row, int column) const;

    void ToggleFlag (int row, int column);
    void UntoggleFlag (int row, int column);
    void RevealField (int row, int column);
    void RevealMinedField (int row, int column);

    void DebugDisplay() const;
};


#endif