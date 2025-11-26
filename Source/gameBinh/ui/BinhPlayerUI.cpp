#include "BinhPlayerUI.h"
#include "core/utils/StringUtility.h"
#include "../logic/BinhGameLogic.h"
#include "core/utils/TienlenGameSound.h"
#include "Game/Utility/JNIUtils.h"
#include "core/gui/SceneMgr.h"
#include "MauBinhGroup.h"
#include "common/UserInfoGUI.h"

#define PLAYER_UI_BTN_INFO 1
BinhPlayerUI::BinhPlayerUI()
{
	chairIndex = 0;
}

BinhPlayerUI::~BinhPlayerUI()
{

}

void BinhPlayerUI::initGUI()
{
	initCommon();
	initGroupCard();
}

void BinhPlayerUI::initCommon()
{
	bg = (ImageView*) layout->getChildByName("bg");
	avatarUI = (Node*)layout->getChildByName("avatarUI");
	avatarUI->setLocalZOrder(50);
	btnAvatar = (Button*)avatarUI->getChildByName("btnAvatar");
	btnAvatar->setOpacity(0);
	btnAvatar->addClickEventListener([this](Object*) {
		//userMgr->openUserInfo(BinhGameLogic::getInstance()->getUserInfo(chairIndex));
		if (chairIndex == 0)
		{
			BaseLayer* layer = sceneMgr->openGUI(UserInfoGUI::className, UserInfoGUI::ZODER, UserInfoGUI::TAG);
			UserInfoGUI *gui = dynamic_cast<UserInfoGUI*> (layer);
			gui->showInfo(TypeGame::BINH);
		}
		//sceneMgr->openGUI(NewLevelGUI::className, NewLevelGUI::ZODER, NewLevelGUI::TAG);
	});

	btnAvatar->setPressedActionEnabled(false);
	labelName = (Text *)avatarUI->getChildByName("name");
	labelGold = (Text *)avatarUI->getChildByName("gold");
	labelGold->setVisible(true);
	//this.icoGold = this.getControl("icoGold", this.btnAvatar);

	bgAvatar = avatarUI->getChildByName("bgAvatar");
	//uiAvatar = AvatarUI::create("Common/defaultAvatar.png", "Common/maskAvatar.png");////engine.UIavatar->create("Common/defaultavatar->png");
	uiAvatar = Sprite::create("avatar/avatar_0.png");
	Size size = bgAvatar->getContentSize();
	uiAvatar->setScale(0.92);
	uiAvatar->setPosition(Vec2(size.width / 2, size.height * 0.43));
	bgAvatar->addChild(uiAvatar, -1);

	borderAvatar = (ImageView*)bgAvatar->getChildByName("border");
	borderAvatar->setLocalZOrder(1);
	//defaultFrame->setVisible(false);

	imgState = (ImageView*)layout->getChildByName("imgState");
	imgState->ignoreContentAdaptWithSize(true);
	imgState->setLocalZOrder(30);
	
	pEffect = Node::create();
	avatarUI->addChild(pEffect);
	pEffect->setPosition(bgAvatar->getPosition());

	//effectViewing = new Viewing();
	//effectViewing->setPosition(btnAvatar->getPosition());
	//bg->addChild(effectViewing);

	imgSap = (ImageView*)layout->getChildByName("imageSap");
	imgSap->setLocalZOrder(50);

	//moneyGroup = TextBMFont::create( "10000", "Font/loseNumber.fnt");
	moneyGroup = Text::create("10000", "fonts/tahomabd.ttf", 40);
	bgAvatar->addChild(moneyGroup);
	moneyGroup->setPosition(borderAvatar->getPosition());
	moneyGroup->setLocalZOrder(2);

	imgResult = Sprite::create("table/win.png");
	avatarUI->addChild(imgResult, 1);
	imgResult->setPosition(bgAvatar->getPositionX(), bgAvatar->getPositionY() - bgAvatar->getContentSize().height * 0.6);

	imgEffectChi = Sprite::create("table/win.png");
	layout->addChild(imgEffectChi);
	imgEffectChi->setLocalZOrder(50);

     auto effect = efk::Effect::create("fire.efk", 30);
    if (effect != nullptr)
    {
        effBomb = efk::EffectEmitter::create(manager);
        effBomb->setEffect(effect);
        effBomb->setPlayOnEnter(false);
        effBomb->setRemoveOnStop(false);
        effBomb->setSpeed(0.5);
        // emitter->setScale(13);
        effBomb->setPosition(btnAvatar->getPosition());
        layout->addChild(effBomb, 100);
    }

	//effectMauBinh = DBCCFactory::getInstance()->buildArmatureNode("tile_light");
	//if (effectMauBinh) {
	//	avatarUI->addChild(effectMauBinh);
	//	if (chairIndex == USER_TOP)
	//		effectMauBinh->setPosition(btnAvatar->getPositionX(), btnAvatar->getPositionY() - btnAvatar->getContentSize().height * 0.8);
	//	else
	//		effectMauBinh->setPosition(btnAvatar->getPositionX(), btnAvatar->getPositionY() + btnAvatar->getContentSize().height * 0.8);
	//	effectMauBinh->setScale(0.65);
	//}

	//effectWin = DBCCFactory::getInstance()->buildArmatureNode("Chest");
	//if (effectWin) {
	//	avatarUI->addChild(effectWin, -1);
	//	effectWin->setVisible(false);
	//	effectWin->setPosition(avatarUI->getContentSize().width * 0.5, avatarUI->getContentSize().height * 0.5);
	//	//effectMauBinh->setScale(0.65);
	//}
    int idAvatar = AXRANDOM_0_1() * 41.99999;
    uiAvatar->setTexture("images1/avatar_" + to_string(idAvatar) + ".png");
}

