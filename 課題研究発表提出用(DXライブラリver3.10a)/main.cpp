#include"DxLib.h"
#include"main_menu.h"
#include"Novel_Base_Class.h"
#include"ShootingGame.h"
#include"Stage1-1_Novel.h"
#include"Game.h"
#pragma warning(disable:4244)
#include<iostream>
#include<map>
#include<vector>
#include<stdio.h>
#include <time.h>
using namespace std;

void Novel_Road_Main(void){																		//セーブデータ読み出し部
	Method();																					//セーブデータ読み出し
	switch(Data_r.EpisodeNumber){																//セーブデータによる切り替え部
	case EP1_1:
		if(Data_r.LineNumber!=-1){
			Novel_Base *novel;
			novel=new Stage1_1_Novel(Data_r.LineNumber);
			novel->Move();
			delete novel;
		}
		else{
			ShootingGame *Stage1_1;
			Stage1_1=new ShootingGame(EP1_1);
			Stage1_1->Stage();
			delete Stage1_1;
		}
		break;
	}
}

void Shooting_main(void){																		//仮設
	InitGraph();
	ShootingGame *Stage1_1;
	Stage1_1=new ShootingGame(EP1_1);
	Stage1_1->Stage();
	delete Stage1_1;
}

void Novel_main(void){																			//仮設
	Novel_Base *novel;
	novel=new Stage1_1_Novel();
	novel->Move();
	delete novel;
}

void gamemain(void){
	int Selecter;
	Game *game;																					//宣言(ゲーム本体)
	MainMenu *main_menu;																		//宣言(メインメニュー)
	main_menu=new MainMenu();																	//コンストラクタ(メインメニュー)
	Selecter=main_menu->Main_Menu();
	delete main_menu;																			//デストラクタ(メインメニュー)
	SetDrawBright(0,0,0);
	switch(Selecter){
	case 0:
		game=new Game(FALSE);																	//コンストラクタ
		game->Play();																			//本体処理
		delete game;																			//デストラクタ
		break;
	case 1:
		game=new Game(TRUE);																	//コンストラクタ
		game->Play();																			//本体処理
		delete game;																			//デストラクタ
		break;
	case 2:
		Novel_main();
		break;
	case 3:
		Novel_Road_Main();																		//作業用
		break;
	case 4:
		break;
	default:
		break;
	}
}

bool message_box(){																				//メッセージボックス部(必要に応じて使用)
	int flag;
	flag=MessageBox(
		NULL ,
		TEXT("フルスクリーンモードで起動しますか？(マウスで選択してください)"),
		TEXT("スクリーン設定"),
		MB_YESNO | MB_ICONQUESTION );
	if(flag==IDNO) return TRUE;
	else return FALSE;
}

//仮設=========================================================================================================================================
void ResultPut(void){
	int FontHandle=CreateFontToHandle("ＭＳ ゴシック",18,3,DX_FONTTYPE_ANTIALIASING_EDGE);
	int color=GetColor(0,0,0);
	int EndGraph;
	EndGraph=LoadGraph("Char_Pic/Ep1/終了画面.png");
	for(int i=0;i<255;i+=5){
		ClearDrawScreen();
		SetDrawBright(i,i,i);
		DrawGraph(0,0,EndGraph,TRUE);
		DrawFormatStringToHandle(110,385,color,FontHandle,"%d",Result);
		ScreenFlip();
	}
	WaitKey();
	FILE *fp;
	if ((fp = fopen("Result.txt", "a")) == NULL) {
		printf("file open error!!\n");
		exit(EXIT_FAILURE);																		//エラーの場合は通常、異常終了する
	}
	time_t now = time(NULL);
    struct tm *pnow = localtime(&now);
	fprintf(fp,"%d:%d:%d記録%d\n",pnow->tm_hour,pnow->tm_min,pnow->tm_sec,Result);
	fclose(fp);
}
void StartingGame(void){																		//起動時の処理
	int Logo1=LoadGraph("OP/高知県立高知工業高等学校.png");
	for(int i=0;i<255;i+=5){
		ClearDrawScreen();
		SetDrawBright(i,i,i);
		DrawGraph(0,0,Logo1,TRUE);
		ScreenFlip();
	}
	WaitTimer(3000);
	for(int i=255;i>=0;i-=5){
		ClearDrawScreen();
		SetDrawBright(i,i,i);
		DrawGraph(0,0,Logo1,TRUE);
		ScreenFlip();
	}
	SetDrawBright(255,255,255);
	PlayMovie("OpAnime.AVI",1,DX_MOVIEPLAYTYPE_NORMAL);
}
//=============================================================================================================================================

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
											LPSTR lpCmdLine, int nCmdShow ){					//メイン関数

	SetMainWindowText("未完成ゲーム");															//タイトルの名前を変更
//	if(message_box()==TRUE) ChangeWindowMode(TRUE);												//ウィンドウモード(仮設)
	ChangeWindowMode(TRUE);																		//ウィンドウモードで実行
	SetWindowSizeChangeEnableFlag(TRUE);														//画面の大きさの変更を可能に
	if(DxLib_Init()==-1||SetDrawScreen(DX_SCREEN_BACK)!=0) return -1;							//初期化と裏画面化

	StartingGame();																				//起動時の処理
	gamemain();																					//ゲーム本体処理
//	ResultPut();																				//仮設
	DxLib_End();																				//終了
	return 0;																					//OSに正常終了したことを通知
}