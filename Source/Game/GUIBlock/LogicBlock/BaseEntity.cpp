#include "BaseEntity.h"
#include "Engine/GlobalVar.h"
#include "Game/GUIManager.h"
#include "Game/Utility/GameSound.h"
#include "Game/Utility/GameUtility.h"


BaseEntity::BaseEntity(void)
{
	
	state = 0;
}

BaseEntity::~BaseEntity(void)
{
	
}

void BaseEntity::initCell()
{
	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);
	float sizeCell = GUIManager::getInstance().guiBlock->sizeCell;
	isNext = false;
	for (int i = 0; i < data.size(); i++) {
		GameImage* image = new GameImage(GameUtility::getTextureCellImage(idBlock).c_str());
		arrayImage.push_back(image);
		image->setWidth(sizeCell * 0.9);
		image->setHeight(sizeCell * 0.9);
		addChild(image);
		float posX = -getRealWidth() * 0.5 + (0.5f + data.at(i)->x) * sizeCell;
		float posY = (0.5f + data.at(i)->y) * sizeCell;
		image->setPos(posX, posY);
	}
	isNext = true;
	setVisible(true);
	setIsNext(isNext);
}

void BaseEntity::saveRoot()
{
	rootX = getPositionX();
	rootY = getPositionY();
}

void BaseEntity::changeMap()
{
	PointGame p = getPointInMap();
	for (int i = 0; i < this->data.size(); i++) {
		game->dataBlockPuzzel[p.y + data.at(i)->y][p.x + data.at(i)->x] = idBlock;
	}
}

PointGame BaseEntity::getPointInMap()
{
	float x = getPositionX() - getRealWidth() * 0.5;
	PointGame p = GUIManager::getInstance().guiBlock->getPointInBoard(getPositionX() - getRealWidth() * 0.5, getPositionY());
	return p;
}

// kiem tra xem khi di chuyen thi co the dat xuogn trong map hay khong
bool BaseEntity::validInMap()
{
	PointGame p = getPointInMap();
	return validPointInMap(p);
}

// thay doi map khi dang giu va di chuyen
void BaseEntity::changeNextMap()
{
	if (validInMap()) {
		PointGame p = getPointInMap();
		for (int i = 0; i < this->data.size(); i++) {
			game->dataBlockPuzzel[p.y + data.at(i)->y][p.x + data.at(i)->x] = 20 + idBlock;
		}
	}
}

// thay doi map khi da tha Vat the ra
void BaseEntity::changeCurrentMap()
{
	if (validInMap()) {
		PointGame p = getPointInMap();
		for (int i = 0; i < this->data.size(); i++) {
			game->dataBlockPuzzel[p.y + data.at(i)->y][p.x + data.at(i)->x] = idBlock + 40;
		}
		Point pos;
		pos.x = GUIManager::getInstance().guiBlock->startX + p.x * GUIManager::getInstance().guiBlock->sizeCell + getRealWidth() * 0.5;
		pos.y = GUIManager::getInstance().guiBlock->startY + p.y * GUIManager::getInstance().guiBlock->sizeCell;
		runAction(Sequence::create(
			MoveTo::create(0.5, pos),
			RemoveSelf::create(true),
			NULL
		));
	}
}

bool BaseEntity::canPut()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (validPointInMap(PointGame(i, j))) {
				// co the dat vao trong map
				for (int k = 0; k < arrayImage.size(); k++) {
					arrayImage.at(k)->getImg()->setOpacity(255);
				}
				return true;
			}
		}
	// ko the dat vao trong map
	for (int k = 0; k < arrayImage.size(); k++) {
		arrayImage.at(k)->getImg()->setOpacity(150);
	}
	return false;
}

// kiem tra xem co that dat vat the nay o mot vi tri nao do trong Map hay khong
bool BaseEntity::validPointInMap(PointGame p)
{
	PointGame pCheck;
	for (int i = 0; i < data.size(); i++) {
		pCheck.x = p.x + data.at(i)->x;
		pCheck.y = p.y + data.at(i)->y;
		if (pCheck.x < 0 || pCheck.x >= 8 || pCheck.y < 0 || pCheck.y >= 8 || game->dataBlockPuzzel[pCheck.y][pCheck.x] != 0) {
			return false;
		}
	}
	return true;
}

float BaseEntity::getRealWidth()
{
	if (isNext)
		return GUIManager::getInstance().guiBlock->sizeCell * ConfigDataBlock::RATE_NEXT_CELL * getWidth();
	else
		return GUIManager::getInstance().guiBlock->sizeCell * getWidth();
}

float BaseEntity::getRealHeight()
{
	if (isNext)
		return GUIManager::getInstance().guiBlock->sizeCell * ConfigDataBlock::RATE_NEXT_CELL * getHeight();
	else
		return GUIManager::getInstance().guiBlock->sizeCell * getHeight();
}

int BaseEntity::getWidth()
{
	return 0;
}

int BaseEntity::getHeight()
{
	return 0;
}

bool BaseEntity::isTouch(Point point)
{
	if (point.x > arrangePoint.x && point.x < arrangePoint.x + arrangeSize.width &&
		point.y > arrangePoint.y && point.y < arrangePoint.y + arrangeSize.height) {
		return true;
	}
	return false;
}

void BaseEntity::setIsNext(bool _isNext)
{
	if (isNext != _isNext) {
		isNext = _isNext;
		if (isNext) {
			// thu nho lai ve vi tri cu
			runAction(EaseExponentialOut::create(MoveTo::create(0.3, Vec2(rootX, rootY))));
			runAction(EaseExponentialOut::create(ScaleTo::create(0.3, ConfigDataBlock::RATE_NEXT_CELL)));
		}
		else {
			// phong to len o vi tri hien tai
			runAction(EaseExponentialOut::create(MoveTo::create(0.1, Vec2(rootX, rootY + 50))));
			runAction(EaseExponentialOut::create(ScaleTo::create(0.1, 1)));
		}
	}
	else {
		if (isNext) {
			setScale(ConfigDataBlock::RATE_NEXT_CELL);
		}
		else {
			setScale(1);
		}
	}
}

void BaseEntity::endGame()
{
	for (int i = 0; i < arrayImage.size(); i++) {
		arrayImage.at(i)->getImg()->setColor(Color3B(191, 183, 183));
	}
}

int BaseEntity::getNumCell()
{
	return arrayImage.size();
}
