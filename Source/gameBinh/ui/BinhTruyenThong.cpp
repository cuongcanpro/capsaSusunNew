#include "BinhTruyenThong.h"
#include "core/utils/StringUtility.h"
#include "../logic/BinhGameLogic.h"
#include "core/gui/SceneMgr.h"
#include "../BinhInGameMgr.h"
#include "core/utils/TienlenGameSound.h"
#include "../logic/gamePlay/MaubinhplayerCard.h"
#include "../logic/gamePlay/MaubinhPlayerCard.h"
#include "../logic/gamePlay/MaubinhGroupCardLogic.h"
#include "BinhBoardScene.h"
#include "core/utils/TalaGameSound.h"
#include "gameTala/TalaInGameMgr.h"

using namespace ax::ui;
#define BINH_TRUYEN_THONG_BTN_COMPLETE 0
#define BINH_TRUYEN_THONG_BTN_SWAP 1
#define BINH_TRUYEN_THONG_BTN_HARD 2
/**
 * Chi Dau o tren cung, gom 3 con : 10, 11, 12: Chi 0
 * Chi Giua o giua: 5, 6, 7, 8, 9: Chi 1
 * CHI Cuoi o cuoi: 0, 1, 2, 3, 4: Chi 2
 */

BinhTruyenThong::BinhTruyenThong()
{
}
BinhTruyenThong::~BinhTruyenThong()
{

}

bool BinhTruyenThong::init()
{
	BaseLayer::init();
	initWithBinaryFile("Board/ArrangeCard.csb");
	return true;
}

void BinhTruyenThong::initGUI()
{
	groupCard = getControl("groupCard");
	btnSwap = customButton("btnSwap", BINH_TRUYEN_THONG_BTN_SWAP, groupCard);
	btnComplete = customButton("btnComplete", BINH_TRUYEN_THONG_BTN_COMPLETE, groupCard);
	btnHard = customButton("btnHard", BINH_TRUYEN_THONG_BTN_HARD, groupCard);
	
	// int group 13 card
	float height = groupCard->getContentSize().height;
	float width = groupCard->getContentSize().width;
	for (int i = 0; i < NUM_CARD; i++) {
		int random = AXRANDOM_0_1() * 52 * 0.999f;
		arrayCard[i] = new BinhCardButton(i, random, this);
		groupCard->addChild(arrayCard[i]);
		arrayCard[i]->setIdCard(random);
	}
	float padX = 2;
	float padY = 12;
	float widthCard = (width - padX * (NUM_CARD_BIG_CHI - 1)) / NUM_CARD_BIG_CHI;
	float scale = widthCard / arrayCard[0]->getContentSize().width;
	for (int i = 0; i < 3; i++) {
		int numCard = NUM_CARD_BIG_CHI;
		if (i == 2) {
			numCard = NUM_CARD_SMALL_CHI;
		}
		for (int j = 0; j < numCard; j++) {
			int index = i * NUM_CARD_BIG_CHI + j;
			BinhCardButton* card = arrayCard[index];
			card->setScale(scale);
			card->setPositionX(padX * j + widthCard * (0.5 + j));
			card->setPositionY(padY * i + card->getContentSize().height * card->getScale() * (0.5 + i));
			card->saveDefaultPos();
		}
	}

	clockGame = new ClockGame();
	groupCard->addChild(clockGame);
	clockGame->setPosition(arrayCard[8]->getPositionX() + arrayCard[8]->getCardWidth() * 0.5, arrayCard[12]->getPositionY());
	clockGame->setCallback([this]() {
		sendReady(TypeSend::AUTO);
	});
	
	for (int i = 0; i < NUM_CHI; i++) {
		arrayBorder[i] = (ImageView*)getControl("border" + to_string(i), groupCard);
		bgTypeChi[i] = (ImageView*)getControl("bgTypeChi" + to_string(i), groupCard);
		bgTypeChi[i]->setLocalZOrder(10);

		typeChi[i] = Text::create("a", FONT_BOLD, 18);
		typeChi[i]->enableOutline(Color4B(10, 10, 10, 255), 1);
		groupCard->addChild(typeChi[i]);
		typeChi[i]->setLocalZOrder(11);
		typeChi[i]->setAnchorPoint(Vec2(0.5, 0.5f));
		typeChi[i]->setPosition(Vec2(bgTypeChi[i]->getPositionX(), bgTypeChi[i]->getPositionY()));
		

		Node* clipper = getControl("clipper" + to_string(i), groupCard);
		clipper->setLocalZOrder(11);
        arrayEffectChi[i] = new Sparkle(clipper->getContentSize().width, clipper->getContentSize().height, "Board/Particles/flare.png");
        clipper->addChild(arrayEffectChi[i]);
        arrayEffectChi[i]->setVisible(false);
        arrayEffectChi[i]->emitTime = 0.1f;
        arrayEffectChi[i]->type = SPARKLE_SHOW;
	}
	effectImage = Sprite::create("table/lucPheBon.png");
	groupCard->addChild(effectImage);
	effectImage->setLocalZOrder(10);
	effectImage->setPosition(arrayCard[2]->getPosition());

    if (languageMgr->checkCurrentLanguage(LANGUAGE_EN))
    {
        string res = "table/textEnglish/btnReady.png";
        btnComplete->loadTextures(res, res, res);
    }
}

