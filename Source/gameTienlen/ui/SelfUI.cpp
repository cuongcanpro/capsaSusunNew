#include "SelfUI.h"
#include "../logic/GameLogic.h"
#include "BoardScene.h"
#include "core/gui/SceneMgr.h"
#include "../InGameMgr.h"
#include "core/utils/TienlenGameSound.h"

#define BTN_SELF_UI_ARRANGE 6
#define BTN_SELF_UI_CHOOSE 2
#define BTN_SELF_UI_CANCEL 3
#define BTN_SELF_UI_EMO 4
#define BTN_SELF_UI_CHAT 5

#define PADX_CARD 0.4
//#define BTN_ARRANGE 4
SelfUI::SelfUI() : PlayerUI()
{
	init();
}

SelfUI::~SelfUI()
{

}


bool SelfUI::init()
{
	BaseLayer::init();
	initWithBinaryFile("SelfUI.csb");
	return true;
}

void SelfUI::initGUI()
{
	PlayerUI::initGUI();
	initMyUI();
}

void SelfUI::initMyUI()
{
	btnArrange = customizeButton("arrange", BTN_SELF_UI_ARRANGE, bg);
	btnCancel = customizeButton("cancel", BTN_SELF_UI_CANCEL, bg);
	btnChoose = customizeButton("accept", BTN_SELF_UI_CHOOSE, bg);
	btnEmo = customizeButton("btnEmo", BTN_SELF_UI_EMO, bg);
	btnChat = customizeButton("btnChat", BTN_SELF_UI_CHAT, bg);

	arrow = (ImageView *) getControl("arrow", bg);
	panelCard = getControl("pCard", bg);

	initGroupCard();

	ImageView* bgProgress = (ImageView*)btnAvatar->getChildByName("bgProgress");
	lbLevel = (Text*)bgProgress->getChildByName("lbProgress");
	progress = (LoadingBar*)bgProgress->getChildByName("progress");
	_listener = EventListenerTouchOneByOne::create();
	//_listener->setSwallowTouches(true);

	_listener->onTouchBegan = AX_CALLBACK_2(SelfUI::onTouchBegan, this);
	_listener->onTouchMoved = AX_CALLBACK_2(SelfUI::onTouchMoved, this);
	_listener->onTouchEnded = AX_CALLBACK_2(SelfUI::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
	//setScale(_scale);
}

bool SelfUI::onTouchBegan(Touch*touch, Event* event) {
	AXLOGD("On touch began ");
	return true;
}

void SelfUI::onTouchMoved(Touch*touch, Event* event) {

}


void SelfUI::onTouchEnded(Touch*touch, Event* event) {

}

void SelfUI::initGroupCard()
{
	Vec2 posStart = Vec2(0, panelCard->getContentSize().height / 2);
	float padX = 38;
	Size size = Director::getInstance()->getVisibleSize();
	Size size1 = Director::getInstance()->getWinSize();
	float rate = size.width / 800;
	padX = 38 * rate;
	float sum = 0;
	for (int i = 0; i < NUM_CARD; i++) {
		CardButton *card = new CardButton(i + 1, this);
		card->setScale(1.03f);
		panelCard->addChild(card);
		arrayCard[i] = card;
	}
	sum = padX * (NUM_CARD - 1) + arrayCard[0]->getContentSize().width * arrayCard[0]->getScale();
	panelCard->setContentSize(Size(sum, panelCard->getContentSize().height));
	panelCard->setPositionX(-sum * 0.5 + bg->getContentSize().width * 0.5);
	for (int i = 0; i < NUM_CARD; i++) {
		CardButton *card = arrayCard[i];
		card->setPosition(Vec2(posStart.x + card->getContentSize().width * 0.5 * card->getScale() + i * padX, posStart.y));
		card->setPosDefaultY(card->getPositionY());
		card->setPosDefaultX(card->getPositionX());
	}
	panelCard->setVisible(true);
	btnAvatar->setPositionX(panelCard->getPositionX() - btnAvatar->getContentSize().width * 0.8);
	btnArrange->setPositionX(panelCard->getPositionX() + panelCard->getContentSize().width + btnArrange->getContentSize().width * 0.8);
	pEffect->setPositionX(btnAvatar->getPositionX());
}

void SelfUI::newGame()
{
	PlayerUI::newGame();
	btnArrange->setVisible(false);
	btnCancel->setVisible(false);
	btnChoose->setVisible(false);
	
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setVisible(false);
		arrayCard[i]->setIdCard(52);
	}
	normalAllPosition();
	updateLevel();
}

