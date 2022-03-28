#ifndef ENEMYBULLETSORT_1_H
#define ENEMYBULLETSORT_1_H
#include"EnemyBullet.h"
#include<math.h>

class Directionalshooter : public EnemyBullet{						//�����e
public:
	int Pic;
	Directionalshooter(float x,float y,float Angle,float Speed,int pic)
	:	EnemyBullet(x,y,Angle,Speed,0,0,0),
		Pic(pic)
	{}
	void Move(void){
		new EnemyBullet(x,y,ShotAngle,speed,0,0,Pic);
		ShootStop_Method();
	}
};
class SpiralShooter : public EnemyBullet{							//�Q�����e
public:
	float Shot_Angle,Shot_AngleRate,Shot_Speed;

	SpiralShooter(float x,float y,float Angle,float Speed,float Anglerate)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(Angle),
		Shot_Speed(Speed),
		Shot_AngleRate(Anglerate)
	{}
	void Move(void){
		Shot_Angle+=Shot_AngleRate;
		new EnemyBullet(x,y,Shot_Angle,Shot_Speed,0,0,1);
		Shot_Angle-=floor(Shot_Angle);
		ShootStop_Method();
	}
};
class MultipleSpiralShooter : public EnemyBullet{					//�����������e
public:
	float Shot_Angle,Shot_AngleRate,Shot_Speed;
	int Shot_Count;

	MultipleSpiralShooter(float x,float y,float Angle,
		float Speed,float Anglerate,int count)						//�R���X�g���N�^
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(Angle),
		Shot_Speed(Speed),
		Shot_AngleRate(Anglerate),
		Shot_Count(count)
	{}
	void Move(void){
		for(int i=0;i<Shot_Count;i++){
			new EnemyBullet(x,y,Shot_Angle+
				(float)i/Shot_Count,Shot_Speed,0,0,1);
		}
		Shot_Angle+=Shot_AngleRate;
		Shot_Angle-=floor(Shot_Angle);
		ShootStop_Method();
	}
};
class IntervalMultipleSpiralShooter : public EnemyBullet{			//���ǌ^�������Q�����e
public:
	float Shot_Angle,Shot_AngleRate,Shot_Speed;
	int Shot_Count,Interval,Time;

