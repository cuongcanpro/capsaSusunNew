// SudokuSolver.h
#pragma once
#include "SudokuTypes.h"

namespace sudoku
{

class Solver
{
public:
    // returns true if solved in-place
    static bool solve(Grid& g);
    // count number of solutions up to `limit` (early stop)
    static int countSolutions(Grid g, int limit = 2);

public:
    static bool findEmpty(const Grid& g, int& r, int& c);
    static bool isSafe(const Grid& g, int r, int c, int val);
};

}  // namespace sudoku