void BinhTruyenThong::onEnterFinish()
{
	clockGame->onEnterFinish();
    touchCard = -1;
//	highlightCard(false);
}

void BinhTruyenThong::showEffect(Vec2 arrayPos[], float widthCard, bool effectGUI)
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(0);
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setIdCard(info->arrayCard[i]);
		if (effectGUI) {
			Vec2 pos = groupCard->convertToNodeSpace(arrayPos[i]);
			arrayCard[i]->setPosition(pos);
			float scale = widthCard / (arrayCard[i]->getCardWidth() * this->groupCard->getScale());
			arrayCard[i]->setScale(scale);
			arrayCard[i]->moveToDefault(0.3, 0.02 * i);
		}
		else {
			arrayCard[i]->setPosition(arrayCard[i]->getDefaultPos());
		}
	}
	btnComplete->setVisible(false);
	if (effectGUI) {
		runAction(Sequence::create(
			DelayTime::create(0.5),
			CallFuncN::create(AX_CALLBACK_1(BinhTruyenThong::callbackShow, this)),
			NULL
		));
	}
	else {
		callbackShow(NULL);
	}
	effectImage->setVisible(false);
    for (int i = 0; i < 3; i++) {
        arrayEffectChi[i]->setVisible(false);
    }
}

void BinhTruyenThong::callbackShow(Node* pSender)
{
	highlightCard(false);
	btnComplete->setVisible(true);
}