void SelfUI::updateDealCard(int num)
{
	arrayCard[num]->setIdCard(52);
	arrayCard[num]->setVisible(true);
}

void SelfUI::endDealCard()
{
	PlayerInfo *info = GameLogic::getInstance()->getInfo(0);
	if (info->arrayCard.size() == 0)
		return;
	for (int i = 0; i < info->arrayCard.size(); i++) {
		if (i >= info->arrayCard.size()) {
			arrayCard[i]->setVisible(false);
		}
		else {
			arrayCard[i]->setVisible(true);
			arrayCard[i]->setIdCard(info->arrayCard.at(i));
		}
	}
	sortCard(true);
	btnArrange->setVisible(true);
	//updateCard();
}


void SelfUI::updateCard()
{
	PlayerInfo *info = GameLogic::getInstance()->getInfo(0);
	vector <char> arrayId;
	vector <Vec2> arrayPos;
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setVisible(false);
		arrayCard[i]->setSelect(false);
		if (info->haveCard(arrayCard[i]->id)) {
			arrayId.push_back(arrayCard[i]->id);
			arrayPos.push_back(arrayCard[i]->getPosition());
		}
	}
	for (int i = 0; i < info->arrayCard.size(); i++) {
		arrayCard[i]->setVisible(true);
		arrayCard[i]->setIdCard(info->arrayCard.at(i));
		if (i < arrayId.size()) {
			for (int j = 0; j < arrayId.size(); j++) {
				if (arrayId[j] == info->arrayCard[i]) {
					arrayCard[i]->setPosition(arrayPos.at(j));
					break;
				}
			}
		}
		else {
			arrayCard[i]->setPosition(Vec2(0, 0));
		}
		// co the thuc hien hieu ung di chuyen tu vi tri hien tai don qua ben trai o day
		arrayCard[i]->stopAllActions();
		arrayCard[i]->runAction(MoveTo::create(0.2f, Vec2(arrayCard[i]->posDefaultX, arrayCard[i]->posDefaultY)));
	}
	
}


void SelfUI::changeTurn(int time)
{
	TienlenGameSound::playDenLuot();
	PlayerUI::changeTurn(time);
	//DBArmatureNode *effIcon = DBFactory::getInstance()->buildArmatureNode("Vaoban");
	//if (effIcon) {
	//	pEffect->addChild(effIcon);
	//	//effIcon->setScale(_scale);
	//	effIcon->getAnimation()->gotoAndPlay("vaoban", -1, -1, 1);
	//	effIcon->setPosition(pEffect->getContentSize().width * 0.5, pEffect->getContentSize().height * 0.5);
	//	effIcon->runAction(
	//		Sequence::create(
	//			DelayTime::create(2),
	//			RemoveSelf::create(),
	//			NULL
	//		)
	//	);
	//}

	if (GameLogic::getInstance()->lastCard->GetNumOfCards() == 0) {
		setEnableButton(btnCancel, true, false);
		setEnableButton(btnChoose, true, true);
		if (!checkCanThrowCard()) {
			if (getArraySelect().size() > 0)
				normalAllPosition();
		}
	}
	else {
		setEnableButton(btnCancel, true, true);
		if (GameLogic::getInstance()->CanPlayVsLastCard()) {
			setEnableButton(btnChoose, true, true);
			if (!checkCanThrowCard()) {
				if (getArraySelect().size() > 0)
					normalAllPosition();
			}
		}
		else {
			setEnableButton(btnChoose, true, false);
			showArrowButton(true, btnCancel->getPositionX());
		}
	}
	//showButtonTurn(true);
}

