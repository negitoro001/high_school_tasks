#ifndef ENEMYBULLETSORT_2_H
#define ENEMYBULLETSORT_2_H
#include"EnemyBullet.h"
#include"Mersenne twister.h"
#include<math.h>
#include<windows.h>
#pragma comment(lib, "winmm.lib")

class NWayShooter :public EnemyBullet{								//NWay�e�̂ӂ��̏���
public:
	float Shot_Angle;												//���ˊp�x
	float Shot_Angle_Range;											//���ˊp�x�͈�
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	float Bullet_AngleRate;											//�e�̊p���x
	float Bullet_SpeedRate;											//�e�̉����x
	NWayShooter(float x,float y,float angle,float angle_range,float speed,
		int count,int interval,float bullet_angle_rate,float bullet_speed_rate)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(angle),
		Shot_Angle_Range(angle_range),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		Bullet_AngleRate(bullet_angle_rate),
		Bullet_SpeedRate(bullet_speed_rate),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			ShootNWay(x,y,Shot_Angle,Shot_Angle_Range,Shot_Speed,
				Shot_Count,Bullet_AngleRate,Bullet_SpeedRate);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class CircleShooter : public NWayShooter{
public:
	CircleShooter(float x,float y,float angle,float speed,int count,
		int interval,float bullet_angle_rate,float bullet_speed_rate)

	:	NWayShooter(x,y,angle,1.0f-1.0f/count,speed,count,
	interval,bullet_angle_rate,bullet_speed_rate)
	{}
};
class AimingNWayShooter : public EnemyBullet{						//�_��NWay�e
public:
	float Shot_AngleRange;											//���ˊp�x�͈�
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	AimingNWayShooter(float x,float y,float angle_range,
		float speed,int count,int interval)

	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_AngleRange(angle_range),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			ShootNWay(x,y,GetMyShipAngle(x,y),Shot_AngleRange,
				Shot_Speed,Shot_Count,0,0);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class IntermittentAimingNWayShooter : public EnemyBullet{			//�Ԍ��_��n-way�e
public:
	float Shot_AngleRange;											//���ˊp�x�͈�
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int Interval;													//���ˊԊu
	int Shot_Time;													//���ˎ���
	int Wait_Time;													//�x�~����
	int Time;														//�^�C�}�[
	IntermittentAimingNWayShooter(float x,float y,float angle_range,float speed,
		int count,int interval,int shot_time,int wait_time)

	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_AngleRange(angle_range),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		Shot_Time(shot_time),
		Wait_Time(wait_time),
		Time(0)
	{}
	void Move(void){
		if((Time<Shot_Time)&&(Time%Interval==0)){
			ShootNWay(x,y,GetMyShipAngle(x,y),Shot_AngleRange,Shot_Speed,Shot_Count,0,0);
		}
		Time=(Time+1)%(Shot_Time+Wait_Time);
		ShootStop_Method();
	}
};
class RandamNWayShooter : public EnemyBullet{						//�����_��n-way�e
public:
	float Shot_Angle;												//���ˊp�x
	float Shot_AngleRange;											//���ˊp�x�͈�
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	RandamNWayShooter(float x,float y,float angle,float angle_range,
		float speed,int count,int interval)

	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(angle),
		Shot_AngleRange(angle_range),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			for(int i=0;i<Shot_Count;i++){
				init_genrand((unsigned long)timeGetTime());
				new EnemyBullet(x,y,Shot_Angle+Shot_AngleRange*
					(genrand_real1()-0.5f),Shot_Speed,0,0,1);
			}
			Time=(Time+1)%Interval;
			ShootStop_Method();
		}
	}
};
class RandamCircleShooter : public EnemyBullet{						//�����_���~�`�e
public:
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int Interval;													//�Ԋu
	int Time;														//�^�C�}�[
	RandamCircleShooter(float x,float y,float Speed,int count,int interval)
	:	Shot_Speed(Speed),
		Shot_Count(count),
		Interval(interval),
		Time(0),
		EnemyBullet(x,y,0,0,0,0,0)
	{}
	void Move(void){
		if(Time==0){
			for(int i=0;i<Shot_Count;i++){
				init_genrand((unsigned long)timeGetTime());
				new EnemyBullet(x,y,genrand_real2(),Shot_Speed,0,0,1);
			}
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class RollingNWayShooter : public EnemyBullet{						//��]n-way�e
public:
	float Shot_Angle;												//���ˊp�x
	float Shot_AngleRange;											//���ˊp�x�͈�
	float Shot_AngleRate;											//���ˊp���x
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int NWayCount;													//�O���[�v��
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	RollingNWayShooter(float x,float y,float angle,float angle_range,
		float angle_rate,float speed,int count,int nway_count,int interval)

	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(angle),
		Shot_AngleRange(angle_range),
		Shot_AngleRate(angle_rate),
		Shot_Speed(speed),
		Shot_Count(count),
		NWayCount(nway_count),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			for(int i=0;i<NWayCount;i++){
				ShootNWay(x,y,Shot_Angle+(float)i/NWayCount,Shot_AngleRange,
					Shot_Speed,Shot_Count,0,0);
			}
			Shot_Angle+=Shot_AngleRate;
			Shot_Angle-=floor(Shot_Angle);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class WavingNWayShooter : public EnemyBullet{						//�g��n-way�e
public:
	float Shot_Angle;												//���ˊp�x
	float Shot_AngleRange;											//���ˊp�x�͈�
	float WavingAngleRange;											//�U��
	float Shot_Speed;												//���ˑ��x
	int Shot_Count;													//���ː�
	int Interval;													//���ˊԊu
	int Cycle;														//����
	int Time;														//�^�C�}�[
	WavingNWayShooter(float x,float y,float angle,float angle_range,
		float waving_angle_range,float speed,int count,int interval,int cycle)

	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(angle),
		Shot_AngleRange(angle_range),
		WavingAngleRange(waving_angle_range),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		Cycle(cycle),
		Time(0)
	{}
	void Move(void){
		if(Time%Interval==0){
			ShootNWay(x,y,Shot_Angle+WavingAngleRange*sinf(DX_PI_F*2*Time/Cycle),
				Shot_AngleRange,Shot_Speed,Shot_Count,0,0);
		}
		Time=(Time+1)%Cycle;
		ShootStop_Method();
	}
};
class WavingCircleShooter : public WavingNWayShooter{				//�g��~�`�e
public:
	WavingCircleShooter(float x,float y,float angle,float waving_angle_range,
		float speed,int count,int interval,int cycle)

	:	WavingNWayShooter(x,y,angle,1.0f-1.0f/count,waving_angle_range,
			speed,count,interval,cycle)
	{}
};
#endif