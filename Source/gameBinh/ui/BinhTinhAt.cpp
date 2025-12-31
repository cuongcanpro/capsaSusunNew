#include "BinhTinhAt.h"
#include "core/utils/StringUtility.h"
#include "../logic/BinhGameLogic.h"
#include "core/gui/SceneMgr.h"
#include "../BinhInGameMgr.h"
#include "../logic/gamePlay/MaubinhplayerCard.h"
#include "../logic/gamePlay/MaubinhPlayerCard.h"
#include "core/utils/TienlenGameSound.h"
#include "BinhBoardScene.h"
#include "gameTala/TalaInGameMgr.h"
#include "core/utils/TalaGameSound.h"
#include <Game/Utility/JNIUtils.h>

using namespace ax::ui;
#define BINH_TINH_AT_BTN_BAO 0
#define BINH_TINH_AT_BTN_COMPLETE 1
#define BINH_TINH_AT_BTN_CANCEL 2
#define BINH_TINH_AT_BTN_BINH 3
#define BINH_TINH_AT_BTN_BAI 4
#define BINH_TINH_AT_BTN_ARRANGE 5
#define BINH_TINH_AT_BTN_NORMAL 6

/**
 * Chi Dau o tren cung, gom 3 con : 10, 11, 12: Chi 0
 * Chi Giua o giua: 5, 6, 7, 8, 9: Chi 1
 * CHI Cuoi o cuoi: 0, 1, 2, 3, 4: Chi 2
 */

BinhTinhAt::BinhTinhAt()
{
}
BinhTinhAt::~BinhTinhAt()
{

}

bool BinhTinhAt::init()
{
	BaseLayer::init();
	initWithBinaryFile("Board/BinhAt.csb");
	return true;
}

void BinhTinhAt::initGUI()
{
	initBottomCard();
	panelCenter = getControl("panelCenter");
	initCenterCard();

	initButton();
	panelSort = (Layout*)getControl("panelSort");
	panelSort->addTouchEventListener(AX_CALLBACK_2(BinhTinhAt::onTouchSort, this));

	effectImage = Sprite::create("table/lucPheBon.png");
	groupCard->addChild(effectImage);
	effectImage->setLocalZOrder(30);
	effectImage->setPosition(arrayCard[2]->getPosition());

	clockGame = new ClockGame();
	groupCard->addChild(clockGame);
	clockGame->setPosition(arrayCard[5]->getPositionX() - arrayCard[5]->getCardWidth() * 1.5, arrayCard[5]->getPositionY());
	clockGame->setCallback([this]() {
		vector<int> arrayId = getArrayId();
		sendReady(arrayId, TypeSend::AUTO);
	});

	bubbleText = new BinhBubbleText();
	addChild(bubbleText);

	iconHand = Sprite::create("table/hand1.png");
	addChild(iconHand);
	
}

void BinhTinhAt::initBottomCard()
{
	Size size = Director::getInstance()->getVisibleSize();
	ImageView* bgCard = (ImageView*)getControl("bgCard");
	float scale = size.width / bgCard->getContentSize().width;
	bgCard->setScaleX(scale);

	float hCard = bgCard->getContentSize().height * 0.9;
	for (int i = 0; i < NUM_CARD; i++) {
		int random = AXRANDOM_0_1() * 52;
		arrayCardBottom[i] = new BinhCardButton(i, random, BinhCardButtonType::BOTTOM, this);
		_layout->addChild(arrayCardBottom[i]);
		arrayCardBottom[i]->setIdCard(random);
	}
	float widthPanelCard = size.width * 0.97;
	float startX = (size.width - widthPanelCard) * 0.5;
	float startY = 5;
	float padX = arrayCardBottom[0]->getContentSize().width * 0.6;
	float padY = 0;
	float sumWidthCard = padX * (NUM_CARD - 1) + arrayCardBottom[0]->getContentSize().width;
	scale = widthPanelCard / sumWidthCard;
	float widthCard = arrayCardBottom[0]->getContentSize().width * scale;
	float heightCard = arrayCardBottom[0]->getContentSize().height * scale;
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCardBottom[i]->setScale(scale);
		arrayCardBottom[i]->setPositionX(startX + widthCard * 0.5 + padX * i * scale);
		arrayCardBottom[i]->setPositionY(startY + heightCard * 0.5);
		arrayCardBottom[i]->setLocalZOrder(i);
		arrayCardBottom[i]->saveInfoCard();
		//	arrayCardBottom[i]->setPosition(Vec2(300, 300));
	}
	scale = (startY * 2 + heightCard) / bgCard->getContentSize().height;
	bgCard->setScaleY(scale);
}

