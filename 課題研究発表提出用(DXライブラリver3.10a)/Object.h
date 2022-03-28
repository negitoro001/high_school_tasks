#ifndef OBJECT_H
#define OBJECT_H
#include"Task.h"
#define Disp_Width 480
#define Disp_Height 387							//パラメータ調整可能
class Object : public Task{
public:
	Object(TaskList *List);						//コンストラクタ
	float x,y,speed;							//座標、スピード変数
	bool Alive;									//生存フラグ
	int Pic,hp;									//Picは一枚イラスト用、体力変数

	virtual void Move(void)=0;					//移動関数(純粋仮想関数）
	virtual void Draw(void);					//描画関数(仮想関数）
	virtual void Alive_Judge(Object *object);	//あたり判定
};
#endif
//純粋仮想関数とは、基底クラスでは宣言のみで、定義されていない関数のこと