void BinhPlayerUI::onEnterFinish()
{
	
}

void BinhPlayerUI::initGroupCard()
{
	Node* panel = layout->getChildByName("card1");
	float scale = 0.3;
	if (chairIndex == 0) {
		scale = 0.4;
	}
	initOneGroupCard(panel, scale, arrayCard1);

	panel = layout->getChildByName("card2");
	scale = 0.4;
	if (chairIndex == 0) {
		scale = 0.6;
		//scale = 1.5;
	}
	initOneGroupCard(panel, scale, arrayCard2);
}

void BinhPlayerUI::initOneGroupCard(Node* panel, float scale, BinhCardButton* arrayCard[])
{
	for (int i = 0; i < NUM_CARD; i++) {
		int index = i / NUM_CARD_BIG_CHI;
		int midle = (index == 2 ? 1 : 2);
		arrayCard[i] = new BinhCardButton(52);
		layout->addChild(arrayCard[i]);
		arrayCard[i]->setScale(scale);
		float padY = arrayCard[i]->getCardHeight() * 0.55;
		float padX = arrayCard[i]->getCardWidth() * 0.45;
		if (index == 2)
			arrayCard[i]->setPositionX(arrayCard[i]->getCardWidth() * 0.5 + (i % NUM_CARD_BIG_CHI + 1) * padX + panel->getPositionX());
		else 
			arrayCard[i]->setPositionX(arrayCard[i]->getCardWidth() * 0.5 + (i % NUM_CARD_BIG_CHI) * padX + panel->getPositionX());
		arrayCard[i]->setRotation(5 * (i % NUM_CARD_BIG_CHI - midle));
		arrayCard[i]->setPositionY(arrayCard[i]->getCardHeight() * 0.5 + padY * index + panel->getPositionY() - 3 * abs(i % NUM_CARD_BIG_CHI - midle));
		arrayCard[i]->setLocalZOrder(BinhGameLogic::getInstance()->getZOrderCard(i) + 10);
		arrayCard[i]->saveInfoCard();
	}
}

