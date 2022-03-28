#ifndef ENEMYCRASH_H
#define ENEMYCRASH_H
#include"Object.h"
#include"DxLib.h"
#include"Enemy.h"
#include"Fokker_D_VII_BOSS.h"

class EnemyCrash : public Enemy{
public:
	int X,Y;																	//座標
	int Crash_Pic[10];															//爆破アニメーション記憶変数
	int Number,Num;																//モーション記録変数
	EnemyCrash(float x,float y,int Pic)											//コンストラクタ
	:	Enemy(2,2,0,0,0,0)
	{
//座標算出=====================================================================================================
		int x_buffer,y_buffer;
		GetGraphSize(Pic,&x_buffer,&y_buffer);
		X=(x+1)*Disp_Height/2-x_buffer/2;
		Y=(y+1)*Disp_Width/2-y_buffer/2;
//=============================================================================================================
		LoadDivGraph("crash_pic/E_B-まとめ.bmp",10,10,1,60,60,Crash_Pic);		//画像読み出し
		Number=0;Num=0;															//初期数値
	}
	void Move(void){															//移動関数(動作)
		if(Number<=9){
			DrawGraph(X,Y,Crash_Pic[Number],TRUE);
			Num++;
			Number=Num/3;
		}
		else {																	//一定時間経過後消滅
			Alive=FALSE;
			for(int i=0;i<10;i++) DeleteGraph(Crash_Pic[i]);
		}
	}
};
#endif