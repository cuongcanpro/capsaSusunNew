#ifndef TypeGameData_h__
#define TypeGameData_h__

enum class BinhGameState {
	BINH_GAME_WAITING,
	BINH_GAME_PLAYING,
	BINH_EFFECT_END_GAME,
	BINH_GAME_DEAL_CARD,
	BINH_GAME_VIEWING,
	BINH_GAME_COMPARE // khi nhan duoc goi tin End card, chuyen sang trang thai nay de co the xu li cac goi tin so bai
};

enum TypeSend {
	AUTO = 0,
	MANUAL = 1
};

enum ResultChi {
	WIN = 1,
	LOSE = -1,
	DRAW = 0
};

enum GameType {
	TINH_AT = 1,
	TRUYEN_THONG = 0
};

enum SapBaiType {
	BAT_SAP = 0,
	BI_SAP = 1,
	NOT_SAP = 2 // khong tham gia vao qua trinh bat sap
};


#endif // TypeGameData_h__