void BinhTruyenThong::onButtonRelease(ax::ui::Button* button, int id)
{
	switch (id)
	{
	case BINH_TRUYEN_THONG_BTN_COMPLETE:
	{
		sendReady(TypeSend::MANUAL);
		onClose();
		break;
	}
	case BINH_TRUYEN_THONG_BTN_SWAP:
	{
//		MaubinhPlayerCard playerCard;
//		int i, j, num;
//		effectImage->setVisible(false);
//		int arrayIdCard[13] = { 28 ,22 ,50, 3, 15, 31 ,49, 41, 36, 7 ,21 ,10, 37 };
//		for (i = NUM_CARD - 1; i >= 0; i--) {
//			MaubinhGroupCardLogic* group = new MaubinhGroupCardLogic();
//			group->AddCardByID(arrayCard[i]->id);
//			//group->AddCardByID(arrayIdCard[i]);
//			playerCard.AddGroupCard(group);
//		}
//		int* arrayId;
//		arrayId = playerCard.getAutoArrangeCard();
//		string s = "";
//		string s1 = "";
//		for (int i = 0; i < NUM_CARD; i++) {
//			AXLOGD("INDEX %i %i ", i, arrayId[i]);
//			s = s + ", " + to_string(arrayId[i]);
//		}
//		AXLOGD("ARRAY ID %s ", s.c_str());
//		for (int i = 0; i < NUM_CARD; i++) {
//			arrayCard[i]->setIdCard(arrayId[i]);
//		}
//		return;
		for (int i = 0; i < NUM_CARD_BIG_CHI; i++) {
			swapCard(arrayCard[i], arrayCard[NUM_CARD_BIG_CHI + i]);
			highlightCard(false);
		}
		break;
	}
	case BINH_TRUYEN_THONG_BTN_HARD:
	{
		gameMgr->useGuiAt = true;
		UserDefault::getInstance()->setBoolForKey("useGuiAt", true);
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

void BinhTruyenThong::sendReady(TypeSend type)
{
	
	TienlenGameSound::playSoundfinishgroupcard();
	vector <int> arrayId = getArrayId();
	vector <Vec2> arrayPos;
	vector <float> arraySize;
	
	for (int i = 0; i < NUM_CARD; i++) {
		arrayPos.push_back(groupCard->convertToWorldSpace(arrayCard[i]->getPosition()));
		arraySize.push_back(arrayCard[i]->getCardWidth() * groupCard->getScale());
	}
	BinhGameLogic::getInstance()->setMyCard(arrayId, arrayPos, arraySize);
	onClose();
	if (BinhGameLogic::getInstance()->isOffline) {
		BinhGameLogic::getInstance()->timeAuto = 0;
		BinhGameLogic::getInstance()->ready(0);
	}
    else {
        binhInGameMgr->sendReady(arrayId, type);
        binhInGameMgr->sendConfirmInGame();
    }
}

void BinhTruyenThong::touchEvent(Object *pSender, Widget::TouchEventType type)
{
	BinhCardButton* card = dynamic_cast<BinhCardButton*> (pSender);
	Vec2 point = card->getTouchMovePosition();
	point = groupCard->convertToNodeSpace(point);
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		AXLOGD("TOUCH BEGAN ");
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

		break;

	default:
		break;
	}
}

void BinhTruyenThong::onTouchBeganCard(BinhCardButton * card)
{
	if (touchCard < 0)
		touchCard = card->index;
	arrayCard[touchCard]->setLocalZOrder(1);
}

void BinhTruyenThong::onTouchMoveCard(BinhCardButton* card, Vec2 point)
{
	card->setLocalZOrder(20);
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

void BinhTruyenThong::onTouchEndCard(BinhCardButton * card, Vec2 point)
{
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
			card->moveToDefault(0.3);
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
			card->setSelect(!card->IsSelect());
			TalaGameSound::playEffect(TalaInGameMgr::SOUND_SELECT_CARD);
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
		highlightCard(true);
	}
}

void BinhTruyenThong::onTouchCancelCard(BinhCardButton* card, Vec2 point)
{

}

int BinhTruyenThong::getCardFromPoint(Vec2 point, int indexNotSelect)
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (i != indexNotSelect) {
			Rect rect = arrayCard[i]->getBoundingBox();
			if (rect.containsPoint(point)) {
				return i;
				break;
			}
		}
	}
	return -1;
}

void BinhTruyenThong::swapCard(BinhCardButton* card1, BinhCardButton* card2)
{
	int saveId = card1->id;
	card1->setIdCard(card2->id);
	card2->setIdCard(saveId);
	Vec2 savePos = card1->getPosition();
	card1->setPosition(card2->getPosition());
	card2->setPosition(savePos);
	card1->moveToDefault(0.3);
	card2->moveToDefault(0.3);
	card2->setSelect(false);
	card1->setSelect(false);
	card1->setLocalZOrder(2);
	card2->setLocalZOrder(1);
	TalaGameSound::playEffect(TalaInGameMgr::SOUND_DRAW_CARD);
}

void BinhTruyenThong::callbackSwapCard(Node* pSender)
{
	pSender->setLocalZOrder(0);
}