	IntervalMultipleSpiralShooter(float x,float y,float Angle,
		float Speed,float Anglerate,int count,int interval)			//�R���X�g���N�^
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(Angle),
		Shot_Speed(Speed),
		Shot_AngleRate(Anglerate),
		Shot_Count(count),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			for(int i=0;i<Shot_Count;i++){
				new EnemyBullet(x,y,Shot_Angle+
					(float)i/Shot_Count,Shot_Speed,0,0,1);
			}
			Shot_Angle+=Shot_AngleRate;
			Shot_Angle-=floor(Shot_Angle);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class BiDirectionalSpiralShooter : public EnemyBullet{				//����]�Q���e
public:
	float Shot_Angle[2];											//���ˊp�x
	float Shot_AngleRate[2];										//���ˊp���x
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	BiDirectionalSpiralShooter(float x,float y,float Angle,float Speed,
		float Anglerate1,float Anglerate2,int count,int interval)	//�R���X�g���N�^
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Speed(Speed),
		Shot_Count(count),
		Interval(interval),
		Time(0)
	{
		Shot_Angle[0]=Angle;
		Shot_Angle[1]=Angle;
		Shot_AngleRate[0]=Anglerate1;
		Shot_AngleRate[1]=Anglerate2;
	}
	void Move(void){
		if(Time==0){
			for(int j=0;j<2;j++){
				for(int i=0;i<Shot_Count;i++){
					new EnemyBullet(x,y,Shot_Angle[j]+
						(float)i/Shot_Count,Shot_Speed,0,0,2);
				}
				Shot_Angle[j]+=Shot_AngleRate[j];
				Shot_Angle[j]-=floor(Shot_Angle[j]);
			}
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class BentSpiralShooter : public EnemyBullet{						//����Q���e
public:
	float Shot_Angle;												//���ˊp�x
	float Shot_AngleRate;											//���ˊp���x
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ˑ��x
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	float bullet_AngleRate;											//�e�̊p���x
	float bullet_SpeedRate;											//�e�̊p���x
	BentSpiralShooter(float x,float y,float Angle,float Anglerate,float speed,int count,
		int interval,float bullet_anglerate,float bullet_speedrate)	//�R���X�g���N�^

	:	EnemyBullet(x,y,0,0,0,0,0),									//�����ȂƂ��낱��x,y�ȊO�Ӗ��Ȃ�
		Shot_Angle(Angle),
		Shot_AngleRate(Anglerate),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		bullet_AngleRate(bullet_anglerate),
		bullet_SpeedRate(bullet_speedrate)
	{}
	void Move(void){
		if(Time==0){
			for(int i=0;i<Shot_Count;i++){
				new EnemyBullet(x,y,Shot_Angle+(float)i/Shot_Count,
					Shot_Speed,bullet_AngleRate,bullet_SpeedRate,1);

			}
			Shot_Angle+=Shot_AngleRate;
			Shot_Angle-=floor(Shot_Angle);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class CombinedSpiralShooter : public EnemyBullet{					//����]�Q���e+��������Q���e
public:
	BiDirectionalSpiralShooter *BiDirectional;						//����]�Q���e
	BentSpiralShooter *Bent;										//��������Q���e
	CombinedSpiralShooter(float x,float y)
	:	EnemyBullet(x,y,0,0,0,0,0)
	{
		BiDirectional=new BiDirectionalSpiralShooter(x,y,
			0,0.02f,0.015f,-0.01f,4,5);

		Bent=new BentSpiralShooter(x,y,0,0.02f,0,10,10,-0.003f,0.0002f);
	}
	void Move(void){
		ShootStop_Method();
	}
};
class WasherSpiralShooter : public EnemyBullet{						//����@�Q���e
public:
	BiDirectionalSpiralShooter *BiDirectional;						//����]�Q���e
	BentSpiralShooter *Bent;										//����Q���e
	float MaxShotAngleRate;											//���ˊp�x�̍ő�l
	float MaxbulletAngleRate;										//�e�̊p���x�̍ő�l
	int Time;														//�^�C�}�[
	WasherSpiralShooter(float x,float y)
	:	EnemyBullet(x,y,0,0,0,0,0),
		MaxShotAngleRate(0.02f),
		MaxbulletAngleRate(0.003f),
		Time(0)
	{
		BiDirectional=new BiDirectionalSpiralShooter(x,y,
			0,0.015f,-0.01f,0.02f,4,5);

		Bent=new BentSpiralShooter(x,y,0,0,0,10,10,0,0.0002f);
	}
	void Move(void){
		if(Time<250){												//�E����
			Bent->Shot_AngleRate=MaxShotAngleRate;
			Bent->bullet_AngleRate=-MaxbulletAngleRate;
		}else
		if(Time<300){												//�E�������獶������
			Bent->Shot_AngleRate=MaxShotAngleRate*(275-Time)/25;
			Bent->bullet_AngleRate=-MaxbulletAngleRate*(275-Time)/25;
		}else
		if(Time<550){												//������
			Bent->Shot_AngleRate=-MaxShotAngleRate;
			Bent->bullet_AngleRate=MaxbulletAngleRate;
		}else
		{															//����������E������
			Bent->Shot_AngleRate=-MaxShotAngleRate*(575-Time)/25;
			Bent->bullet_AngleRate=MaxbulletAngleRate*(575-Time)/25;
		}
		Time=(Time+1)%600;
		ShootStop_Method();
	}
};
class HardWasherSpiralShooter : public WasherSpiralShooter{			//����Փx�^����@�Q���e
public:
	HardWasherSpiralShooter(float x,float y)
	:	WasherSpiralShooter(x,y)
	{
		BiDirectional->Shot_Speed=0.04f;
		Bent->bullet_SpeedRate=0.0004f;

		BiDirectional->Interval=3;
		Bent->Interval=5;

		MaxShotAngleRate=0.028f;
		MaxbulletAngleRate=0.0042f;
	}
};
#endif
//���̃v���O�����͎Q�l���̓��e��������������悤�ɕς��������ł��B
//�ڂ����͎Q�l�����������������B