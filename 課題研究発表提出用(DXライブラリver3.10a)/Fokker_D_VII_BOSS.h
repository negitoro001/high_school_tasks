#ifndef FOKKER_D_VII_BOSS_H
#define FOKKER_D_VII_BOSS_H
#include"Enemy.h"
#include"Object.h"

class Fokker_D_VII_BOSS : public Enemy{
public:
	Fokker_D_VII_BOSS(float x,float y,
		float speed,int hp,int type);						//�R���X�g���N�^
	void Move(void);										//�ړ��֐�(�I�[�o�[���C�h)
};
#endif