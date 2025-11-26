#include "GUISudoku.h"
#include "../../Engine/Utility/ScreenUtils.h"
#include "../../Engine/GlobalVar.h"
#include "../GUIManager.h"
#include "Game/Data/GlobalData.h"

#include <DragonBones/CCFactory.h>
#include <spine/spine-cocos2dx.h>
#include <Game/Utility/JNIUtils.h>
#include <Game/Utility/GameUtility.h>
#include <Game/Utility/GameSound.h>
#include "SudokuSolver.h"

#define BTN_BACK_ID 1
#define BTN_SOUND_ID 2
#define BTN_UNDO_ID 3
#define BTN_ERASE_ID  4
#define BTN_NOTES_ID  5
#define BTN_HINT_ID   6
#define BTN_NEW_GAME_ID 7
#define BTN_SETTING_ID 8

// --- UserDefault persistence (puzzle + current only, ignore notes) ---
static const char* kSudokuSaveKey  = "sudoku_save_pref";
static const char* kSudokuHeartKey = "sudoku_heart_pref";
GUISudoku::GUISudoku(void) : BaseGUI()
{
	BaseGUI();
	Node::onEnter();
	//setKeypadEnabled(true);
}
std::string GUISudoku::className = "GUISudoku";
GUISudoku::~GUISudoku(void)
{
}

