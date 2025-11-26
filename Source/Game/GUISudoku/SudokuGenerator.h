// SudokuGenerator.h
#pragma once
#include "SudokuTypes.h"

namespace sudoku
{

enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD,
    EXPERT
};

class Generator
{
public:
    static Grid makeFull();                                     // filled valid board
    static Grid makePuzzle(Difficulty d = Difficulty::MEDIUM);  // unique-solution puzzle
private:
    static int removalsFor(Difficulty d);
};

}  // namespace sudoku