void BinhTinhAt::initCenterCard()
{
	groupCard = getControl("bgCardArrange", panelCenter);
	float startY = 0;
	float padY = 75;
	for (int i = 0; i < NUM_CARD; i++) {
		int index = i / NUM_CARD_BIG_CHI;
		if (index == 0) {
			arrayBgCard[i] = Sprite::create("table/bgBaiAt1.png");
		}
		else {
			arrayBgCard[i] = Sprite::create("table/bgBaiAt2.png");
		}
		groupCard->addChild(arrayBgCard[i]);
		arrayBgCard[i]->setPositionX(arrayBgCard[i]->getContentSize().width * (0.5 + i % NUM_CARD_BIG_CHI));
		arrayBgCard[i]->setPositionY(arrayBgCard[i]->getContentSize().height * 0.5 + padY * index);
	}
	// ti le Scale de bien Card Bottom thanh Center
	scaleBottomToCenter = arrayBgCard[0]->getContentSize().width * panelCenter->getScale() / (arrayCardBottom[0]->getContentSize().width * arrayCardBottom[0]->getScale());
	// ti le Scale de bien Card Center thanh Bottom
	scaleCenterToBottom = 1 / scaleBottomToCenter;

	// int group 13 card
	float height = groupCard->getContentSize().height;
	float width = groupCard->getContentSize().width;
	for (int i = 0; i < NUM_CARD; i++) {
		int random = AXRANDOM_0_1() * 52;
		arrayCard[i] = new BinhCardButton(i, random, BinhCardButtonType::CENTER, this);
		groupCard->addChild(arrayCard[i]);
		arrayCard[i]->setIdCard(random);
	}
	float scale = arrayBgCard[0]->getContentSize().width / arrayCard[0]->getContentSize().width;
	for (int i = 0; i < NUM_CARD; i++) {
		BinhCardButton* card = arrayCard[i];
		card->setScale(scale);
		card->setPosition(arrayBgCard[i]->getPosition());
		card->setLocalZOrder(NUM_CARD - i);
		card->setVisible(false);
		card->saveInfoCard();
	}
}

void BinhTinhAt::initButton()
{
	btnBao = customButton("btnBao", BINH_TINH_AT_BTN_BAO, _layout);
	btnCancel = customButton("btnCancel", BINH_TINH_AT_BTN_CANCEL, panelCenter);
	btnComplete = customButton("btnComplete", BINH_TINH_AT_BTN_COMPLETE, panelCenter);
	btnArrange = customButton("btnArrange", BINH_TINH_AT_BTN_ARRANGE, _layout);
	btnNormal = customButton("btnNormal", BINH_TINH_AT_BTN_NORMAL, _layout);

    
}

void BinhTinhAt::initOneButton(Button* btn, string resource)
{
	
}

void BinhTinhAt::onEnterFinish()
{
    touchCard = -1;
	sendAuto = false;
	for (int i = 0; i < NUM_TYPE_CARD; i++) {
		dataBinh[i] = 0;
		dataBai[i] = 0;
	}
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setVisible(false);
	}
	setDarkAllCard(false);
	stateSort = SortCard::KIND;
	isSort = false;
	effectImage->setVisible(false);
	btnComplete->setVisible(false);
	btnCancel->setVisible(false);
	scheduleUpdate();
	setFog(true, 0);
	clockGame->onEnterFinish();
	if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
    {
        string res = "table/textEnglish/btnReady.png";
        btnComplete->loadTextures(res, res, res);

        res = "table/textEnglish/btnArrange1.png";
        btnArrange->loadTextures(res, res, res);

        res = "table/textEnglish/btnCancel.png";
        btnCancel->loadTextures(res, res, res);
    }
    else
    {
    	string res = "table/btnReady.png";
        btnComplete->loadTextures(res, res, res);

        res = "table/btnArrange1.png";
        btnArrange->loadTextures(res, res, res);

        res = "table/btnCancel.png";
        btnCancel->loadTextures(res, res, res);	
    }
}

void BinhTinhAt::showEffect(Vec2 arrayPos[], float widthCard, bool effectGUI)
{
	btnBao->setVisible(false);
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(MY_INDEX);
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCardBottom[i]->setVisible(true);
		arrayCardBottom[i]->setIdCard(info->arrayCard[i]);
		if (effectGUI) {
			arrayCardBottom[i]->setPosition(arrayPos[i]);
			float scale = widthCard / (arrayCardBottom[i]->getCardWidth());
			arrayCardBottom[i]->setScale(scale);
			arrayCardBottom[i]->moveToDefault(0.5, 0.02 * i);
		}
		else {
			arrayCardBottom[i]->moveToDefault(0, 0);
		}
	}
	// De chan loi bai bi hien thi lon xon khi Reconnect vao thang ban choi khi Kill app
	this->effectGUI = effectGUI;
	if (effectGUI) {
		runAction(Sequence::create(
			DelayTime::create(0.5),
			CallFuncN::create(AX_CALLBACK_1(BinhTinhAt::callbackShow, this)),
			NULL
		));
	}
	else {
		callbackShow(NULL);
	}
	
}