void GUISudoku::initGUI()
{
    BaseGUI::initGUI();
    //if (!Scene::init())
        //return false;
    auto vs  = Director::getInstance()->getVisibleSize();
    auto org = Director::getInstance()->getVisibleOrigin();

    // Background
    auto bg = LayerColor::create(Color4B(18, 18, 24, 255));
    addChild(bg);

    Size size = Director::getInstance()->getRenderView()->getVisibleSize();
    btnBack   = addButton(BTN_BACK_ID, "btnBack.png");
    if (size.width / size.height < 11.0 / 20.0)
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 1.7f);
    else
        btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.8f);
    //	btnBack->setPosition(size.width - btnBack->getWidth() * 0.6f, size.height - btnBack->getHeight() * 0.7f);

    btnSound = addButton(BTN_SOUND_ID, "btnSoundOn.png");
    btnSound->setPosition(btnBack->getPositionX() - btnBack->getWidth() * 1.1f, btnBack->getPositionY());
    if (game->music)
    {
        btnSound->normalImage->setImage("btnSoundOn.png");
    }
    else
    {
        btnSound->normalImage->setImage("btnSoundOff.png");
    }

    btnSetting = addButton(BTN_SETTING_ID, "btnSetting.png");
    btnSetting->setPosition(btnSound->getPositionX() - btnSound->getWidth() * 1.1f, btnBack->getPositionY());

    
    // New Game button
    btnNewGame = addButton(BTN_NEW_GAME_ID, "sudoku/btnNewGame.png");
    btnNewGame->setPosition(vs.width - btnNewGame->getWidth() * 0.53, btnBack->getPositionY() - btnNewGame->getHeight() * 1.4);

     // Hearts UI
    initHeartsUI();

    
    // Time labels at top-left
    bestTimeLabel_ = Label::createWithTTF("Best: --:--", "fonts/tahoma.ttf", 18);
    bestTimeLabel_->setAnchorPoint(Vec2(0, 0.5));
    bestTimeLabel_->setPosition(org + Vec2(20, btnNewGame->getPositionY() + 35));
    addChild(bestTimeLabel_, 3);

    timeLabel_ = Label::createWithTTF("Time: 00:00", "fonts/tahoma.ttf", 18);
    timeLabel_->setAnchorPoint(Vec2(0, 0.5));
    timeLabel_->setPosition(org + Vec2(20, btnNewGame->getPositionY()));
    addChild(timeLabel_, 3);

    // Grid draw node
    grid_ = DrawNode::create();
    addChild(grid_, 1);

    // Selection rectangle
    selectRect_ = LayerColor::create(Color4B(100, 170, 255, 80), 0, 0);
    addChild(selectRect_, 2);

    

    // Keypad (1..9 + Erase + Notes)
    float btnY = vs.height * 0.15 + 30;
    float padX = vs.width / 9.0f;
    for (int d = 1; d <= 9; ++d)
    {
        int index                = d - 1;
        arrayButtonNumber[index] = addButton(100 + d, "sudoku/bgNumberSmall.png");
        arrayButtonNumber[index]->setPosition(padX * (d - 0.5), btnY);
        arrayButtonNumber[index]->normalImage->setColor(ax::Color3B(46, 57, 86));
        arrayButtonNumber[index]->normalImage->_img->setOpacity(100);

        auto item              = MenuItemLabel::create(Label::createWithTTF(std::to_string(d), "fonts/tahoma.ttf", 45),
                                                       [=](Object*) { onDigit(d); });
        arrayMenuNumber[index] = item;
        item->setPosition(Vec2(padX * (d - 0.5), btnY));
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

    btnY     = arrayButtonNumber[0]->getPositionY() + arrayButtonNumber[0]->getHeight() * 0.6;
    float pad = 90; // Reduced padding to fit 5 buttons
    float sX = (vs.width - pad * 4) * 0.5;

    btnErase = addButton(BTN_ERASE_ID, "sudoku/btnErase.png");
    btnErase->setPosition(sX + pad * 0.5, btnY + btnErase->getHeight() * 0.5);

    btnNotes = addButton(BTN_NOTES_ID, "sudoku/btnNoteActive.png");
    btnNotes->setPosition(sX + pad * 1.5, btnErase->getPositionY());

    // Undo button
    btnUndo = addButton(BTN_UNDO_ID, "sudoku/btnUndoActive.png");
    btnUndo->setPosition(sX + pad * 2.5, btnErase->getPositionY());

    // Hint button (BaseButton)
    btnHint = addButton(BTN_HINT_ID, "sudoku/btnHintActive.png");
    btnHint->setPosition(sX + pad * 3.5, btnErase->getPositionY());

    // Status
    statusLabel_ = Label::createWithTTF("OFF", "fonts/tahoma.ttf", 20);
    statusLabel_->enableOutline(Color4B(60, 82, 105, 255), 4);
    statusLabel_->setColor(Color3B(132, 152, 175));
    statusLabel_->setAnchorPoint(Vec2(0, 0.5));
    statusLabel_->setPosition(Vec2(btnNotes->getPositionX() - btnNotes->getWidth() * 0.55, btnNotes->getPositionY() + btnNotes->getHeight() * 0.3));
    addChild(statusLabel_, 4);

    btnY         = btnErase->getPositionY() + btnErase->getHeight() * 0.6;
    float height = heartIcons_[0]->getPositionY() - 35 - btnY;
    boardSize = std::min(vs.width, height);
    cellSize  = boardSize / 9.0f;
    origin    = org + Vec2((vs.width - boardSize) / 2.0f, btnY);
    for (int i = 0; i < 9; i++)
    {
        arrayBgSelect[i] = LayerColor::create(Color4B(170, 170, 55, 80), 0, 0);
        addChild(arrayBgSelect[i], 2);
        arrayBgSelect[i]->setContentSize(Size(cellSize, cellSize));
    }

    // Initialize related cell highlight arrays
    for (int i = 0; i < 27; i++)
    {
        arrayRelatedHighlight[i] = LayerColor::create(Color4B(100, 150, 255, 40), 0, 0);
        addChild(arrayRelatedHighlight[i], 1);
        arrayRelatedHighlight[i]->setContentSize(Size(cellSize, cellSize));
        arrayRelatedHighlight[i]->setVisible(false);
    }

    numbersLayer_ = Node::create();
    addChild(numbersLayer_, 2);

    // Initialize number labels array
    initNumberLabels();

    // Draw grid lines once during initialization
    drawGridLines();

   
    
    // Initialize timing state
    bestSeconds_ = UserDefault::getInstance()->getIntegerForKey("sudoku_best_time", -1);
    elapsedSeconds_ = 0.0f;
    isSolved_ = false;
    timeSinceLastSave_ = 0.0f;

    // Touch input: select cell & place value
    auto listener          = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch* t, Event*) {
        auto p = t->getLocation();
        // determine r,c under touch
        Rect boardRect(origin.x, origin.y, boardSize, boardSize);
        if (!boardRect.containsPoint(p))
            return false;
        int c = (int)((p.x - origin.x) / cellSize);
        int r = 8 - (int)((p.y - origin.y) / cellSize);  // y top->bottom
        if (tutorialActive_)
        {
            // Only allow selecting the guided cell in step 0
            if (tutStep_ == 0)
            {
                if (r != tutTargetR_ || c != tutTargetC_)
                    return false;
            }
        }
        setSelected(r, c);
        if (tutorialActive_ && tutStep_ == 0 && r == tutTargetR_ && c == tutTargetC_)
        {
            advanceTutorial();
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    curDiff = (sudoku::Difficulty) UserDefault::getInstance()->getIntegerForKey("sudoku_diff", 1);
}

void GUISudoku::startTutorialIfFirstTime()
{
    auto ud = UserDefault::getInstance();
    bool done = ud->getBoolForKey("sudoku_tutorial_done", false);
    //done      = false;
    if (done)
        return;
    beginTutorial();
}

void GUISudoku::beginTutorial()
{
    // Find an empty cell and its solution via solver
    Grid g = board_.exportState();
    if (!sudoku::Solver::solve(g))
        return;
    tutTargetR_ = -1;
    tutTargetC_ = -1;
    tutTargetVal_ = 0;
    for (int r = 0; r < 9 && tutTargetR_ < 0; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            if (board_.getValue(r, c) == 0 && g[r][c] != 0)
            {
                tutTargetR_  = r;
                tutTargetC_  = c;
                tutTargetVal_ = g[r][c];
                break;
            }
        }
    }
    if (tutTargetR_ < 0)
        return;

    tutorialActive_ = true;
    tutStep_        = 0; // tap cell first

    if (!tutHighlight_)
    {
        auto vs  = Director::getInstance()->getVisibleSize();
        auto org = Director::getInstance()->getVisibleOrigin();
        tutHighlight_ = LayerColor::create(Color4B(0, 0, 0, 90), vs.width, vs.height);
        tutHighlight_->setPosition(org);
        addChild(tutHighlight_, 50);
    }
    else
    {
        tutHighlight_->setVisible(true);
        tutHighlight_->setOpacity(90);
    }

    if (!tutPointer_)
    {
        tutPointer_ = Sprite::create("GuiGame/iconHand.png");
        if (!tutPointer_)
        {
            tutPointer_ = Sprite::create();
            auto draw = DrawNode::create();
            draw->drawSolidRect(Vec2(-10, -10), Vec2(10, 10), Color4F(1, 1, 0, 1));
            tutPointer_->addChild(draw);
        }
        tutPointer_->setAnchorPoint(Vec2(0.1f, 0.85f));
        addChild(tutPointer_, 60);
    }
    tutPointer_->setVisible(true);
    positionPointerAtCell(tutTargetR_, tutTargetC_);
}

void GUISudoku::endTutorial()
{
    tutorialActive_ = false;
    if (tutPointer_) tutPointer_->setVisible(false);
    if (tutHighlight_) tutHighlight_->setVisible(false);
    auto ud = UserDefault::getInstance();
    ud->setBoolForKey("sudoku_tutorial_done", true);
    ud->flush();
}

void GUISudoku::advanceTutorial()
{
    if (!tutorialActive_) return;
    if (tutStep_ == 0)
    {
        tutStep_ = 1;
        positionPointerAtNumber(tutTargetVal_);
    }
    else
    {
        endTutorial();
    }
}

