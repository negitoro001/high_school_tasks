#ifndef ENEMYBULLETSORT_3_H
#define ENEMYBULLETSORT_3_H
#include"EnemyBullet.h"
#include"Mersenne twister.h"

class AimingShooter : public EnemyBullet{								//�_���e
public:
	float Shot_Speed;													//���ˑ��x
	int Interval;														//���ˊԊu
	int Time;															//�^�C�}�[
	AimingShooter(float x,float y,float speed,int interval)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Speed(speed),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			new EnemyBullet(x,y,GetMyShipAngle(x,y),Shot_Speed,0,0,1);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class LineShooter : public EnemyBullet{									//�����e
public:
	float Shot_Angle;													//���ˊp�x
	float Shot_Speed;													//���ˑ��x
	int Interval;														//���ˊԊu
	int Shot_Time;														//���ˎ���
	int WaitTime;														//�x�~����
	int Time;															//�^�C�}�[
	LineShooter(float x,float y,float angle,float speed,
			int interval,int shot_time,int wait_time)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(angle),
		Shot_Speed(speed),
		Interval(interval),
		Shot_Time(shot_time),
		WaitTime(wait_time),
		Time(0)
	{}
	void Move(void){
		if(Time<Shot_Time && Time%Interval==0){
			new EnemyBullet(x,y,Shot_Angle,Shot_Speed,0,0,1);
		}
		Time=(Time+1)%(Shot_Time+WaitTime);
		ShootStop_Method();
	}
};
class AimingLineShooter : public EnemyBullet{							//�_�������e
public:
	float Shot_Angle;													//���ˊp�x
	float Shot_Speed;													//���ˑ��x
	int Interval;														//���ˊԊu
	int Shot_Time;														//���ˎ���
	int WaitTime;														//�x�~����
	int Time;															//�^�C�}�[
	AimingLineShooter(float x,float y,float speed,
			int interval,int shot_time,int wait_time)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Speed(speed),
		Interval(interval),
		Shot_Time(shot_time),
		WaitTime(wait_time),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			Shot_Angle=GetMyShipAngle(x,y);
		}
		if(Time<Shot_Time && Time%Interval==0){
			new EnemyBullet(x,y,Shot_Angle,Shot_Speed,0,0,1);
		}
		Time=(Time+1)%(Shot_Time+WaitTime);
		ShootStop_Method();
	}
};
class SpreadingShooter : public EnemyBullet{							//�g�U�e
public:
	float Shot_AngleRange;												//���ˊp�x�͈�
	float Shot_Speed;													//���ˊp�x
	int Shot_Count;														//���ː�
	int Interval;														//���ˊԊu
	float GroupSpeed;													//�O���[�v���x
	int GroupCount;														//�O���[�v��
	int Time;															//�^�C�}�[
	SpreadingShooter(float x,float y,float angle_range,
			float speed,int count,int interval,float group_speed,
				int group_count)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_AngleRange(angle_range),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		GroupSpeed(group_speed),
		GroupCount(group_count),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			for(int i=0;i<GroupCount;i++){
				ShootNWay(x,y,GetMyShipAngle(x,y),Shot_AngleRange,
					Shot_Speed+GroupSpeed*i,Shot_Count,0,0);
			}
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class RandamSpreadingShooter : public EnemyBullet{						//�����_���g�U�e
public:
	float Shot_AngleRange;												//���ˊp�x�͈�
	float Shot_Speed;													//���ˑ��x
	float Shot_SpeedRange;												//���ˑ��x�͈�
	int Shot_Count;														//���ː�
	int Interval;														//���ˊԊu
	int Time;															//�^�C�}�[
	RandamSpreadingShooter(float x,float y,float angle_range,
			float speed,float speed_range,int count,int interval)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_AngleRange(angle_range),
		Shot_Speed(speed),
		Shot_SpeedRange(speed_range),
		Shot_Count(count),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			for(int i=0;i<Shot_Count;i++){
				init_genrand((unsigned long)timeGetTime());
					new EnemyBullet(x,y,GetMyShipAngle(x,y)+
						Shot_AngleRange*(genrand_real1()-0.5f),
							Shot_Speed+Shot_SpeedRange*genrand_real1(),0,0,1);
			}
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class OvertakingShooter : public EnemyBullet{							//�ǂ��z���e
public:
	float Shot_AngleRange;												//���ˊp�x�͈�
	float Shot_Speed;													//���ˑ��x
	int Shot_Count;														//���ː�
	int Interval;														//���ˊԊu
	float GroupSpeed;													//�O���[�v���x
	float GroupAngle;													//�O���[�v�p�x
	int GroupCount;														//�O���[�v��
	int GroupInterval;													//�O���[�v�Ԋu
	float Shot_Angle;													//���ˊp�x
	int Time;															//�^�C�}�[
	OvertakingShooter(float x,float y,float angle_range,float speed,
		int count,int interval,float group_speed,float group_angle,
			int group_count,int group_interval)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_AngleRange(angle_range),
		Shot_Speed(speed),
		Shot_Count(count),
		Interval(interval),
		GroupSpeed(group_speed),
		GroupAngle(group_angle),
		GroupCount(group_count),
		GroupInterval(group_interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			Shot_Angle=GetMyShipAngle(x,y);
		}
		int i=Time/GroupInterval;
		if(i<GroupCount && Time%GroupInterval==0){
			ShootNWay(x,y,Shot_Angle+GroupAngle*i,Shot_AngleRange,
				Shot_Speed+GroupSpeed*i,Shot_Count,0,0);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}

};
#endif