void BinhTinhAt::callbackShow(Node* pSender)
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(MY_INDEX);
	sortCard();
	MaubinhPlayerCard playerCard;
	playerCard.setArrayCard(info->arrayCard);
	playerCard.SapXepTruocSoBai();
	int cardKind = playerCard.GetPlayerCardsKind(false);
	showBinh = false;
	bool mauBinh, isEffect;
	checkBoBai(playerCard, cardKind, mauBinh, isEffect);
	btnArrange->setVisible(true);
	showHelp();
}

void BinhTinhAt::sendReady(vector <int> arrayId, TypeSend type)
{
	binhInGameMgr->sendConfirmInGame();
	int i;
	int j = 0;
	vector <Vec2> arrayPos;
	vector <float> arraySize;
	for (i = 0; i < NUM_CARD; i++) {
		for (j = 0; j < NUM_CARD; j++) {
			if (arrayCardBottom[j]->isVisible() && arrayId[i] == arrayCardBottom[j]->id) {
				arrayPos.push_back(arrayCardBottom[j]->getPosition());
				arraySize.push_back(arrayCardBottom[j]->getCardWidth());
				break;
			}
			else if (arrayCard[j]->isVisible() && arrayId[j] == arrayCard[j]->id) {
				arrayPos.push_back(groupCard->convertToWorldSpace(arrayCard[j]->getPosition()));
				arraySize.push_back(arrayCard[j]->getCardWidth() * panelCenter->getScale());
				break;
			}
		}
	}
	BinhGameLogic::getInstance()->setMyCard(arrayId, arrayPos, arraySize);
	//binhInGameMgr->sendReady(arrayId, type);
	if (BinhGameLogic::getInstance()->isOffline) {
		BinhGameLogic::getInstance()->timeAuto = 0;
		BinhGameLogic::getInstance()->ready(0);
	}
	else {
		binhInGameMgr->sendReady(arrayId, type);
		//binhInGameMgr->sendConfirmInGame();
	}
}

void BinhTinhAt::onButtonRelease(ax::ui::Button* button, int id)
{
	switch (id)
	{
	case BINH_TINH_AT_BTN_BAO:
	{
		BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(MY_INDEX);
		info->WaitBaoBinh(true);
		binhInGameMgr->sendBaoBinh();
		MaubinhPlayerCard playerCard;
		vector<int> arrayId = BinhGameLogic::getInstance()->getArrayCardBao();
		sendReady(arrayId, TypeSend::MANUAL);
	//	BinhGameLogic::getInstance()->setMyCard(arrayId);
		break;
	}
	case BINH_TINH_AT_BTN_COMPLETE:
	{
		TienlenGameSound::playSoundfinishgroupcard();
		vector<int> arrayId = getArrayId();
		sendReady(arrayId, TypeSend::MANUAL);

		break;
	}
	case BINH_TINH_AT_BTN_CANCEL:
		btnCancel->setVisible(false);
		btnComplete->setVisible(false);
		setDarkAllCard(false);
		for (int i = 0; i < NUM_CARD; i++) {
			if (arrayCard[i]->isVisible()) {
				hideCardToBottom(arrayCard[i]);
			}
		}
		break;
	case BINH_TINH_AT_BTN_ARRANGE:
	{
		sortCard();
		showHelp();
		break;
	}
	case BINH_TINH_AT_BTN_NORMAL:
	{
		gameMgr->useGuiAt = false;
		UserDefault::getInstance()->setBoolForKey("useGuiAt", false);
		UserDefault::getInstance()->flush();
		BinhBoardScene *gui = (BinhBoardScene *)SceneMgr::getInstance()->getMainLayer();
		gui->showGUIArrange(false);
		removeFromParent();
		break;
	}
	default:
		break;
	}
}