void GUISudoku::positionPointerAtCell(int r, int c)
{
    if (!tutPointer_) return;
    auto pos = cellToPos(r, c, cellSize, origin);
    tutPointer_->stopAllActions();
    tutPointer_->setRotation(0);
    tutPointer_->setScale(1.0f);
    tutPointer_->setPosition(pos + Vec2(0, cellSize * 0.0f));
    tutPointer_->runAction(RepeatForever::create(Sequence::create(
        MoveBy::create(0.5f, Vec2(0, -8)),
        MoveBy::create(0.5f, Vec2(0, 8)),
        nullptr)));
}

void GUISudoku::positionPointerAtNumber(int d)
{
    if (!tutPointer_) return;
    int idx = d - 1;
    if (idx < 0 || idx >= 9) return;
    auto menuItem = arrayMenuNumber[idx];
    if (!menuItem) return;
    tutPointer_->stopAllActions();
    //tutPointer_->setRotation(-90);
    tutPointer_->setScale(1.0f);
    tutPointer_->setPosition(menuItem->getPosition() + Vec2(0, 0));
    tutPointer_->runAction(RepeatForever::create(Sequence::create(
        MoveBy::create(0.5f, Vec2(0, -8)),
        MoveBy::create(0.5f, Vec2(0, 8)),
        nullptr)));
}

void GUISudoku::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
    BaseGUI::showGUI(parent, hasFog);
    // Nếu có save tạm, tiếp tục; không thì ván mới

    if (!loadFromPrefsIfAny())
    {
        newGame(curDiff);
    }
    else
    {
        animateInitialNumbers();
    }
    updateTimeLabels();
    scheduleUpdate();

    // Tutorial trigger for first-time users
    startTutorialIfFirstTime();
}

Vec2 GUISudoku::cellToPos(int r, int c, float cell, Vec2 origin)
{
    return origin + Vec2(c * cell + cell * 0.5f, (8 - r) * cell + cell * 0.5f);
}

void GUISudoku::drawGrid()
{
    // Update selection rectangle
    if (selR_ >= 0)
    {
        selectRect_->setContentSize(Size(cellSize, cellSize));
        selectRect_->setPosition(origin + Vec2(selC_ * cellSize, (8 - selR_) * cellSize));
        selectRect_->setVisible(true);
    }
    else
    {
        selectRect_->setVisible(false);
        clearRelatedHighlights();
    }

    // Update numbers using stored labels
    redrawNumbers();
    
    // Update number button states
    for (int i = 0; i < 9; i++)
    {
        if (board_.isFinishNumber(i + 1))
        {
            arrayMenuNumber[i]->setOpacity(50);
        }
        else
        {
            arrayMenuNumber[i]->setOpacity(255);
        }
    }
}

void GUISudoku::redrawNumbers()
{
    // Clear all note labels first (keep only the main number labels)
    auto children = numbersLayer_->getChildren();
    for (auto it = children.begin(); it != children.end();)
    {
        auto child = *it;
        bool isMainLabel = false;
        for (int r = 0; r < 9 && !isMainLabel; ++r)
        {
            for (int c = 0; c < 9 && !isMainLabel; ++c)
            {
                if (child == numberLabels_[r][c])
                {
                    isMainLabel = true;
                }
            }
        }
        if (!isMainLabel)
        {
            child->removeFromParent();
            it = children.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    // Hide all main number labels first
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            numberLabels_[r][c]->setVisible(false);
        }
    }

    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            int v    = board_.getValue(r, c);
            auto pos = cellToPos(r, c, cellSize, origin);
            
            if (v)
            {
                // Reuse existing label
                numberLabels_[r][c]->setString(std::to_string(v));
                numberLabels_[r][c]->setTextColor(board_.isFixed(r, c) ? Color4B(220, 220, 220, 255) : Color4B(90, 220, 120, 255));
                numberLabels_[r][c]->setPosition(pos);
                numberLabels_[r][c]->setVisible(true);
            }
            else if (auto bits = board_.notes.bits[r][c])
            {
                // draw 3x3 tiny notes (still create new labels for notes as they're dynamic)
                for (int d = 1; d <= 9; ++d)
                {
                    if (bits & (1u << d))
                    {
                        int rr = (d - 1) / 3, cc = (d - 1) % 3;
                        auto s = Label::createWithTTF(std::to_string(d), "fonts/tahoma.ttf", 15);
                        s->setPosition(pos + Vec2((cc - 1) * cellSize * 0.28f, (1 - rr) * cellSize * 0.28f));
                        s->setTextColor(Color4B(160, 160, 180, 255));
                        numbersLayer_->addChild(s);
                    }
                }
            }
        }
    }
}

void GUISudoku::setSelected(int r, int c)
{
    selR_ = r;
    selC_ = c;
    highlightRelatedCells(r, c);
    drawGrid();
    int number = board_.getValue(r, c);
    btnErase->normalImage->setImage("sudoku/btnEraseActive.png");
    if (number <= 0)
    {
        for (int i = 0; i < 9; i++)
        {
            this->arrayButtonNumber[i]->normalImage->_img->setOpacity(200);
            this->arrayMenuNumber[i]->setColor(Color3B(40, 190, 255));
        }
        uint16_t prevBits = board_.notes.bits[selR_][selC_];
        if (prevBits == 0)
            btnErase->normalImage->setImage("sudoku/btnErase.png");
    }
    else
    {
        selectNumber(number);
        for (int i = 0; i < 9; i++)
        {
            this->arrayButtonNumber[i]->normalImage->_img->setOpacity(50);
            this->arrayMenuNumber[i]->setColor(Color3B(46, 57, 86));
        }
        if (board_.isFixed(r, c))
        {
            btnErase->normalImage->setImage("sudoku/btnErase.png");
        }
    }
}

void GUISudoku::unSelect() {
    selR_ = -1;
    selC_ = -1;
    selectRect_->setVisible(false);
    for (int i = 0; i < 9; i++)
    {
        this->arrayButtonNumber[i]->normalImage->_img->setOpacity(50);
        this->arrayMenuNumber[i]->setColor(Color3B(46, 57, 86));
    }
}

