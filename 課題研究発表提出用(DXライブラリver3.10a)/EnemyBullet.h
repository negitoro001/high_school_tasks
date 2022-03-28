#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include"Object.h"

class EnemyBullet : public Object{
public:
	float ShotAngle;													//���ˊp�x
	float Anglerange;													//���ˊp�x�͈�
	float Anglerate;													//�p�x�ω�
	float Speedrate;													//�e�̉����x
	
	void *operator new(size_t n);										//new���Z�q���I�[�o�[���[�h
	void operator delete(void *p);										//delete���Z�q���I�[�o�[���[�h

	EnemyBullet(float x,float y,float angle,float speed,
			float anglerate,float speedrate,int bullet_pic_type);		//�R���X�g���N�^
	virtual void Move(void);
	void ShootStop_Method(void);										//���ˏI���֐�
};
void ShootNWay(float x,float y,float angle,float angle_range,
			float speed,int count,float angle_rate,float speed_rate);	//NWay�e
float GetMyShipAngle(float x,float y);									//���@�̕������Z�o
#endif