void BinhTinhAt::touchEvent(Object *pSender, Widget::TouchEventType type)
{
	BinhCardButton* card = dynamic_cast<BinhCardButton*> (pSender);
	Vec2 point = card->getTouchMovePosition();
	point = groupCard->convertToNodeSpace(point);
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		onTouchBeganCard(card);
		break;

	case Widget::TouchEventType::MOVED:
	{
		onTouchMoveCard(card, point);
		break;
	}
	case Widget::TouchEventType::ENDED:
	{
		onTouchEndCard(card, point);
	}
	break;
	case Widget::TouchEventType::CANCELED:
		onTouchCancelCard(card, point);
		break;
	default:
		break;
	}
}

void BinhTinhAt::onTouchBeganCard(BinhCardButton * card)
{
	if (touchCard < 0)
		touchCard = card->index;
	
}

void BinhTinhAt::onTouchMoveCard(BinhCardButton* card, Vec2 point)
{
	if (lastTouchPoint.x >= 0) {
		if (point.getDistance(lastTouchPoint) < 1) {
			return;
		}
	}
	lastTouchPoint = point;

	if (card->type == BinhCardButtonType::CENTER) {
		arrayCard[touchCard]->setLocalZOrder(NUM_CARD + 1);
		card->setPosition(point);
		if (touchCard >= 0) {
			arrayCard[touchCard]->setSelect(false);
			touchCard = -1;
		}
		moveCard = card->index;
		// tim vi tri quan card co the doi
		setDarkAllCard(false);
		int visitCard = getCardFromPoint(point, moveCard);
		if (visitCard >= 0)
			arrayCard[visitCard]->setDark(true);
	}
}

void BinhTinhAt::onTouchEndCard(BinhCardButton * card, Vec2 point)
{
	if (card->type == BinhCardButtonType::CENTER) {
		int targetIndex = -1;
		if (moveCard >= 0) {
			// tim vi tri quan card co the doi
			int index = getCardFromPoint(point, moveCard);
			if (index >= 0) {
				swapCard(card, arrayCard[index]);
				targetIndex = index;
			}
			else {
				// back Card lai vi tri cu
				card->moveToDefault(0.5, 0);
				TalaGameSound::playEffect(TalaInGameMgr::SOUND_SEND_CARD);
			}
		}
		else {
			if (touchCard != card->index) {
				// doi vi tri 2 quan card
				swapCard(arrayCard[touchCard], card);
				targetIndex = arrayCard[touchCard]->index;
				touchCard = -1;
			}
			else {
				// chon quan card nay
				if (!card->IsSelect()) {
					card->setSelect(!card->IsSelect());
					TalaGameSound::playEffect(TalaInGameMgr::SOUND_SELECT_CARD);
				}
				else {
					// bay ve vi tri ben duoi
					hideCardToBottom(card);
					TalaGameSound::playEffect(TalaInGameMgr::SOUND_SEND_CARD);
				}
			}
		}
		moveCard = -1;
		if (targetIndex >= 0) {
			if (targetIndex >= 10) {
				chiGoal = CHI_DAU;
			}
			else if (targetIndex >= 5) {
				chiGoal = CHI_GIUA;
			}
			else if (targetIndex >= 0) {
				chiGoal = CHI_CUOI;
			}
			if (checkEnoughCard()) {
				highlightCard(true);
			}
		}
	}
	// Touch end Card Bottom
	else {
		// bay quan card len group card
		showCardToCenter(card);
		TalaGameSound::playEffect(TalaInGameMgr::SOUND_SEND_CARD);
	}
	btnComplete->setVisible(checkEnoughCard());
	btnCancel->setVisible(checkHaveCard());
	lastTouchPoint.x = -1;
	showHelp();
}

void BinhTinhAt::showCardToCenter(BinhCardButton* card)
{
    JNIUtils::vibrate(10);
	int index = findIndexCardToShow();
	BinhCardButton* cardCenter = arrayCard[index];
	card->setVisible(false);
	cardCenter->setVisible(true);
	cardCenter->setIdCard(card->id);

	Vec2 pos = card->getPosition();
	pos = groupCard->convertToNodeSpace(pos);
	cardCenter->setPosition(pos);
	cardCenter->setScale(scaleCenterToBottom);

	cardCenter->moveToDefault(0.5, 0);
	touchCard = -1;
	if (checkEnoughCard()) {
		highlightCard(false);
	}
}

void BinhTinhAt::hideCardToBottom(BinhCardButton* card)
{
    JNIUtils::vibrate(10);
	int index = findIndexCardToHide();
	BinhCardButton* cardBottom = arrayCardBottom[index];
	card->setVisible(false);
	cardBottom->setVisible(true);
	cardBottom->setIdCard(card->id);

	Vec2 pos = card->getPosition();
	pos = groupCard->convertToWorldSpace(pos);
	cardBottom->setPosition(pos);
	cardBottom->setScale(scaleBottomToCenter);

	cardBottom->moveToDefault(0.5, 0);
	touchCard = -1;
}

