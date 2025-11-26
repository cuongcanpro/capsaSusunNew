#pragma once
#include <array>
#include <vector>
#include <cstdint>

constexpr int SUDOKU_N = 9;
using Grid             = std::array<std::array<int, SUDOKU_N>, SUDOKU_N>;  // 0 = empty

struct CellIndex
{
    int r = 0, c = 0;
};  // row, col [0..8]

struct Move
{
    CellIndex idx;
    int prevVal = 0;
    int newVal  = 0;
    bool note   = false;
};

struct Notes
{
    // bitmask for digits 1..9 in each cell
    std::array<std::array<uint16_t, SUDOKU_N>, SUDOKU_N> bits{};  // bit i => (1<<i)
};