void GUISudoku::onDigit(int d)
{
    selectNumber(d);
    if (selR_ < 0)
        return;
    if (tutorialActive_)
    {
        // During tutorial, only accept the correct number at step 1
        if (tutStep_ == 1)
        {
            if (d != tutTargetVal_)
            {
                GameSound::playInvalid();
                return;
            }
        }
        else if (tutStep_ == 0)
        {
            // Not yet on number selection step
            return;
        }
    }
    if (notesMode_)
    {
        // record previous state for undo
        Notes beforeNotes = board_.notes;
        uint16_t prevBits         = board_.notes.bits[selR_][selC_];
        board_.toggleNote(selR_, selC_, d);
        Move mv{selR_, selC_, board_.getValue(selR_, selC_), prevBits, board_.getValue(selR_, selC_),
                board_.notes.bits[selR_][selC_], true};
        undoStack_.push_back(mv);
        GameSound::playMark();
    }
    else
    {
        if (board_.isFixed(selR_, selC_)) {
            // khong the chon o da Fix
            return;
        }
        int prev = board_.getValue(selR_, selC_);
        if (prev > 0)
            // can fai Erase truoc
            return;
        uint16_t prevBits = board_.notes.bits[selR_][selC_];
        bool valid = board_.isValidMove(selR_, selC_, d);
        bool changed = false;
        if (valid)
        {
            changed = board_.setValue(selR_, selC_, d);
            if (changed)
            {
                playCellEffect(selR_, selC_, Color4B(60, 220, 120, 120));
                GameSound::playCorrect();
                saveToPrefs();
            }
            JNIUtils::vibrate(10);
        }
        else
        {
            playCellEffect(selR_, selC_, Color4B(255, 60, 60, 140));
            showConflicts(selR_, selC_, d);
            loseLife();
            JNIUtils::vibrate(100);
            GameSound::playMistake();
        }
        if (changed)
        {
            if (tutorialActive_ && tutStep_ == 1 && selR_ == tutTargetR_ && selC_ == tutTargetC_ && d == tutTargetVal_)
            {
                // Completed guided fill
                advanceTutorial();
            }
            if (board_.isComplete())
            {
                isSolved_ = true;
                int currentSec = (int)elapsedSeconds_;
                if (bestSeconds_ < 0 || currentSec < bestSeconds_)
                {
                    bestSeconds_ = currentSec;
                    auto ud = UserDefault::getInstance();
                    ud->setIntegerForKey(("sudoku_best_time_" + to_string((int)(curDiff))).c_str(), bestSeconds_);
                    ud->flush();
                }
                updateTimeLabels();
                // Persist final elapsed time
                saveToPrefs();
                onFinishGame();
            }
            Move mv{selR_, selC_, prev, prevBits, board_.getValue(selR_, selC_), board_.notes.bits[selR_][selC_], false};
            undoStack_.push_back(mv);
            unSelect();
        }
    }
    drawGrid();
}

void GUISudoku::onErase()
{
    if (selR_ < 0)
        return;
    if (!board_.isFixed(selR_, selC_))
    {
        int saveR = selR_, saveC = selC_;
        int prev = board_.getValue(selR_, selC_);
        if (prev <= 0 && board_.notes.bits[selR_][selC_] == 0)
            return;
        uint16_t prevBits = board_.notes.bits[selR_][selC_];
        board_.eraseValue(selR_, selC_);
        Move mv{selR_, selC_, prev, prevBits, 0, 0, false};
        undoStack_.push_back(mv);
        board_.notes.bits[selR_][selC_] = 0;
        drawGrid();
        saveToPrefs();
        playCellEffect(selR_, selC_, Color4B(100, 100, 100, 250));
        unSelect();
       // setSelected(saveR, saveC);
        GameSound::playErase();
        btnErase->normalImage->setImage("sudoku/btnErase.png");
    }
    else
    {
        GameSound::playInvalid();
    }
}

void GUISudoku::onToggleNotes()
{
    notesMode_ = !notesMode_;
    statusLabel_->setString(std::string("") + (notesMode_ ? "ON" : "OFF"));
}

void GUISudoku::newGame(sudoku::Difficulty d)
{
    GameSound::playStartGame();
    bestSeconds_ =
        UserDefault::getInstance()->getIntegerForKey(("sudoku_best_time_" + to_string((int)(curDiff))).c_str(), -1);
    curDiff  = d;
    auto puz = sudoku::Generator::makePuzzle(d);
    board_.load(puz);
    unSelect();
    undoStack_.clear();
    lives_ = 3;
    updateHeartsUI();
    statusLabel_->setString("OFF");
    notesMode_ = false;
    drawGrid();
    saveToPrefs();
    // Reset timer state
    elapsedSeconds_ = 0.0f;
    isSolved_ = false;
    updateTimeLabels();
    // Persist reset current time
    auto ud = UserDefault::getInstance();
    ud->setIntegerForKey("sudoku_current_time", 0);
    ud->flush();
    animateInitialNumbers();
    btnErase->normalImage->setImage("sudoku/btnErase.png");
    for (int i = 0; i < 9; i++)
    {
        arrayBgSelect[i]->setVisible(false);
    }
    float y = btnNewGame->getPositionY();
    for (int i = 0; i < 3; i++)
    {
        heartIcons_[i]->setPositionY(y);
    }

    // Restart tutorial on new game if still not completed
    startTutorialIfFirstTime();
}

