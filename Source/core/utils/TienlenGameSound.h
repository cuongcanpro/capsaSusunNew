#ifndef TienlenGameSound_h__
#define TienlenGameSound_h__

#include <vector>
#include <string>

const int VOICES_NUMBER = 3;

class TienlenGameSound
{
public:
	TienlenGameSound();
	~TienlenGameSound();
	static void stopMusic();
	static void playSoundSpinWheel();
	static void playSoundGiftNormal();
	static void playSoundGiftBig();
	static std::string getRandomSound(std::string path, int number, std::string duoi);
	static bool getRandom(int percent);
	static void playDkThoat();
	static void playJackpot();
	static void playHuyThoat();
	static void playClick();

	static void playRegQuit(bool success);
	static void playBackgroundMusic();
	static void playInGameBackgroundMusic();
	static void stopBackgroundMusic();

	// game tien len
	static void playSoundJackpot();
	static void regQuit(bool success);
	static void playCard();
	static void musicWin();
	static void startGame();
	static void playBoLuot();
	static void playDenLuot();
	static void playEndWin();
	static void playEndLose();
	static void playSoundbaobinh_12caydongmau();
	static void playSoundbaobinh_13caydongmau();
	static void playSoundbaobinh_3caisanh();
	static void playSoundbaobinh_3caithung();
	static void playSoundbaobinh_lucphebon();
	static void playSoundbaobinh_sanhrong();
	static void playSoundBatDauGame();
	static void playSoundbatsapnay();
	static void playSoundBinhLung();
	static void playSoundButtonClick();
	static void playSoundbutton_cancel();
	static void playSoundcardmatch();
	static void playSoundchaomung_1();
	static void playSoundchaomung_2();
	static void playSoundChiaBai();
	static void playSoundchiabai_00();
	static void playSoundCountDown();
	static void playSoundDemGio();
	static void playSoundfinishgroupcard();
	static void playSoundgroupcard();
	static void playSounds_lose();
	static void playSoundlose_1();
	static void playSoundlose_2();
	static void playSoundlose_3();
	static void playSoundMauBinh();
	static void playSoundmaubinh_12caydongmau();
	static void playSoundmaubinh_13caydongmau();
	static void playSoundmaubinh_3caisanh();
	static void playSoundmaubinh_3caithung();
	static void playSoundmaubinh_lucphebon();
	static void playSoundmaubinh_sanhrong();
	static void playSoundsaproi();
	static void playSoundSoBai();
	static void playSoundsobai_00();
	static void playSoundsobai_01();
	static void playSoundsobai_02();
	static void playSoundsochi();
	static void playSoundThang();
	static void playSoundthang_culu();
	static void playSoundthang_culuhaichi();
	static void playSoundthang_doi();
	static void playSoundthang_mauthau();
	static void playSoundthang_samchicu2oi();
	static void playSoundthang_samchicuoi();
	static void playSoundthang_sanh();
	static void playSoundthang_thu();
	static void playSoundthang_thung();
	static void playSoundthang_thungphasanh();
	static void playSoundthang_tuquy();
	static void playSoundThua();
	static void playSoundwin_1();
	static void playSoundwin_2();
	static void playSoundwin_3();
	static void playSoundXepBai();
	static void playSoundxepbai_1();
	static void playSoundxepbai_2();
	static void playSoundxepbai_3();
	static void playSoundxepbai_culu();
	static void playSoundxepbai_culuhaichi();
	static void playSoundxepbai_doi();
	static void playSoundxepbai_mauthau();
	static void playSoundxepbai_samchi();
	static void playSoundxepbai_sanh();
	static void playSoundxepbai_thu();
	static void playSoundxepbai_thung();
	static void playSoundxepbai_thungphasanh();
	static void playSoundxepbai_tuquy();
	static void playSoundrematch_1();
	static void playSoundrematch_2();
	static void playSoundrematch_3();
	static void playSounds_win();
	static void playSoundstart_1();
	static void playSoundChi();
	static void stopAllEffects();
	static void playSoBai();
	static void playClickCard();
	static void playArrangeCard();
	static void playAutoWin();
	static void playChiWin();
	static void playChiLose();
	static void playChatGroupCard();
	static void playChangeTurn();
	static void playEndCard();
	static void playChipFly();
	static void playCardDown();
private:
	static int _playerVoice;
	static int _dealerVoice;
};
#endif // TienlenGameSound_h__