void BinhPlayerUI::setInfo(BinhPlayerInfo* pInfo)
{
	layout->setVisible(true);
	labelGold->setString(StringUtility::formatNumberSymbol(pInfo->Gold()).c_str());
	AXLOGD("GOLD *** %s ", StringUtility::formatNumberSymbol(pInfo->Gold()).c_str());
    string s = pInfo->DisplayName();
	labelName->setString(StringUtility::longWordBreaker(s, 12).c_str());
	//uiAvatar->asyncExecuteWithUrl(std::to_string(pInfo->ID()), pInfo->Avatar());
	//uiAvatar->setTexture(pInfo->Avatar());
	//uiAvatar->setTexture("avatar/avatar_" + to_string(chairIndex) + ".png");
	updateMoney();
	setViewing();
}

void BinhPlayerUI::newGame() {
	setViewing();
	moneyGroup->setVisible(false);
	pEffect->removeAllChildren();
	imgState->setVisible(false);
	imgResult->setVisible(false);
	imgSap->setVisible(false);
	imgEffectChi->setVisible(false);
	//effectMauBinh->setVisible(false);
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard1[i]->setVisible(false);
		arrayCard2[i]->setVisible(false);
		arrayCard2[i]->setIdCard(52);
		arrayCard1[i]->setIdCard(52);
		arrayCard2[i]->setLocalZOrder(arrayCard2[i]->rootZOrder);
	}
	setDarkAll(false);
}

void BinhPlayerUI::setViewing()
{
	countViewing = 0;
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	if (info->isViewing()) {
		uiAvatar->setOpacity(150);
		labelName->setOpacity(150);
		labelGold->setOpacity(150);
		AXLOGD("SET VIEWING ");
	}
	else {
		uiAvatar->setOpacity(255);
		labelName->setOpacity(255);
		labelGold->setOpacity(255);
		AXLOGD("NO VIEWING ");
	}
}

void BinhPlayerUI::updateDealCard(int num)
{

}

void BinhPlayerUI::endDealCard()
{
	showArrayCard1(true);
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	if (info->IsArranging()) {
		unReady();
	}
	else {
		ready();
	}
}

void BinhPlayerUI::updateCard()
{
	updateCardOneChi(CHI_1);
	updateCardOneChi(CHI_2);
	updateCardOneChi(CHI_3);
}

void BinhPlayerUI::ready()
{
	imgState->setVisible(true);
	imgState->loadTexture("table/arranged.png");
}

void BinhPlayerUI::unReady()
{
	imgState->setVisible(true);
	imgState->loadTexture("table/arranging.png");
}

/**
 * cap nhat card luc het van choi
 */
void BinhPlayerUI::endCard()
{
	imgState->setVisible(false);
	imgEffectChi->setVisible(false);
	// phong to bai len
	startCompare();
}

/**
 * Update card khi reconnect lai ban choi, view game
 */
void BinhPlayerUI::updateCardEnd()
{
	showArrayCard2(true);
	showArrayCard1(false);
	updateCard();
}

void BinhPlayerUI::chiIndex(char chi)
{
	// dua quan card ve dung ZOrder
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	setNormalZOrder();
}

void BinhPlayerUI::startCompare()
{
	setDarkAll(true);
	showArrayCard1(false);
	showArrayCard2(true);
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard2[i]->setPosition(arrayCard1[i]->getPosition());
		arrayCard2[i]->setScale(arrayCard1[i]->getScale());
		arrayCard2[i]->moveToDefault(0.2, 0);
	}
}

