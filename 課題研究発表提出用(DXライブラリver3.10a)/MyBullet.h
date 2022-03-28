#ifndef MYBULLET_H
#define MYBULLET_H
#include"Object.h"
#include"EnemyCrash.h"

class MyBullet : public Object{
public:
	void *operator new(size_t n);						//new演算子をオーバーロード
	void operator delete(void *p);						//delete演算子をオーバーロード

	MyBullet(float x,float y);							//コンストラクタ
	virtual void Move(void);							//移動関数(オーバーライド)
};

class MyBullet_Missile : public MyBullet{				//自機ミサイル
public:
	float Angle;										//角度変数
	int Picture[14];									//アニメーション記録変数
	int Time;											//内部カウンタ
	MyBullet_Missile(float x,float y,float speed);		//コンストラクタ
	void Move(void);									//移動関数(オーバーライド)
	void Draw(void);									//描画関数(オーバーライド)
};
float GetEnemyAngle(float x,float y);					//敵の方向を算出
#endif