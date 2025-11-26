// SudokuGenerator.cpp
#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include <random>
#include <algorithm>
#include <functional>
namespace sudoku
{

static std::mt19937& rng()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

Grid Generator::makeFull()
{
    Grid g{};  // fill using randomized backtracking
    std::array<int, 9> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::function<bool(int, int)> fill = [&](int r, int c) {
        if (r == 9)
            return true;
        int nr = (c == 8) ? r + 1 : r;
        int nc = (c + 1) % 9;
        std::shuffle(nums.begin(), nums.end(), rng());
        for (int v : nums)
        {
            bool ok = true;
            for (int i = 0; i < 9 && ok; ++i)
                if (g[r][i] == v || g[i][c] == v)
                    ok = false;
            int r0 = (r / 3) * 3, c0 = (c / 3) * 3;
            for (int i = 0; i < 3 && ok; ++i)
                for (int j = 0; j < 3; ++j)
                    if (g[r0 + i][c0 + j] == v)
                        ok = false;
            if (ok)
            {
                g[r][c] = v;
                if (fill(nr, nc))
                    return true;
                g[r][c] = 0;
            }
        }
        return false;
    };
    fill(0, 0);
    return g;
}

int Generator::removalsFor(Difficulty d)
{
    switch (d)
    {
    case Difficulty::EASY:
        return 40;  // about 41 givens
    case Difficulty::MEDIUM:
        return 50;  // ~31 givens
    case Difficulty::HARD:
        return 55;  // ~26 givens
    case Difficulty::EXPERT:
        return 60;  // ~21 givens
    }
    return 50;
}

Grid Generator::makePuzzle(Difficulty d)
{
    Grid full = makeFull();
    // create a list of all positions and remove symmetrically while maintaining unique solution
    std::vector<CellIndex> cells;
    cells.reserve(81);
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            cells.push_back({r, c});
    std::shuffle(cells.begin(), cells.end(), rng());

    Grid puzzle  = full;
    int toRemove = removalsFor(d);
    for (auto& ci : cells)
    {
        if (toRemove <= 0)
            break;
        int r = ci.r, c = ci.c;
        int r2 = 8 - r, c2 = 8 - c;  // symmetric pair
        int old1 = puzzle[r][c];
        int old2 = puzzle[r2][c2];
        if (old1 == 0 && old2 == 0)
            continue;
        puzzle[r][c]   = 0;
        puzzle[r2][c2] = 0;
        if (Solver::countSolutions(puzzle, 2) == 1)
        {
            toRemove -= (r == r2 && c == c2) ? 1 : 2;
        }
        else
        {
            puzzle[r][c]   = old1;
            puzzle[r2][c2] = old2;
        }
    }
    return puzzle;
}

}  // namespace sudoku