void BinhTruyenThong::highlightCard(bool sound)
{
	MaubinhPlayerCard playerCard;
	int i, j, num;
	effectImage->setVisible(false);
	for (i = NUM_CARD - 1; i >= 0; i--) {
		MaubinhGroupCardLogic* group = new MaubinhGroupCardLogic();
		group->AddCardByID(arrayCard[i]->id);
		playerCard.AddGroupCard(group);
	}
	playerCard.SapXepTruocSoBai();
	int cardKind = playerCard.GetPlayerCardsKind(false);

	bool isEffect = false;
	bool mauBinh = false;
	checkBoBai(playerCard, cardKind, mauBinh, isEffect);
	if (!mauBinh  && sound) {
		playSoundChi(playerCard);
	}
	checkTypeChi(playerCard);
	BinhGameLogic::getInstance()->showDarkCard(playerCard, cardKind, mauBinh, arrayCard);
}

void BinhTruyenThong::checkBoBai(MaubinhPlayerCard playerCard, int cardKind, bool &mauBinh, bool &isEffect)
{
	int i;
	for (i = 0; i < NUM_CHI; i++) {
	//	arrayIconCheck[i]->setVisible(true);
		arrayBorder[i]->setColor(Color3B(16, 151, 2));
		bgTypeChi[i]->setColor(Color3B(16, 151, 2));
	}
	switch (cardKind) {
	case EM_BINHLUNG:
	{
		mauBinh = false;
		isEffect = true;
		bool wrongChi = playerCard.getWrongChi0(false);
		if (wrongChi) {
			arrayBorder[CHI_DAU]->setColor(Color3B(190, 1, 27));
			bgTypeChi[CHI_DAU]->setColor(Color3B(190, 1, 27));
		}
		wrongChi = playerCard.getWrongChi1(false);
		if (wrongChi) {
			arrayBorder[CHI_GIUA]->setColor(Color3B(190, 1, 27));
			bgTypeChi[CHI_GIUA]->setColor(Color3B(190, 1, 27));
		}
		break;
	}
	case EM_LUCPHEBON:
	{
		effectBoBai(BinhGameLogic::getInstance()->getResourceBinh(cardKind));
		mauBinh = true;
		isEffect = true;
		effectParticle();
		TienlenGameSound::playSoundmaubinh_lucphebon();
		TienlenGameSound::playSoundThang();
        effect3Chi();
		break;
	}
	case EM_3SANH:
	{
		effectBoBai(BinhGameLogic::getInstance()->getResourceBinh(cardKind));
		mauBinh = true;
		isEffect = true;
		effectParticle();
		TienlenGameSound::playSoundmaubinh_3caisanh();
		TienlenGameSound::playSoundThang();
        effect3Chi();
		break;
	}
	case EM_3THUNG:
	{
		effectBoBai(BinhGameLogic::getInstance()->getResourceBinh(cardKind));
		mauBinh = true;
		isEffect = true;
		effectParticle();
		TienlenGameSound::playSoundmaubinh_3caithung();
		TienlenGameSound::playSoundThang();
        effect3Chi();
		break;
	}
	case EM_SANHRONG:
	{
		effectBoBai(BinhGameLogic::getInstance()->getResourceBinh(cardKind));
		 mauBinh = true;
		isEffect = true;
		effectParticle();
		TienlenGameSound::playSoundmaubinh_sanhrong();
		TienlenGameSound::playSoundThang();
        effect3Chi();
		break;
	}
	default:
		mauBinh = false;
		break;
	}
}

void BinhTruyenThong::playSoundChi(MaubinhPlayerCard playerCard)
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
	//	TienlenGameSound::playSoundxepbai_mauthau();
		break;
	case EG_DOI:
		//TienlenGameSound::playSoundxepbai_doi();
		break;
	case EG_THU:
		//TienlenGameSound::playSoundxepbai_thu();
		break;
	case EG_SAMCO:
	//	TienlenGameSound::playSoundxepbai_samchi();
		if (chiGoal == CHI_DAU) {
			effectChi(chiGoal);
		}
		break;
	case EG_SANH:
		//TienlenGameSound::playSoundxepbai_sanh();
		effectChi(chiGoal);
		break;
	case EG_THUNG:
		//TienlenGameSound::playSoundxepbai_thung();
		effectChi(chiGoal);
		break;
	case EG_TUQUI:
		//TienlenGameSound::playSoundxepbai_tuquy();
		effectChi(chiGoal);
		break;
	case EG_THUNGPHASANH:
	//	TienlenGameSound::playSoundxepbai_thungphasanh();
		effectChi(chiGoal);
		break;
	case EG_CULU:
		//TienlenGameSound::playSoundxepbai_culu();
		effectChi(chiGoal);
		break;
	default:
		break;
	}
}