void SelfUI::endTurnCard()
{
	setEnableButton(btnChoose, false, false);
	setEnableButton(btnCancel, false, false);
	showArrowButton(false, 0);
}

/**
 * Thuc hien khi nguoi choi co the danh bo luot
 */
void SelfUI::showAutoTurn()
{
	setEnableButton(btnChoose, true, true);
	setEnableButton(btnCancel, true, false);
	checkCanThrowCard();
}

void SelfUI::showCancel(bool show)
{
	PlayerUI::showCancel(show);
	endTurnCard();
}

void SelfUI::getRank(char rank, bool isCong)
{
	PlayerUI::getRank(rank, isCong);
	setEnableButton(btnCancel, false, false);
	setEnableButton(btnChoose, false, false);
	btnArrange->setVisible(false);
	arrow->setVisible(false);
}

/**
 * Ham thuc hien kiem tra nhung quan Card dang duoc chon co hop le hay khong
 * Thuc hien moi khi den Turn nguoi choi, auto danh, nguoi choi chon quan bai
 */
bool SelfUI::checkCanThrowCard()
{
	// neu da kiem tra truoc do khong the danh bo bai cuoi cung thi dung luon, khong phai set lai trang thai cua Arrow
	if (!GameLogic::getInstance()->CanPlayVsLastCard())
		return false;
	vector <int> arraySelect = getArraySelect();
	if (GameLogic::getInstance()->checkCanThrowCard(arraySelect)) {
		if (btnChoose->isVisible())
			showArrowButton(true, btnChoose->getPositionX());
		return true;
	}
	arrow->setVisible(false);
	return false;
}

Vec2 SelfUI::getCardPosById(int id)
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard[i]->id == id) {
			return panelCard->convertToWorldSpace(arrayCard[i]->getPosition());
		}
	}
	return Vec2(0, 0);
}

void SelfUI::setEnableButton(Button* button, bool show, bool enable)
{
	button->setVisible(show);
	button->setTouchEnabled(enable);
	if (enable) {
		button->setColor(Color3B(255, 255, 255));
	}
	else {
		button->setColor(Color3B(150, 150, 150));
	}
}

void SelfUI::showArrowButton(bool show, float posX)
{
	arrow->setVisible(show);
	if (show) {
		arrow->setPositionY(btnCancel->getPositionY() + 50);
		arrow->setPositionX(posX);
		arrow->stopAllActions();
		arrow->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.2f, Vec2(0, 5)), MoveBy::create(0.2, Vec2(0, -5)), NULL)));
	}
	
}

void SelfUI::normalAllPosition()
{
	AXLOGD("NORMAL ALL POSITION CARD");
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setDefaultPos();
	}
}

void SelfUI::hideAllButton()
{
	btnCancel->setVisible(false);
	btnChoose->setVisible(false);
	arrow->setVisible(false);
}

void SelfUI::sortCard(bool isSortNormal)
{
	normalAllPosition();
	PlayerInfo* info = GameLogic::getInstance()->getInfo(0);
	info->sortCard(isSortNormal);
	updateCard();
}

std::vector <int> SelfUI::getArraySelect()
{
	vector <int> arraySelect;
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard[i]->isVisible() && arrayCard[i]->IsSelect()) {
			arraySelect.push_back(arrayCard[i]->id);
		}
	}
	return arraySelect;
}

void SelfUI::autoCard(vector <int> arrayId)
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard[i]->isVisible()) {
			for (int j = 0; j < arrayId.size(); j++) {
				if (arrayCard[i]->id == arrayId.at(j)) {
					arrayCard[i]->setSelect(true);
				}
			}
		}
	}
	if (arrayId.size() >= 4) {
		//TienlenGameSound::playSoundBoBai();
	}
}

Size SelfUI::getCardSize()
{
	return Size(arrayCard[0]->getContentSize().width * _scale * arrayCard[0]->getScale(), arrayCard[0]->getContentSize().height * _scale * arrayCard[0]->getScale());
}

Vec2 SelfUI::getCardPos(int index)
{
	return panelCard->convertToWorldSpace(arrayCard[index]->getPosition());
}


