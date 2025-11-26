
// =============================
// File: GUI2048.cpp
// =============================
#include "GUI2048.h"
#include <algorithm>
#include <sstream>
#include <Game/Utility/GameUtility.h>
#include <Game/Utility/GameSound.h>
#include <Game/GUIManager.h>
#define BTN_BACK_ID 0
#define BTN_SOUND_ID 1

using namespace ax;

// RNG
static std::mt19937& rng()
{
    static std::mt19937 g{std::random_device{}()};
    return g;
}
int GUI2048::randInt(int a, int b)
{
    std::uniform_int_distribution<int> d(a, b);
    return d(rng());
}

GUI2048::GUI2048(void) : BaseGUI()
{
    BaseGUI();
    Node::onEnter();
    setKeypadEnabled(true);
}

GUI2048::~GUI2048(void) {}

void GUI2048::initGUI()
{
    // if (!Scene::init())
    //  return false;
    BaseGUI::initGUI();
    buildThemes();
    loadTheme();
    // Nền scene theo theme
    bgColor = LayerColor::create(_themes[_themeIndex].sceneBg);
    this->addChild(bgColor);

    auto vs   = Director::getInstance()->getVisibleSize();
    auto org  = Director::getInstance()->getVisibleOrigin();
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

    // Buttons
    auto mkBtn = [&](const std::string& text) {
        auto b = ui::Button::create();
        b->setTitleFontName("fonts/tahoma.ttf");
        b->setTitleText(text);
        b->setTitleFontSize(20);
        b->setScale9Enabled(true);
        b->setContentSize(Size(120, 42));
        b->setTitleAlignment(TextHAlignment::CENTER);
        b->setZoomScale(0.05f);
        return b;
    };

    _btnRestart = mkBtn("Restart");
    _btnRestart->setPosition(Vec2(org.x + vs.width * 0.20f, btnBack->getPositionY() - 60));
    addChild(_btnRestart);
    _btnRestart->addClickEventListener([&](Object*) {
        game->showAdsFull();
        newGame(true);
    });

    _btnUndo = mkBtn("Undo");
    _btnUndo->setPosition(Vec2(org.x + vs.width * 0.62f, _btnRestart->getPositionY()));
    addChild(_btnUndo);
    _btnUndo->addClickEventListener([&](Object*) {
        if (!_history.empty())
        {
            auto s = _history.back();
            _history.pop_back();
            _board    = s.board;
            _score    = s.score;
            _gameOver = false;
            updateScore();
            updateVisuals();
            saveContinueState();
        }
    });

    _btnSkin = mkBtn("Skin");
    _btnSkin->setPosition(Vec2(org.x + vs.width * 0.86f, _btnRestart->getPositionY()));
    addChild(_btnSkin);
    _btnSkin->addClickEventListener([&](Object*) {
        _themeIndex = (_themeIndex + 1) % (int)_themes.size();
        applyTheme();
        saveTheme();
        updateVisuals();
    });

    _btnPause = mkBtn("Pause");
    _btnPause->setPosition(Vec2(org.x + vs.width * 0.41f, _btnRestart->getPositionY()));
    addChild(_btnPause);
    _btnPause->addClickEventListener([&](Object*) { togglePause(); });

    // Pause overlay
    _pauseOverlay = LayerColor::create(Color4B(0, 0, 0, 120));
    _pauseOverlay->setContentSize(vs);
    _pauseOverlay->setPosition(org);
    _pauseOverlay->setVisible(false);
    addChild(_pauseOverlay, 20);
    auto lblPause = Text::create("PAUSED \nTap Resume", "fonts/tahomabd.ttf", 36);
    lblPause->setTextHorizontalAlignment(TextHAlignment::CENTER);
    lblPause->setPosition(Vec2(org.x + vs.width * 0.5f, org.y + vs.height * 0.55f));
    _pauseOverlay->addChild(lblPause);
    auto btnResume = mkBtn("Resume");
    btnResume->setPosition(Vec2(org.x + vs.width * 0.5f, org.y + vs.height * 0.45f));
    _pauseOverlay->addChild(btnResume);
    btnResume->addClickEventListener([&](Object*) { togglePause(); });

    _scoreLabel = Text::create("Score: 0", "fonts/tahomabd.ttf", 26);
    _scoreLabel->setColor(Color3B(119, 110, 101));
    _scoreLabel->setPosition(
        Vec2(org.x + vs.width * 0.5f, _btnPause->getPositionY() - _btnPause->getContentSize().height));
    addChild(_scoreLabel);

    _bestLabel = Text::create("Best: 0", "fonts/tahomabd.ttf", 22);
    _bestLabel->setColor(Color3B(119, 110, 101));
    _bestLabel->setPosition(Vec2(org.x + vs.width * 0.5f, _scoreLabel->getPositionY() - 30));
    addChild(_bestLabel);

    // Kích thước lưới co theo màn hình
    float lY     = _bestLabel->getPositionY() - _bestLabel->getContentSize().height;
    float height = (lY - vs.height * 0.15);
    float area   = std::min(vs.width, height) * 0.96f;
    _gap         = std::floor(area * 0.012f);  // khe
    _cell        = std::floor((area - _gap * (GRID + 1)) / GRID);

    float boardW = _cell * GRID + _gap * (GRID + 1);
    float boardH = boardW;  // vuông
    _originBoard = {org.x + (vs.width - boardW) * 0.5f + _gap, org.y + (lY - boardH)};

    // Game over label (ẩn ban đầu)
    _overLabel = Text::create("GAME OVER \nTap/Click to Restart", "fonts/tahomabd.ttf", 30);
    _overLabel->setTextHorizontalAlignment(TextHAlignment::CENTER);
    _overLabel->setTextColor(Color4B(119, 110, 101, 255));
    _overLabel->setPosition(Vec2(org.x + vs.width * 0.5f, org.y + vs.height * 0.5f));
    _overLabel->setVisible(false);
    addChild(_overLabel, 10);

    buildGrid();
    loadBest();

    preloadAudio();

   

    // Input: bàn phím
    auto key          = EventListenerKeyboard::create();
    key->onKeyPressed = AX_CALLBACK_2(GUI2048::onKey, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(key, this);
}

void GUI2048::showGUI(Node* parent /* = NULL */, bool hasFog /* = true */)
{
    BaseGUI::showGUI(parent, hasFog);
    // Nếu có save tạm, tiếp tục; không thì ván mới
    if (!loadContinueState())
        newGame(true);
}
    // ---------------- UI / Grid ----------------

void GUI2048::buildGrid()
{
    if (_gridRoot)
        _gridRoot->removeFromParent();
    _gridRoot = Node::create();
    addChild(_gridRoot);

    // Khung nền bảng theo theme
    auto frame = DrawNode::create();
    frame->setName("__frame");
    _gridRoot->addChild(frame, 0);

    // Tạo 16 ô và label sẵn
    for (int r = 0; r < GRID; ++r)
    {
        for (int c = 0; c < GRID; ++c)
        {
            auto cellNode = Node::create();
            cellNode->setContentSize(Size(_cell, _cell));
            cellNode->setPosition(cellPosition(r, c));
            _gridRoot->addChild(cellNode, 1);

            auto bg = DrawNode::create();
            cellNode->addChild(bg);
            bg->setPosition(-_cell * 0.5, -_cell * 0.5);

            auto label = Text::create("", "fonts/tahomabd.ttf", _cell * 0.4f);
            label->setAnchorPoint(Vec2(0.5f, 0.5f));
            // label->setPosition(Vec2(_cell * 0.5f, _cell * 0.5f));
            label->setColor(Color3B::WHITE);
            cellNode->addChild(label, 1);

            _visuals[r][c] = {cellNode, bg, label};
        }
    }

    applyTheme();
}

Vec2 GUI2048::cellPosition(int r, int c) const
{
    float x = _originBoard.x + (c + 0.5) * (_cell + _gap);
    float y = _originBoard.y + (GRID - 1 - r + 0.5) * (_cell + _gap);  // r=0 là hàng dưới
    // return _originBoard;
    return Vec2(x, y);
}

void GUI2048::drawCellBG(DrawNode* dn, const Size& size, const Color4B& c)
{
    dn->clear();
    dn->drawSolidRect(Vec2::ZERO, Vec2(size.width, size.height), Color4F(c));
}

ax::Color4B GUI2048::colorFor(int v) const
{
    return _themes[_themeIndex].tileColor(v);
}

void GUI2048::updateScore()
{
    std::ostringstream ss;
    ss << "Score: " << _score;
    _scoreLabel->setString(ss.str());
    if (_score > _bestScore)
    {
        _bestScore = _score;
        updateBest();
        saveBest();
    }
}

void GUI2048::updateBest()
{
    std::ostringstream ss;
    ss << "Best: " << _bestScore;
    _bestLabel->setString(ss.str());
}

void GUI2048::updateVisuals()
{
    // Vẽ khung
    auto frame            = dynamic_cast<DrawNode*>(_gridRoot->getChildByName("__frame"));
    const float boardSize = _cell * GRID + _gap * (GRID + 1);
    frame->clear();
    frame->drawSolidRect(Vec2(_originBoard.x - _gap, _originBoard.y - _gap),
                         Vec2(_originBoard.x  + boardSize, _originBoard.y  + boardSize),
                         Color4F(_themes[_themeIndex].boardFrame));

    // Vẽ từng cell
    for (int r = 0; r < GRID; ++r)
    {
        for (int c = 0; c < GRID; ++c)
        {
            int v     = _board[r][c];
            auto& vis = _visuals[r][c];
            drawCellBG(vis.bg, Size(_cell, _cell), v ? colorFor(v) : _themes[_themeIndex].emptyCell);

            if (v == 0)
            {
                vis.label->setString("");
            }
            else
            {
                vis.label->setString(std::to_string(v));
                if (v <= 4)
                    vis.label->setTextColor(_themes[_themeIndex].textDark);
                else
                    vis.label->setTextColor(_themes[_themeIndex].textLight);

                int digits  = (int)std::to_string(v).size();
                float scale = 0.5f;
                if (digits == 1)
                    scale = 0.6f;
                else if (digits == 2)
                    scale = 0.5f;
                else if (digits == 3)
                    scale = 0.42f;
                else
                    scale = 0.36f;
                vis.label->setFontSize(_cell * scale);
                // vis.label->setPosition(Vec2(_cell * 0.5f, _cell * 0.5f));
            }
        }
    }

    if (!canMove())
    {
        _gameOver = true;
        //_overLabel->setVisible(true);
        // playGameOver();
        runAction(
            Sequence::create(
                DelayTime::create(2.0f),
                CallFunc::create(AX_CALLBACK_0(GUI2048::endGame, this)),
                NULL
            ));
        GameSound::playSoundLose();
        
    }
}

void GUI2048::endGame()
{
    // Play pre-result effect: sequential gray-out of tiles, then show result
    runGameOverGrayOut([this]() {
        GUIManager::getInstance().guiResult->showGUI(_score, _bestScore);
    });
}

// ---------------- Game lifecycle ----------------

void GUI2048::newGame(bool forceReset)
{
    GameSound::playStartGame();
    if (!forceReset && loadContinueState())
    {
        updateScore();
        updateBest();
        updateVisuals();
        _maxTileAchieved = getCurrentMaxTile();
        return;
    }

    for (auto& row : _board)
        row.fill(0);
    _score    = 0;
    _gameOver = false;
    _history.clear();
    _mergedToPop.clear();
    _lastSpawn = {-1, -1};
    _maxTileAchieved = 0;
    updateScore();
    updateBest();

    spawnRandomTile();
    spawnRandomTile();
    updateVisuals();
    animateSpawn();
    saveContinueState();
}

// ---------------- 2048 logic (tính toán) ----------------

bool GUI2048::canMove() const
{
    for (int r = 0; r < GRID; ++r)
        for (int c = 0; c < GRID; ++c)
            if (_board[r][c] == 0)
                return true;
    for (int r = 0; r < GRID; ++r)
        for (int c = 0; c < GRID - 1; ++c)
            if (_board[r][c] == _board[r][c + 1])
                return true;
    for (int c = 0; c < GRID; ++c)
        for (int r = 0; r < GRID - 1; ++r)
            if (_board[r][c] == _board[r + 1][c])
                return true;
    return false;
}

bool GUI2048::spawnRandomTile()
{
    std::vector<std::pair<int, int>> empty;
    for (int r = 0; r < GRID; ++r)
        for (int c = 0; c < GRID; ++c)
            if (_board[r][c] == 0)
                empty.emplace_back(r, c);

    if (empty.empty())
        return false;

    auto [r, c]  = empty[randInt(0, (int)empty.size() - 1)];
    _board[r][c] = (randInt(0, 9) == 0) ? 4 : 2;  // 10% là 4
    _lastSpawn   = {r, c};
    return true;
}

bool GUI2048::compressMergeLine(std::array<int, GRID>& line, int& gainedScore, std::vector<int>& mergedIdx)
{
    bool changed = false;
    gainedScore  = 0;
    mergedIdx.clear();
    std::array<int, GRID> tmp{};
    int idx = 0;
    for (int i = 0; i < GRID; ++i)
        if (line[i] != 0)
            tmp[idx++] = line[i];
    if (tmp != line)
    {
        line    = tmp;
        changed = true;
    }
    for (int i = 0; i < GRID - 1; ++i)
    {
        if (line[i] != 0 && line[i] == line[i + 1])
        {
            line[i] *= 2;
            gainedScore += line[i];
            mergedIdx.push_back(i);
            for (int k = i + 1; k < GRID - 1; ++k)
                line[k] = line[k + 1];
            line[GRID - 1] = 0;
            changed        = true;
        }
    }
    return changed;
}

// 4 hàm planMove tạo danh sách MoveOp và next-board (chưa set ngay), cũng tính score tăng
void GUI2048::planMoveLeft(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained)
{
    next   = _board;
    gained = 0;
    ops.clear();
    _mergedToPop.clear();
    for (int r = 0; r < GRID; ++r)
    {
        std::array<int, GRID> line{};
        for (int c = 0; c < GRID; ++c)
            line[c] = next[r][c];
        std::array<int, GRID> before = line;
        int g                        = 0;
        std::vector<int> mIdx;
        bool ch = compressMergeLine(line, g, mIdx);
        if (!ch)
            continue;
        // map từ before -> after để sinh MoveOp
        int dst = 0;  // vị trí đích đang lấp
        for (int c = 0; c < GRID; ++c)
        {
            if (before[c] == 0)
                continue;
            int v = before[c];
            // tìm đích trong line: duyệt từ dst tới GRID-1 tìm phần tử khớp tạo bởi nén/gộp
            while (dst < GRID && line[dst] == 0)
                dst++;
            if (dst >= GRID)
                break;
            // nếu có merge tại dst (mIdx chứa dst), giá trị line[dst] có thể = v*2
            bool willMerge = false;
            if (!mIdx.empty())
            {
                for (int id : mIdx)
                    if (id == dst)
                    {
                        willMerge = (line[dst] == v * 2);
                        break;
                    }
            }
            ops.push_back({r, c, r, dst, v, willMerge});
            dst++;
        }
        // ghi next row = line
        for (int c = 0; c < GRID; ++c)
            next[r][c] = line[c];
        gained += g;
        for (int id : mIdx)
            _mergedToPop.emplace_back(r, id);
    }
}
void GUI2048::planMoveRight(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained)
{
    next   = _board;
    gained = 0;
    ops.clear();
    _mergedToPop.clear();
    for (int r = 0; r < GRID; ++r)
    {
        std::array<int, GRID> line{};
        for (int c = 0; c < GRID; ++c)
            line[c] = next[r][GRID - 1 - c];
        std::array<int, GRID> before = line;
        int g                        = 0;
        std::vector<int> mIdx;
        bool ch = compressMergeLine(line, g, mIdx);
        if (!ch)
            continue;
        int dst = 0;
        for (int c = 0; c < GRID; ++c)
        {
            if (before[c] == 0)
                continue;
            int v = before[c];
            while (dst < GRID && line[dst] == 0)
                dst++;
            if (dst >= GRID)
                break;
            bool willMerge = false;
            for (int id : mIdx)
                if (id == dst)
                {
                    willMerge = (line[dst] == v * 2);
                    break;
                }
            int colTo   = GRID - 1 - dst;
            int colFrom = GRID - 1 - c;
            ops.push_back({r, colFrom, r, colTo, v, willMerge});
            dst++;
        }
        for (int c = 0; c < GRID; ++c)
            next[r][GRID - 1 - c] = line[c];
        gained += g;
        for (int id : mIdx)
            _mergedToPop.emplace_back(r, GRID - 1 - id);
    }
}
void GUI2048::planMoveUp(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained)
{
    next   = _board;
    gained = 0;
    ops.clear();
    _mergedToPop.clear();
    for (int c = 0; c < GRID; ++c)
    {
        std::array<int, GRID> line{};
        for (int r = 0; r < GRID; ++r)
            line[r] = next[GRID - 1 - r][c];
        std::array<int, GRID> before = line;
        int g                        = 0;
        std::vector<int> mIdx;
        bool ch = compressMergeLine(line, g, mIdx);
        if (!ch)
            continue;
        int dst = 0;
        for (int r = 0; r < GRID; ++r)
        {
            if (before[r] == 0)
                continue;
            int v = before[r];
            while (dst < GRID && line[dst] == 0)
                dst++;
            if (dst >= GRID)
                break;
            bool willMerge = false;
            for (int id : mIdx)
                if (id == dst)
                {
                    willMerge = (line[dst] == v * 2);
                    break;
                }
            int rowTo   = GRID - 1 - dst;
            int rowFrom = GRID - 1 - r;
            ops.push_back({rowFrom, c, rowTo, c, v, willMerge});
            dst++;
        }
        for (int r = 0; r < GRID; ++r)
            next[GRID - 1 - r][c] = line[r];
        gained += g;
        for (int id : mIdx)
            _mergedToPop.emplace_back(GRID - 1 - id, c);
    }
}
void GUI2048::planMoveDown(std::vector<MoveOp>& ops, std::array<std::array<int, GRID>, GRID>& next, int& gained)
{
    next   = _board;
    gained = 0;
    ops.clear();
    _mergedToPop.clear();
    for (int c = 0; c < GRID; ++c)
    {
        std::array<int, GRID> line{};
        for (int r = 0; r < GRID; ++r)
            line[r] = next[r][c];
        std::array<int, GRID> before = line;
        int g                        = 0;
        std::vector<int> mIdx;
        bool ch = compressMergeLine(line, g, mIdx);
        if (!ch)
            continue;
        int dst = 0;
        for (int r = 0; r < GRID; ++r)
        {
            if (before[r] == 0)
                continue;
            int v = before[r];
            while (dst < GRID && line[dst] == 0)
                dst++;
            if (dst >= GRID)
                break;
            bool willMerge = false;
            for (int id : mIdx)
                if (id == dst)
                {
                    willMerge = (line[dst] == v * 2);
                    break;
                }
            ops.push_back({r, c, dst, c, v, willMerge});
            dst++;
        }
        for (int r = 0; r < GRID; ++r)
            next[r][c] = line[r];
        gained += g;
        for (int id : mIdx)
            _mergedToPop.emplace_back(id, c);
    }
}

// Chạy animation trượt: tạo "ghost tiles" di chuyển từ from -> to; sau khi xong thì set bảng mới & hiệu ứng pop/spawn
void GUI2048::runSlideAnimation(const std::vector<MoveOp>& ops,
                                const std::array<std::array<int, GRID>, GRID>& next,
                                int addScore)
{
    if (ops.empty())
        return;  // nothing to animate

    _animating = true;

    // tạo ghost cho từng op
    Vector<Node*> ghosts;
    float maxDur = 0.f;

    for (auto& op : ops)
    {
        int v     = _board[op.r0][op.c0];
        auto& vis = _visuals[op.r0][op.c0];
        drawCellBG(vis.bg, Size(_cell, _cell), _themes[_themeIndex].emptyCell);
        vis.label->setString("");

        auto ghost = Node::create();
        ghost->setPosition(cellPosition(op.r0, op.c0));
        auto bg  = DrawNode::create();
        auto lbl = Text::create(std::to_string(op.val), "fonts/tahomabd.ttf", _cell * 0.5f);
        lbl->setAnchorPoint(Vec2(0.5f, 0.5f));
        bg->setPosition(Vec2(-_cell * 0.5f, -_cell * 0.5f));
        // lbl->setPosition(Vec2(_cell * 0.5f, _cell * 0.5f));
        lbl->setTextColor(op.val <= 4 ? _themes[_themeIndex].textDark : _themes[_themeIndex].textLight);
        ghost->addChild(bg);
        ghost->addChild(lbl);
        _gridRoot->addChild(ghost, 5);
        bg->drawSolidRect(Vec2::ZERO, Vec2(_cell, _cell), Color4F(colorFor(op.val)));

        Vec2 to    = cellPosition(op.r1, op.c1);
        float dist = (to - ghost->getPosition()).length();
        float dur  = 0.06f + 0.04f * (dist / (_cell + _gap));  // khoảng 0.1s mỗi vài ô
        if (dur > maxDur)
            maxDur = dur;
        ghost->runAction(MoveTo::create(dur, to));
        ghosts.pushBack(ghost);
    }

    // chơi âm thanh move
    playMove();

    // Sau khi tất cả hoàn tất, cập nhật state thật
    runAction(Sequence::create(DelayTime::create(maxDur), CallFunc::create([=] {
        for (auto g : ghosts)
            g->removeFromParent();
        _board = next;
        _score += addScore;
        updateScore();
        updateVisuals();  // vẽ giá trị gộp
        animateMerges();  // pop ô gộp
        checkAndPlayMilestoneSound();
        spawnRandomTile();
        updateVisuals();
        animateSpawn();
        saveContinueState();
        _animating = false;
    }),
                               nullptr));
}

// ---------------- Animations ----------------

void GUI2048::popAt(int r, int c, float s)
{
    auto n = _visuals[r][c].container;
    if (!n)
        return;
    n->stopAllActions();
    n->setScale(1.0f);
    n->runAction(Sequence::create(ScaleTo::create(0.06f, s), ScaleTo::create(0.08f, 1.0f), nullptr));
}

void GUI2048::animateSpawn()
{
    if (_lastSpawn.first < 0)
        return;
    auto [r, c] = _lastSpawn;
    auto n      = _visuals[r][c].container;
    if (!n)
        return;
    n->stopAllActions();
    n->setScale(0.0f);
    n->runAction(ScaleTo::create(0.12f, 1.0f));
    playSpawn();
}

void GUI2048::animateMerges()
{
    if (_mergedToPop.empty())
        return;
    playMerge();
    for (auto& rc : _mergedToPop)
        popAt(rc.first, rc.second, 1.18f);
}

// ---------------- Input ----------------

void GUI2048::onKey(EventKeyboard::KeyCode code, Event*)
{
    if (_gameOver || _animating)
        return;

    if (code == EventKeyboard::KeyCode::KEY_P)
    {
        togglePause();
        return;
    }
    if (_paused)
        return;

    // Undo bằng phím U
    if (code == EventKeyboard::KeyCode::KEY_U)
    {
        if (!_history.empty())
        {
            auto s = _history.back();
            _history.pop_back();
            _board    = s.board;
            _score    = s.score;
            _gameOver = false;
            updateScore();
            updateVisuals();
            saveContinueState();
        }
        return;
    }

    // Tính kế hoạch slide trước, nếu không thay đổi thì bỏ
    std::vector<MoveOp> ops;
    std::array<std::array<int, GRID>, GRID> next;
    int gained   = 0;
    bool changed = false;
    switch (code)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        planMoveLeft(ops, next, gained);
        changed = !ops.empty();
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        planMoveRight(ops, next, gained);
        changed = !ops.empty();
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        planMoveUp(ops, next, gained);
        changed = !ops.empty();
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        planMoveDown(ops, next, gained);
        changed = !ops.empty();
        break;
    default:
        break;
    }

    if (changed)
    {
        // push vào history
        _history.push_back({_board, _score});
        if ((int)_history.size() > _undoLimit)
            _history.pop_front();
        runSlideAnimation(ops, next, gained);
    }
}