void BinhTinhAt::onTouchCancelCard(BinhCardButton* card, Vec2 point)
{
	AXLOGD("TOUCH CANCEL %i ", card->index);
	touchCard = -1;
	moveCard = -1;
	lastTouchPoint.x = -1;
}

int BinhTinhAt::getCardFromPoint(Vec2 point, int indexNotSelect)
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (i != indexNotSelect) {
			if (arrayCard[i]->isVisible()) {
				Rect rect = arrayCard[i]->getBoundingBox();
				if (rect.containsPoint(point)) {
					return i;
					break;
				}
			}
		}
	}
	return -1;
}

void BinhTinhAt::swapCard(BinhCardButton* card1, BinhCardButton* card2)
{
	card1->stopAllActions();
	card2->stopAllActions();
	int saveId = card1->id;
	card1->setIdCard(card2->id);
	card2->setIdCard(saveId);

	Vec2 savePos = card1->getPosition();
	card1->setPosition(card2->getPosition());
	card2->setPosition(savePos);
	card1->moveToDefault(0.3, 0);
	card2->moveToDefault(0.3, 0);
	card2->setSelect(false);
	card1->setSelect(false);
	card1->setLocalZOrder(NUM_CARD + 1);
	card2->setLocalZOrder(NUM_CARD + 2);
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_DRAW_CARD);
}

void BinhTinhAt::callbackSwapCard(Node* pSender)
{
	BinhCardButton* card = (BinhCardButton*)pSender;
	pSender->setLocalZOrder(NUM_CARD - card->index);
	AXLOGD("INDEX %i ", card->index);
}

void BinhTinhAt::highlightCard(bool sound)
{
	MaubinhPlayerCard playerCard;
	int i, j, num;
	effectImage->setVisible(false);
	for (i = NUM_CARD - 1; i >= 0; i--)
	{
		MaubinhGroupCardLogic* group = new MaubinhGroupCardLogic();
		group->AddCardByID(arrayCard[i]->id);
		playerCard.AddGroupCard(group);
	}
	playerCard.SapXepTruocSoBai();
	int cardKind = playerCard.GetPlayerCardsKind(false);
	bool isLung = playerCard.isLung();
	bool isEffect = false;
	bool mauBinh = false;
	showBinh = false;
	
	if (!isLung) {
		showEffectChi(playerCard);
	}
	else {
        if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
		    effectBoBai("table/binhLungBig.png");
        else
            effectBoBai("table/textEnglish/binhLungBig.png");
	}
	checkBoBai(playerCard, cardKind, mauBinh, isEffect);
	showGroupTypeCard();
	if (!mauBinh  && sound) {
		playSoundChi(playerCard);
	}
	//checkEffectChi(playerCard, isEffect);
	//checkTypeChi(playerCard);
	BinhGameLogic::getInstance()->showDarkCard(playerCard, cardKind, mauBinh, arrayCard);
}

void BinhTinhAt::checkBoBai(MaubinhPlayerCard playerCard, int cardKind, bool &mauBinh, bool &isEffect)
{
	int i;
	for (i = 0; i < 10; i++) {
		dataBai[i] = 0;
		dataBinh[i] = 0;
	}
	
	/*if (BinhGameLogic::getInstance()->isMauBinh(cardKind)) {
		showBinh = true;
		btnBao->setVisible(true);
		btnComplete->setPosition(Vec2(btnCancel->getPositionX(), btnCancel->getPositionY() + btnCancel->getContentSize().height * 1.2));
	}
	else {*/
		btnBao->setVisible(false);
		btnComplete->setPosition(Vec2(groupCard->getPositionX(), groupCard->getPositionY() - groupCard->getContentSize().height * 0.5 - btnComplete->getContentSize().height * 0.7));
	//}
	if (BinhGameLogic::getInstance()->isMauBinh(cardKind)) {
		switch (cardKind) {
		case EM_LUCPHEBON:
		{
			TienlenGameSound::playSoundmaubinh_lucphebon();
			break;
		}
		case EM_3SANH:
		{
			TienlenGameSound::playSoundmaubinh_3caisanh();
			break;
		}
		case EM_3THUNG:
		{
			TienlenGameSound::playSoundmaubinh_3caithung();
			break;
		}
		case EM_SANHRONG:
		{
			TienlenGameSound::playSoundmaubinh_sanhrong();
			break;
		}
		default:
			break;
		}
		effectBoBai(BinhGameLogic::getInstance()->getResourceBinh(cardKind));
		TienlenGameSound::playSoundThang();
	}
		
	showGroupTypeCard();
}

