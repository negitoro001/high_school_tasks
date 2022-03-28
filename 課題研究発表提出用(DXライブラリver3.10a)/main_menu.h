#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include"Invariable_FPS.h"

class Menu{
public:
	int Font;								//フォントデータ
	int CurrentFont;						//選択されたモードのフォント
	char *string;							//文字列
	int White;								//色（白）
	int x,y,pic;							//座標保存変数
	Menu(int lenth,char *string);			//コンストラクタ
	void PutMenu(bool Flag);				//表示部
	~Menu(void);							//デストラクタ
};
class MainMenu{
public:
	Menu* maindisp[5];						//宣言
	FPS *fps;								//宣言
	MainMenu(void);							//コンストラクタ
	bool mainmenu_flag;						//メインメニューフラグ
	bool stopflag;							//停止フラグ
	int back_pic;							//背景
	int y;									//座標
	int White;								//色（白）
	int selecter;							//どれを選んでいるか
	int Timer;								//タイマー

	int Main_Menu(void);					//処理
	void MainMenu_Input_Key(void);			//キーボード入力処理
	~MainMenu(void);						//デストラクタ
};
#endif