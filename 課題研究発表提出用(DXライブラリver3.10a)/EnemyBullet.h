#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include"Object.h"

class EnemyBullet : public Object{
public:
	float ShotAngle;													//発射角度
	float Anglerange;													//発射角度範囲
	float Anglerate;													//角度変化
	float Speedrate;													//弾の加速度
	
	void *operator new(size_t n);										//new演算子をオーバーロード
	void operator delete(void *p);										//delete演算子をオーバーロード

	EnemyBullet(float x,float y,float angle,float speed,
			float anglerate,float speedrate,int bullet_pic_type);		//コンストラクタ
	virtual void Move(void);
	void ShootStop_Method(void);										//発射終了関数
};
void ShootNWay(float x,float y,float angle,float angle_range,
			float speed,int count,float angle_rate,float speed_rate);	//NWay弾
float GetMyShipAngle(float x,float y);									//自機の方向を算出
#endif