void SelfUI::endCard()
{
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	vector <int> cards = info->arrayCard;
	for (int i = 0; i < (int)cards.size() && i < NUM_CARD; i++) {
		arrayCard[i]->setVisible(true);
		arrayCard[i]->setIdCard(cards.at(i));
	}
	setDarkCard(true);
	
	if (GameLogic::getInstance()->isSuddenWin()) {
		endCard1();
	}
	else {
		// lam sang nhung quan card bi thoi
		endCard2();
	}
}

void SelfUI::endCard1()
{
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	TienlenGamePlayer* game = info->Game();
	if (GameLogic::getInstance()->isSuddenWin()) {
		if (info->isSuddenWin()) {
			// lam sang nhung quan card trong mang toi trang
			for (int i = 0; i < game->WinCards.size() && i < NUM_CARD; i++) {
				arrayCard[i]->setIdCard(game->WinCards.at(i));
				arrayCard[i]->setDark(false);
			}
			for (int i = game->WinCards.size(); i < NUM_CARD; i++) {
				if (i - game->WinCards.size() < game->WinExcess.size())
					arrayCard[i]->setIdCard(game->WinExcess.at(i - game->WinCards.size()));
			}
		}
	}
}

void SelfUI::endCard2()
{
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	TienlenGamePlayer* game = info->Game();

	// lam sang nhung quan card bi thoi
	for (int i = 0; i < game->WinCards.size() && i < NUM_CARD; i++) {
		arrayCard[i]->setIdCard(game->WinCards.at(i));
		arrayCard[i]->setDark(false);
	}
	for (int i = 0; i < game->WinExcess.size() && i + game->WinCards.size() < NUM_CARD; i++) {
		arrayCard[i + game->WinCards.size()]->setIdCard(game->WinExcess.at(i));
	}
}

bool SelfUI::checkCardSelectByMove(Vec2 point, int i, int index, float direct)
{
	Vec2 pointToLocal = arrayCard[i]->convertToNodeSpace(point);
	if (i == index) {
		AXLOGD("Point %f %f ", pointToLocal.x, pointToLocal.y);
	}
	else {
		if (arrayCard[i]->IsSelect() == false) {
			
		}
	}

	Rect rect = arrayCard[i]->getBoundingBox();
	rect.origin = Vec2(0, 0);
	if (rect.containsPoint(pointToLocal)) {
		if (i == index) {
			return true;
		}
		else {
			if (arrayCard[i]->IsSelect() == false) {
				arrayCard[i]->setSelect(true);
				if (gameMgr->useMove == false) {
					gameMgr->useMove = true;
					UserDefault::getInstance()->setBoolForKey("useMove", true);
					UserDefault::getInstance()->flush();
				}
			}
			return true;
		}
	}
}

void SelfUI::onMoveCard(Vec2 point, Vec2 startPoint, int id)
{
	int indexCard = 0;
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard[i]->isVisible() && id == arrayCard[i]->id) {
			indexCard = i;
			break;
		}
	}
	float dx = point.x - startPoint.x;
	

	if (dx >= 0) {
		int i;
		for (i = NUM_CARD - 1; i > indexCard; i--) {
			if (arrayCard[i]->isVisible()) {
				Vec2 pointToLocal = arrayCard[i]->convertToNodeSpace(point);
				Rect rect = arrayCard[i]->getBoundingBox();
				rect.origin = Vec2(0, 0);
				if (rect.containsPoint(pointToLocal)) {
					break;
				}
			}
		}
		for (int j = i; j > indexCard; j--) {
			if (arrayCard[j]->IsSelect() == false) {
				arrayCard[j]->setSelect(true);
			}
		}
		/*for (int i = indexCard + 1; i < NUM_CARD; i++) {
			Vec2 pointToLocal = arrayCard[i]->convertToNodeSpace(point);
			Rect rect = arrayCard[i]->getBoundingBox();
			rect.origin = Vec2(0, 0);
			if (rect.containsPoint(pointToLocal)) {

			}
			else {

			}
			checkCardSelectByMove(point, i, indexCard, dx);
		}*/
	}
	else {
		int i;
		for (i = indexCard - 1; i >= 0; i--) {
			if (arrayCard[i]->isVisible()) {
				Vec2 pointToLocal = arrayCard[i]->convertToNodeSpace(point);
				Rect rect = arrayCard[i]->getBoundingBox();
				rect.origin = Vec2(0, 0);
				if (rect.containsPoint(pointToLocal) == false) {
					if (i - 1 >= 0) {
						Vec2 pointToLocal1 = arrayCard[i - 1]->convertToNodeSpace(point);
						Rect rect1 = arrayCard[i]->getBoundingBox();
						rect1.origin = Vec2(0, 0);
						if (rect1.containsPoint(pointToLocal1)) {
							break;
						}
					}
				}
			}
		}
		if (i > 0) {
			for (int j = i - 1; j < indexCard; j++) {
				if (arrayCard[j]->IsSelect() == false) {
					arrayCard[j]->setSelect(true);
				}
			}
		}
		
		/*for (int i = indexCard - 1; i >= 0; i--) {
			if (checkCardSelectByMove(point, i, indexCard, dx))
				break;
		}*/
	}
}

