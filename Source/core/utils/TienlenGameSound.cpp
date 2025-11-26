#include "TienlenGameSound.h"
#include "axmol.h"
#include <vector>
#include "app/GameMgr.h"
#include "core/utils/LanguageMgr.h"
#include "app/Constant.h"
#include "audio/AudioEngine.h"
using namespace std;

//lobby
const char* sound_backgroundMusic = "GameSound/mobileCard/bg.mp3";
const char* sound_chupanh = "GameSound/mobileCard/chupanh.mp3";
const char* sound_click = "GameSound/mobileCard/click.mp3";
const char* sound_coinFall = "GameSound/mobileCard/coinFall.mp3";
const char* sound_coin1 = "GameSound/mobileCard/coin_01.mp3";
const char* sound_coin2 = "GameSound/mobileCard/coin_02.mp3";
const char* sound_coin3 = "GameSound/mobileCard/coin_03.mp3";
const char* sound_giftNormal = "GameSound/mobileCard/giftOnl_normal.mp3";
const char* sound_giftBig = "GameSound/mobileCard/giftOnl_big.mp3";
const char* sound_spinWheel = "GameSound/mobileCard/giftOnl_spinWheel.mp3";
//sounds
const char* sound_rainGold = "GameSound/mobileCard/coinFall.mp3";
const char* sound_specify = "GameSound/mobileCard/s_bobai.mp3";
const char* sound_arrange_card = "GameSound/mobileCard/arrange_card.mp3";
const char* sound_click_card = "GameSound/mobileCard/select_card.mp3";
const char* sound_danhbai = "GameSound/mobileCard/danhbai.mp3";
const char* sound_dangkythoat = "GameSound/mobileCard/dangkythoat.mp3";
const char* sound_huythoat = "GameSound/mobileCard/huythoat.mp3";
const char* sound_jackpot = "GameSound/mobileCard/jackpot.mp3";
const char* sound_music_lose = "GameSound/mobileCard/music_lose.mp3";
const char* sound_music_win = "GameSound/mobileCard/music_win.mp3";
const char* sound_start_game = "GameSound/mobileCard/start.mp3";

