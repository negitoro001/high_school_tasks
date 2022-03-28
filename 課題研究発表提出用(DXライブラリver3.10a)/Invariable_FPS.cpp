#include"DxLib.h"
#include"Invariable_FPS.h"

Invariable_FPS::Invariable_FPS(void){			//コンストラクタ
	StartTime=0;
	Count=0;
	Fps=0;
}
bool Invariable_FPS::measurement(void){			//計測
	if(Count==0){								//1フレーム目なら時刻を記憶
		StartTime=GetNowCount();
	}
	if(Count==COUNT){							//60フレーム目なら平均を計算する
		int t=GetNowCount();
		Fps=1000.f/((t-StartTime)/(float)COUNT);
		Count=0;
		StartTime=t;
	}
	Count++;
	return true;
}
void Invariable_FPS::Wait(void){
	int tookTime=GetNowCount()-StartTime;		//かかった時間
	int waitTime=Count*1000/FPS-tookTime;		//待つべき時間
	if(waitTime>0) Sleep(waitTime);				//待機
}