bool GUI2048::onTouchBegan(Touch* t, Event* event)
{
    _touchStart = t->getLocation();
    return BaseGUI::onTouchBegan(t, event);
}

void GUI2048::onTouchEnded(Touch* t, Event* event)
{
    if (_gameOver || _animating || _paused)
        return BaseGUI::onTouchEnded(t, event);
    Vec2 d   = t->getLocation() - _touchStart;
    float th = 12.0f;
    if (d.length() < th)
        return BaseGUI::onTouchEnded(t, event);

    std::vector<MoveOp> ops;
    std::array<std::array<int, GRID>, GRID> next;
    int gained   = 0;
    bool changed = false;
    if (std::abs(d.x) > std::abs(d.y))
    {
        if (d.x > 0)
        {
            planMoveRight(ops, next, gained);
        }
        else
        {
            planMoveLeft(ops, next, gained);
        }
    }
    else
    {
        if (d.y > 0)
        {
            planMoveDown(ops, next, gained);
        }
        else
        {
            planMoveUp(ops, next, gained);
        }
    }
    changed = !ops.empty();

    if (changed)
    {
        _history.push_back({_board, _score});
        if ((int)_history.size() > _undoLimit)
            _history.pop_front();
        runSlideAnimation(ops, next, gained);
    }
    BaseGUI::onTouchEnded(t, event);
}