const char* sound_baobinh_12caydongmau  = "GameSound/mobileCard/baobinh_12caydongmau.mp3";
const char* sound_baobinh_13caydongmau = "GameSound/mobileCard/baobinh_13caydongmau.mp3";
const char* sound_baobinh_3caisanh = "GameSound/mobileCard/otherSpecialThreeStraights.mp3";
const char* sound_baobinh_3caithung = "GameSound/mobileCard/otherSpecialThreeFlushes.mp3";
const char* sound_baobinh_lucphebon = "GameSound/mobileCard/otherSpecialSixPairs.mp3";
const char* sound_baobinh_sanhrong = "GameSound/mobileCard/otherSpecialDragon.mp3";
const char* sound_BatDauGame = "GameSound/mobileCard/BatDauGame.mp3";
const char* sound_batsapnay = "GameSound/mobileCard/batSap.mp3";
const char* sound_BinhLung = "GameSound/mobileCard/BinhLung.mp3";
const char* sound_ButtonClick = "GameSound/mobileCard/ButtonClick.mp3";
const char* sound_button_cancel = "GameSound/mobileCard/button_cancel.mp3";
const char* sound_button_click = "GameSound/mobileCard/button_click.mp3";
const char* sound_cardmatch = "GameSound/mobileCard/cardmatch.mp3";
const char* sound_chaomung_1 = "GameSound/mobileCard/chaomung_1.mp3";
const char* sound_chaomung_2 = "GameSound/mobileCard/chaomung_2.mp3";
const char* sound_ChiaBai = "GameSound/mobileCard/s_chiabai.mp3";
const char* sound_chiabai_00 = "GameSound/mobileCard/chiabai_00.mp3";
const char* sound_ChipChamNhau = "GameSound/mobileCard/ChipChamNhau.mp3";
const char* sound_CountDown = "GameSound/mobileCard/CountDown.mp3";
const char* sound_DemGio = "GameSound/mobileCard/DemGio.mp3";
const char* sound_e_Chat = "GameSound/mobileCard/e_Chat.mp3";
const char* sound_e_In = "GameSound/mobileCard/e_In.mp3";
const char* sound_e_OutCan = "GameSound/mobileCard/e_OutCan.mp3";
const char* sound_e_OutVol = "GameSound/mobileCard/e_OutVol.mp3";
const char* sound_e_ScreenShot = "GameSound/mobileCard/e_ScreenShot.mp3";
const char* sound_finishgroupcard = "GameSound/mobileCard/finishgroupcard.mp3";
const char* sound_givecard = "GameSound/mobileCard/givecard.mp3";
const char* sound_groupcard = "GameSound/mobileCard/groupcard.mp3";
const char* sound_Jackpot = "GameSound/mobileCard/Jackpot.mp3";
const char* sound_JoinRoom = "GameSound/mobileCard/JoinRoom.mp3";
const char* sound_LeaveRoom = "GameSound/mobileCard/LeaveRoom.mp3";
const char* sound_lose_1 = "GameSound/mobileCard/lose_1.mp3";
const char* sound_lose_2 = "GameSound/mobileCard/lose_2.mp3";
const char* sound_lose_3 = "GameSound/mobileCard/lose_3.mp3";
const char* sound_MauBinh = "GameSound/mobileCard/MauBinh.mp3";
const char* sound_maubinh_12caydongmau = "GameSound/mobileCard/maubinh_12caydongmau.mp3";
const char* sound_maubinh_13caydongmau = "GameSound/mobileCard/maubinh_13caydongmau.mp3";
const char* sound_maubinh_3caisanh = "GameSound/mobileCard/specialThreeStraights.mp3";
const char* sound_maubinh_3caithung = "GameSound/mobileCard/specialThreeFlushes.mp3";
const char* sound_maubinh_lucphebon = "GameSound/mobileCard/specialSixPairs.mp3";
const char* sound_maubinh_sanhrong = "GameSound/mobileCard/specialDragon.mp3";
const char* sound_menu_transition = "GameSound/mobileCard/menu_transition.mp3";
const char* sound_OpenWindow = "GameSound/mobileCard/OpenWindow.mp3";
const char* sound_out = "GameSound/mobileCard/out.mp3";
const char* sound_player_bing = "GameSound/mobileCard/player_bing.mp3";
const char* sound_player_join = "GameSound/mobileCard/player_join.mp3";
const char* sound_player_leave = "GameSound/mobileCard/player_leave.mp3";
const char* sound_rematch_1 = "GameSound/mobileCard/rematch_1.mp3";
const char* sound_rematch_2 = "GameSound/mobileCard/rematch_2.mp3";
const char* sound_rematch_3 = "GameSound/mobileCard/rematch_3.mp3";
const char* sound_saproi = "GameSound/mobileCard/bomb.mp3";
const char* sound_SoBai = "GameSound/mobileCard/SoBai.mp3";
const char* sound_sobai_00 = "GameSound/mobileCard/sobai_00.mp3";
const char* sound_sobai_01 = "GameSound/mobileCard/sobai_01.mp3";
const char* sound_sobai_02 = "GameSound/mobileCard/sobai_02.mp3";
const char* sound_sochi = "GameSound/mobileCard/sochi.mp3";
const char* sound_start_1 = "GameSound/mobileCard/start_1.mp3";
const char* sound_start_2 = "GameSound/mobileCard/start_2.mp3";
const char* sound_s_lose = "GameSound/mobileCard/s_lose.mp3";
const char* sound_s_win = "GameSound/mobileCard/s_win.mp3";
const char* sound_Thang = "GameSound/mobileCard/Thang.mp3";
const char* sound_thang_culu = "GameSound/mobileCard/winFullHouse.mp3";
const char* sound_thang_culuhaichi = "GameSound/mobileCard/winFullHouse.mp3";
const char* sound_thang_doi = "GameSound/mobileCard/winPair.mp3";
const char* sound_thang_mauthau = "GameSound/mobileCard/winHighCard.mp3";
const char* sound_thang_samchicu2oi = "GameSound/mobileCard/winThreeKind.mp3";
const char* sound_thang_samchicuoi = "GameSound/mobileCard/winThreeKind.mp3";
const char* sound_thang_sanh = "GameSound/mobileCard/winStraight.mp3";
const char* sound_thang_thu = "GameSound/mobileCard/winTwoPair.mp3";
const char* sound_thang_thung = "GameSound/mobileCard/winFlush.mp3";
const char* sound_thang_thungphasanh = "GameSound/mobileCard/winStraightFlush.mp3";
const char* sound_thang_tuquy = "GameSound/mobileCard/winFourKind.mp3";
const char* sound_Thua = "GameSound/mobileCard/Thua.mp3";
const char* sound_win_1 = "GameSound/mobileCard/win_1.mp3";
const char* sound_win_2 = "GameSound/mobileCard/win_2.mp3";
const char* sound_win_3 = "GameSound/mobileCard/win_3.mp3";
const char* sound_XepBai = "GameSound/mobileCard/XepBai.mp3";
const char* sound_xepbai_1 = "GameSound/mobileCard/xepbai_1.mp3";
const char* sound_xepbai_2 = "GameSound/mobileCard/xepbai_2.mp3";
const char* sound_xepbai_3 = "GameSound/mobileCard/xepbai_3.mp3";
const char* sound_xepbai_culu = "GameSound/mobileCard/loseFullHouse.mp3";
const char* sound_xepbai_culuhaichi = "GameSound/mobileCard/loseFullHouse.mp3";
const char* sound_xepbai_doi = "GameSound/mobileCard/losePair.mp3";
const char* sound_xepbai_mauthau = "GameSound/mobileCard/loseHighCard.mp3";
const char* sound_xepbai_samchi = "GameSound/mobileCard/loseThreeKind.mp3";
const char* sound_xepbai_sanh = "GameSound/mobileCard/loseStraight.mp3";
const char* sound_xepbai_thu = "GameSound/mobileCard/loseTwoPair.mp3";
const char* sound_xepbai_thung = "GameSound/mobileCard/loseFlush.mp3";
const char* sound_xepbai_thungphasanh = "GameSound/mobileCard/loseStraightFlush.mp3";
const char* sound_xepbai_tuquy = "GameSound/mobileCard/loseFourKind.mp3";

