#ifndef MYSHIP_H
#define MYSHIP_H
#include"Object.h"

class MyShip : public Object{
public:
	int color;									//�F�ϐ�
	int FontHandle;								//�t�H���g����ϐ�
	int Rest_Bullet;							//�c�i��
	bool Missile_Fire;							//�~�T�C�����˃t���O
	int Time;									//�����J�E���^
	int AnimeLoopNum;							//�A�j���[�V��������ϐ�
	int Anime[30];								//�A�j���[�V�����L���ϐ�
	int Smog[4];								//���@����ɏo�Ă��鉌

	void *operator new(size_t n);				//new���Z�q���I�[�o�[���[�h
	void operator delete(void *p);				//delete���Z�q���I�[�o�[���[�h

	MyShip(float x,float y,float speed);		//�R���X�g���N�^
	void Move(void);							//�ړ��֐�(�I�[�o�[���C�h)
	virtual void Draw(void);					//�`��֐�(�I�[�o�[���C�h)
};
#endif