void BinhTinhAt::playSoundChi(MaubinhPlayerCard playerCard)
{
	int typeGroup = -1;
	switch (chiGoal)
	{
	case CHI_CUOI:
		typeGroup = playerCard.ChiCuoi->GetGroupKind();
		break;
	case CHI_GIUA:
		typeGroup = playerCard.ChiGiua->GetGroupKind();
		break;
	case CHI_DAU:
		typeGroup = playerCard.ChiDau->GetGroupKind();
		break;
	default:
		break;
	}

	switch (typeGroup)
	{
	case EG_MAUTHAU:
		TienlenGameSound::playSoundxepbai_mauthau();
		break;
	case EG_DOI:
		TienlenGameSound::playSoundxepbai_doi();
		break;
	case EG_THU:
		TienlenGameSound::playSoundxepbai_thu();
		break;
	case EG_SAMCO:
		TienlenGameSound::playSoundxepbai_samchi();
		if (chiGoal == CHI_DAU) {
		}
		break;
	case EG_SANH:
		TienlenGameSound::playSoundxepbai_sanh();
		break;
	case EG_THUNG:
		TienlenGameSound::playSoundxepbai_thung();
		break;
	case EG_TUQUI:
		TienlenGameSound::playSoundxepbai_tuquy();
		break;
	case EG_THUNGPHASANH:
		TienlenGameSound::playSoundxepbai_thungphasanh();
		break;
	case EG_CULU:
		TienlenGameSound::playSoundxepbai_culu();
		break;
	default:
		break;
	}
}

// show Dai dien mot Effect cua mot chi cao nhat
void BinhTinhAt::showEffectChi(MaubinhPlayerCard playerCard)
{
	dataBai[playerCard.ChiCuoi->GetGroupKind()] = 1;
	dataBai[playerCard.ChiGiua->GetGroupKind()] = 1;
	dataBai[playerCard.ChiDau->GetGroupKind()] = 1;
	string resource = "";
	//uu tien hien thi effect dac biet cua chi giua
	switch (playerCard.ChiGiua->GetGroupKind()) {
	case EG_TUQUI:
		if (resource.compare("") == 0)
			resource = "poker/tuQuyChi2.png";
		break;
	case EG_THUNGPHASANH:
		if (resource.compare("") == 0)
			resource = "poker/thungPhaSanhChi2.png";
		break;
	}

	switch (playerCard.ChiCuoi->GetGroupKind()) {
	case EG_THUNGPHASANH:
		if (resource.compare("") == 0)
			resource = "poker/thungPhaSanh.png";
		break;
	case EG_TUQUI:
		if (resource.compare("") == 0)
			resource = "poker/tuQuy.png";
		break;
	}

	switch (playerCard.ChiDau->GetGroupKind()) {
	case EG_SAMCO:
	{
		if (resource.compare("") == 0)
			resource = "poker/xamChiCuoi.png";
		showBinh = true;
		break;
	}
	}
	
	switch (playerCard.ChiGiua->GetGroupKind()) {
	case EG_CULU:
	{
		if (resource.compare("") == 0)
			resource = "poker/cuLuChi2.png";
		showBinh = true;
		break;
	}
	case EG_TUQUI:
	{
		if (resource.compare("") == 0)
			resource = "poker/tuQuyChi2.png";
		showBinh = true;
		break;
	}
	case EG_THUNGPHASANH:
	{
		if (resource.compare("") == 0)
			resource = "poker/thungPhaSanhChi2.png";
		showBinh = true;
		break;
	}
	}
	if (resource.compare("") != 0) {
	//	effectBoBai(resource);
		effectParticle();
	}
}

void BinhTinhAt::showDarkCard(MaubinhPlayerCard playerCard, int cardKind, bool mauBinh)
{
	int i, j;
	MaubinhGroupCardLogic* gc = nullptr;
	setDarkAllCard(true);
	if (cardKind == EM_BINHLUNG) {
		setDarkAllCard(false);
		return;
	}
	if (cardKind == EM_SANHRONG || cardKind == EM_3SANH || cardKind == EM_3THUNG || cardKind == EM_LUCPHEBON || cardKind == EM_MUOI_HAI || cardKind == EM_MUOI_BA) {
		setDarkAllCard(true);
		return;
	}

	if (!mauBinh) {
		if (playerCard.ChiDau->GetGroupKind() != EG_SAMCO) {
			switch (playerCard.ChiDau->GetGroupKind()) {

			case EG_MAUTHAU:
				gc = playerCard.ChiDau->getMaxCard();
				break;
			case EG_THU:
				gc = playerCard.ChiDau->get2DoiKhacNhau();
				break;
			case EG_DOI:
				gc = playerCard.ChiDau->getPair();
				break;
			}
			if (gc != nullptr) {
				for (i = 0; i < NUM_CARD_SMALL_CHI; i++) {
					int stt = 10 + i;
					for (j = 0; j < gc->Cards.size(); j++) {
						if (gc->Cards[j]->ID == arrayCard[stt]->id) {
							break;
						}
					}
					if (j == gc->Cards.size()) {
						arrayCard[stt]->setDark(false);
					}
				}
			}
		}
		showDark2BigChi(playerCard.ChiGiua, CHI_GIUA);
		showDark2BigChi(playerCard.ChiCuoi, CHI_CUOI);
	}
}

