#include"MyShip.h"
#include"DxLib.h"
#include"MyBullet.h"

MyShip::MyShip(float x,float y,float speed)								//�C���X�^���X����
:	Object(MyShipList)
{
	this->x=x;
	this->y=y;
	this->speed=speed;
	hp=50;
	Alive=TRUE;
//	Pic=LoadGraph("syujinnko.bmp");
	AnimeLoopNum=9;
	LoadDivGraph("Char_Pic/Ep1/mainep1.bmp",9,9,1,20,46,Anime);
	LoadDivGraph("Char_Pic/mainep1-kumo.bmp",4,4,1,20,24,Smog);			//���@����̉�
	Missile_Fire=FALSE;
	Time=0;
	FontHandle=CreateFontToHandle("�l�r �S�V�b�N",
					18,3,DX_FONTTYPE_ANTIALIASING_EDGE);
	color=GetColor(255,255,255);
	Rest_Bullet=300;													//����

}
void MyShip::Move(void){												//�L�[�{�[�h������́B��ʂ���o�Ȃ��悤�ɂ���B
	if(CheckHitKey(KEY_INPUT_UP)==1)y-=speed;
	if(CheckHitKey(KEY_INPUT_LEFT)==1)x-=speed;
	if(CheckHitKey(KEY_INPUT_RIGHT)==1)x+=speed;
	if(CheckHitKey(KEY_INPUT_DOWN)==1)y+=speed;
	if(x<-1.0f)x+=speed;
	if(x>1.0f) x-=speed;
	if(y<-1.0f)y+=speed;
	if(y>1.0f) y-=speed;
	if(Rest_Bullet>0 && CheckHitKey(KEY_INPUT_SPACE)==1 && Time%3==0) {
		new MyBullet(x,y);												//�ʔ���
		Rest_Bullet--;
	}
	for(TaskIterator i(EnemyList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		Alive_Judge(object);
	}
	for(TaskIterator i(EnemyBulletList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		Alive_Judge(object);
	}
//	if(Missile_Fire==FALSE &&
//	CheckHitKey(KEY_INPUT_X)==TRUE){									//���@�~�T�C���i�\��j
//		Missile_Fire=TRUE;
//		new MyBullet_Missile(x,y,0.035f);
//	}
	if(hp<=0) Alive=FALSE;
	Time++;
	if(Alive==TRUE && EndShooting==TRUE) Result+=hp*75+Rest_Bullet*10.5;//����
	Result++;
}

void *MyShip::operator new(size_t n){									//new���Z�q�̃I�[�o�[���[�h
	return MyShipList->New(n);
}
void MyShip::operator delete(void *p){									//delete���Z�q�̃I�[�o�[���[�h
	//����
	MyShipList->Delete(p);
}
void MyShip::Draw(void){
	int	object_x,object_y;
	object_x=(x+1)*Disp_Height/2;
	object_y=(y+1)*Disp_Width/2;
	DrawGraph(object_x,object_y,Anime[Time%AnimeLoopNum],TRUE);
	DrawFormatStringToHandle(520,111,color,FontHandle,"H P");
	DrawFormatStringToHandle(505,141,color,FontHandle,"�c�i��");
	DrawFormatStringToHandle(578,111,color,FontHandle,"%d",hp);
	DrawFormatStringToHandle(578,141,color,FontHandle,"%d",Rest_Bullet);

	DrawGraph(object_x,object_y+50,Smog[Time%4],TRUE);					//���G�t�F�N�g�\����(���̍s���R�����g�ɂ���Ə�����)
}