// ---------------- Theme/Skin ----------------

void GUI2048::buildThemes()
{
    _themes.clear();

    // Theme 0: Classic (na ná 2048)
    Theme classic;
    classic.sceneBg    = Color4B(250, 248, 239, 255);
    classic.boardFrame = Color4B(187, 173, 160, 255);
    classic.emptyCell  = Color4B(205, 193, 180, 255);
    classic.textDark   = Color4B(119, 110, 101, 255);
    classic.textLight  = Color4B::WHITE;
    classic.tileColor  = [](int v) {
        switch (v)
        {
        case 2:
            return Color4B(238, 228, 218, 255);
        case 4:
            return Color4B(237, 224, 200, 255);
        case 8:
            return Color4B(242, 177, 121, 255);
        case 16:
            return Color4B(245, 149, 99, 255);
        case 32:
            return Color4B(246, 124, 95, 255);
        case 64:
            return Color4B(246, 94, 59, 255);
        case 128:
            return Color4B(237, 207, 114, 255);
        case 256:
            return Color4B(237, 204, 97, 255);
        case 512:
            return Color4B(237, 200, 80, 255);
        case 1024:
            return Color4B(237, 197, 63, 255);
        case 2048:
            return Color4B(237, 194, 46, 255);
        default:
            return Color4B(60, 58, 50, 255);
        }
    };
    _themes.push_back(classic);

    // Theme 1: Night
    Theme night;
    night.sceneBg    = Color4B(20, 20, 24, 255);
    night.boardFrame = Color4B(40, 40, 48, 255);
    night.emptyCell  = Color4B(55, 55, 65, 255);
    night.textDark   = Color4B(220, 220, 230, 255);
    night.textLight  = Color4B(255, 255, 255, 255);
    night.tileColor  = [](int v) {
        switch (v)
        {
        case 2:
            return Color4B(80, 80, 100, 255);
        case 4:
            return Color4B(90, 90, 120, 255);
        case 8:
            return Color4B(100, 120, 180, 255);
        case 16:
            return Color4B(120, 150, 200, 255);
        case 32:
            return Color4B(140, 160, 210, 255);
        case 64:
            return Color4B(160, 170, 220, 255);
        case 128:
            return Color4B(180, 180, 230, 255);
        case 256:
            return Color4B(190, 190, 235, 255);
        case 512:
            return Color4B(200, 200, 240, 255);
        case 1024:
            return Color4B(210, 210, 245, 255);
        case 2048:
            return Color4B(220, 220, 250, 255);
        default:
            return Color4B(40, 40, 48, 255);
        }
    };
    _themes.push_back(night);
}