void BinhTinhAt::showDark2BigChi(MaubinhGroupCardLogic* gc1, int chi)
{
	int i, j;
	MaubinhGroupCardLogic* gc = nullptr;
	if (gc1->GetGroupKind() != EG_THUNGPHASANH && gc1->GetGroupKind() != EG_THUNG && gc1->GetGroupKind() != EG_SANH && gc1->GetGroupKind() != EG_CULU) {
		switch (gc1->GetGroupKind()) {
		case EG_MAUTHAU:
			gc = gc1->getMaxCard();
			break;
		case EG_THU:
			gc = gc1->get2DoiKhacNhau();
			break;
		case EG_DOI:
			gc = gc1->getPair();
			break;
		case EG_SAMCO:
			gc = gc1->getXamChi();
			break;
		case EG_TUQUI:
			gc = gc1->getFour();
			break;
		}
		if (gc != nullptr) {
			for (i = 0; i < NUM_CARD_BIG_CHI; i++) {
				int stt = NUM_CARD_BIG_CHI * (NUM_CHI - chi - 1) + i;
				for (j = 0; j < gc->Cards.size(); j++) {
					if (gc->Cards[j]->ID == arrayCard[stt]->id) {
						break;
					}
				}
				if (j == gc->Cards.size()) {

					arrayCard[stt]->setDark(false);
				}

			}
		}
	}
}

void BinhTinhAt::showGroupTypeCard()
{
	
}

void BinhTinhAt::onTouchSort(Object *pSender, Widget::TouchEventType type)
{
	Layout* node = (Layout*)pSender;
	Vec2 newTouch = node->getTouchMovePosition();
	switch (type)
	{
	case ax::ui::Widget::TouchEventType::BEGAN:
		break;
	case ax::ui::Widget::TouchEventType::MOVED:
		if (lastTouchPoint.x >= 0) {
			if (newTouch.getDistance(lastTouchPoint) > 15) {
				sortCard();
			}
		}
		lastTouchPoint = newTouch;
		break;
	case ax::ui::Widget::TouchEventType::ENDED:
		lastTouchPoint.x = -1;
		break;
	case ax::ui::Widget::TouchEventType::CANCELED:
		lastTouchPoint.x = -1;
		break;
	default:
		break;
	}
	
}

void BinhTinhAt::sortCard()
{
	if (isSort)
		return;
	isSort = true;
	// xep tu nho den lon
	int arrayArrange [NUM_CARD]; // mang luu lai ID cua cacs quan card duoc xap xep
	int arraySavePos [NUM_CARD];// mang luu lai vi tri ban dau cua tung quan card
	int count = 0;
	for (int i = 0; i < NUM_CARD; i++)
		arrayArrange[i] = -1;
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCardBottom[i]->isVisible()) {
			arrayArrange[count] = arrayCardBottom[i]->id;
			count++;
		}
	}
	BinhGameLogic::getInstance()->sortArrayId(arrayArrange, count, stateSort);

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < NUM_CARD; j++) {
			if (arrayCardBottom[j]->isVisible() && arrayArrange[i] == arrayCardBottom[j]->id) {
				arraySavePos[i] = j;
			}
		}
	}
	for (int i = 0; i < NUM_CARD; i++) {
		if (i < count) {
			arrayCardBottom[i]->setVisible(true);
			arrayCardBottom[i]->setIdCard(arrayArrange[i]);
			arrayCardBottom[i]->setPosition(arrayCardBottom[arraySavePos[i]]->getDefaultPos());
			if (this->effectGUI)
				arrayCardBottom[i]->moveToDefault(0.2, 0);
			else
				arrayCardBottom[i]->moveToDefault(0, 0);
		}
		else {
			arrayCardBottom[i]->setVisible(false);
		}
	}
	stateSort = (SortCard) (1 - stateSort);
	runAction(Sequence::create(
		DelayTime::create(0.22), 
		CallFuncN::create(AX_CALLBACK_1(BinhTinhAt::callbackSortCard, this)),
		NULL
	));
	this->effectGUI = true;
}

