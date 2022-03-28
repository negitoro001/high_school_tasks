#include"DxLib.h"
#include"Invariable_FPS.h"

Invariable_FPS::Invariable_FPS(void){			//�R���X�g���N�^
	StartTime=0;
	Count=0;
	Fps=0;
}
bool Invariable_FPS::measurement(void){			//�v��
	if(Count==0){								//1�t���[���ڂȂ玞�����L��
		StartTime=GetNowCount();
	}
	if(Count==COUNT){							//60�t���[���ڂȂ畽�ς��v�Z����
		int t=GetNowCount();
		Fps=1000.f/((t-StartTime)/(float)COUNT);
		Count=0;
		StartTime=t;
	}
	Count++;
	return true;
}
void Invariable_FPS::Wait(void){
	int tookTime=GetNowCount()-StartTime;		//������������
	int waitTime=Count*1000/FPS-tookTime;		//�҂ׂ�����
	if(waitTime>0) Sleep(waitTime);				//�ҋ@
}