#ifndef FOKKER_D_VII_BOSS_H
#define FOKKER_D_VII_BOSS_H
#include"Enemy.h"
#include"Object.h"

class Fokker_D_VII_BOSS : public Enemy{
public:
	Fokker_D_VII_BOSS(float x,float y,
		float speed,int hp,int type);						//コンストラクタ
	void Move(void);										//移動関数(オーバーライド)
};
#endif