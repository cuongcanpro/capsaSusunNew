// =============================
// File: Game2048Scene.h (Upgraded: slide animations, multi-undo, pause, sounds)
// =============================
#pragma once
#include "axmol.h"
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include <array>
#include <random>
#include <vector>
#include <utility>
#include <functional>
#include <string>
#include <deque>

using namespace ax::ui;
class GUI2048 : public BaseGUI
{
public:
    GUI2048(void);
    ~GUI2048(void);

public:
    void initGUI();
    void endGame();
    void newGame(bool forceReset = false);
    void onBackKey();
    void onButtonRelease(int buttonID, Touch* touch);
    void onTouchEnded(Touch* pTouch, Event* pEvent);
    bool onTouchBegan(Touch* pTouch, Event* pEvent);
    void showGUI(Node* parent /* = NULL */, bool hasFog /* = true */);

private:
    BaseButton *btnBack, *btnSound;

    // --- Hằng số ---
    static constexpr int GRID = 4;

    // --- Trạng thái game ---
    std::array<std::array<int, GRID>, GRID> _board{};  // [row][col]
    int _score     = 0;
    int _bestScore = 0;
    bool _gameOver = false;

    // --- Undo nhiều bước ---
    struct Snapshot
    {
        std::array<std::array<int, GRID>, GRID> board;
        int score;
    };
    std::deque<Snapshot> _history;  // push trước khi move, giới hạn 20 bước
    int _undoLimit = 20;

    // --- Cờ đang chạy animation / pause ---
    bool _animating = false;
    bool _paused    = false;

    // --- Vẽ/Hiển thị ---
    ax::Node* _gridRoot = nullptr;  // node chứa toàn bộ lưới
    float _cell         = 100.0f;
    float _gap          = 10.0f;
    ax::Vec2 _originBoard;
    LayerColor* bgColor;
    struct CellVisual
    {
        ax::Node* container = nullptr;  // node cha để animate pop
        ax::DrawNode* bg    = nullptr;
        ax::ui::Text* label    = nullptr;
    };
    std::array<std::array<CellVisual, GRID>, GRID> _visuals{};

    // --- Input ---
    ax::Vec2 _touchStart;

    // --- UI ---
    ax::ui::Text* _scoreLabel        = nullptr;
    ax::ui::Text* _bestLabel      = nullptr;
    ax::ui::Text* _overLabel       = nullptr;
    ax::ui::Button* _btnRestart   = nullptr;
    ax::ui::Button* _btnUndo      = nullptr;
    ax::ui::Button* _btnSkin      = nullptr;
    ax::ui::Button* _btnPause     = nullptr;
    ax::LayerColor* _pauseOverlay = nullptr;

    // --- Theme/Skin ---
    struct Theme
    {
        ax::Color4B sceneBg;
        ax::Color4B boardFrame;
        ax::Color4B emptyCell;
        ax::Color4B textDark;
        ax::Color4B textLight;
        std::function<ax::Color4B(int)> tileColor;  // theo giá trị tile
    };
    std::vector<Theme> _themes;
    int _themeIndex = 0;

    // --- Ghi nhớ hiệu ứng ---
    std::vector<std::pair<int, int>> _mergedToPop;  // (r,c) sau khi move kết thúc
    std::pair<int, int> _lastSpawn{-1, -1};

    // --- Khởi tạo/Vẽ ---
    
    void buildGrid();
    void updateVisuals();
    void updateScore();
    void updateBest();

    // --- Core 2048 ---
    bool canMove() const;
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool spawnRandomTile();

    // trợ giúp cho move
    bool compressMergeLine(std::array<int, GRID>& line, int& gainedScore, std::vector<int>& mergedIdx);

    // --- Input handlers ---
    void onKey(ax::EventKeyboard::KeyCode code, ax::Event* e);

    // --- Tiện ích ---
    ax::Color4B colorFor(int v) const;
    void drawCellBG(ax::DrawNode* dn, const ax::Size& size, const ax::Color4B& c);
    static int randInt(int a, int b);
    ax::Vec2 cellPosition(int r, int c) const;

    // --- Animations (pop/slide) ---
    void popAt(int r, int c, float s = 1.12f);
    void animateSpawn();
    void animateMerges();

    struct MoveOp
    {
        int r0, c0, r1, c1, val;
        bool willMerge = false;
    };
    void planMoveLeft(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained);
    void planMoveRight(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained);
    void planMoveUp(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained);
    void planMoveDown(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained);
    void runSlideAnimation(const std::vector<MoveOp>& ops,
                           const std::array<std::array<int, GRID>, GRID>& next,
                           int addScore);

    // --- Theme ---
    void buildThemes();
    void applyTheme();

    // --- Persistence ---
    void saveBest();
    void loadBest();
    void saveTheme();
    void loadTheme();
    void saveContinueState();
    bool loadContinueState();
    static std::string boardToString(const std::array<std::array<int, GRID>, GRID>& b);
    static bool stringToBoard(const std::string& s, std::array<std::array<int, GRID>, GRID>& out);

    // --- Pause ---
    void togglePause();

    // --- Audio ---
    int _sndMove = -1, _sndMerge = -1, _sndSpawn = -1, _sndGameOver = -1;
    void preloadAudio();
    void playMove();
    void playMerge();
    void playSpawn();
    void playGameOver();

    // --- 2048 milestone sound ---
    int _maxTileAchieved = 0;
    int getCurrentMaxTile() const;
    void checkAndPlayMilestoneSound();

    // --- Game over effect ---
    void runGameOverGrayOut(const std::function<void()>& onComplete);

public:
    static std::string className;
};