void SelfUI::onButtonRelease(ax::ui::Button* button, int id)
{
	PlayerUI::onButtonRelease(button, id);
	switch (id) {
	case BTN_SELF_UI_CHAT: {
		AXLOGD("BTN_SELF_UI_CHAT ");
		break;
	}
	case BTN_SELF_UI_EMO: {
		break;
	}
	case BTN_SELF_UI_ARRANGE: {
		AXLOGD("ARRANGE ");
		TienlenGameSound::playArrangeCard();
		sortCard(false);
		if (GameLogic::getInstance()->CanPlayVsLastCard())
			arrow->setVisible(false);
		break;
	}
	case BTN_SELF_UI_CANCEL: {
		AXLOGD("CANCEL ");
	//	inGameMgr->sendCancel();
		vector <char> arr;
		GameLogic::getInstance()->myPlay(arr);
		break;
	}
	case BTN_SELF_UI_CHOOSE: {
		AXLOGD("CHOSE ");
		bool cheat = false;
		if (cheat) {
			BoardScene *gui = (BoardScene *)SceneMgr::getInstance()->getMainLayer();
			//gui->newUserJoinRoom(getChair(info->Chair()), info);
			vector <int> ar = getArraySelect();
			vector <char> arr;
			for (int i = 0; i < ar.size(); i++) {
				arr[i] = ar.at(i);
			}
			GameLogic::getInstance()->myPlay(arr);
			//gui->playCard(arr, ar.size(), 0, -1);
		}
		else {
			if (checkCanThrowCard()) {
				//inGameMgr->sendPlayCard(getArraySelect());
				vector <int> ar = getArraySelect();
				vector <char> arr;
				for (int i = 0; i < ar.size(); i++) {
					arr.push_back(ar.at(i));
				}
				GameLogic::getInstance()->myPlay(arr);
				btnChoose->setVisible(false);
				arrow->setVisible(false);
			}
			else {
				if (GameLogic::getInstance()->checkWrong3Space()) {
					ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("PLAY_3_BICH"));
				}
				else {
					ToastFloat::makeToast(ToastFloat::SHORT, LocalizedString::to("PLAY_WRONG"));
				}
			}
		}
			
		break;
	}			 
	}
}

void SelfUI::setDarkCard(bool isDark)
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setDark(isDark);
	}
}

void SelfUI::updateLevel()
{
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	lbLevel->setString("Level " + to_string(info->getLevel() + 1));
	progress->setPercent(info->getPercentLevel());
	borderAvatar->loadTexture(info->getAvatarLevel());
}

void SelfUI::updateMoney()
{
	PlayerUI::updateMoney();
	updateLevel();
}

void SelfUI::updateLanguage() {
    string path     = "Game/";
    string resource = gameMgr->isIndo == false ? (path + "textViet/btnPlay.png") : (path + "btnPlay.png");
    btnChoose->loadTextures(resource, resource, resource);

    resource = gameMgr->isIndo == false ? (path + "textViet/btnPass.png") : (path + "btnPass.png");
    btnCancel->loadTextures(resource, resource, resource);
}