void GUI2048::applyTheme()
{
    bgColor->setColor(Color3B(_themes[_themeIndex].sceneBg));
    bgColor->setOpacity(_themes[_themeIndex].sceneBg.a);
    _btnPause->setTitleColor(Color3B(_themes[_themeIndex].textDark));
    _btnSkin->setTitleColor(Color3B(_themes[_themeIndex].textDark));
    _btnUndo->setTitleColor(Color3B(_themes[_themeIndex].textDark));
    _btnRestart->setTitleColor(Color3B(_themes[_themeIndex].textDark));
}

// ---------------- Persistence ----------------

static const char* K_BEST  = "g2048.best";
static const char* K_THEME = "g2048.theme";
static const char* K_BOARD = "g2048.board";
static const char* K_SCORE = "g2048.score";

void GUI2048::saveBest()
{
    UserDefault::getInstance()->setIntegerForKey(K_BEST, _bestScore);
    UserDefault::getInstance()->flush();
}
void GUI2048::loadBest()
{
    _bestScore = UserDefault::getInstance()->getIntegerForKey(K_BEST, 0);
    updateBest();
}
void GUI2048::saveTheme()
{
    UserDefault::getInstance()->setIntegerForKey(K_THEME, _themeIndex);
    UserDefault::getInstance()->flush();
}
void GUI2048::loadTheme()
{
    _themeIndex = UserDefault::getInstance()->getIntegerForKey(K_THEME, 0);
    if (_themeIndex < 0 || _themeIndex >= (int)_themes.size())
        _themeIndex = 0;
}

