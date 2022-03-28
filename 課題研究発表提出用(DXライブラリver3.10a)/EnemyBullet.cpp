#include"EnemyBullet.h"
#include"DxLib.h"
#include"MyShip.h"
#include<math.h>

EnemyBullet::EnemyBullet(float x,float y,float angle,float speed,
				float anglerate,float speedrate,int bullet_pic_type)			//コンストラクタ
:	Object(EnemyBulletList)
	{
	this->x=x;
	this->y=y;
	ShotAngle=angle;
	this->speed=speed;
	Anglerate=anglerate;
	Speedrate=speedrate;
	Alive=TRUE;
	hp=1;
	switch(bullet_pic_type){
	case 1:
		Pic=LoadGraph("GB..png");
		break;
	case 2:
		Pic=LoadGraph("GB..png");
		break;
	}
}
void EnemyBullet::Move(void){
	float rad=ShotAngle*3.14159265*2;											//ラジアン
	x+=speed*cosf(rad);
	y+=speed*sinf(rad);
	ShotAngle+=Anglerate;
	speed+=Speedrate;
	for(TaskIterator i(MyShipList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		Alive_Judge(object);
	}
	if(abs(x)>1 || abs(y)>1)Alive=FALSE;
	if(hp<=0)Alive=FALSE;
}
void EnemyBullet::ShootStop_Method(void){
	Alive=FALSE;
	for(TaskIterator i(EnemyList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		if(object->x==x && object->y==y)Alive=TRUE;
	}
}

void *EnemyBullet::operator new(size_t n){
	return EnemyBulletList->New(n);
}

void EnemyBullet::operator delete(void *p){
	EnemyBulletList->Delete(p);
}
void ShootNWay(float x,float y,float angle,float angle_range,
					float speed,int count,float angle_rate,float speed_rate){	//N-Way弾
	if(count>1){
		for(int i=0;i<count;i++){
			new EnemyBullet(x,y,angle+angle_range*((float)i/(count-1)-0.5f),
								speed,angle_rate,speed_rate,1);					//N-Way弾の画像の種類
		}
	}else
	if(count==1){
		new EnemyBullet(x,y,angle,speed,angle_rate,speed_rate,1);
	}
}
float GetMyShipAngle(float x,float y){											//自機の方向を算出
	for(TaskIterator i(MyShipList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		return atan2f(object->y-y,object->x-x)/3.14159265/2;
	}
}