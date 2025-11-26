#include "PlayerUI.h"
#include "core/utils/StringUtility.h"
#include "../logic/GameLogic.h"
#include "common/UserInfoGUI.h"

#define PLAYER_UI_BTN_INFO 1
PlayerUI::PlayerUI()
{
	chairIndex = 0;
}

PlayerUI::~PlayerUI()
{

}

bool PlayerUI::init()
{
	return BaseLayer::init();
}

void PlayerUI::initGUI()
{
	initCommon();
}

void PlayerUI::initCommon()
{
	bg = getControl("bg");

	btnAvatar = customizeButton("btnAvatar", PLAYER_UI_BTN_INFO, bg);
	btnAvatar->setPressedActionEnabled(false);
	labelName = (Text *)getControl("name", btnAvatar);
	labelGold = (Text *)getControl("gold", btnAvatar);
	labelGold->setVisible(true);
	labelGold->ignoreContentAdaptWithSize(true);

	avatar = (ImageView*)getControl("avatar", btnAvatar);
        int idAvatar = AXRANDOM_0_1() * 41.99999;
    avatar->loadTexture("images1/avatar_" + to_string(idAvatar) + ".png");
	
	borderAvatar = (ImageView*)getControl("border", btnAvatar);

	pEffect = getControl("pEffect", bg);
	pEffect->setLocalZOrder(1);
	
	turnClock = new ClockGame();
	btnAvatar->addChild(turnClock);
	turnClock->setPosition(btnAvatar->getContentSize().width / 2, btnAvatar->getContentSize().height / 2);

	effectCancel = new CancelTurn();
	effectCancel->setPosition(btnAvatar->getPosition());
	bg->addChild(effectCancel);

	moneyGroup = new MoneyGroup();
	moneyGroup->setMoney(100000);
	bg->addChild(moneyGroup);
	moneyGroup->setLocalZOrder(2);

	resultGroup = new ResultGroup();
	btnAvatar->addChild(resultGroup);
	resultGroup->setPosition(btnAvatar->getContentSize().width * 0.5, btnAvatar->getContentSize().height *  0.5);
	resultGroup->setScale(0.35);
	resultGroup->setLocalZOrder(10);
}

void PlayerUI::setInfo(PlayerInfo* pInfo)
{
	setVisible(true);
	labelGold->setString(StringUtility::formatNumberSymbol(pInfo->Gold()).c_str());
	AXLOGD("GOLD *** %s ", StringUtility::formatNumberSymbol(pInfo->Gold()).c_str());
	setLabelText(pInfo->DisplayName(), labelName);
	setViewing();
}

void PlayerUI::newGame() {
	showCancel(false);
	setViewing();
	moneyGroup->setVisible(false);
	pEffect->removeAllChildren();
	resultGroup->setVisible(false);
	setDarkCard(false);
	turnClock->setPause(true);
}

void PlayerUI::setViewing()
{
	if (GameLogic::getInstance()->getInfo(chairIndex)->isViewing()) {
		btnAvatar->setOpacity(150);
		labelName->setOpacity(150);
		labelGold->setOpacity(150);
	}
	else {
		btnAvatar->setOpacity(255);
		labelName->setOpacity(255);
		labelGold->setOpacity(255);
	}
}

void PlayerUI::updateDealCard(int num)
{
}

void PlayerUI::endDealCard()
{
	
}

void PlayerUI::changeTurn(int time)
{
	turnClock->setVisible(true);
	turnClock->setTime(time);
}

void PlayerUI::stopTurn()
{
	turnClock->setPause(true);
}

void PlayerUI::showCancel(bool show)
{
	if (show) {
		effectCancel->startEffect();
	}
	else {
		effectCancel->stopEffect();
	}
	
}

void PlayerUI::updateCard()
{

}

void PlayerUI::getRank(char rank, bool isCong)
{
	AXLOGD("RANK %i ", rank);
	if (false) {
		// hien effect cong
		//effectResult(GameRank::RANK_CONG);
	}
	else {
		rank = GameLogic::getInstance()->convertRank(rank);
		//effectResult(rank);
		resultGroup->showMauBinh(rank);
	}
}

void PlayerUI::effectResult(char rank)
{
	//string resource = GameLogic::getInstance()->getResourceRank(rank);
	//DBCCArmatureNode *effIcon = DBCCFactory::getInstance()->buildArmatureNode(resource.c_str());
	//if (effIcon) {
	//	pEffect->addChild(effIcon);
	//	//effIcon->setScale(_scale);
	//	effIcon->getAnimation()->gotoAndPlay("1", -1, -1, 1);
	//	effIcon->setPosition(pEffect->getContentSize().width * 0.5, pEffect->getContentSize().height * 0.5);
	//	effIcon->runAction(
	//		Sequence::create(
	//			DelayTime::create(2),
	//			CallFuncN::create(AX_CALLBACK_1(PlayerUI::callbackEffectResult, this)),
	//			NULL
	//		)
	//	);
	//}
}

void PlayerUI::callbackEffectResult(Node* sender)
{
	//DBCCArmatureNode *effIcon = dynamic_cast<DBCCArmatureNode*> (sender);
	//effIcon->getAnimation()->gotoAndPlay("2", -1, -1, -1);
}

/**
 * cap nhat card luc het van choi
 */
void PlayerUI::endCard()
{

}

void PlayerUI::showCard()
{

}