std::string GUI2048::boardToString(const std::array<std::array<int, GRID>, GRID>& b)
{
    std::ostringstream ss;
    bool first = true;
    for (int r = 0; r < GRID; ++r)
        for (int c = 0; c < GRID; ++c)
        {
            if (!first)
                ss << ',';
            first = false;
            ss << b[r][c];
        }
    return ss.str();
}

bool GUI2048::stringToBoard(const std::string& s, std::array<std::array<int, GRID>, GRID>& out)
{
    int vals[GRID * GRID]{};
    int idx    = 0;
    int cur    = 0;
    bool neg   = false;
    bool inNum = false;
    for (size_t i = 0; i <= s.size(); ++i)
    {
        if (i < s.size() && (isdigit((unsigned char)s[i]) || s[i] == '-'))
        {
            if (s[i] == '-')
            {
                neg = true;
            }
            else
            {
                cur   = cur * 10 + (s[i] - '0');
                inNum = true;
            }
        }
        else
        {
            if (inNum)
            {
                vals[idx++] = neg ? -cur : cur;
                cur         = 0;
                neg         = false;
                inNum       = false;
                if (idx == GRID * GRID)
                    break;
            }
        }
    }
    if (idx != GRID * GRID)
        return false;
    for (int r = 0; r < GRID; ++r)
        for (int c = 0; c < GRID; ++c)
            out[r][c] = vals[r * GRID + c];
    return true;
}

