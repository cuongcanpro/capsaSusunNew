#include "BinhOtherUI.h"
#include "../logic/BinhGameLogic.h"
//#define BTN_ARRANGE 4
BinhOtherUI::BinhOtherUI(int chairIndex, Node* panel, efk::EffectManager* manager) : BinhPlayerUI()
{
    this->manager    = manager;
	this->chairIndex = chairIndex;
	this->layout = panel;
	timeArrange = -1;
	initGUI();
}

BinhOtherUI::~BinhOtherUI()
{

}

void BinhOtherUI::initGUI()
{
	BinhPlayerUI::initGUI();
	
}

void BinhOtherUI::onEnterFinish()
{
	
}

void BinhOtherUI::newGame()
{
	BinhPlayerUI::newGame();
	timeArrange = -1;
}

void BinhOtherUI::updateDealCard(int num)
{
	arrayCard1[num]->setVisible(true);
}

void BinhOtherUI::endDealCard()
{
	BinhPlayerUI::endDealCard();
	timeArrange = 2;
}

void BinhOtherUI::ready()
{
	BinhPlayerUI::ready();
	timeArrange = -1;
	AXLOGD("READY %f ", timeArrange);
}

void BinhOtherUI::unReady()
{
	BinhPlayerUI::unReady();
	timeArrange = 2;
}

void BinhOtherUI::endCard()
{
	BinhPlayerUI::endCard();
	timeArrange = -1;
}

void BinhOtherUI::chiIndex(char chi)
{
	BinhPlayerUI::chiIndex(chi);
}

void BinhOtherUI::compareChi(char chi, double money, int result)
{
	BinhPlayerUI::compareChi(chi, money, result);
}

void BinhOtherUI::sapLang(char chair, double money)
{
	BinhPlayerUI::sapLang(chair, money);
	/*DBCCArmatureNode *effIcon = DBCCFactory::getInstance()->buildArmatureNode("batsaplang");
	if (effIcon) {
		pEffect->addChild(effIcon);
		effIcon->setScale(0.6);
		effIcon->getAnimation()->gotoAndPlay("1", -1, -1, 1);
		effIcon->runAction(
			Sequence::create(
				DelayTime::create(3.0),
				RemoveSelf::create(),
				NULL
			)
		);
	}*/
}

void BinhOtherUI::update(float delta)
{
	BinhPlayerUI::update(delta);

	if (timeArrange == 0) {
		timeArrange = 2;
	}
	if (timeArrange >= 0) {
		timeArrange = timeArrange - delta;
		if (timeArrange <= 0) {
			vector<int> arrayRandom;
			for (int i = 0; i < NUM_CARD; i++) {
				arrayRandom.push_back(i);
			}
		
			for (int i = 0; i < 2; i++) {
				int random1 = AXRANDOM_0_1() * arrayRandom.size() * 0.999;
				int value1 = arrayRandom[random1];
				arrayRandom.erase(arrayRandom.begin() + random1);

				int random2 = AXRANDOM_0_1() * arrayRandom.size() * 0.999;
				int value2 = arrayRandom[random2];
				arrayRandom.erase(arrayRandom.begin() + random2);

				if (random1 != random2) {
					Vec2 savePos = arrayCard1[random1]->getPosition();
					arrayCard1[random1]->setPosition(arrayCard1[random2]->getPosition());
					arrayCard1[random2]->setPosition(savePos);
					arrayCard1[random1]->moveToDefault(0.4, i * 0.5);
					arrayCard1[random2]->moveToDefault(0.4, i * 0.5);
				}
			}
			timeArrange = 1.0 + AXRANDOM_0_1() * 3;
		}
	}
}