void BinhPlayerUI::compareChi(char chi, double money, int result)
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	if (chi <= CHI_3) {
		effectGold(money);
		for (int i = 0; i < NUM_CARD; i++) {
			arrayCard2[i]->setDark(true);
		}

		// open card o chi hien tai
		int num = NUM_CARD_BIG_CHI * chi;
		int center = 2;
		if (chi == CHI_3) {
			num = NUM_CARD;
			center = 1;
		}
		if (chairIndex != MY_INDEX) {
			updateCardOneChi(chi);
		}
		for (int i = NUM_CARD_BIG_CHI * (chi - 1); i < num; i++) {
			arrayCard2[i]->setDark(false);
			arrayCard2[i]->setLocalZOrder(NUM_CARD * 2 + i);
			if (chairIndex != MY_INDEX) {
				arrayCard2[i]->showCard(arrayCard2[NUM_CARD_BIG_CHI * (chi - 1) + center]->getDefaultPos());
			}
		}
		
		// show effect cua loai chi hien tai
		if (BinhGameLogic::getInstance()->isTinhAt() && info->IsBinhLung()) {
            string res = BinhGameLogic::getInstance()->getRes();
            effectChi(chi, ("table/" + res + "binhLung.png").c_str());
		}
		else {
			bool isEffectParticle = false;
			string resource = BinhGameLogic::getInstance()->getResourceEffectChiCompare(chi, money, info->PlayerCard(), isEffectParticle, chairIndex == MY_INDEX);
			//resource = "TextTypeChi.png";
			effectChi(chi, resource);
			if (isEffectParticle) {
				/*DBCCArmatureNode *effIcon = DBCCFactory::getInstance()->buildArmatureNode("bom_change");
				if (effIcon) {
					layout->addChild(effIcon, 100);
					effIcon->setScale(0.5);
					effIcon->getAnimation()->gotoAndPlay("run", -1, -1, 1);
					effIcon->setPosition(imgEffectChi->getPosition().x, imgEffectChi->getPosition().y - 40);
					effIcon->setCompleteListener([](DBCCArmatureNode* armature) {
						armature->removeFromParent();
					});
				}*/
			}
		}
		//imgResult->setVisible(true);
		//imgResult->setTexture(BinhGameLogic::getInstance()->getResourceResult(result));
	}
	else {
		// ket thuc so chi
	}
}

void BinhPlayerUI::sapBai(double money, SapBaiType sapType)
{
	AXLOGD("MONEY SAP %f", money);
	setNormalZOrder();
	if (sapType == SapBaiType::BI_SAP) {
		setDarkCard2(true);
		imgSap->setVisible(true);
		effectGold(money, false);

        effBomb->stop();
        effBomb->setVisible(true);
        effBomb->play(0);
        effBomb->setPosition(arrayCard2[7]->getPosition());
	}
	else {
		setDarkCard2(false);
		effectGold(money, true);
	}
}

void BinhPlayerUI::sapLang(char chair, double money)
{
	imgSap->setVisible(false);
	if (chair == chairIndex) {
		effectGold(money, true);
	}
	else {
		effectGold(money, false);
	}
}

void BinhPlayerUI::binhAt(double money)
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	if (info->getNumAt() > 1) {
		effectGold(money, true);
		for (int i = 0; i < NUM_CARD; i++) {
			if (arrayCard2[i]->id >= 48) {
				arrayCard2[i]->showAt();
			}
		}
	}
	else if (info->getNumAt() < 1) {
		effectGold(money, false);
	}
}

void BinhPlayerUI::soBaiBinhLung(double money)
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	
	if (info->IsBinhLung()) {
		setDarkCard2(true);
		updateCard();
        string res = BinhGameLogic::getInstance()->getRes();
        effectChi(CHI_3, "table/" + res + "binhLung.png");
		effectGold(money, true);
		if (chairIndex == MY_INDEX)
			TienlenGameSound::playSoundBinhLung();
	}
	else {
		effectGold(money, false);
	}
}

void BinhPlayerUI::soBaiMauBinh(double money)
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);

	if (info->IsMauBinh()) {
		setDarkCard2(false);
		updateCard();
		// so nguoi Mau binh > 1 thi moi hien effect Binh o tung vi tri nguoi choi
		if (BinhGameLogic::getInstance()->getNumMauBinh() > 1) {
			string animation;
			int kind = BinhGameLogic::getInstance()->getEffectMaubinh(chairIndex);

			MauBinhGroup* group = new MauBinhGroup();
			pEffect->addChild(group);
			Vec2 pos = arrayCard2[7]->getPosition();
			pos = arrayCard2[7]->getParent()->convertToWorldSpace(pos);
			pos = pEffect->convertToNodeSpace(pos);
			group->setPosition(pos);
			group->showMauBinh(kind);
			group->setScale(0.35);
			group->runAction(
				Sequence::create(
					DelayTime::create(5.0),
					FadeOut::create(0.5),
					RemoveSelf::create(),
					NULL
				)
			);

			/*DBCCArmatureNode *effIcon = DBCCFactory::getInstance()->buildArmatureNode(resource);
			if (effIcon) {
				pEffect->addChild(effIcon);
				effIcon->getAnimation()->gotoAndPlay(animation, -1, -1, 1);
				effIcon->setScale(0.3);
				effIcon->runAction(
					Sequence::create(
						DelayTime::create(3.0),
						RemoveSelf::create(),
						NULL
					)
				);
			}*/
		}
		//effectMauBinh->setVisible(true);
		//effectMauBinh->gotoAndPlay("run", -1, -1, -1);
		effectGold(money, true);
		showParticle();
		if (chairIndex == 0) {
			JNIUtils::sendEvent("mau_binh_my", "1");
		}
		else {
			JNIUtils::sendEvent("mau_binh_ther", "1");
		}
	}
	else {
		setDarkCard2(true);
		effectGold(money, false);
	}
}