const char* sound_cancel_turn = "GameSound/mobileCard/cancelTurn.mp3";
const char* sound_yourturn = "GameSound/mobileCard/yourTurn.mp3";

const char* soundAutoWin = "GameSound/mobileCard/active_airplane.mp3";
const char* soundChiWin = "GameSound/mobileCard/chiWin.mp3";
const char* soundChiLose = "GameSound/mobileCard/chiLose.mp3";
const char* soundChatGroupCard = "GameSound/mobileCard/chatGroupCard.mp3";
const char* soundChangeTurn = "GameSound/mobileCard/ui_turn.mp3";
const char* soundEndCard = "GameSound/mobileCard/fx_last_card.mp3";

const char* sound_bg_lobby = "GameSound/mobileCard/bg_lobby.mp3";
const char* sound_bg_ingame = "GameSound/mobileCard/bg_ingame.mp3";
const char* soundChipFly = "GameSound/mobileCard/card_deal.mp3";
const char* soundCardDown = "GameSound/mobileCard/card_02.mp3";
//board sound

const vector<string> voice_en_discard = {

	"sounds/voice/en/dump_0.mp3",
	"sounds/voice/en/dump_1.mp3",
	"sounds/voice/en/dump_2.mp3",
};
const vector<string> voice_en_lastCard = {
	"sounds/voice/en/last_get_0.mp3",
	"sounds/voice/en/last_get_1.mp3"
};
const vector<string> voice_en_eatPot = {
	"sounds/voice/en/pot_0.mp3",
	"sounds/voice/en/pot_1.mp3",
	"sounds/voice/en/pot_2.mp3",
	"sounds/voice/en/pot_3.mp3",
	"sounds/voice/en/pot_4.mp3",
	"sounds/voice/en/pot_5.mp3"
};
const vector<string> voice_en_thinkSlow = {
	"sounds/voice/en/fast_turn_0.mp3",
	"sounds/voice/en/fast_turn_1.mp3",
	"sounds/voice/en/fast_turn_2.mp3",
	"sounds/voice/en/fast_turn_3.mp3",
	"sounds/voice/en/fast_turn_4.mp3",
	"sounds/voice/en/fast_turn_5.mp3",
	"sounds/voice/en/fast_turn_6.mp3",
	"sounds/voice/en/fast_turn_7.mp3"
};
const vector<string> voice_en_win = {
	"sounds/voice/en/win_0.mp3",
	"sounds/voice/en/win_1.mp3",
};

const vector<string> voice_en_draw = {};
const vector<string> voice_en_lose = {};
const vector<string> voice_en_pass = {};
const vector<string> voice_en_welcome = {};
const vector<string> voice_en_winTrophy = {
	"sounds/voice/en/hitter_0.mp3",
	"sounds/voice/en/hitter_1.mp3",
	"sounds/voice/en/hitter_2.mp3"
};
const vector<string> voice_en_eatCard = {
	"sounds/voice/en/chow_0.mp3",
	"sounds/voice/en/chow_1.mp3",
	"sounds/voice/en/chow_2.mp3",
	"sounds/voice/en/chow_3.mp3",
	"sounds/voice/en/chow_4.mp3",
	"sounds/voice/en/chow_5.mp3",
	"sounds/voice/en/chow_6.mp3",
	"sounds/voice/en/chow_7.mp3",
	"sounds/voice/en/chow_8.mp3",
	"sounds/voice/en/chow_9.mp3",
};


