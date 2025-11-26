// SudokuScene.cpp
#include "SudokuScene.h"
using namespace ax;

Scene* SudokuScene::createScene()
{
    return SudokuScene::create();
}

bool SudokuScene::init()
{
    if (!Scene::init())
        return false;
    auto vs  = Director::getInstance()->getVisibleSize();
    auto org = Director::getInstance()->getVisibleOrigin();

    // Background
    auto bg = LayerColor::create(Color4B(18, 18, 24, 255));
    addChild(bg);

    // UI Title
    auto title = Label::createWithTTF("Sudoku", "fonts/tahoma.ttf", 36);
    title->setPosition(org + Vec2(vs.width * 0.5f, vs.height - 40));
    addChild(title);

    // Grid draw node
    grid_ = DrawNode::create();
    addChild(grid_, 1);

    // Selection rectangle
    selectRect_ = LayerColor::create(Color4B(100, 170, 255, 80), 0, 0);
    addChild(selectRect_, 2);

    // Related cell highlighting
    rowHighlight_ = LayerColor::create(Color4B(255, 255, 100, 40), 0, 0);
    colHighlight_ = LayerColor::create(Color4B(255, 255, 100, 40), 0, 0);
    boxHighlight_ = LayerColor::create(Color4B(255, 255, 100, 40), 0, 0);
    addChild(rowHighlight_, 1);
    addChild(colHighlight_, 1);
    addChild(boxHighlight_, 1);

    boardSize = std::min(vs.width, vs.height) - 160;
    cellSize      = boardSize / 9.0f;
    origin    = org + Vec2((vs.width - boardSize) / 2.0f, (vs.height - boardSize) / 2.0f + 20);
    for (int i = 0; i < 9; i++)
    {
        arrayBgSelect[i] = LayerColor::create(Color4B(170, 170, 55, 80), 0, 0);
        addChild(arrayBgSelect[i], 2);
        arrayBgSelect[i]->setContentSize(Size(cellSize, cellSize));
    }

    numbersLayer_ = Node::create();
    addChild(numbersLayer_, 2);

    // Status
    statusLabel_ = Label::createWithTTF("Notes: OFF", "fonts/tahoma.ttf", 18);
    statusLabel_->setAnchorPoint(Vec2(0, 0.5));
    statusLabel_->setPosition(org + Vec2(20, 30));
    addChild(statusLabel_);

    // Keypad (1..9 + Erase + Notes)
    float btnY = 70;
    for (int d = 1; d <= 9; ++d)
    {
        auto item = MenuItemLabel::create(Label::createWithTTF(std::to_string(d), "fonts/tahoma.ttf", 24),
                                          [=](Object*) { onDigit(d); });
        arrayMenuNumber[d - 1] = item;
        item->setPosition(org + Vec2(40 + (d - 1) * 35, btnY));
        auto menu = (Menu*)getChildByName("keymenu");
        if (!menu)
        {
            menu = Menu::create();
            menu->setName("keymenu");
            menu->setPosition(Vec2::ZERO);
            addChild(menu, 3);
        }
        menu->addChild(item);
    }
    auto erase = MenuItemLabel::create(Label::createWithTTF("Erase", "fonts/tahoma.ttf", 20),
                                       [=](Object*) { onErase(); });
    auto notes = MenuItemLabel::create(Label::createWithTTF("Notes", "fonts/tahoma.ttf", 20),
                                       [=](Object*) { onToggleNotes(); });
    erase->setPosition(org + Vec2(380, btnY));
    notes->setPosition(org + Vec2(450, btnY));
    ((Menu*)getChildByName("keymenu"))->addChild(erase);
    ((Menu*)getChildByName("keymenu"))->addChild(notes);

    // Touch input: select cell & place value
    auto listener          = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch* t, Event*) {
        auto p = t->getLocation();
        // determine r,c under touch
        auto vs         = Director::getInstance()->getVisibleSize();
        auto org        = Director::getInstance()->getVisibleOrigin();
        float boardSize = std::min(vs.width, vs.height) - 160;
        float cell      = boardSize / 9.0f;
        Vec2 origin     = org + Vec2((vs.width - boardSize) / 2.0f, (vs.height - boardSize) / 2.0f + 20);
        Rect boardRect(origin.x, origin.y, boardSize, boardSize);
        if (!boardRect.containsPoint(p))
            return false;
        int c = (int)((p.x - origin.x) / cell);
        int r = 8 - (int)((p.y - origin.y) / cell);  // y top->bottom
        setSelected(r, c);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    newGame(sudoku::Difficulty::MEDIUM);
    return true;
}