void GUI2048::saveContinueState()
{
    UserDefault::getInstance()->setStringForKey(K_BOARD, boardToString(_board));
    UserDefault::getInstance()->setIntegerForKey(K_SCORE, _score);
    UserDefault::getInstance()->flush();
}

bool GUI2048::loadContinueState()
{
    std::string s = (std::string)UserDefault::getInstance()->getStringForKey(K_BOARD, "");
    if (s.empty())
        return false;
    if (!stringToBoard(s, _board))
        return false;
    _score    = UserDefault::getInstance()->getIntegerForKey(K_SCORE, 0);
    _gameOver = !canMove();
    updateScore();
    updateVisuals();
    return true;
}

// ---------------- Pause ----------------

void GUI2048::togglePause()
{
    _paused = !_paused;
    _pauseOverlay->setVisible(_paused);
    _btnPause->setTitleText(_paused ? "Resume" : "Pause");
}

// ---------------- Audio ----------------

void GUI2048::preloadAudio()
{
    // Đặt các file này vào Resources: s_move.mp3, s_merge.mp3, s_spawn.mp3, s_over.mp3
    // Nếu thiếu file, AudioEngine sẽ im lặng.
    //  _sndMove     = AudioEngine::preload("s_move.mp3");
    //_sndMerge    = AudioEngine::preload("s_merge.mp3");
    // _sndSpawn    = AudioEngine::preload("s_spawn.mp3");
    // _sndGameOver = AudioEngine::preload("s_over.mp3");
}