void GUISudoku::onButtonRelease(int buttonID, Touch* touch)
{
    GameSound::playClick();
    if (buttonID == BTN_BACK_ID)
    {
        onBackKey();
    }
    else if (buttonID == BTN_SOUND_ID)
    {
        game->music = !game->music;
        if (game->music)
        {
            btnSound->normalImage->setImage("btnSoundOn.png");
        }
        else
        {
            btnSound->normalImage->setImage("btnSoundOff.png");
        }

        UserDefault::getInstance()->setBoolForKey("music", game->music);
        UserDefault::getInstance()->flush();
    }
    else if (buttonID == BTN_SETTING_ID)
    {
        GUIMenuSudoku* gui = (GUIMenuSudoku*) GUIManager::getInstance().showGuiWithName(GUIMenuSudoku::className);
        gui->updateCurrentLevel((int)curDiff);
    }
    else if (buttonID == BTN_ERASE_ID)
    {
        onErase();
    }
    else if (buttonID == BTN_NOTES_ID)
    {
        onToggleNotes();
    }
    else if (buttonID == BTN_UNDO_ID)
    {
        onUndo();
    }
    else if (buttonID == BTN_HINT_ID)
    {
        
        #if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
            onHint();
        #else
            GUIManager::getInstance().guiDialog->showGUI(
            "Stuck? Watch a quick ad to get a helpful hint!", []() { JNIUtils::showRewardedAds();
            }, false, NULL);
        #endif
    }
    else if (buttonID == BTN_NEW_GAME_ID)
    {
        game->showAdsFull();
        onNewGame();
    }
}

void GUISudoku::onHint()
{
    if (board_.isComplete())
        return;
    // Build a grid from current state and solve it
    Grid g = board_.exportState();
    if (!sudoku::Solver::solve(g))
        return;
    // Find first empty cell and reveal the correct digit there
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            if (board_.getValue(r, c) == 0 && g[r][c] != 0)
            {
                selR_ = r;
                selC_ = c;
                //drawGrid();
                // Apply the solved value directly (bypass validation since it's from solution)
                board_.current[r][c] = g[r][c];
                board_.notes.bits[r][c] = 0;
                playCellEffect(r, c, Color4B(60, 220, 120, 120));
                saveToPrefs();
                drawGrid();
                selectNumber(g[r][c]);
                // If puzzle is now complete, update status
                if (board_.isComplete())
                {
                    isSolved_ = true;
                    int currentSec = (int)elapsedSeconds_;
                    if (bestSeconds_ < 0 || currentSec < bestSeconds_)
                    {
                        bestSeconds_ = currentSec;
                        auto ud = UserDefault::getInstance();
                        ud->setIntegerForKey(("sudoku_best_time_" + to_string((int)(curDiff))).c_str(), bestSeconds_);
                        ud->flush();
                    }
                    updateTimeLabels();
                    onFinishGame();
                }
                return;
            }
        }
    }
}

void GUISudoku::onNewGame()
{
    // Start a new game with medium difficulty
    newGame(curDiff);
}

void GUISudoku::initHeartsUI()
{
    auto vs  = Director::getInstance()->getVisibleSize();
    auto org = Director::getInstance()->getVisibleOrigin();
    float startX = org.x + (vs.width - 50 * 3) * 0.5;
    float y = org.y + btnNewGame->getPositionY();
    for (int i = 0; i < 3; ++i)
    {
        auto icon = Sprite::create("GuiGame/sudoku/iconHeart.png");
        addChild(icon);
        icon->setPosition(Vec2(startX + (i + 0.5) * 50, y));
        heartIcons_[i] = icon;
    }
    updateHeartsUI();
}

void GUISudoku::updateHeartsUI()
{
    for (int i = 0; i < 3; ++i)
    {
        if (heartIcons_[i])
            heartIcons_[i]->setVisible(i < lives_);
    }
}

void GUISudoku::loseLife()
{
    if (lives_ <= 0)
        return;
    lives_--;
    UserDefault::getInstance()->setIntegerForKey(kSudokuHeartKey, lives_);
    UserDefault::getInstance()->flush();
    updateHeartsUI();
    // simple fly up fade for the last heart turned off
    int idx = lives_;
    if (idx >= 0 && idx < 3 && heartIcons_[idx])
    {
        auto h = heartIcons_[idx];
        h->setVisible(true);
        h->stopAllActions();
        auto seq = Sequence::create(Spawn::create(MoveBy::create(0.6f, Vec2(0, 30)), FadeOut::create(0.6f), nullptr),
                                    CallFunc::create([this, h]() {
                                        h->setOpacity(255);
                                        h->setVisible(false);
                                    }),
                                    nullptr);
        h->runAction(seq);
    }
    
    // Check for game over
    if (lives_ <= 0)
    {
        UserDefault::getInstance()->setStringForKey(kSudokuSaveKey, "");
        GameSound::playSoundLose();
        // Gray out visible cells sequentially, then show game over dialog
        runFinishGrayOut([this]() {
            this->showGameOverDialog();
        });
    }
    UserDefault::getInstance()->flush();
}

void GUISudoku::playCellEffect(int r, int c, Color4B color)
{
    auto pos = cellToPos(r, c, cellSize, origin);
    //auto color = correct ? Color4B(60, 220, 120, 120) : Color4B(255, 60, 60, 140);
    auto effect = LayerColor::create(color, cellSize, cellSize);
    effect->setPosition(Vec2(pos.x - cellSize * 0.5f, pos.y - cellSize * 0.5f));
    addChild(effect, 3);
    effect->setOpacity(0);
    auto seq = Sequence::create(FadeIn::create(0.08f), DelayTime::create(0.08f), FadeOut::create(0.25f),
                                CallFunc::create([effect]() { effect->removeFromParent(); }), nullptr);
    effect->runAction(seq);
   /* Color color2;
    if (correct)
    {
        color2 = Color(0, 255, 0, 255);
    }
    else
    {
        color2 = Color(255, 0, 0, 255);
    }*/
    Color4F color2 = Color4F(color);
    Layer* layer           = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
    ParticleEffect* effect1 = new ParticleEffect();
    effect1->create("particles/sudoku.plist", layer);
    // ParticleEffect *effect =  effectMgr->addParticleEffect("particles/twenty.plist", Vec2 (posX, posY), layer);
    effect1->particle->setPosition(pos.x, pos.y - cellSize * 0.5f);
    effect1->particle->setBlendAdditive(true);
    effect1->particle->setStartColor(color2);
    effect1->particle->setStartColorVar(Color4F(0, 0, 0, 0));
    effect1->particle->setEndColor(color2);
    effect1->particle->setEndColorVar(Color4F(0, 0, 0, 0));
    effect1->particle->setAutoRemoveOnFinish(true);
}

