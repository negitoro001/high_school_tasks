#ifndef ENEMY_H
#define ENEMY_H
#include"Object.h"

class Enemy : public Object{
public:
	int type,cnt;														//敵種類、内部カウンタ
	bool ShootFlag;														//発射フラグ
	float Angle;														//角度
	float Angle_a;														//角度の加速度
	float rad;															//ラジアン計算変数
	int FireInterval;													//弾幕間隔
	bool  IntervalFlag;													//弾幕間隔（フラグ）
	int AnimeLoopNum;													//アニメーション制御変数
	int Anime[30];														//アニメーション記憶変数

	void *operator new(size_t n);										//new演算子をオーバーロード
	void operator delete(void *p);										//delete演算子をオーバーロード

	Enemy(float x,float y,float speed,int hp,int type,int pic_tipe);	//コンストラクタ
	virtual void Move(void);											//移動関数(オーバーライド)
	virtual void Draw(void);											//描画関数(オーバーライド)
};
void Pattern1(float x,float y);											//図柄のパターン1
#endif