void GUI2048::playMove()
{
    // if (_sndMove >= 0)
    GameSound::playMove2048();
}
void GUI2048::playMerge()
{
    GameSound::playMerge2048();
}
void GUI2048::playSpawn()
{
    GameSound::playSpawn2048();
}
void GUI2048::playGameOver()
{
    // if (_sndGameOver >= 0)
    //   AudioEngine::play2d("s_over.mp3", false, 0.8f);
    game->showAdsFull();
    GameSound::playGameOver();
}

int GUI2048::getCurrentMaxTile() const
{
    int mx = 0;
    for (int r = 0; r < GRID; ++r)
        for (int c = 0; c < GRID; ++c)
            mx = std::max(mx, _board[r][c]);
    return mx;
}

void GUI2048::checkAndPlayMilestoneSound()
{
    int mx = getCurrentMaxTile();
    if (mx <= _maxTileAchieved)
        return;
    // New milestone achieved
    _maxTileAchieved = mx;
    // Play generic new-number sound on any increase, with a special for 2048+
    if (mx >= 2048)
    {
        GameSound::playWin2048();
    }
    else
    {
        GameSound::playNewNumber2048();
    }
    // Visual glow on the cells that have the new max value
    for (int r = 0; r < GRID; ++r)
    {
        for (int c = 0; c < GRID; ++c)
        {
            if (_board[r][c] == mx)
            {
                auto n = _visuals[r][c].container;
                if (!n) continue;
                auto glow = LayerColor::create(Color4B(255, 230, 90, 160), _cell, _cell);
                glow->setPosition(Vec2(-_cell * 0.5f, -_cell * 0.5f));
                glow->setOpacity(0);
                n->addChild(glow, 0);
                glow->runAction(Sequence::create(
                    Spawn::create(
                        FadeTo::create(0.08f, 200),
                        ScaleTo::create(0.14f, 1.12f),
                        nullptr
                    ),
                    FadeOut::create(0.22f),
                    CallFunc::create([glow]() { glow->removeFromParent(); }),
                    nullptr
                ));
            }
        }
    }
}

