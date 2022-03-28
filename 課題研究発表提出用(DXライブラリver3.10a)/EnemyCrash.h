#ifndef ENEMYCRASH_H
#define ENEMYCRASH_H
#include"Object.h"
#include"DxLib.h"
#include"Enemy.h"
#include"Fokker_D_VII_BOSS.h"

class EnemyCrash : public Enemy{
public:
	int X,Y;																	//���W
	int Crash_Pic[10];															//���j�A�j���[�V�����L���ϐ�
	int Number,Num;																//���[�V�����L�^�ϐ�
	EnemyCrash(float x,float y,int Pic)											//�R���X�g���N�^
	:	Enemy(2,2,0,0,0,0)
	{
//���W�Z�o=====================================================================================================
		int x_buffer,y_buffer;
		GetGraphSize(Pic,&x_buffer,&y_buffer);
		X=(x+1)*Disp_Height/2-x_buffer/2;
		Y=(y+1)*Disp_Width/2-y_buffer/2;
//=============================================================================================================
		LoadDivGraph("crash_pic/E_B-�܂Ƃ�.bmp",10,10,1,60,60,Crash_Pic);		//�摜�ǂݏo��
		Number=0;Num=0;															//�������l
	}
	void Move(void){															//�ړ��֐�(����)
		if(Number<=9){
			DrawGraph(X,Y,Crash_Pic[Number],TRUE);
			Num++;
			Number=Num/3;
		}
		else {																	//��莞�Ԍo�ߌ����
			Alive=FALSE;
			for(int i=0;i<10;i++) DeleteGraph(Crash_Pic[i]);
		}
	}
};
#endif