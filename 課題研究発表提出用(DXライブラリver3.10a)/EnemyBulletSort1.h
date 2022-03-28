#ifndef ENEMYBULLETSORT_1_H
#define ENEMYBULLETSORT_1_H
#include"EnemyBullet.h"
#include<math.h>

class Directionalshooter : public EnemyBullet{						//方向弾
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
class SpiralShooter : public EnemyBullet{							//渦巻き弾
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
class MultipleSpiralShooter : public EnemyBullet{					//多方向巻き弾
public:
	float Shot_Angle,Shot_AngleRate,Shot_Speed;
	int Shot_Count;

	MultipleSpiralShooter(float x,float y,float Angle,
		float Speed,float Anglerate,int count)						//コンストラクタ
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
class IntervalMultipleSpiralShooter : public EnemyBullet{			//改良型多方向渦巻き弾
public:
	float Shot_Angle,Shot_AngleRate,Shot_Speed;
	int Shot_Count,Interval,Time;

	IntervalMultipleSpiralShooter(float x,float y,float Angle,
		float Speed,float Anglerate,int count,int interval)			//コンストラクタ
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
class BiDirectionalSpiralShooter : public EnemyBullet{				//両回転渦巻弾
public:
	float Shot_Angle[2];											//発射角度
	float Shot_AngleRate[2];										//発射角速度
	float Shot_Speed;												//発射速度
	int Shot_Count;													//発射数
	int Interval;													//発射間隔
	int Time;														//タイマー
	BiDirectionalSpiralShooter(float x,float y,float Angle,float Speed,
		float Anglerate1,float Anglerate2,int count,int interval)	//コンストラクタ
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
class BentSpiralShooter : public EnemyBullet{						//旋回渦巻弾
public:
	float Shot_Angle;												//発射角度
	float Shot_AngleRate;											//発射角速度
	float Shot_Speed;												//発射速度
	int Shot_Count;													//発射速度
	int Interval;													//発射間隔
	int Time;														//タイマー
	float bullet_AngleRate;											//弾の角速度
	float bullet_SpeedRate;											//弾の角速度
	BentSpiralShooter(float x,float y,float Angle,float Anglerate,float speed,int count,
		int interval,float bullet_anglerate,float bullet_speedrate)	//コンストラクタ

	:	EnemyBullet(x,y,0,0,0,0,0),									//正直なところこれx,y以外意味ない
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
class CombinedSpiralShooter : public EnemyBullet{					//両回転渦巻弾+旋回加速渦巻弾
public:
	BiDirectionalSpiralShooter *BiDirectional;						//両回転渦巻弾
	BentSpiralShooter *Bent;										//旋回加速渦巻弾
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
class WasherSpiralShooter : public EnemyBullet{						//洗濯機渦巻弾
public:
	BiDirectionalSpiralShooter *BiDirectional;						//両回転渦巻弾
	BentSpiralShooter *Bent;										//旋回渦巻弾
	float MaxShotAngleRate;											//発射角度の最大値
	float MaxbulletAngleRate;										//弾の角速度の最大値
	int Time;														//タイマー
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
		if(Time<250){												//右巻き
			Bent->Shot_AngleRate=MaxShotAngleRate;
			Bent->bullet_AngleRate=-MaxbulletAngleRate;
		}else
		if(Time<300){												//右巻きから左巻きへ
			Bent->Shot_AngleRate=MaxShotAngleRate*(275-Time)/25;
			Bent->bullet_AngleRate=-MaxbulletAngleRate*(275-Time)/25;
		}else
		if(Time<550){												//左巻き
			Bent->Shot_AngleRate=-MaxShotAngleRate;
			Bent->bullet_AngleRate=MaxbulletAngleRate;
		}else
		{															//左巻きから右巻きへ
			Bent->Shot_AngleRate=-MaxShotAngleRate*(575-Time)/25;
			Bent->bullet_AngleRate=MaxbulletAngleRate*(575-Time)/25;
		}
		Time=(Time+1)%600;
		ShootStop_Method();
	}
};
class HardWasherSpiralShooter : public WasherSpiralShooter{			//高難易度型洗濯機渦巻弾
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
//このプログラムは参考書の内容を自分が作ったように変えただけです。
//詳しくは参考書をご覧ください。