int randInSize(int size)
{
	int value = AXRANDOM_0_1() * size;
	if (value == size)
		value = 0;
	return value;
}
void playEffect(const std::string &path, bool isLoop = false, float pitch = 1.0f) {
	if (!gameMgr->getSetting().sound)
		return;
	AudioEngine::play2d(path.c_str());
}
void playMusic(const std::string &path, bool isLoop = false) {
	if (!gameMgr->getSetting().music)
		return;
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(path.c_str(), isLoop);
}
void playRandom(vector<string> sounds, bool isLoop = false, float pitch = 1.0f)
{
	playEffect(sounds[randInSize(sounds.size())], isLoop, pitch);
}

TienlenGameSound::TienlenGameSound()
{
}

TienlenGameSound::~TienlenGameSound()
{
}


void TienlenGameSound::stopMusic()
{
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void TienlenGameSound::playSoundSpinWheel()
{
	playEffect(sound_spinWheel);
}

void TienlenGameSound::playSoundGiftNormal()
{
	playEffect(sound_giftNormal);
}

void TienlenGameSound::playSoundGiftBig()
{
	playEffect(sound_giftBig);
}

std::string TienlenGameSound::getRandomSound(std::string path, int number, std::string duoi)
{
	int rd = floor(AXRANDOM_0_1() * number + 1);
	if (rd > number)
		rd = number;

	//std::string ret = StringUtils::format("%s%d.%s", path.c_str(), rd, duoi.c_str());
        std::string ret = "";
	return ret;
}

bool TienlenGameSound::getRandom(int percent)
{
	int test = floor(AXRANDOM_0_1() * 100);
	return test <= percent;
}

void TienlenGameSound::playDkThoat()
{
	playEffect(sound_dangkythoat);
}

void TienlenGameSound::playJackpot()
{
	playEffect(sound_jackpot, false);
	playEffect(sound_rainGold, false);
}

void TienlenGameSound::playHuyThoat()
{
	playEffect(sound_huythoat);
}

void TienlenGameSound::playClick()
{
	playEffect(sound_click);
}

void TienlenGameSound::playRegQuit(bool success)
{
	if (success) {
		playEffect(sound_dangkythoat);
	}
	else {
		playEffect(sound_huythoat);
	}
}

void TienlenGameSound::playSoundJackpot()
{
	playEffect(sound_jackpot);
}

void TienlenGameSound::playSounds_lose()
{
	playEffect(sound_s_lose);
}

void TienlenGameSound::regQuit(bool success)
{
	if (success)
		playEffect(sound_dangkythoat);
	else
		playEffect(sound_huythoat);
}

void TienlenGameSound::playCard()
{
	playEffect(sound_danhbai);
}

void TienlenGameSound::musicWin()
{
	playEffect(sound_music_win);
}

void TienlenGameSound::startGame()
{
	playEffect(sound_start_game);
}

void TienlenGameSound::playBoLuot()
{
	playEffect(sound_cancel_turn);
}

void TienlenGameSound::playDenLuot()
{
	playEffect(sound_yourturn);
}

void TienlenGameSound::playEndWin()
{
	//playEffect(sound_s_danh_bo);
}

void TienlenGameSound::playEndLose()
{
	//playEffect(sound_s_danh_bo);
}

void TienlenGameSound::playSoundbaobinh_12caydongmau()
{
	playEffect(sound_baobinh_12caydongmau);
}

void TienlenGameSound::playSoundbaobinh_13caydongmau()
{
	playEffect(sound_baobinh_13caydongmau);
}

void TienlenGameSound::playSoundbaobinh_3caisanh()
{
	playEffect(sound_baobinh_3caisanh);
}

void TienlenGameSound::playSoundbaobinh_3caithung()
{
	playEffect(sound_baobinh_3caithung);
}

void TienlenGameSound::playSoundbaobinh_lucphebon()
{
	playEffect(sound_baobinh_lucphebon);
}

void TienlenGameSound::playSoundbaobinh_sanhrong()
{
	playEffect(sound_baobinh_sanhrong);
}

void TienlenGameSound::playSoundBatDauGame()
{
	playEffect(sound_BatDauGame);
}

void TienlenGameSound::playSoundbatsapnay()
{
	playEffect(sound_batsapnay);
}

void TienlenGameSound::playSoundBinhLung()
{
	playEffect(sound_BinhLung);
}

void TienlenGameSound::playSoundButtonClick()
{
	playEffect(sound_ButtonClick);
}

void TienlenGameSound::playSoundbutton_cancel()
{
	playEffect(sound_button_cancel);
}

void TienlenGameSound::playSoundcardmatch()
{
	playEffect(sound_cardmatch);
}

void TienlenGameSound::playSoundchaomung_1()
{
	playEffect(sound_chaomung_1);
}

void TienlenGameSound::playSoundchaomung_2()
{
	playEffect(sound_chaomung_2);
}

void TienlenGameSound::playSoundChiaBai()
{
	playEffect(sound_ChiaBai);
}

void TienlenGameSound::playSoundchiabai_00()
{
	playEffect(sound_chiabai_00);
}

void TienlenGameSound::playSoundCountDown()
{
	playEffect(sound_CountDown);
}

void TienlenGameSound::playSoundDemGio()
{
	playEffect(sound_DemGio);
}

void TienlenGameSound::playSoundfinishgroupcard()
{
	playEffect(sound_finishgroupcard);
}

void TienlenGameSound::playSoundgroupcard()
{
	playEffect(sound_groupcard);
}

void TienlenGameSound::playSoundlose_1()
{
	playEffect(sound_lose_1);
}

void TienlenGameSound::playSoundlose_2()
{
	playEffect(sound_lose_2);
}

void TienlenGameSound::playSoundlose_3()
{
	playEffect(sound_lose_3);
}

void TienlenGameSound::playSoundMauBinh()
{
	playEffect(sound_MauBinh);
}

void TienlenGameSound::playSoundmaubinh_12caydongmau()
{
	playEffect(sound_maubinh_12caydongmau);
}

void TienlenGameSound::playSoundmaubinh_13caydongmau()
{
	playEffect(sound_maubinh_13caydongmau);
}

void TienlenGameSound::playSoundmaubinh_3caisanh()
{
	playEffect(sound_maubinh_3caisanh);
}

void TienlenGameSound::playSoundmaubinh_3caithung()
{
	playEffect(sound_maubinh_3caithung);
}

void TienlenGameSound::playSoundmaubinh_lucphebon()
{
	playEffect(sound_maubinh_lucphebon);
}

void TienlenGameSound::playSoundmaubinh_sanhrong()
{
	playEffect(sound_maubinh_sanhrong);
}


void TienlenGameSound::playSoundsaproi()
{
	playEffect(sound_saproi);
}

void TienlenGameSound::playSoundSoBai()
{
	playEffect(sound_SoBai);
}

void TienlenGameSound::playSoundsobai_00()
{
	playEffect(sound_sobai_00);
}

void TienlenGameSound::playSoundsobai_01()
{
	playEffect(sound_sobai_01);
}

void TienlenGameSound::playSoundsobai_02()
{
	playEffect(sound_sobai_02);
}

void TienlenGameSound::playSoundsochi()
{
	playEffect(sound_sochi);
}

void TienlenGameSound::playSoundThang()
{
	playEffect(sound_sochi);
}

void TienlenGameSound::playSoundthang_culu()
{
	playEffect(sound_thang_culu);
}

void TienlenGameSound::playSoundthang_culuhaichi()
{
	playEffect(sound_thang_culuhaichi);
}

void TienlenGameSound::playSoundthang_doi()
{
	playEffect(sound_thang_doi);
}

void TienlenGameSound::playSoundthang_mauthau()
{
	playEffect(sound_thang_mauthau);
}

void TienlenGameSound::playSoundthang_samchicu2oi()
{
	playEffect(sound_thang_samchicu2oi);
}

void TienlenGameSound::playSoundthang_samchicuoi()
{
	playEffect(sound_thang_samchicuoi);
}

void TienlenGameSound::playSoundthang_sanh()
{
	playEffect(sound_thang_sanh);
}

void TienlenGameSound::playSoundthang_thu()
{
	playEffect(sound_thang_thu);
}

void TienlenGameSound::playSoundthang_thung()
{
	playEffect(sound_thang_thung);
}

void TienlenGameSound::playSoundthang_thungphasanh()
{
	playEffect(sound_thang_thungphasanh);
}

void TienlenGameSound::playSoundthang_tuquy()
{
	playEffect(sound_thang_tuquy);
}

void TienlenGameSound::playSoundThua()
{
	playEffect(sound_Thua);
}

void TienlenGameSound::playSoundwin_1()
{
	playEffect(sound_win_1);
}

void TienlenGameSound::playSoundwin_2()
{
	playEffect(sound_win_2);
}

void TienlenGameSound::playSoundwin_3()
{
	playEffect(sound_win_3);
}

void TienlenGameSound::playSoundXepBai()
{
	playEffect(sound_XepBai);
}

void TienlenGameSound::playSoundxepbai_1()
{
	playEffect(sound_xepbai_1);
}

void TienlenGameSound::playSoundxepbai_2()
{
	playEffect(sound_xepbai_2);
}

void TienlenGameSound::playSoundxepbai_3()
{
	playEffect(sound_xepbai_3);
}

void TienlenGameSound::playSoundxepbai_culu()
{
	playEffect(sound_xepbai_culu);
}

void TienlenGameSound::playSoundxepbai_culuhaichi()
{
	playEffect(sound_xepbai_culuhaichi);
}

void TienlenGameSound::playSoundxepbai_doi()
{
	playEffect(sound_xepbai_doi);
}

void TienlenGameSound::playSoundxepbai_mauthau()
{
	playEffect(sound_xepbai_mauthau);
}

void TienlenGameSound::playSoundxepbai_samchi()
{
	playEffect(sound_xepbai_samchi);
}

void TienlenGameSound::playSoundxepbai_sanh()
{
	playEffect(sound_xepbai_sanh);
}

void TienlenGameSound::playSoundxepbai_thu()
{
	playEffect(sound_xepbai_thu);
}

void TienlenGameSound::playSoundxepbai_thung()
{
	playEffect(sound_xepbai_thung);
}

void TienlenGameSound::playSoundxepbai_thungphasanh()
{
	playEffect(sound_xepbai_thungphasanh);
}

void TienlenGameSound::playSoundxepbai_tuquy()
{
	playEffect(sound_xepbai_tuquy);
}

void TienlenGameSound::playSoundrematch_1()
{
	playEffect(sound_rematch_1);
}

void TienlenGameSound::playSoundrematch_2()
{
	playEffect(sound_rematch_2);
}

void TienlenGameSound::playSoundrematch_3()
{
	playEffect(sound_rematch_3);
}

void TienlenGameSound::playSounds_win()
{
	playEffect(sound_s_win);
}

void TienlenGameSound::playSoundstart_1()
{
	playEffect(sound_start_1);
}

void TienlenGameSound::playSoundChi()
{
	playEffect("GameSound/mobileCard/player_bing.mp3");
}

void TienlenGameSound::playBackgroundMusic()
{
	playMusic(sound_bg_lobby, true);

}

void TienlenGameSound::playInGameBackgroundMusic()
{
	playMusic(sound_bg_ingame, true);
}

void TienlenGameSound::stopBackgroundMusic()
{
	stopMusic();
}

void TienlenGameSound::stopAllEffects()
{
	//SimpleAudioEngine::getInstance()->stopAllEffects();
}

void TienlenGameSound::playSoBai()
{
	float rand = AXRANDOM_0_1() * 2;
	if (rand < 1) {
		playSoBai();
	}
	else if (rand < 2) {
		playSoundsobai_00();
	}
	
}

void TienlenGameSound::playClickCard()
{
	playEffect(sound_click_card);
}


void TienlenGameSound::playArrangeCard()
{
	playEffect(sound_arrange_card);
}

void TienlenGameSound::playAutoWin()
{
	playEffect(soundAutoWin);
}

void TienlenGameSound::playChiWin()
{
	playEffect(soundChiWin);
}

void TienlenGameSound::playChiLose()
{
	playEffect(soundChiLose);
}

void TienlenGameSound::playChatGroupCard()
{
	playEffect(soundChatGroupCard);
}

void TienlenGameSound::playChangeTurn()
{
	playEffect(soundChangeTurn);
}

void TienlenGameSound::playEndCard()
{
	playEffect(soundEndCard);
}

void TienlenGameSound::playChipFly()
{
	playEffect(soundChipFly);
}

void TienlenGameSound::playCardDown()
{
	playEffect(soundCardDown);
}
int TienlenGameSound::_playerVoice = 0;
int TienlenGameSound::_dealerVoice = 0;
