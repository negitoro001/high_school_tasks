#ifndef ENEMY_H
#define ENEMY_H
#include"Object.h"

class Enemy : public Object{
public:
	int type,cnt;														//�G��ށA�����J�E���^
	bool ShootFlag;														//���˃t���O
	float Angle;														//�p�x
	float Angle_a;														//�p�x�̉����x
	float rad;															//���W�A���v�Z�ϐ�
	int FireInterval;													//�e���Ԋu
	bool  IntervalFlag;													//�e���Ԋu�i�t���O�j
	int AnimeLoopNum;													//�A�j���[�V��������ϐ�
	int Anime[30];														//�A�j���[�V�����L���ϐ�

	void *operator new(size_t n);										//new���Z�q���I�[�o�[���[�h
	void operator delete(void *p);										//delete���Z�q���I�[�o�[���[�h

	Enemy(float x,float y,float speed,int hp,int type,int pic_tipe);	//�R���X�g���N�^
	virtual void Move(void);											//�ړ��֐�(�I�[�o�[���C�h)
	virtual void Draw(void);											//�`��֐�(�I�[�o�[���C�h)
};
void Pattern1(float x,float y);											//�}���̃p�^�[��1
#endif