// Sequentially gray out number cells before showing result
void GUI2048::runGameOverGrayOut(const std::function<void()>& onComplete)
{
    // Build list of visible (non-empty) cells in a simple order (top-left to bottom-right)
    std::vector<std::pair<int,int>> cells;
    cells.reserve(GRID * GRID);
    for (int r = GRID - 1; r >= 0; --r) // visual top row is r=GRID-1
    {
        for (int c = 0; c < GRID; ++c)
        {
            if (_board[r][c] != 0)
                cells.emplace_back(r, c);
        }
    }

    // If no cells or very few, just call complete immediately
    if (cells.empty())
    {
        if (onComplete) onComplete();
        return;
    }

    const float delayStep = 0.06f;
    const Color4B grayCol = Color4B(90, 90, 90, 255);
    float lastDelay = 0.0f;

    for (size_t i = 0; i < cells.size(); ++i)
    {
        //auto [r, c] = cells[i];
        int r       = cells[i].first;
        int c       = cells[i].second;
        auto vis    = _visuals[r][c];
        float d     = delayStep * static_cast<float>(i);
        lastDelay   = d;
        // For each cell: tint bg to gray and fade label a bit to simulate becoming gray
        auto act = Sequence::create(
            DelayTime::create(d),
            CallFunc::create([this, r, c, grayCol]() {
                drawCellBG(_visuals[r][c].bg, Size(_cell, _cell), grayCol);
                if (_visuals[r][c].label)
                {
                    _visuals[r][c].label->setTextColor(Color4B(200, 200, 200, 255));
                }
            }),
            nullptr);
        if (vis.container)
            vis.container->runAction(act);
    }

    // After the last one, small pause then callback
    this->runAction(Sequence::create(
        DelayTime::create(lastDelay + 0.12f),
        CallFunc::create([onComplete]() { if (onComplete) onComplete(); }),
        nullptr));
}

void GUI2048::onButtonRelease(int buttonID, Touch* touch)
{
    GameSound::playClick();
    switch (buttonID)
    {

    case BTN_BACK_ID:
    {
        onBackKey();
        /*arrayNumber[2][4]->setVisible(false);
        checkListFall();*/
    }

    break;
    case BTN_SOUND_ID:
    {

        // tutorial1();
        // curNumber->increaseNumber();
        // showEffectLabel("GuiGame/brick/iconNewBest.png");
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
    break;

    default:
        break;
    }
}

void GUI2048::onBackKey()
{
    if (GUIManager::getInstance().isCallBackPress == false && GUIManager::getInstance().getLastGui() == this)
    {
        game->changeToLandscape();
        GUIManager::getInstance().removeAllGui();
        GUIManager::getInstance().showGuiWithName(GUIMinigames::className);
        GUIManager::getInstance().isCallBackPress = true;
    }
}
std::string GUI2048::className = "GUI2048";
