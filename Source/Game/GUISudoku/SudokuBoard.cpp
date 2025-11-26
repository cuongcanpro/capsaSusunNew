// SudokuBoard.cpp
#include "SudokuBoard.h"
#include <sstream>
#include <iomanip>

namespace sudoku
{

bool Board::rowOk(int r) const
{
    bool seen[10]{};
    for (int c = 0; c < 9; ++c)
    {
        int v = current[r][c];
        if (v)
        {
            if (seen[v])
                return false;
            seen[v] = true;
        }
    }
    return true;
}
bool Board::colOk(int c) const
{
    bool seen[10]{};
    for (int r = 0; r < 9; ++r)
    {
        int v = current[r][c];
        if (v)
        {
            if (seen[v])
                return false;
            seen[v] = true;
        }
    }
    return true;
}
bool Board::boxOk(int br, int bc) const
{
    bool seen[10]{};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            int v = current[br * 3 + i][bc * 3 + j];
            if (v)
            {
                if (seen[v])
                    return false;
                seen[v] = true;
            }
        }
    return true;
}

bool Board::isValidMove(int r, int c, int v) const
{
    if (v < 1 || v > 9)
        return false;
    if (isFixed(r, c))
        return false;
    // Temporarily set and check
    int old   = current[r][c];
    Grid tmp  = current;
    tmp[r][c] = v;
    // Validate row/col/box constraints only (allow other empties)
    for (int i = 0; i < 9; ++i)
        if (i != c && tmp[r][i] == v)
            return false;
    for (int i = 0; i < 9; ++i)
        if (i != r && tmp[i][c] == v)
            return false;
    int r0 = (r / 3) * 3, c0 = (c / 3) * 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            int rr = r0 + i, cc = c0 + j;
            if ((rr != r || cc != c) && tmp[rr][cc] == v)
                return false;
        }
    (void)old;
    return true;
}

int Board::countNumber(int number)
{
    int count = 0;
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            if (current[r][c] == number)
                count++;
        }
    }
    return count;
}

bool Board::isFinishNumber(int number)
{
    return countNumber(number) == 9;
}

bool Board::setValue(int r, int c, int v)
{
    if (!isValidMove(r, c, v))
        return false;
    current[r][c]    = v;
    notes.bits[r][c] = 0;
    return true;
}

void Board::eraseValue(int r, int c)
{
    current[r][c]    = 0;
    notes.bits[r][c] = 0;
}

void Board::toggleNote(int r, int c, int v)
{
    if (isFixed(r, c))
        return;
    if (v < 1 || v > 9)
        return;
    notes.bits[r][c] ^= (1u << v);
}

bool Board::isComplete() const
{
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            if (current[r][c] == 0)
                return false;
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        if (!rowOk(i) || !colOk(i))
            return false;
    }
    for (int br = 0; br < 3; ++br)
        for (int bc = 0; bc < 3; ++bc)
            if (!boxOk(br, bc))
                return false;
    return true;
}

void Board::resetToPuzzle()
{
    current    = puzzle;
    notes.bits = {};
}

void Board::load(const Grid& puz)
{
    puzzle = puz;
    resetToPuzzle();
}

// Simple compact JSON: {"p":[...81...],"c":[...81...],"n":[...81 ints bits...]}
std::string Board::toJson() const
{
    auto dumpArr = [&](const Grid& g) {
        std::ostringstream os;
        os << "[";
        bool first = true;
        for (int r = 0; r < 9; ++r)
        {
            for (int c = 0; c < 9; ++c)
            {
                if (!first)
                    os << ",";
                first = false;
                os << g[r][c];
            }
        }
        os << "]";
        return os.str();
    };
    auto dumpNotes = [&]() {
        std::ostringstream os;
        os << "[";
        bool first = true;
        for (int r = 0; r < 9; ++r)
        {
            for (int c = 0; c < 9; ++c)
            {
                if (!first)
                    os << ",";
                first = false;
                os << notes.bits[r][c];
            }
        }
        os << "]";
        return os.str();
    };
    std::ostringstream out;
    out << "{\"p\":" << dumpArr(puzzle) << ",\"c\":" << dumpArr(current) << ",\"n\":" << dumpNotes() << "}";
    return out.str();
}

bool Board::fromJson(const std::string& js)
{
    auto parse81 = [&](const std::string& s, size_t& pos) {
        Grid g{};
        int cnt = 0;
        while (pos < s.size() && s[pos] != '[')
            ++pos;
        if (pos == s.size())
            return g;
        ++pos;
        std::string num;
        while (pos < s.size() && cnt < 81)
        {
            if ((s[pos] >= '0' && s[pos] <= '9'))
            {
                num.push_back(s[pos]);
            }
            else if (s[pos] == ',' || s[pos] == ']')
            {
                if (!num.empty())
                {
                    g[cnt / 9][cnt % 9] = std::stoi(num);
                    num.clear();
                    ++cnt;
                }
                if (s[pos] == ']')
                    break;
            }
            ++pos;
        }
        return g;
    };
    auto parse81u = [&](const std::string& s, size_t& pos) {
        Notes n;
        int cnt = 0;
        while (pos < s.size() && s[pos] != '[')
            ++pos;
        if (pos == s.size())
            return n;
        ++pos;
        std::string num;
        while (pos < s.size() && cnt < 81)
        {
            if ((s[pos] >= '0' && s[pos] <= '9'))
            {
                num.push_back(s[pos]);
            }
            else if (s[pos] == ',' || s[pos] == ']')
            {
                if (!num.empty())
                {
                    n.bits[cnt / 9][cnt % 9] = static_cast<uint16_t>(std::stoi(num));
                    num.clear();
                    ++cnt;
                }
                if (s[pos] == ']')
                    break;
            }
            ++pos;
        }
        return n;
    };

    size_t p = 0;
    puzzle   = parse81(js, p);
    current  = parse81(js, p);
    notes    = parse81u(js, p);
    return true;
}

}  // namespace sudoku
