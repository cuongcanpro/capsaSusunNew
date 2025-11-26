#include "OtherUI.h"
#include "../logic/GameLogic.h"
//#define BTN_ARRANGE 4
OtherUI::OtherUI(int chairIndex) : PlayerUI()
{
	this->chairIndex = chairIndex;
	init();
}

OtherUI::~OtherUI()
{

}


bool OtherUI::init()
{
	BaseLayer::init();
	initWithBinaryFile("EnemyUI.csb");
	return true;
}

void OtherUI::initGUI()
{
	
	PlayerUI::initGUI();
	cardImage = (ImageView *)getControl("card", bg);
	labelNumber = (Text *)getControl("lb", cardImage);
	lbShowCard = (Text *)getControl("lbShowCard", btnAvatar);
	
	initGroupCard();
	if (chairIndex == 3) {
		getControl("sub0")->setVisible(false);
		cardImage->setPosition(getControl("p1")->getPosition());
	}
	else {
		getControl("sub1")->setVisible(false);
		cardImage->setPosition(getControl("p0")->getPosition());
	}
	getControl("sub1")->setVisible(false);
	getControl("sub0")->setVisible(false);
}

void OtherUI::initGroupCard()
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i] = new CardImage(52);
		bg->addChild(arrayCard[i]);
		arrayCard[i]->setScale(0.6f);
	}
}

void OtherUI::newGame()
{
	AXLOGD("PAYERUI NEW GAME");
	PlayerUI::newGame();
	cardImage->setVisible(false);
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setVisible(false);
	}
	if (GameLogic::getInstance()->isPosture) {
		if (GameLogic::getInstance()->canShowCard == false) {
			string s;
			if (2 - GameLogic::getInstance()->countLose == 0) {
				s = LocalizedString::to("VIEW_CARD_AT_NEXT");
			}
			else {
				s = LocalizedString::to("VIEW_CARD");
				s = StringUtility::replaceAll(s, "@num", 2 - GameLogic::getInstance()->countLose);
			}
			lbShowCard->setString(s);
			lbShowCard->setVisible(true);
		}
		else {
			lbShowCard->setVisible(false);
		}
	}
	else {
		lbShowCard->setVisible(false);
	}
}

void OtherUI::updateDealCard(int num)
{
	if (num > 0) {
		labelNumber->setString(to_string(num + 1));
		cardImage->setVisible(true);
	}
	else {
		cardImage->setVisible(false);
	}
}

void OtherUI::endDealCard()
{
	updateCard();
}

void OtherUI::updateCard()
{
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	cardImage->setVisible(false);
	if (info->NumCard() > 0) {
		labelNumber->setString(to_string(info->NumCard()));
		cardImage->setVisible(true);
	}
	if (GameLogic::getInstance()->canShowCard) {
		showCard();
	}
}

void OtherUI::endCard()
{
	cardImage->setVisible(false);
	showCard();
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	TienlenGamePlayer* game = info->Game();
	if (GameLogic::getInstance()->isSuddenWin()) {
		if (info->isSuddenWin()) {
			// lam sang nhung quan card trong mang toi trang
			for (int i = 0; i < game->WinCards.size(); i++) {
				arrayCard[i]->setIdCard(game->WinCards.at(i));
				arrayCard[i]->setDark(false);
			}
			for (int i = game->WinCards.size(); i < NUM_CARD; i++) {
				if ((i - game->WinCards.size()) < game->WinExcess.size())
					arrayCard[i]->setIdCard(game->WinExcess.at(i - game->WinCards.size()));
			}
		}
	}
	else {
		// lam sang nhung quan card bi thoi
		for (int i = 0; i < game->WinCards.size(); i++) {
			arrayCard[i]->setIdCard(game->WinCards.at(i));
			arrayCard[i]->setDark(false);
		}
		for (int i = 0; i < game->WinExcess.size(); i++) {
			if (i + game->WinCards.size() < NUM_CARD)
				arrayCard[i + game->WinCards.size()]->setIdCard(game->WinExcess.at(i));
		}
	}
}

void OtherUI::showCard()
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setVisible(false);
	}
	PlayerInfo* info = GameLogic::getInstance()->getInfo(chairIndex);
	vector <int> cards = info->arrayCard;
	for (int i = 0; i < (int)cards.size(); i++) {
		arrayCard[i]->setVisible(true);
		arrayCard[i]->setIdCard(cards.at(i));
	}
	updatePositionGroupCard(cards.size());
	setDarkCard(true);
}

void OtherUI::updatePositionGroupCard(int num)
{
	float startX, startY;
	float widthCard = arrayCard[0]->getRealWidth();
	float heightCard = arrayCard[0]->getRealHeight();
	float padX = 0, padY = 0;
	if (chairIndex == 1) {
		// ben trai man hinh
		startX = btnAvatar->getPositionX() + 90;
		padY = heightCard * 0.3;
		startY = btnAvatar->getPositionY() + num * padY * 0.5 + heightCard * 0.2;
	}
	else if (chairIndex == 2) {
		// o giua
		startX = btnAvatar->getPositionX() + btnAvatar->getContentSize().width * 0.5 + 90;
		startY = btnAvatar->getPositionY();
		padX = widthCard * 0.4;
	}
	else {
		// ben phai
		startX = btnAvatar->getPositionX() - 90;
		padY = heightCard * 0.3;
		startY = btnAvatar->getPositionY() + num * padY * 0.5 + heightCard * 0.2;
	}
	for (int i = 0; i < num; i++) {
		arrayCard[i]->setPosition(startX + padX * i, startY - padY * i);
	}
}

Size OtherUI::getCardSize()
{
	return Size(cardImage->getContentSize().width * _scale, cardImage->getContentSize().height * _scale);
}

Vec2 OtherUI::getCardPos(int index)
{
	return bg->convertToWorldSpace(cardImage->getPosition());
}

Vec2 OtherUI::getCardPosById(int index)
{
	return bg->convertToWorldSpace(cardImage->getPosition());
}

void OtherUI::setDarkCard(bool isDark)
{
	for (int i = 0; i < NUM_CARD; i++) {
		arrayCard[i]->setDark(isDark);
	}
}