void BinhTinhAt::callbackSortCard(Node* pSender)
{
	isSort = false;
}

int BinhTinhAt::findIndexCardToShow()
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (!arrayCard[i]->isVisible()) {
			return i;
		}
	}
	return 0;
}

int BinhTinhAt::findIndexCardToHide()
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (!arrayCardBottom[i]->isVisible()) {
			return i;
		}
	}
	return 0;
}

bool BinhTinhAt::checkEnoughCard()
{
	for (int i = 0; i < NUM_CARD; i++)
		if (!arrayCard[i]->isVisible()) {
			return false;
		}
	return true;
}

bool BinhTinhAt::checkHaveCard()
{
	for (int i = 0; i < NUM_CARD; i++)
		if (arrayCard[i]->isVisible()) {
			return true;
		}
	return false;
}

void BinhTinhAt::effectBoBai(string resource)
{
	effectImage->setVisible(true);
	effectImage->setTexture(resource);
	effectImage->setScale(0);
	effectImage->runAction(EaseBounceOut::create(ScaleTo::create(0.5, 1.0)));
}

void BinhTinhAt::effectParticle()
{

}

void BinhTinhAt::setDarkAllCard(bool isDark)
{
	for (int i = 0; i < NUM_CARD; i++)
		arrayCard[i]->setDark(isDark);
}

std::vector<int> BinhTinhAt::getArrayId()
{
	vector<int> arrayId;
	int i;
	int j = 0;
	for (i = 0; i < NUM_CARD; i++) {
		if (arrayCard[i]->isVisible()) {
			arrayId.push_back(arrayCard[i]->id);
		}
		else {
			for (; j < NUM_CARD; j++) {
				if (arrayCardBottom[j]->isVisible()) {
					arrayId.push_back(arrayCardBottom[j]->id);
					j++;
					break;
				}
			}
		}
	}
	return arrayId;
}

void BinhTinhAt::update(float dt)
{
	float percent = BinhGameLogic::getInstance()->getPercentTime();
	//progress->setPercent(percent);
	/*if (percent < 0.5 && sendAuto == false) {
		sendAuto = true;
		vector<int> arrayId = getArrayId();
		sendReady(arrayId, TypeSend::AUTO);
	}*/
}

void BinhTinhAt::setGameTime(int time)
{
	clockGame->setTime(time);
}

void BinhTinhAt::showHelp()
{
	if (gameMgr->countHelpAt <= 1) {
		
	}
	else {
		bubbleText->setVisible(false);
		iconHand->setVisible(false);
		return;
	}
	bubbleText->setText(LocalizedString::to("HELP_AT_" + to_string(gameMgr->countHelpAt)).c_str());
	iconHand->setVisible(true);
	bubbleText->setVisible(true);
	Vec2 pos;
	switch (gameMgr->countHelpAt)
	{
	case 0:
        pos = btnArrange->getParent()->convertToWorldSpace(btnArrange->getPosition());
        bubbleText->setPosition(pos.x - 50, pos.y + 80);
        break;
	case 1:
		pos = arrayCardBottom[3]->getParent()->convertToWorldSpace(arrayCardBottom[3]->getDefaultPos());
		bubbleText->setPosition(pos.x, pos.y + 100);
		break;
	default:
		break;
	}
	iconHand->setPosition(pos);
	iconHand->stopAllActions();
	iconHand->setPosition(pos.x + 100, pos.y + 30);
	iconHand->setScale(1.1);
	iconHand->setRotation(10);
	iconHand->runAction(
		RepeatForever::create(
			Sequence::create(
				Spawn::create(
					MoveTo::create(0.2, Vec2(pos.x + iconHand->getContentSize().width * 0.5, pos.y)),
					ScaleTo::create(0.2, 1),
					RotateTo::create(0.2, -20),
					NULL
				),
				DelayTime::create(0.5),
				Spawn::create(
					MoveTo::create(0, Vec2(pos.x + 100, pos.y + 30)),
					ScaleTo::create(0, 1.1),
					RotateTo::create(0.0, 10),
					NULL
				),
				NULL
			)
		)
	);
	gameMgr->countHelpAt++;
	UserDefault::getInstance()->setIntegerForKey("countHelpAt", gameMgr->countHelpAt);
	UserDefault::getInstance()->flush();
}

const std::string BinhTinhAt::className = "BinhTinhAt";
const int BinhTinhAt::TAG = 10051;