void BinhPlayerUI::summary(double money)
{
	setNormalZOrder();
	imgSap->setVisible(false);
	imgEffectChi->setVisible(false);
	setDarkCard2(false);
	effectGold(money);
	imgResult->setVisible(true);
	imgResult->setTexture(BinhGameLogic::getInstance()->getResourceResult(money >= 0));
	if (money > 0) {
		showParticle();
		/*effectWin->setVisible(true);
		effectWin->getAnimation()->gotoAndPlay("1", -1, -1, 1);
		effectWin->runAction(
			Sequence::create(
				DelayTime::create(5.0),
				Hide::create(),
				NULL
			)
		);*/
	}
}

void BinhPlayerUI::effectGold(double gold, bool isWin)
{
	if (gold >= 0) {
		//TextBMFont *text;
	//	moneyGroup->setFntFile("Font/winNumber.fnt");
		moneyGroup->setTextColor(Color4B(231, 233, 10, 255));
		moneyGroup->enableOutline(Color4B(125, 48, 1, 255), 2);
		moneyGroup->setString("+" + StringUtility::pointNumber(gold));

		showParticle();
	}
	else {
		//moneyGroup->setFntFile("Font/loseNumber.fnt");
		moneyGroup->setTextColor(Color4B(210, 210, 210, 255));
		moneyGroup->enableOutline(Color4B(100, 100, 100, 255), 2);
		moneyGroup->setString(StringUtility::pointNumber(gold));
	}
	
//	moneyGroup->setMoney(gold, isWin);
//	moneyGroup->setPositionX(btnAvatar->getPositionX() - moneyGroup->getContentSize().width * 0.5);
	if (chairIndex == 1) {
		if (moneyGroup->getPositionX() - moneyGroup->getContentSize().width * 0.5 < -20) {
			moneyGroup->setPositionX(moneyGroup->getContentSize().width * 0.5 - 20);
		}
		else {
			moneyGroup->setPositionX(bgAvatar->getContentSize().width * 0.5);
		}
	}
	else if (chairIndex == 3) {
		if (moneyGroup->getPositionX() + moneyGroup->getContentSize().width * 0.5 > bgAvatar->getContentSize().width + 20) {
			moneyGroup->setPositionX(bgAvatar->getContentSize().width + 20 - moneyGroup->getContentSize().width * 0.5);
		}
		else {
			moneyGroup->setPositionX(bgAvatar->getContentSize().width * 0.5);
		}
	}
	
	moneyGroup->setVisible(true);
	moneyGroup->setOpacity(255);
    moneyGroup->setScale(0);
	moneyGroup->stopAllActions();
	moneyGroup->runAction(
		//Sequence::create(
		//	Spawn::create(
			//	FadeIn::create(0.4),
				EaseBounceOut::create(ScaleTo::create(0.5, 1.0f, 1.0f))
		//	)
			//NULL
		//)
	);
}

void BinhPlayerUI::chatEmoticon(char id, char emoId)
{
	
}

void BinhPlayerUI::showEffectVip()
{
	
}