void GUISudoku::showConflicts(int r, int c, int v)
{
    // Highlight conflicting cells in row, column, and 3x3 box that already have value v
    Color4B color = Color4B(255, 60, 60, 160);
    auto spawnFlash = [&](int rr, int cc) {
        auto pos = cellToPos(rr, cc, cellSize, origin);
        auto effect = LayerColor::create(color, cellSize, cellSize);
        effect->setPosition(Vec2(pos.x - cellSize * 0.5f, pos.y - cellSize * 0.5f));
        addChild(effect, 4);
        effect->setOpacity(0);
        auto seq = Sequence::create(FadeIn::create(0.06f), DelayTime::create(0.1f), FadeOut::create(0.22f),
                                    CallFunc::create([effect]() { effect->removeFromParent(); }), nullptr);
        effect->runAction(seq);
    };

    // row
    for (int cc = 0; cc < 9; ++cc)
    {
        if (cc == c) continue;
        if (board_.getValue(r, cc) == v)
            spawnFlash(r, cc);
    }
    // column
    for (int rr = 0; rr < 9; ++rr)
    {
        if (rr == r) continue;
        if (board_.getValue(rr, c) == v)
            spawnFlash(rr, c);
    }
    // 3x3 box
    int r0 = (r / 3) * 3;
    int c0 = (c / 3) * 3;
    for (int dr = 0; dr < 3; ++dr)
    {
        for (int dc = 0; dc < 3; ++dc)
        {
            int rr = r0 + dr, cc = c0 + dc;
            if (rr == r && cc == c) continue;
            if (board_.getValue(rr, cc) == v)
                spawnFlash(rr, cc);
        }
    }
}


std::string GUISudoku::serializeBoard() const
{
    std::string s;
    s.reserve(325);
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            s.push_back(char('0' + board_.puzzle[r][c]));
        }
    }
    s.push_back('|');
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            s.push_back(char('0' + board_.current[r][c]));
        }
    }
    return s;
}

bool GUISudoku::deserializeBoard(const std::string& data)
{
    if (data.size() != 163) // 162 + '|' + 162
        return false;
    if (data[81] != '|')
        return false;
    Grid puz{};
    Grid cur{};
    int idx = 0;
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            puz[r][c] = data[idx++] - '0';
    idx++; // skip '|'
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            cur[r][c] = data[idx++] - '0';

    board_.puzzle = puz;
    board_.current = cur;
    board_.notes.bits = {};
    return true;
}

void GUISudoku::saveToPrefs()
{
    auto ud = UserDefault::getInstance();
    ud->setStringForKey(kSudokuSaveKey, serializeBoard());
    ud->setIntegerForKey(kSudokuHeartKey, lives_);
    ud->flush();
}

bool GUISudoku::loadFromPrefsIfAny()
{
    auto ud = UserDefault::getInstance();
    std::string s = string(ud->getStringForKey(kSudokuSaveKey, ""));
    if (s.empty())
        return false;
    if (!deserializeBoard(s))
        return false;
    unSelect();
    undoStack_.clear();
    lives_ = ud->getIntegerForKey(kSudokuHeartKey, 3);
    updateHeartsUI();
    notesMode_ = false;
    statusLabel_->setString("OFF");
    drawGrid();
    // Restore current elapsed time and best
    elapsedSeconds_ = (float)ud->getIntegerForKey("sudoku_current_time", 0);
    isSolved_ = false;
    bestSeconds_ =
        UserDefault::getInstance()->getIntegerForKey(("sudoku_best_time_" + to_string((int)(curDiff))).c_str(), -1);
    updateTimeLabels();
    return true;
}

void GUISudoku::onUndo()
{
    if (undoStack_.empty())
        return;
    Move mv = undoStack_.back();
    undoStack_.pop_back();

    // restore previous state
    if (!board_.isFixed(mv.r, mv.c))
    {
        board_.current[mv.r][mv.c] = mv.prevValue;
        board_.notes.bits[mv.r][mv.c] = mv.prevNotes;
    }
    selR_ = mv.r;
    selC_ = mv.c;
    selectRect_->setVisible(true);
    highlightRelatedCells(selR_, selC_);
    drawGrid();
    selectNumber(board_.getValue(selR_, selC_));
    saveToPrefs();
}

void GUISudoku::selectNumber(int number) {
    for (int i = 0; i < 9; i++)
    {
        arrayBgSelect[i]->setVisible(false);
    }
    if (number <= 0)
        return;
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board_.getValue(i, j) == number)
            {
                arrayBgSelect[count]->setVisible(true);
                Vec2 pos = cellToPos(i, j, cellSize, origin);
                arrayBgSelect[count]->setPosition(Vec2(pos.x - cellSize * 0.5, pos.y - cellSize * 0.5));
                count++;
            }
        }
    }
}