Vec2 SudokuScene::cellToPos(int r, int c, float cell, Vec2 origin)
{
    return origin + Vec2(c * cell + cell * 0.5f, (8 - r) * cell + cell * 0.5f);
}

void SudokuScene::drawGrid()
{
    grid_->clear();
    auto vs         = Director::getInstance()->getVisibleSize();
    auto org        = Director::getInstance()->getVisibleOrigin();
    float boardSize = std::min(vs.width, vs.height) - 160;
    float cell      = boardSize / 9.0f;
    Vec2 origin     = org + Vec2((vs.width - boardSize) / 2.0f, (vs.height - boardSize) / 2.0f + 20);

    // selection rect size
    if (selR_ >= 0)
    {
        selectRect_->setContentSize(Size(cell, cell));
        selectRect_->setPosition(origin + Vec2(selC_ * cell, (8 - selR_) * cell));
        selectRect_->setVisible(true);
    }
    else
    {
        selectRect_->setVisible(false);
    }

    // background
    grid_->drawSolidRect(origin, origin + Vec2(boardSize, boardSize), Color4F(0.12f, 0.12f, 0.16f, 1));

    // grid lines
    for (int i = 0; i <= 9; ++i)
    {
        float x     = origin.x + i * cell;
        float y     = origin.y + i * cell;
        float thick = (i % 3 == 0) ? 6.0f : 1.0f;
        //grid_->drawLine(Vec2(x, origin.y), Vec2(x, origin.y + boardSize), Color::WHITE);
        //grid_->drawLine(Vec2(origin.x, origin.y + i * cell), Vec2(origin.x + boardSize, origin.y + i * cell),
                        //Color::WHITE);
        if (i % 3 == 0)
        {
            grid_->drawSegment(Vec2(x, origin.y), Vec2(x, origin.y + boardSize), 3, Color4F::WHITE);
            grid_->drawSegment(Vec2(origin.x, origin.y + i * cell), Vec2(origin.x + boardSize, origin.y + i * cell), 3,
                            Color4F::WHITE);
        }
        else
        {
            grid_->drawLine(Vec2(x, origin.y), Vec2(x, origin.y + boardSize), Color4F::WHITE);
            grid_->drawLine(Vec2(origin.x, origin.y + i * cell), Vec2(origin.x + boardSize, origin.y + i * cell),
                            Color4F::WHITE);
        }
    }

    redrawNumbers();
    for (int i = 0; i < 9; i++)
    {
        if (board_.isFinishNumber(i + 1))
        {
            arrayMenuNumber[i]->setOpacity(100);
        }
    }
}

void SudokuScene::redrawNumbers()
{
    numbersLayer_->removeAllChildren();
    auto vs         = Director::getInstance()->getVisibleSize();
    auto org        = Director::getInstance()->getVisibleOrigin();
    float boardSize = std::min(vs.width, vs.height) - 160;
    float cell      = boardSize / 9.0f;
    Vec2 origin     = org + Vec2((vs.width - boardSize) / 2.0f, (vs.height - boardSize) / 2.0f + 20);

    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            int v    = board_.getValue(r, c);
            auto pos = cellToPos(r, c, cell, origin);
            if (v)
            {
                auto lab =
                    Label::createWithTTF(std::to_string(v), "fonts/tahoma.ttf", board_.isFixed(r, c) ? 28 : 28);
                lab->setTextColor(board_.isFixed(r, c) ? Color4B(220, 220, 220, 255) : Color4B(90, 220, 120, 255));
                lab->setPosition(pos);
                numbersLayer_->addChild(lab);
            }
            else if (auto bits = board_.notes.bits[r][c])
            {
                // draw 3x3 tiny notes
                for (int d = 1; d <= 9; ++d)
                {
                    if (bits & (1u << d))
                    {
                        int rr = (d - 1) / 3, cc = (d - 1) % 3;
                        auto s = Label::createWithTTF(std::to_string(d), "fonts/tahoma.ttf", 12);
                        s->setPosition(pos + Vec2((cc - 1) * cell * 0.28f, (1 - rr) * cell * 0.28f));
                        s->setTextColor(Color4B(160, 160, 180, 255));
                        numbersLayer_->addChild(s);
                    }
                }
            }
        }
    }
}

