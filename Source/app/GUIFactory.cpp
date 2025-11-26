#include "GUIFactory.h"

#include "core/gui/Dialog.h"

#include "gameTienlen/ui/BoardScene.h"
#include "gameTienlen/ui/LoadingScene.h"
#include "gameTienlen/ui/LobbyScene.h"
#include "gameTienlen/ui/GUILevel.h"
#include "gameTienlen/ui/GUIHelp.h"
#include "gameTala/ui/TalaScene.h"
#include "gameTala/ui/TalaLobbyScene.h"
#include "common/UserInfoGUI.h"
#include "common/ChooseGameScene.h"
#include "common/ChooseCardGUI.h"
#include "gameBinh/ui/BinhBoardScene.h"
#include "gameBinh/ui/BinhTruyenThong.h"
#include "gameBinh/ui/BinhTinhAt.h"
#include "gameBinh/ui/BinhLobbyScene.h"
#include "gameBinh/ui/BinhHelpGUI.h"

BaseLayer* GUIFactory::createGUI(std::string className) {
	if (className.compare(Dialog::className) == 0) {
		return Dialog::create();
	}
	if (className.compare(BoardScene::className) == 0) {
		return BoardScene::create();
	}
	if (className.compare(TalaScene::className) == 0) {
		return TalaScene::create();
	}

	if (className.compare(LoadingScene::className) == 0) {
		return LoadingScene::create();
	}
	if (className.compare(UserInfoGUI::className) == 0) {
		return UserInfoGUI::create();
	}
	if (className.compare(NewLevelGUI::className) == 0) {
		return NewLevelGUI::create();
	}
	
	if (className.compare(LobbyScene::className) == 0) {
		return LobbyScene::create();
	}
	if (className.compare(GUILevel::className) == 0) {
		return GUILevel::create();
	}
	if (className.compare(GUIHelp::className) == 0) {
		return GUIHelp::create();
	}
	if (className.compare(TalaLobbyScene::className) == 0) {
		return TalaLobbyScene::create();
	}
	if (className.compare(ChooseGameScene::className) == 0) {
		return ChooseGameScene::create();
	}
	if (className.compare(ChooseCardGUI::className) == 0) {
		return ChooseCardGUI::create();
	}
	if (className.compare(BinhBoardScene::className) == 0) {
		return BinhBoardScene::create();
	}
	if (className.compare(BinhTruyenThong::className) == 0) {
		return BinhTruyenThong::create();
	}
	if (className.compare(BinhTinhAt::className) == 0) {
		return BinhTinhAt::create();
	}
	if (className.compare(BinhLobbyScene::className) == 0) {
		return BinhLobbyScene::create();
	}
	if (className.compare(BinhHelpGUI::className) == 0) {
		return BinhHelpGUI::create();
	}
	
	return nullptr;
}