void GUISudoku::highlightRelatedCells(int r, int c)
{
   // bool isCheck[81] = {false};
    // Clear all highlights first
    clearRelatedHighlights();
    
    int highlightIndex = 0;
    
    // Highlight row (9 cells)
    for (int col = 0; col < 9; col++)
    {
        if (col != c) // Don't highlight the selected cell itself
        {
            Vec2 pos = cellToPos(r, col, cellSize, origin);
            arrayRelatedHighlight[highlightIndex]->setPosition(Vec2(pos.x - cellSize * 0.5, pos.y - cellSize * 0.5));
            arrayRelatedHighlight[highlightIndex]->setVisible(true);
            highlightIndex++;
           // isCheck[r * 9 + col] = true;
        }
    }
    
    // Highlight column (9 cells)
    for (int row = 0; row < 9; row++)
    {
        if (row != r) // Don't highlight the selected cell itself
        {
            Vec2 pos = cellToPos(row, c, cellSize, origin);
            arrayRelatedHighlight[highlightIndex]->setPosition(Vec2(pos.x - cellSize * 0.5, pos.y - cellSize * 0.5));
            arrayRelatedHighlight[highlightIndex]->setVisible(true);
            highlightIndex++;
           // isCheck[row * 9 + c] = true;
        }
    }
    
    // Highlight 3x3 box (9 cells)
    int boxStartRow = (r / 3) * 3;
    int boxStartCol = (c / 3) * 3;
    for (int boxRow = boxStartRow; boxRow < boxStartRow + 3; boxRow++)
    {
        for (int boxCol = boxStartCol; boxCol < boxStartCol + 3; boxCol++)
        {
            if (boxRow != r && boxCol != c ) // Don't highlight the selected cell itself
            {
                Vec2 pos = cellToPos(boxRow, boxCol, cellSize, origin);
                arrayRelatedHighlight[highlightIndex]->setPosition(Vec2(pos.x - cellSize * 0.5, pos.y - cellSize * 0.5));
                arrayRelatedHighlight[highlightIndex]->setVisible(true);
                highlightIndex++;
            }
        }
    }
}

void GUISudoku::clearRelatedHighlights()
{
    for (int i = 0; i < 27; i++)
    {
        arrayRelatedHighlight[i]->setVisible(false);
    }
}

void GUISudoku::update(float dt)
{
    if (!isSolved_)
    {
        elapsedSeconds_ += dt;
        updateTimeLabels();
        // Throttle autosave of current time once per second
        timeSinceLastSave_ += dt;
        if (timeSinceLastSave_ >= 1.0f)
        {
            timeSinceLastSave_ = 0.0f;
            auto ud = UserDefault::getInstance();
            ud->setIntegerForKey("sudoku_current_time", (int)elapsedSeconds_);
            ud->flush();
        }
    }
}

void GUISudoku::newGame() {
    newGame(curDiff);
}

void GUISudoku::updateTimeLabels()
{
    int cur = (int)elapsedSeconds_;
    if (timeLabel_)
        timeLabel_->setString(std::string("Time: ") + formatTimeMMSS(cur));
    if (bestTimeLabel_)
    {
        if (bestSeconds_ >= 0)
            bestTimeLabel_->setString(std::string("Best: ") + formatTimeMMSS(bestSeconds_));
        else
            bestTimeLabel_->setString("Best: --:--");
    }
}

std::string GUISudoku::formatTimeMMSS(int totalSeconds)
{
    int mm = totalSeconds / 60;
    int ss = totalSeconds % 60;
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d", mm, ss);
    return std::string(buf);
}

void GUISudoku::animateInitialNumbers()
{
    // Collect fixed puzzle numbers for animation
    struct CellAnim { int r; int c; int v; };
    std::vector<CellAnim> cells;
    cells.reserve(81);
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            int v = board_.puzzle[r][c];
            if (v != 0)
            {
                cells.push_back({r, c, v});
            }
        }
    }

    // Hide all number labels initially
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            numberLabels_[r][c]->setVisible(false);
            numberLabels_[r][c]->setScale(1.0f);
            numberLabels_[r][c]->setOpacity(255);
        }
    }

    float delayStep = 0.03f;
    float scaleIn = 0.25f;
    
    // Animate each fixed number using the existing labels
    for (size_t i = 0; i < cells.size(); ++i)
    {
        const auto& ca = cells[i];
        auto& label = numberLabels_[ca.r][ca.c];
        
        // Set up the label for animation
        label->setString(std::to_string(ca.v));
        label->setTextColor(Color4B(220, 220, 220, 255)); // Fixed number color
        label->setPosition(cellToPos(ca.r, ca.c, cellSize, origin));
        label->setScale(0.0f);
        label->setOpacity(0);
        label->setVisible(true);

        float startDelay = (float)i * delayStep;
        auto seq = Sequence::create(
            DelayTime::create(startDelay),
            Spawn::create(
                FadeIn::create(scaleIn), 
                EaseBackOut::create(ScaleTo::create(scaleIn, 1.0f)), 
                nullptr
            ),
            nullptr
        );
        label->runAction(seq);
    }

    // After animation completes, update all numbers normally
    float total = (cells.empty() ? 0.0f : (float)(cells.size() - 1) * delayStep + scaleIn + 0.1f);
    auto updateAction = Sequence::create(
        DelayTime::create(total),
        CallFunc::create([this]() {
            // Refresh all numbers to show current state (including user inputs)
            redrawNumbers();
        }),
        nullptr
    );
    this->runAction(updateAction);
}

void okNewGameSudoku() {
    GUIManager::getInstance().guiSudoku->newGame();
}

void GUISudoku::showGameOverDialog()
{
    game->showAdsFull();
    // Pause the game timer
    GUIManager::getInstance().guiDialog->showGUI("GameOver. Please start a new game?", okNewGameSudoku, true);
}

void GUISudoku::onContinueGame()
{
    
}

void GUISudoku::onEndGame()
{
    
}

void GUISudoku::onFinishGame() {
    auto ud = UserDefault::getInstance();
    ud->setStringForKey(kSudokuSaveKey, "");
    ud->flush();
    int cur = (int)elapsedSeconds_;
    // Winning flow: sparkle yellow across filled cells, then show result (time)
    runWinSparkleThenResult([this, cur]() {
        GUIManager::getInstance().guiResult->showGUI(cur, bestSeconds_, true);
    });
    GameSound::playLevelUp();
}

