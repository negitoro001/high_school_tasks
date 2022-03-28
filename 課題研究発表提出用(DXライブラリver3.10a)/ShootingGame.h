#ifndef SHOOTINGGAME_H
#define SHOOTINGGAME_H
#include"DxLib.h"
#include"Task.h"
#include"Object.h"
#include"Enemy.h"
#include"MyShip.h"
#include"Invariable_FPS.h"
#include"Novel_Base_Class.h"

class ShootingGame{
public:
	FPS *fps;													//宣言
	int enemy_book,appear_cnt,count,Back_Music,Back_Picture;	//宣言（作業用の関数）
	ShootingGame(int TitleNum);									//コンストラクタ
	~ShootingGame(void);										//デストラクタ

	int Contrast;												//コントラスト調整
	int FontHandle,color,TitleNum;								//フォントハンドル、色変数、タイトル番号
	int Side;													//画面右サイドの画像

	int EnemyDataLoader_appear_cnt(int enemy_csv);				//敵出現時間データ読み込み
	virtual void Back_Pictures_Move(int count,int Pic);			//背景読み込み(仮想関数)
	void StageDetail(void);										//ステージ詳細表示
	void GameTask(TaskList *List);								//タスクリスト管理部
	void EnemyDataLoader(int enemy_csv);						//敵データ読み込み
	virtual void Stage(void);									//ゲーム本体(仮想関数)
	bool EndFlag;												//終了フラグ
	bool EndCheck(void);										//終了チェック
};
#endif