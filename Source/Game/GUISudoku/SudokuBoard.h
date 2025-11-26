// SudokuBoard.h
#pragma once
#include "SudokuTypes.h"
#include <stack>
#include <string>

namespace sudoku
{

class Board
{
public:
    Grid puzzle{};   // fixed given cells (0 = blank)
    Grid current{};  // player state
    Notes notes{};   // pencil marks

    bool isFixed(int r, int c) const { return puzzle[r][c] != 0; }
    bool setValue(int r, int c, int v);  // returns true if change applied
    void eraseValue(int r, int c);  // returns true if change applied
    int getValue(int r, int c) const { return current[r][c]; }
    void toggleNote(int r, int c, int v);
    bool isComplete() const;
    bool isValidMove(int r, int c, int v) const;
    int countNumber(int number);
    bool isFinishNumber(int number);

    void resetToPuzzle();
    void load(const Grid& puz);
    Grid exportState() const { return current; }

    // simple persistence helpers (JSON strings)
    std::string toJson() const;
    bool fromJson(const std::string& json);
    
private:
    bool rowOk(int r) const;
    bool colOk(int c) const;
    bool boxOk(int br, int bc) const;
};

}  // namespace sudoku