void BinhPlayerUI::updateMoney()
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	labelGold->setString(StringUtility::formatNumberSymbol(info->Gold()).c_str());
    borderAvatar->loadTexture(info->getAvatarLevel());
	//if (info->Gold())
}

void BinhPlayerUI::updateAvatarFrame()
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	borderAvatar->loadTexture(info->getAvatarLevel());
}

void BinhPlayerUI::setRoomOwner(bool show)
{
}

Size BinhPlayerUI::getCardSize()
{
	return Size(arrayCard1[0]->getCardWidth() * layout->getScale(), arrayCard1[0]->getCardHeight() * layout->getScale());
}

Vec2 BinhPlayerUI::getCardPos(int index)
{
	return layout->convertToWorldSpace(arrayCard1[index]->getPosition());
}

Vec2 BinhPlayerUI::getCardPos2(int index)
{
	return layout->convertToWorldSpace(arrayCard2[index]->getPosition());
}

float BinhPlayerUI::getCardRotation(int index)
{
	return arrayCard1[index]->getRotation();
}

Vec2 BinhPlayerUI::getCardPosById(int id)
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard1[i]->id == id)
			return layout->convertToWorldSpace(arrayCard1[i]->getPosition());
	}
	return Vec2(0, 0);
}

void BinhPlayerUI::setDarkCard(bool isDark)
{
}

int BinhPlayerUI::getIndexById(int id)
{
	for (int i = 0; i < NUM_CARD; i++) {
		if (arrayCard1[i]->id == id)
			return i;
	}
	return 0;
}

void BinhPlayerUI::setDarkAll(bool isDark)
{
	if (isDark) {
		uiAvatar->setColor(Color3B(80, 80, 80));
		labelGold->setColor(Color3B(80, 80, 80));
		labelName->setColor(Color3B(80, 80, 80));
	}
	else {
		uiAvatar->setColor(Color3B(255, 255, 255));
		labelGold->setColor(Color3B(255, 255, 255));
		labelName->setColor(Color3B(255, 255, 255));
	}
}

Vec2 BinhPlayerUI::getPositionAvatar()
{
	Vec2 pos = Vec2(borderAvatar->getContentSize().width * 0.5, borderAvatar->getContentSize().height * 0.5);
	return borderAvatar->convertToWorldSpace(pos);
}

void BinhPlayerUI::showArrayCard1(bool show)
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard1[i]->setVisible(show);
	}
}

void BinhPlayerUI::showArrayCard2(bool show)
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard2[i]->setVisible(show);
	}
}

void BinhPlayerUI::setVisible(bool visible)
{
	layout->setVisible(visible);
}

bool BinhPlayerUI::isVisible()
{
	return layout->isVisible();
}

void BinhPlayerUI::setDarkCard1(bool isDark)
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard1[i]->setDark(isDark);
	}
}

void BinhPlayerUI::setDarkCard2(bool isDark)
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard2[i]->setDark(isDark);
		arrayCard2[i]->setLocalZOrder(arrayCard2[i]->rootZOrder);
	}
}

void BinhPlayerUI::effectChi(char chi, string resource)
{
	imgEffectChi->setVisible(true);
	imgEffectChi->stopAllActions();
	imgEffectChi->setScaleX(0);
	imgEffectChi->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
	imgEffectChi->setTexture(resource);
	if (chi == CHI_1) {
		imgEffectChi->setPositionX(arrayCard2[2]->getPositionX());
		imgEffectChi->setPositionY(arrayCard2[2]->getPositionY() - arrayCard2[2]->getCardHeight() * 0.1 - imgEffectChi->getContentSize().height * 0.5);
	}
	else if (chi == CHI_2) {
		imgEffectChi->setPositionX(arrayCard2[7]->getPositionX());
		imgEffectChi->setPositionY(arrayCard2[7]->getPositionY() - arrayCard2[7]->getCardHeight() * 0.1 - imgEffectChi->getContentSize().height * 0.5);
	}
	else {
		imgEffectChi->setPositionX(arrayCard2[6]->getPositionX() + 20);
		imgEffectChi->setPositionY(arrayCard2[12]->getPositionY() - arrayCard2[12]->getCardHeight() * 0.1 - imgEffectChi->getContentSize().height * 0.5);
	}
}