/**
 * Hien thi Loai cua tung chi mot tren bo bai dang xap xep
 */
void BinhTruyenThong::checkTypeChi(MaubinhPlayerCard playerCard)
{
	switch (playerCard.ChiGiua->GetGroupKind()) {
	case EG_THUNGPHASANH:
		showTypeChi(CHI_GIUA, 6, true);
		break;
	case EG_TUQUI:
		showTypeChi(CHI_GIUA, 7, true);
		break;
	case EG_CULU:
		showTypeChi(CHI_GIUA, 9, true);
		break;
	default:
		showTypeChi(CHI_GIUA, playerCard.ChiGiua->GetGroupKind(), false);
		break;
	}

	switch (playerCard.ChiCuoi->GetGroupKind()) {
	case EG_THUNGPHASANH:
		showTypeChi(CHI_CUOI, 11, true);
		break;
	case EG_TUQUI:
		showTypeChi(CHI_CUOI, 10, true);
		break;
	default:
		showTypeChi(CHI_CUOI, playerCard.ChiCuoi->GetGroupKind(), false);
		break;
	}

	switch (playerCard.ChiDau->GetGroupKind()) {
	case EG_SAMCO:
		showTypeChi(CHI_DAU, 8, true);
		break;
	default:
		showTypeChi(CHI_DAU, playerCard.ChiDau->GetGroupKind(), false);
		break;
	}
}

void BinhTruyenThong::showTypeChi(int chi, int type, bool binh)
{
	string resource;
	//string arrayBinh[10] = { "", "", "", "", "","", "", "Thung pha sanh", "", "","", "", "", "" };
	if (binh) {
		resource = "table/binh_" + to_string(type) + ".png";
		resource = LocalizedString::to("CARDKIND_" + to_string(type));
		typeChi[chi]->setTextColor(Color4B(252, 241, 65, 255));
	}
	else {
		resource = "table/typechi_" + to_string(type) + ".png";
		resource = LocalizedString::to("GROUPKIND_" + to_string(type));
		typeChi[chi]->setTextColor(Color4B(255, 255, 255, 255));
	}
	typeChi[chi]->setString(resource);
}

void BinhTruyenThong::effect3Chi() {
    for (int i = 0; i < 3; i++) {
        arrayEffectChi[i]->startEffect(1000);
    }
}

void BinhTruyenThong::effectChi(int chi)
{
//	arrayEffectChi[chi]->getAnimation()->gotoAndPlay("1", -1, -1, 1);
	arrayEffectChi[chi]->startEffect(2.0);
}

void BinhTruyenThong::effectBoBai(string resource)
{
	effectImage->setVisible(true);
	effectImage->setTexture(resource);
	effectImage->setScale(0);
	effectImage->runAction(EaseBounceOut::create(ScaleTo::create(0.5, 1.0)));
}

void BinhTruyenThong::effectParticle()
{

}

void BinhTruyenThong::setDarkAllCard(bool isDark)
{
	for (int i = 0; i < NUM_CARD; i++)
		arrayCard[i]->setDark(isDark);
}

void BinhTruyenThong::setGameTime(int time)
{
	//clockGame->setTime(20);
	clockGame->setTime(time);
}

vector<int> BinhTruyenThong::getArrayId()
{
	vector<int> arrayId;
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard[i]->isVisible())
			arrayId.push_back(arrayCard[i]->id);
	}
	return arrayId;
}

const std::string BinhTruyenThong::className = "BinhTruyenThong";
const int BinhTruyenThong::TAG = 10050;

