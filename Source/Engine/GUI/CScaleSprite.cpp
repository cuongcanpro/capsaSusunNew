#include "CScaleSprite.h"
#include <string>
#include <Engine/Utility/ScreenUtils.h>


// CScaleSprite* CScaleSprite::create()
// {
// 	CScaleSprite *pSprite = new CScaleSprite();
// 	if (pSprite && pSprite->init())
// 	{
// 		pSprite->autorelease();
// 		return pSprite;
// 	}
// 	AX_SAFE_DELETE(pSprite);
// 	return NULL;
// }
CScaleSprite* CScaleSprite::create(const char *pszFileName, bool frame){
	
	CScaleSprite *pobSprite = new CScaleSprite();
	std::string path = ScreenUtils::fileFull(pszFileName);
	
	if(!frame)
	{
		if (pobSprite && pobSprite->initWithFile(ScreenUtils::fileFull(pszFileName).c_str()))
		{
			pobSprite->autorelease();
			//pobSprite->setScale(1);
			//pobSprite->updateSize();
			return pobSprite;
		}
	}
	else
	{
		if (pobSprite && pobSprite->initWithSpriteFrameName(pszFileName))
		{
			pobSprite->autorelease();
			//pobSprite->setScale(1);
			return pobSprite;
		}
	}

	/*if (pobSprite && pobSprite->initWithFile(ScreenUtils::fileFull(pszFileName).c_str()))
	{
		pobSprite->autorelease();
		pobSprite->setScale(1);
		pobSprite->updateSize();
		return pobSprite;
	}
	*/
	std::string s;
	s="khong co anh?";
	s+=pszFileName;
	//MessageBox(s.c_str(),"Thong bao");

	AXLOGD("cant create CScaleSprite");
	AX_SAFE_DELETE(pobSprite);
	return NULL;
};
float CScaleSprite::getWidth(){
	return this->getContentSize().width;//* ScreenUtils::imageScale();
}
float CScaleSprite::getHeight(){
	return this->getContentSize().height;//* ScreenUtils::imageScale();
}
void CScaleSprite::setScale(float scale){
	Sprite::setScale(scale);// * ScreenUtils::imageScale());
}
void CScaleSprite::setScaleX(float scale){
	Sprite::setScaleX(scale);// * ScreenUtils::imageScale());
}
void CScaleSprite::setScaleY(float scale){
	Sprite::setScaleY(scale);// * ScreenUtils::imageScale());
}
float CScaleSprite::getScaleX(){
	return Sprite::getScaleX();///ScreenUtils::imageScale();
}
float CScaleSprite::getScaleY(){
	return Sprite::getScaleY();///ScreenUtils::imageScale();
}
float CScaleSprite::getScale(){
	return Sprite::getScale();///ScreenUtils::imageScale();
}
