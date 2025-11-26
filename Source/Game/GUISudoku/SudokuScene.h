// SudokuScene.h
#pragma once
#include "axmol.h"
#include "SudokuBoard.h"
#include "SudokuGenerator.h"

class SudokuScene : public ax::Scene
{
public:
    static ax::Scene* createScene();
    CREATE_FUNC(SudokuScene);
    virtual bool init() override;

private:
    sudoku::Board board_;
    bool notesMode_             = false;
    ax::DrawNode* grid_         = nullptr;
    ax::Node* numbersLayer_     = nullptr;
    ax::Label* statusLabel_     = nullptr;
    ax::LayerColor* selectRect_ = nullptr;
    ax::MenuItemLabel* arrayMenuNumber[9];
    ax::LayerColor* arrayBgSelect[9];
    ax::LayerColor* rowHighlight_ = nullptr;
    ax::LayerColor* colHighlight_ = nullptr;
    ax::LayerColor* boxHighlight_ = nullptr;
    int selR_ = -1, selC_ = -1;
    float cellSize;
    float boardSize;
    ax::Vec2 origin;

    void newGame(sudoku::Difficulty d);
    void drawGrid();
    void redrawNumbers();
    void setSelected(int r, int c);
    void onDigit(int d);
    void onErase();
    void onToggleNotes();
    ax::Vec2 cellToPos(int r, int c, float cellSize, ax::Vec2 origin);
    void updateRelatedCellHighlighting();
};