void BinhPlayerUI::updateCardOneChi(char chi)
{
	BinhPlayerInfo *info = BinhGameLogic::getInstance()->getInfo(chairIndex);
	MaubinhPlayerCard* playerCard = info->PlayerCard();
	playerCard->SapXepTruocSoBai();
	int start = (chi - 1) * NUM_CARD_BIG_CHI;
	string s = "";
	if (chi == CHI_1) {
		for (int i = 0; i < NUM_CARD_BIG_CHI; i++) {
			s = s + to_string(playerCard->ChiCuoi->Cards[i]->ID) + " ";
			arrayCard1[start + i]->setIdCard(playerCard->ChiCuoi->Cards[i]->ID);
			arrayCard2[start + i]->setIdCard(playerCard->ChiCuoi->Cards[i]->ID);
		}
		AXLOGD("DU MA NO %s ", s.c_str());
	}
	else if (chi == CHI_2) {
		for (int i = 0; i < NUM_CARD_BIG_CHI; i++) {
			arrayCard1[start + i]->setIdCard(playerCard->ChiGiua->Cards[i]->ID);
			arrayCard2[start + i]->setIdCard(playerCard->ChiGiua->Cards[i]->ID);
		}
	}
	else {
		for (int i = 0; i < NUM_CARD_SMALL_CHI; i++) {
			arrayCard1[start + i]->setIdCard(playerCard->ChiDau->Cards[i]->ID);
			arrayCard2[start + i]->setIdCard(playerCard->ChiDau->Cards[i]->ID);
		}
	}
}

void BinhPlayerUI::update(float delta)
{
	BinhPlayerInfo* info = BinhGameLogic::getInstance()->getInfo(chairIndex);
}

void BinhPlayerUI::setNormalZOrder()
{
	moneyGroup->setVisible(false);
	imgEffectChi->setVisible(false);
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard2[i]->setLocalZOrder(arrayCard2[i]->rootZOrder);
	}
}

void BinhPlayerUI::showParticle()
{
	auto particle = ParticleSystemQuad::create("Particles/effectMoney.plist");
	particle->setLocalZOrder(5);
	pEffect->addChild(particle);
	particle->setPosition(pEffect->getContentSize().width * 0.5, pEffect->getContentSize().height);
	particle->setAutoRemoveOnFinish(true);
}

void BinhPlayerUI::loadTheme(int idTheme)
{
	string arrayTheme[3] = { "RedTheme", "BlueTheme", "GreenTheme" };
	string name;
	switch (chairIndex)
	{
	case 0:
		name = "/bgMyPlayer.png";
		break;
	case 1:
		name = "/bgPlayerLeft.png";
		break;
	case 2:
		name = "/bgPlayerTop.png";
		break;
	case 3:
		name = "/bgPlayerRight.png";
		break;
	default:
		break;
	}
	bg->loadTexture("table/" + arrayTheme[idTheme] + name);
}

void BinhPlayerUI::onButtonRelease(Button* button, int id)
{
	switch (id) {
	case PLAYER_UI_BTN_INFO: {
		AXLOGD("PLAYER_UI_BTN_INFO ");
		if (chairIndex == 0)
			sceneMgr->openGUI(UserInfoGUI::className, UserInfoGUI::ZODER, UserInfoGUI::TAG);
		break;
	}
	}
}

void BinhPlayerUI::effectRenew()
{
    auto particle = ParticleSystemQuad::create("Particles/renew.plist");
    particle->setLocalZOrder(5);
    layout->addChild(particle);
    Vec2 pos = borderAvatar->getPosition();
    pos      = borderAvatar->getParent()->convertToWorldSpace(pos);
    pos      = layout->convertToNodeSpace(pos);
    particle->setPosition(pos);
    particle->setAutoRemoveOnFinish(true);

    int idAvatar = AXRANDOM_0_1() * 41.99999;
    uiAvatar->setTexture("images1/avatar_" + to_string(idAvatar) + ".png");
}
