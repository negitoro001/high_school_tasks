#ifndef MYBULLET_H
#define MYBULLET_H
#include"Object.h"
#include"EnemyCrash.h"

class MyBullet : public Object{
public:
	void *operator new(size_t n);						//new���Z�q���I�[�o�[���[�h
	void operator delete(void *p);						//delete���Z�q���I�[�o�[���[�h

	MyBullet(float x,float y);							//�R���X�g���N�^
	virtual void Move(void);							//�ړ��֐�(�I�[�o�[���C�h)
};

class MyBullet_Missile : public MyBullet{				//���@�~�T�C��
public:
	float Angle;										//�p�x�ϐ�
	int Picture[14];									//�A�j���[�V�����L�^�ϐ�
	int Time;											//�����J�E���^
	MyBullet_Missile(float x,float y,float speed);		//�R���X�g���N�^
	void Move(void);									//�ړ��֐�(�I�[�o�[���C�h)
	void Draw(void);									//�`��֐�(�I�[�o�[���C�h)
};
float GetEnemyAngle(float x,float y);					//�G�̕������Z�o
#endif