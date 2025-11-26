// SudokuSolver.cpp
#include "SudokuSolver.h"
#include <algorithm>

namespace sudoku
{

bool Solver::findEmpty(const Grid& g, int& r, int& c)
{
    for (r = 0; r < SUDOKU_N; ++r)
        for (c = 0; c < SUDOKU_N; ++c)
            if (g[r][c] == 0)
                return true;
    return false;
}

bool Solver::isSafe(const Grid& g, int r, int c, int v)
{
    for (int i = 0; i < SUDOKU_N; ++i)
        if (g[r][i] == v || g[i][c] == v)
            return false;
    int r0 = (r / 3) * 3, c0 = (c / 3) * 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (g[r0 + i][c0 + j] == v)
                return false;
    return true;
}

bool Solver::solve(Grid& g)
{
    int r, c;
    if (!findEmpty(g, r, c))
        return true;
    for (int v = 1; v <= 9; ++v)
    {
        if (isSafe(g, r, c, v))
        {
            g[r][c] = v;
            if (solve(g))
                return true;
            g[r][c] = 0;
        }
    }
    return false;
}

static bool countRec(Grid& g, int& count, int limit)
{
    int r, c;
    for (r = 0; r < SUDOKU_N; ++r)
    {
        bool brk = false;
        for (c = 0; c < SUDOKU_N; ++c)
        {
            if (g[r][c] == 0)
            {
                brk = true;
                break;
            }
        }
        if (brk)
            break;
        if (r == SUDOKU_N - 1 && c == SUDOKU_N - 1 && g[r][c] != 0)
        { /*full*/
        }
    }
    // find next empty
    bool found = false;
    for (r = 0; r < SUDOKU_N && !found; ++r)
        for (c = 0; c < SUDOKU_N && !found; ++c)
            if (g[r][c] == 0)
            {
                found = true;
                --r;
                break;
            }
    if (!found)
    {
        count++;
        return count < limit;
    }
    for (int v = 1; v <= 9; ++v)
    {
        if (Solver::isSafe(g, r, c, v))
        {
            g[r][c] = v;
            if (!countRec(g, count, limit))
                return false;
            g[r][c] = 0;
            if (count >= limit)
                return false;
        }
    }
    return true;
}

int Solver::countSolutions(Grid g, int limit)
{
    int cnt = 0;
    countRec(g, cnt, limit);
    return cnt;
}

}  // namespace sudoku
