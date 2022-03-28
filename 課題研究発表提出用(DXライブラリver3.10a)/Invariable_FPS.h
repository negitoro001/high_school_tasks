#ifndef INVARIABLE_FPS_H
#define INVARIABLE_FPS_H

class Invariable_FPS{
	int StartTime;				//測定開始時刻
	int Count;					//カウンタ
	float Fps;					//fps
	static const int COUNT=60;	//平均を取るサンプル数
	static const int FPS=60;	//設定したFPS
public:
	Invariable_FPS(void);		//コンストラクタ
	bool measurement(void);		//計測
	void Wait(void);			//待機
};

typedef Invariable_FPS FPS;		//「Invariable_FPS」を「FPS」に略す

#endif