void GUISudoku::runFinishGrayOut(const std::function<void()>& onComplete)
{
    // Collect positions of number labels that are currently visible
    std::vector<std::pair<int,int>> cells;
    cells.reserve(81);
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            if (numberLabels_[r][c] && numberLabels_[r][c]->isVisible())
            {
                cells.emplace_back(r, c);
            }
        }
    }

    if (cells.empty())
    {
        if (onComplete) onComplete();
        return;
    }

    // Animate in reading order from top-left to bottom-right
    std::sort(cells.begin(), cells.end(), [](const auto& a, const auto& b) {
        // Visual top row is r=8
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    const float delayStep = 0.03f;
    float lastDelay = 0.0f;
    for (size_t i = 0; i < cells.size(); ++i)
    {
        //auto [r, c] = cells[i];
        int r       = cells[i].first;
        int c       = cells[i].second;
        auto lbl    = numberLabels_[r][c];
        float d     = delayStep * static_cast<float>(i);
        lastDelay   = d;
        auto seq = Sequence::create(
            DelayTime::create(d),
            CallFunc::create([lbl]() {
                if (lbl)
                {
                    lbl->setTextColor(Color4B(180, 180, 180, 255));
                }
            }),
            nullptr
        );
        if (lbl) lbl->runAction(seq);
    }

    runAction(Sequence::create(
        DelayTime::create(lastDelay + 0.12f),
        CallFunc::create([onComplete]() { if (onComplete) onComplete(); }),
        nullptr));
}

void GUISudoku::runWinSparkleThenResult(const std::function<void()>& onComplete)
{
    // Gather visible labels
    std::vector<std::pair<int,int>> cells;
    cells.reserve(81);
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (numberLabels_[r][c] && numberLabels_[r][c]->isVisible())
                cells.emplace_back(r, c);

    if (cells.empty())
    {
        if (onComplete) onComplete();
        return;
    }

    // Sort visually top-left -> bottom-right
    std::sort(cells.begin(), cells.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first > b.first; // r=8 on top
        return a.second < b.second;
    });

    const float delayStep = 0.025f;
    float lastDelay = 0.0f;
    for (size_t i = 0; i < cells.size(); ++i)
    {
        //auto [r, c] = cells[i];
        int r       = cells[i].first;
        int c       = cells[i].second;
        auto lbl    = numberLabels_[r][c];
        float d     = delayStep * static_cast<float>(i);
        lastDelay   = d;

        // Sparkle effect: quick bright yellow flash + small pop
        auto seq = Sequence::create(
            DelayTime::create(d),
            CallFunc::create([this, r, c, lbl]() {
                if (!lbl) return;
                lbl->stopAllActions();
                lbl->setScale(1.0f);
                lbl->runAction(Sequence::create(
                    Spawn::create(
                        TintTo::create(0.06f, 255, 230, 90),
                        ScaleTo::create(0.06f, 1.15f),
                        nullptr
                    ),
                    Spawn::create(
                        TintTo::create(0.08f, 255, 255, 255),
                        ScaleTo::create(0.08f, 1.0f),
                        nullptr
                    ),
                    nullptr
                ));
                // Add a small particle sparkle at cell center if available
                Vec2 pos = cellToPos(r, c, cellSize, origin);
                Layer* layer = layerMgr->getLayerByIndex(LAYER_EFFECT_GAME);
                ParticleEffect* star = new ParticleEffect();
                star->create("particles/sudoku.plist", layer);
                star->particle->setPosition(pos.x, pos.y);
                star->particle->setStartColor(Color4F(1.0f, 0.95f, 0.35f, 1.0f));
                star->particle->setEndColor(Color4F(1.0f, 0.95f, 0.35f, 0.0f));
                star->particle->setAutoRemoveOnFinish(true);
            }),
            nullptr
        );
        if (lbl) lbl->runAction(seq);
    }

    runAction(Sequence::create(
        DelayTime::create(lastDelay + 0.2f),
        CallFunc::create([onComplete]() { if (onComplete) onComplete(); }),
        nullptr));
}

void GUISudoku::initNumberLabels()
{
    // Initialize all number labels as empty/invisible
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            numberLabels_[r][c] = Label::createWithTTF("", "fonts/tahoma.ttf", 40);
            numberLabels_[r][c]->setVisible(false);
            numbersLayer_->addChild(numberLabels_[r][c]);
        }
    }
}

void GUISudoku::drawGridLines()
{
    grid_->clear();
    
    // background
    grid_->drawSolidRect(origin, origin + Vec2(boardSize, boardSize), Color4F(0.12f, 0.12f, 0.16f, 1));

    // grid lines
    for (int i = 0; i <= 9; ++i)
    {
        float x     = origin.x + i * cellSize;
        float y     = origin.y + i * cellSize;
        float thick = (i % 3 == 0) ? 6.0f : 1.0f;
        Color4B color1 = Color4B(180, 190, 190, 255);
        Color4F color  = Color4F(color1);
        if (i == 0 || i == 9)
        {
            grid_->drawSegment(Vec2(x, origin.y), Vec2(x, origin.y + boardSize), 4, color);
            grid_->drawSegment(Vec2(origin.x, origin.y + i * cellSize),
                               Vec2(origin.x + boardSize, origin.y + i * cellSize), 4, color);
        }
        else if (i % 3 == 0)
        {
            grid_->drawSegment(Vec2(x, origin.y), Vec2(x, origin.y + boardSize), 3, color);
            grid_->drawSegment(Vec2(origin.x, origin.y + i * cellSize), Vec2(origin.x + boardSize, origin.y + i * cellSize), 3,
                               color);
        }
        else
        {
            grid_->drawLine(Vec2(x, origin.y), Vec2(x, origin.y + boardSize), color);
            grid_->drawLine(Vec2(origin.x, origin.y + i * cellSize), Vec2(origin.x + boardSize, origin.y + i * cellSize),
                            color);
        }
    }
}

void GUISudoku::onBackKey()
{
    if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
    {
        game->changeToLandscape();
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
        GUIManager::getInstance().isCallBackPress = true;
        
    }
}
