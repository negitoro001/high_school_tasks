#ifndef MYSHIP_H
#define MYSHIP_H
#include"Object.h"

class MyShip : public Object{
public:
	int color;									//色変数
	int FontHandle;								//フォント制御変数
	int Rest_Bullet;							//残段数
	bool Missile_Fire;							//ミサイル発射フラグ
	int Time;									//内部カウンタ
	int AnimeLoopNum;							//アニメーション制御変数
	int Anime[30];								//アニメーション記憶変数
	int Smog[4];								//自機後方に出てくる煙

	void *operator new(size_t n);				//new演算子をオーバーロード
	void operator delete(void *p);				//delete演算子をオーバーロード

	MyShip(float x,float y,float speed);		//コンストラクタ
	void Move(void);							//移動関数(オーバーライド)
	virtual void Draw(void);					//描画関数(オーバーライド)
};
#endif