void SudokuScene::setSelected(int r, int c)
{
    selR_ = r;
    selC_ = c;
    updateRelatedCellHighlighting();
    drawGrid();
}

void SudokuScene::onDigit(int d)
{
    for (int i = 0; i < 9; i++)
    {
        arrayBgSelect[i]->setVisible(false);
    }
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board_.getValue(i, j) == d)
            {
                arrayBgSelect[count]->setVisible(true);
                Vec2 pos = cellToPos(i, j, cellSize, origin);
                arrayBgSelect[count]->setPosition(Vec2(pos.x - cellSize * 0.5, pos.y - cellSize * 0.5));
                count++;
            }
        }
    }
    if (selR_ < 0)
        return;
    if (notesMode_)
    {
        board_.toggleNote(selR_, selC_, d);
    }
    else
    {
        if (board_.setValue(selR_, selC_, d) && board_.isComplete())
        {
            statusLabel_->setString("Solved! 🎉");
        }
    }
    drawGrid();
    
}

void SudokuScene::onErase()
{
    if (selR_ < 0)
        return;
    if (!board_.isFixed(selR_, selC_))
    {
        board_.setValue(selR_, selC_, 0);
        board_.notes.bits[selR_][selC_] = 0;
        drawGrid();
    }
}

void SudokuScene::onToggleNotes()
{
    notesMode_ = !notesMode_;
    statusLabel_->setString(std::string("Notes: ") + (notesMode_ ? "ON" : "OFF"));
}

void SudokuScene::updateRelatedCellHighlighting()
{
    // Hide all highlights initially
    rowHighlight_->setVisible(false);
    colHighlight_->setVisible(false);
    boxHighlight_->setVisible(false);
    
    if (selR_ < 0 || selC_ < 0)
        return;
    
    auto vs = Director::getInstance()->getVisibleSize();
    auto org = Director::getInstance()->getVisibleOrigin();
    float boardSize = std::min(vs.width, vs.height) - 160;
    float cell = boardSize / 9.0f;
    Vec2 origin = org + Vec2((vs.width - boardSize) / 2.0f, (vs.height - boardSize) / 2.0f + 20);
    
    // Highlight entire row
    rowHighlight_->setContentSize(Size(boardSize, cell));
    rowHighlight_->setPosition(origin + Vec2(0, (8 - selR_) * cell));
    rowHighlight_->setVisible(true);
    
    // Highlight entire column
    colHighlight_->setContentSize(Size(cell, boardSize));
    colHighlight_->setPosition(origin + Vec2(selC_ * cell, 0));
    colHighlight_->setVisible(true);
    
    // Highlight 3x3 box
    int boxR = (selR_ / 3) * 3;  // Top row of the 3x3 box
    int boxC = (selC_ / 3) * 3;  // Left column of the 3x3 box
    boxHighlight_->setContentSize(Size(cell * 3, cell * 3));
    boxHighlight_->setPosition(origin + Vec2(boxC * cell, (8 - boxR - 2) * cell));
    boxHighlight_->setVisible(true);
}

void SudokuScene::newGame(sudoku::Difficulty d)
{
    auto puz = sudoku::Generator::makePuzzle(d);
    board_.load(puz);
    selR_ = selC_ = -1;
    statusLabel_->setString("Notes: OFF");
    notesMode_ = false;
    updateRelatedCellHighlighting();
    drawGrid();
}
