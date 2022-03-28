#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include"Object.h"

class EnemyBullet : public Object{
public:
	float ShotAngle;													//­Λpx
	float Anglerange;													//­ΛpxΝΝ
	float Anglerate;													//pxΟ»
	float Speedrate;													//eΜΑ¬x
	
	void *operator new(size_t n);										//newZqπI[o[[h
	void operator delete(void *p);										//deleteZqπI[o[[h

	EnemyBullet(float x,float y,float angle,float speed,
			float anglerate,float speedrate,int bullet_pic_type);		//RXgN^
	virtual void Move(void);
	void ShootStop_Method(void);										//­ΛIΉΦ
};
void ShootNWay(float x,float y,float angle,float angle_range,
			float speed,int count,float angle_rate,float speed_rate);	//NWaye
float GetMyShipAngle(float x,float y);									//©@ΜϋόπZo
#endif
