#include"MyBullet.h"
#include"DxLib.h"
#include<math.h>

MyBullet::MyBullet(float x,float y)											//�C���X�^���X����
:	Object(MyBulletList)
	{
	this->x=x;
	this->y=y;
	speed=0.05f;
	Alive=TRUE;
	hp=1;
	Pic=LoadGraph("GB..png");
}
void MyBullet::Move(void){													//�ړ������i�c�����ɐi�ނ����j
	y-=speed;
	for(TaskIterator i(EnemyList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		Alive_Judge(object);
	}
	if(abs(x)>1 || abs(y)>1)Alive=FALSE;
	else if(hp<=0)Alive=FALSE;
}
void *MyBullet::operator new(size_t n){
	return MyBulletList->New(n);
}

void MyBullet::operator delete(void *p){
	MyBulletList->Delete(p);
}
MyBullet_Missile::MyBullet_Missile(float x,float y,float speed)				//�R���X�g���N�^(�~�T�C��)
:	MyBullet(x,y)
{
	this->speed=speed;
	Angle=GetEnemyAngle(x,y);
	LoadDivGraph("crash_pic/cluster_missile.bmp",14,7,2,16,30,Picture);
	Time=0;
	hp=1;
}
void MyBullet_Missile::Move(void){											//�ړ��֐�(�~�T�C��)
	float rad=Angle*DX_PI_F*2;
	x+=speed*cosf(rad);
	y+=speed*sinf(rad);
	Angle=GetEnemyAngle(x,y);
	Time++;
	for(TaskIterator i(EnemyList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		Alive_Judge(object);
	}
	if(abs(x)>1 || abs(y)>1)Alive=FALSE;
	if(hp<=0){
		Alive=FALSE;
		new EnemyCrash(x,y,Picture[0]);
	}
}
void MyBullet_Missile::Draw(void){											//�`��֐�(�A�j���[�V�����Ή�)
	int object_x,object_y,x_buffer,y_buffer;
	GetGraphSize(Picture[Time%14],&x_buffer,&y_buffer);
	object_x=(x+1)*Disp_Height/2-x_buffer/2;
	object_y=(y+1)*Disp_Width/2-y_buffer/2;
	DrawGraph(object_x,object_y,Picture[Time%14],TRUE);
}
float GetEnemyAngle(float x,float y){										//�G�̕������Z�o
	for(TaskIterator i(EnemyList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		return atan2f(object->y-y,object->x-x)/3.14159265/2;
	}
}