void PlayerUI::effectGold(double gold)
{
	moneyGroup->setMoney(gold);
	int rate = 1;
	if (chairIndex == 0) {
		moneyGroup->setPositionY(btnAvatar->getPositionY() + 30);
		moneyGroup->setPositionX(btnAvatar->getPositionX() - 50);
	}
	else if (chairIndex == 1) {
		moneyGroup->setPositionY(btnAvatar->getPositionY() + 30);
		moneyGroup->setPositionX(btnAvatar->getPositionX() - 50);
	}
	else if (chairIndex == 2) {
		moneyGroup->setPositionY(btnAvatar->getPositionY() - 30);
		rate = -1;
		moneyGroup->setPositionX(btnAvatar->getPositionX() - moneyGroup->getContentSize().width * 0.5);
	}
	else if (chairIndex == 3) {
		moneyGroup->setPositionY(btnAvatar->getPositionY() + 30);
		moneyGroup->setPositionX(btnAvatar->getPositionX() + 50 - moneyGroup->getContentSize().width);
	}
	
	moneyGroup->setVisible(true);
	moneyGroup->setOpacity(100);
	moneyGroup->stopAllActions();
	moneyGroup->runAction(
		Sequence::create(
			//Spawn::create(
				FadeIn::create(0.2f),
				EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, 30 * rate))),
			//),
			DelayTime::create(5.0f),
			FadeOut::create(0.5f),
			Hide::create(),
			NULL
		)
	);
}

void PlayerUI::chatEmoticon(char id, char emoId)
{
	//CCNode* effIcon;
	//char type;
	//switch (emoId) {
	//	case 0:
	//		type = ANIM_TYPE_DRAGONBONES;
	//		break;
	//	case 1:
	//		type = ANIM_TYPE_SPINE;
	//		break;
	//	default:
	//		break;
	//}
	//switch (type) {
	//	case ANIM_TYPE_DRAGONBONES: {
	//		string s = "Emoticon";
	//		s = s + StringUtils::format("%ld", id);
	//		effIcon = DBCCFactory::getInstance()->buildArmatureNode(s.c_str());
	//		if (effIcon) {
	//			pEffect->addChild(effIcon);
	//			//effIcon->setScale(_scale);
	//			((DBCCArmatureNode *)effIcon)->getAnimation()->gotoAndPlay("1", -1, -1, 1);
	//			effIcon->setPosition(pEffect->getContentSize().width * 0.5, pEffect->getContentSize().height * 0.5);
	//		}
	//		break;
	//	}
	//	case ANIM_TYPE_SPINE: {
	//		string resource = "Armatures/Emoticon/" + StringUtils::format("%ld", id) + "/" + StringUtils::format("%ld", emoId);
	//		string jsonFile = resource + ".json";
	//		string atlasFile = resource + ".atlas";
	//		effIcon = SkeletonAnimation::createWithFile(jsonFile.c_str(), atlasFile.c_str());
	//		pEffect->addChild(effIcon);
	//		((SkeletonAnimation *)effIcon)->setAnimation(0, "animation", true);
	//		break;
	//	}
	//	default:
	//		break;
	//}
	//effIcon->setOpacity(0);
	//effIcon->setScale(0);
	//effIcon->runAction(
	//	Sequence::create(
	//		Spawn::create(
	//			FadeIn::create(0.4),
	//			ScaleTo::create(0.4, 1.0)
	//		),
	//		DelayTime::create(2.0),
	//		Spawn::create(
	//			FadeOut::create(0.3),
	//			ScaleTo::create(0.3, 0)
	//		),
	//		RemoveSelf::create(),
	//		NULL
	//	)
	//);
}

void PlayerUI::showEffectVip()
{
	
}

void PlayerUI::updateMoney()
{
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	labelGold->setString(StringUtility::formatNumberSymbol(info->Gold()).c_str());
        borderAvatar->loadTexture(info->getAvatarLevel());
}

void PlayerUI::setRoomOwner(bool show)
{
}

Size PlayerUI::getCardSize()
{
	return Size(0, 0);
}

Vec2 PlayerUI::getCardPos(int index)
{
	return Vec2(0, 0);
}

Vec2 PlayerUI::getCardPosById(int id)
{
	return Vec2(0, 0);
}

void PlayerUI::setDarkCard(bool isDark)
{
}

Vec2 PlayerUI::getPositionAvatar()
{
	return bg->convertToWorldSpace(btnAvatar->getPosition());
}

void PlayerUI::updateAvatarFrame(long long uId)
{
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	borderAvatar->loadTexture(info->getAvatarLevel());
}

void PlayerUI::onButtonRelease(Button* button, int id)
{
	switch (id) {
	case PLAYER_UI_BTN_INFO: {
		AXLOGD("PLAYER_UI_BTN_INFO ");
		if (chairIndex == 0) {
			BaseLayer* layer = sceneMgr->openGUI(UserInfoGUI::className, UserInfoGUI::ZODER, UserInfoGUI::TAG);
			UserInfoGUI *gui = dynamic_cast<UserInfoGUI*> (layer);
			gui->showInfo(TypeGame::TIEN_LEN);
		}
		break;
	}
	}
}

void PlayerUI::effectRenew()
{
    auto particle = ParticleSystemQuad::create("Particles/renew.plist");
    particle->setLocalZOrder(5);
    _layout->addChild(particle);
    Vec2 pos = borderAvatar->getPosition();
    pos      = borderAvatar->getParent()->convertToWorldSpace(pos);
    pos      = _layout->convertToNodeSpace(pos);
    particle->setPosition(pos);
    particle->setAutoRemoveOnFinish(true);

    int idAvatar = AXRANDOM_0_1() * 41.99999;
    avatar->loadTexture("images1/avatar_" + to_string(idAvatar) + ".png");
}
