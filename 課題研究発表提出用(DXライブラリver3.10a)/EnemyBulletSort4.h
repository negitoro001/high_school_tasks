#ifndef ENEMYBULLETSORT_4_H
#define ENEMYBULLETSORT_4_H
#include"Enemy.h"
#include"EnemyBullet.h"
#include"MyShip.h"
#include"DxLib.h"
#include"Mersenne twister.h"
#include"EnemyBulletSort2.h"
#include"EnemyBulletSort3.h"
#include"EnemyCrash.h"
#include<math.h>
#define MyShipSize 0.0001827149305391596f							//�Q�����ݒu�e�Ɏg�p����

class SimpleHomingBullet : public EnemyBullet{						//�P���U���e
public:
	SimpleHomingBullet(float x,float y,float angle,float speed)
	:	EnemyBullet(x,y,angle,speed,0,0,1)
	{}
	void Move(void){
		ShotAngle=GetMyShipAngle(x,y);
		EnemyBullet::Move();
	}
};
class SimpleHomingShooter : public EnemyBullet{						//�P���U���e�̌���
public:
	float Shot_Speed;												//���ˑ��x
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	SimpleHomingShooter(float x,float y,float speed,int interval)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Speed(speed),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			new SimpleHomingBullet(x,y,GetMyShipAngle(x,y),Shot_Speed);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class ConstrainedHomingBullet : public EnemyBullet{					//����U���e
public:
	float MaxAngleRate;												//�ő����p���x
	ConstrainedHomingBullet(float x,float y,float angle,
			float speed,int interval,float max_angle_rate)
	:	EnemyBullet(x,y,angle,speed,0,0,1),
		MaxAngleRate(max_angle_rate)
	{}
	void Move(void){
		float angle_rate=GetMyShipAngle(x,y)-ShotAngle;				//����p���x�����߂�
		angle_rate-=floor(angle_rate);								//����p���x�͈̔͂�0.0�`1.0�ɂ���
		if(angle_rate<=MaxAngleRate || 1-angle_rate<=MaxAngleRate){	//���̐��񑬓x�𒴂��ĂȂ���΂������
			ShotAngle+=Anglerate;
		}
		else{
			ShotAngle+=(angle_rate<0.5f)?MaxAngleRate:-MaxAngleRate;//���̐��񑬓x�𒴂��Ă���ݒ肵���ő�l�ɂ���
		}
		ShotAngle-=floor(ShotAngle);
		EnemyBullet::Move();
	}
};
class ConstrainedHomingShooter : public SimpleHomingShooter{		//����U���e������
public:
	float MaxAngleRate;												//�ő����p���x
	ConstrainedHomingShooter(float x,float y,float speed,
		int interval,float max_angle_rate)
	:	SimpleHomingShooter(x,y,speed,interval),
		MaxAngleRate(max_angle_rate)
	{}
	void Move(void){
		if(Time==0){
			new ConstrainedHomingBullet(x,y,GetMyShipAngle(x,y),
				Shot_Speed,Interval,MaxAngleRate);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class BulletTrailer : public Enemy{									//�O�Ւe
public:
	float Speed;													//�G�̑��x
	float Angle;
	float MaxAngleRate;												//�ő����p���x
	int Interval;													//�Ԋu
	int Time;														//�^�C�}�[
	BulletTrailer(Enemy *enemy,float x,float y,float speed,int hp,
			float max_angle_rate,int interval,int color)
	:	Enemy(x,y,speed,hp,0,color),
		Speed(speed),
		MaxAngleRate(max_angle_rate),
		Interval(interval),
		Angle(GetMyShipAngle(x,y)),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			Object *object=new EnemyBullet(x,y,Angle,0,0,0,1);
		}
		Time=(Time+1)%Interval;
		float angle_rate=GetMyShipAngle(x,y)-Angle;
		angle_rate-=floor(angle_rate);
		if(angle_rate<=MaxAngleRate || 1-angle_rate<=MaxAngleRate){
			Angle+=angle_rate;
		}
		else{
			Angle+=(angle_rate<0.5f)?MaxAngleRate:-MaxAngleRate;
		}
		Angle-=floor(Angle);
		float rad=Angle*DX_PI_F*2;
		x+=Speed*cosf(rad);
		y+=Speed*sinf(rad);
		Enemy::Move();
	}
};
class GapShooter : public EnemyBullet{								//�󔒒e
public:
	NWayShooter *NWay;												//n-way�e������
	GapShooter(float x,float y,float angle_range,
			float speed,int count,int interval)
	:	EnemyBullet(x,y,0,speed,0,0,0)
	{
		NWay=new NWayShooter(x,y,0,angle_range,speed,count,interval,0,0);
	}
	void Move(void){
		init_genrand((unsigned long)timeGetTime());
		NWay->Shot_Angle=genrand_real2();
	}
};
class PatternShooter : public EnemyBullet{							//�}���e
public:
	float Shot_Angle;												//���ˊp�x
	float ShotAngleRange;											//���ˊp�x�͈�
	float Shot_Speed;												//���ˑ��x
	int Interval;													//���ˊԊu
	char *Pattern;													//�}��
	int Width;														//��
	int Height;														//����
	int Time;														//�^�C�}�[
	PatternShooter(float x,float y,float angle,float angle_range,
			float speed,float interval,char *pattern,int width,int height)
	:	EnemyBullet(x,y,0,0,0,0,0),
		Shot_Angle(angle),
		ShotAngleRange(angle_range),
		Shot_Speed(speed),
		Interval(interval),
		Pattern(pattern),
		Width(width),
		Height(height),
		Time(0)
	{}
	void Move(void){
		if(Time%Interval==0){
			char *p=Pattern+(Height-1-Time/Interval)*Width;
			for(int i=Width-1;i>=0;i--,p++){
				if(*p=' '){
					new EnemyBullet(x,y,Shot_Angle+ShotAngleRange*
						((float)i/(Width-1)-0.5f),Shot_Speed,0,0,1);
				}
			}
		}
		Time=(Time+1)%(Interval*Height);
		ShootStop_Method();
	}
};
class PlacedBullet : public EnemyBullet{							//�ݒu�e
public:
	float InitialSpeed;												//�������x
	int MoveTime;													//�ړ�����
	int StopTime;													//��~����
	int Time;														//�^�C�}�[
	PlacedBullet(float x,float y,float angle,float speed,
			int move_time,int stop_time)
	:	EnemyBullet(x,y,angle,speed,0,0,1),
		InitialSpeed(speed),
		MoveTime(move_time),
		StopTime(stop_time),
		Time(0)
	{}
	void Move(void){
		if(Time==MoveTime){
			speed=0;
		}
		if(Time==MoveTime+StopTime){
			speed=InitialSpeed;
		}
		Time++;
		EnemyBullet::Move();
	}
};
class PlacedBulletShooter : public EnemyBullet{						//�ݒu�e������
public:
	float InitialSpeed;												//�������x
	int MoveTime;													//�ړ�����
	int StopTime;													//��~����
	int Interval;													//���ˊԊu
	int Time;														//�^�C�}�[
	PlacedBulletShooter(float x,float y,float speed,
			int move_time,int stop_time,int interval)
	:	EnemyBullet(x,y,0,0,0,0,0),
		InitialSpeed(speed),
		MoveTime(move_time),
		StopTime(stop_time),
		Interval(interval),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			new PlacedBullet(x,y,GetMyShipAngle(x,y),
				InitialSpeed,MoveTime,StopTime);
		}
		Time=(Time+1)%Interval;
		ShootStop_Method();
	}
};
class SpiralPlacedShooter : public Enemy{							//�Q�����ݒu�e
public:
	float OrbitAngle;												//�O����̓G�̊p�x
	float OrbitAngleRate;											//�O����̓G�̊p���x
	float OrbitRadius;												//�O����̔��a
	int Shot_Time;													//���ˎ���
	int Wait_Time;													//�ҋ@����
	int Interval;													//���ˊԊu
	int Cycle;														//����
	int Time;														//�^�C�}�[
	float BulletSpeed;												//�e�̑��x
	int GroupCount;													//�O���[�v��
	SpiralPlacedShooter(float orbit_angle,float orbit_angle_rate,
			float orbit_radius,int shot_time,int wait_time,
		int interval,int cycle,float bullet_speed,int group_count)
	:	Enemy(0,0,speed,hp,0,1),
		OrbitAngle(orbit_angle),
		OrbitAngleRate(orbit_angle_rate),
		OrbitRadius(orbit_radius),
		Shot_Time(shot_time),
		Wait_Time(wait_time),
		Interval(interval),
		Cycle(cycle),
		BulletSpeed(bullet_speed),
		GroupCount(group_count),
		Time(0)
	{
		float rad=OrbitAngle*DX_PI_F*2;
		x=cosf(rad)*OrbitRadius;
		y=sinf(rad)*OrbitRadius;
	}
	void Move(void){
		float rad=OrbitAngle*DX_PI_F*2;
		x=cosf(rad)*OrbitRadius;
		y=sinf(rad)*OrbitRadius;
		OrbitAngle+=OrbitAngleRate;
		OrbitAngle-=floor(OrbitAngle);
		
		new EnemyBullet(x,y,OrbitAngle,BulletSpeed,0,0,1);			//��ʊO���ւ̕����e

		//�ݒu�e
		int count=Time/(Shot_Time+Wait_Time);
		int time=Time%(Shot_Time+Wait_Time);
		float base_time=(OrbitRadius-MyShipSize)/BulletSpeed;
		if(count<GroupCount){
			if(time<Shot_Time && time%Interval==0){
				new PlacedBullet(x,y,OrbitAngle+0.5f,BulletSpeed,
					(int)(base_time*count/GroupCount),(int)
						(base_time+(Shot_Time+Wait_Time)*(GroupCount-count)));
			}
		}
		Time=(Time+1)%Cycle;
		Enemy::Move();
	}
};
class StarPlacedShooter : public EnemyBullet{						//���^�ݒu�e
public:
	float X,Y;														//���W
	float StarAngle;												//���̊p�x
	float StarSize;													//���̃T�C�Y
	int Shot_Time;													//���ˎ���
	int Wait_Time;													//�ҋ@����
	int Interval;													//���ˊԊu
	int Cycle;														//����
	int Time;														//�^�C�}�[
	float BulletSpeed;												//�e�̑��x
	float BulletAngle;												//�e�̊p�x
	StarPlacedShooter(float x,float y,float star_angle,float star_size,
			int shot_time,int wait_time,int interval,int cycle,
				float bullet_speed,float bullet_angle)
	:	EnemyBullet(x,y,0,0,0,0,0),
		StarAngle(star_angle),
		StarSize(star_size),
		Shot_Time(shot_time),
		Wait_Time(wait_time),
		Interval(interval),
		Cycle(cycle),
		Time(0),
		BulletSpeed(bullet_speed),
		BulletAngle(bullet_angle)
	{
		X=x;
		Y=y;
	}
	void Move(void){
		static const float 
			x[]={0, 0.59f, -0.95f, 0.95f, -0.59f, 0},
			y[]={-1, 0.81f, -0.31f, -0.31f, 0.81f, -1};
		int line_time=Shot_Time/5;
		if (Time<Shot_Time && Time%Interval==0) {
			int line=Time/line_time;
			int time=Time%line_time;
			float
				ax=(x[line]+(x[line+1]-x[line])*time/line_time),
				ay=(y[line]+(y[line+1]-y[line])*time/line_time);
			float
				rad=StarAngle*DX_PI_F*2, 
				c=cosf(rad), s=sinf(rad), 
				bx=X+(ax*c-ay*s)*StarSize,
				by=Y+(ax*s+ay*c)*StarSize,
				tan_angle=atan2f(by-Y,bx-X)/DX_PI_F/2;
				new PlacedBullet(bx,by,tan_angle+BulletAngle,BulletSpeed,0,Shot_Time+Wait_Time-Time);
		}
		Time=(Time+1)%Cycle;
		ShootStop_Method();
	}
};
class PlacedTwiceBullet : public EnemyBullet{						//���^�Đݒu�e
public:
	float PlacedAngle[2];											//�p�x
	float PlacedSpeed[2];											//���x
	int PlacedTime[3];												//����
	int Time;														//�^�C�}�[
	PlacedTwiceBullet(float x,float y,float angle,float angle0,
		float angle1,float speed0,float speed1,int time0,
			int time1,int time2,int pic)
	:	EnemyBullet(x,y,angle,0,0,0,1),
		Time(0)
	{
		//�p�x
		PlacedAngle[0]=angle0;
		PlacedAngle[1]=angle1;
		//���x
		PlacedSpeed[0]=speed0;
		PlacedSpeed[1]=speed1;
		//����
		PlacedTime[0]=time0;
		PlacedTime[1]=time1;
		PlacedTime[2]=time2;
	}
	void Move(void){
		if(Time==PlacedTime[0]){
			ShotAngle=PlacedAngle[0];
			speed=PlacedSpeed[0];
		}
		if(Time==PlacedTime[0]+PlacedTime[1]){
			speed=0;
		}
		if(Time==PlacedTime[0]+PlacedTime[1]+PlacedTime[2]){
			ShotAngle=PlacedAngle[1];
			speed=PlacedSpeed[1];
		}
		Time++;
		EnemyBullet::Move();
	}
};
class ReStarPlacedShooter : public EnemyBullet{						//�Đݒu���^�ݒu�e
public:
	float X,Y;														//���W
	float StarAngle;												//���̊p�x
	float StarSize;													//���̃T�C�Y
	int Shot_Time;													//���ˎ���
	int Wait_Time;													//�ҋ@����
	int Interval;													//���ˊԊu
	int Cycle;														//����
	int Time;														//�^�C�}�[
	float BulletSpeed;												//�e�̑��x
	float BulletAngle;												//�e�̊p�x
	ReStarPlacedShooter(float x,float y,float star_angle,float star_size,
			int shot_time,int wait_time,int interval,int cycle,
				float bullet_speed,float bullet_angle)
	:	EnemyBullet(x,y,0,0,0,0,0),
		StarAngle(star_angle),
		StarSize(star_size),
		Shot_Time(shot_time),
		Wait_Time(wait_time),
		Interval(interval),
		Cycle(cycle),
		Time(0),
		BulletSpeed(bullet_speed),
		BulletAngle(bullet_angle)
	{
		X=x;
		Y=y;
	}
	void Move(void){
		static const float 
			x[]={0, 0.59f, -0.95f, 0.95f, -0.59f, 0},
			y[]={-1, 0.81f, -0.31f, -0.31f, 0.81f, -1};
		int line_time=Shot_Time/5;
		if (Time<Shot_Time && Time%Interval==0) {
			int line=Time/line_time;
			int time=Time%line_time;
			float
				ax=(x[line]+(x[line+1]-x[line])*time/line_time),
				ay=(y[line]+(y[line+1]-y[line])*time/line_time);
			float
				rad=StarAngle*DX_PI_F*2, 
				c=cosf(rad), s=sinf(rad), 
				bx=X+(ax*c-ay*s)*StarSize,
				by=Y+(ax*s+ay*c)*StarSize,
				tan_angle=atan2f(by-Y,bx-X)/DX_PI_F/2;
			for(int i=0;i<5;i++){
				new PlacedTwiceBullet(bx,by,0,StarAngle+(float)i/5,
					tan_angle+BulletAngle,BulletSpeed,BulletSpeed,Shot_Time+
						Wait_Time-Time,StarSize*1.5f/BulletSpeed,Wait_Time,1);
			}
		}
		Time=(Time+1)%Cycle;
		ShootStop_Method();
	}
};
//���|����====================================================
class CrashBulletTrailer : public EnemyBullet{						//����O�Ւe�̒e
public:
	float Shot_Speed;												//���ˑ��x
	int CrashTime;													//���j����
	int Shot_Count;													//�ˏo�񐔌v��
	int Pic;														//�ʐ^�I��
	int Time;
	CrashBulletTrailer(float x,float y,float shot_speed,int crash_time,int pic)
	:	EnemyBullet(x,y,0,0,0,0,pic),
		Shot_Speed(shot_speed),
		CrashTime(crash_time),
		Shot_Count(0),
		Pic(pic),
		Time(0)
	{}
	void Move(void){
		if(Time>=CrashTime){
			if(Time==Shot_Count*3+CrashTime && Shot_Count<=5){
				new EnemyBullet(x,y,GetMyShipAngle(x,y),Shot_Speed,0,0,Pic);
				Shot_Count++;
			}
			if(Shot_Count==6)Alive=FALSE;
		}
		Time++;
	}
};
class CrashBulletTrailerEnemy : public Enemy{						//����O�Ւe�̌��G
public:
	float Speed;													//�G�̑��x
	float Angle;
	float MaxAngleRate;												//�ő����p���x
	int Interval;													//�Ԋu
	int Time;														//�^�C�}�[
	CrashBulletTrailerEnemy(Enemy *enemy,float x,float y,float speed,
			int hp,float max_angle_rate,int interval,int color)
	:	Enemy(x,y,speed,hp,0,color),
		Speed(speed),
		MaxAngleRate(max_angle_rate),
		Interval(interval),
		Angle(GetMyShipAngle(x,y)),
		Time(0)
	{}
	void Move(void){
		if(Time==0){
			Object *object=new CrashBulletTrailer(x,y,0.02f,100,1);
		}
		Time=(Time+1)%Interval;
		float angle_rate=GetMyShipAngle(x,y)-Angle;
		angle_rate-=floor(angle_rate);
		if(angle_rate<=MaxAngleRate || 1-angle_rate<=MaxAngleRate){
			Angle+=angle_rate;
		}
		else{
			Angle+=(angle_rate<0.5f)?MaxAngleRate:-MaxAngleRate;
		}
		Angle-=floor(Angle);
		float rad=Angle*DX_PI_F*2;
		x+=Speed*cosf(rad);
		y+=Speed*sinf(rad);

		Enemy::Move();
	}
};
//========================================================�i���Ȃ�f�L�������j
class Cluster_Missile : public Enemy{								//�N���X�^�[���e�Ƃ������A�w�b�W�z�b�O�̂悤�ȃ��m�i����j
public:
	int Time;														//�J�E���^�[
	int Crash_Time;													//����
	float Angle;													//�p�x
	int Picture[14];
	int count;
	int Bullet_Count;
	Cluster_Missile(float x,float y,float angle,float speed,int crash_time,int bullet_count)
	:	Enemy(x,y,speed,5,0,0),
		Angle(angle),
		Crash_Time(crash_time),
		Bullet_Count(bullet_count),
		Time(0)
	{
		LoadDivGraph("crash_pic/cluster_missile.bmp",14,7,2,16,30,Picture);
	}
	void Move(void){
		float rad=Angle*DX_PI_F*2;
		x+=speed*cosf(rad);
		y+=speed*sinf(rad);
		Time++;
		count=Time%14;
		if(Crash_Time==Time){
			new RandamSpreadingShooter(x,y,0.2f,0.02f,0.02f,Bullet_Count,240);
			Alive=FALSE;
			new EnemyCrash(x,y,Picture[0]);
		}
	}
	void Draw(void){
	int	object_x,object_y;
	object_x=(x+1)*Disp_Height/2;
	object_y=(y+1)*Disp_Width/2;
	DrawRotaGraph(object_x,object_y,1,DX_PI_F+(Angle-0.25f)*DX_PI_F,Picture[count],TRUE);
	}
};
//���A���A��O�����͕ύX���Ȃ��ł��������B
//=======================================================
//�E�H�[���I�u�f�X!!!(����)
class SelfDestractEnemy : public Enemy{								//�����^�G(�E�H�[���I�u�f�X�Ɏg�p)
public:
	int Time;														//�^�C�}�[
	int Crash_Time;													//���j�^�C��
	bool Direction;													//����(��������^�A��������U�Ƃ���)
	SelfDestractEnemy(float x,float y,int hp,int enemy_pic,
			int crash_time,bool direction)							//�R���X�g���N�^
	:	Enemy(x,y,speed,hp,0,enemy_pic),
		Crash_Time(crash_time),
		Direction(direction),
		Time(0)
	{}
	void Move(void){
		if(Direction==TRUE) y+=0.0035f;
		else y-=0.0035f;
		if(Crash_Time==Time){
			hp=0;													//����
		}
		Enemy::Move();
		Time++;
	}
};
class Wall_Of_Death : public Enemy{									//�X�^�[�^�[
public:
	int Time;														//�^�C�}�[
	int Crash_Time;													//���j�^�C��
	int Quantity;													//�G�̗�
	int CreateQuantity;												//������
	float distance;													//�Ԋu
	bool Direction;													//����(��������^�A��������U�Ƃ���)
	int Enemy_Pic;													//�ʐ^
	Wall_Of_Death(float speed,int hp,int quantity,int enemy_pic,int crash_time)
	:	Enemy(2,2,speed,hp,0,0),
		Quantity(quantity),
		Crash_Time(crash_time),
		CreateQuantity(0),
		Direction(TRUE),
		Enemy_Pic(enemy_pic),
		Time(0)
	{
		distance=(float)4/Quantity;									//�v�Z��2/(Quantity/2)���ȗ���
	}
	void Move(void){
		if(Time%3==0 && CreateQuantity<Quantity-1){					//��������(��C�ɐ�������Ə�����������̂ŉ��)
			CreateQuantity++;
			if(Direction==TRUE) {
				new SelfDestractEnemy((float)distance*CreateQuantity-1.1f,
					-1.0f+CreateQuantity*0.0105f,hp,Enemy_Pic,
						Crash_Time-3*CreateQuantity,TRUE);			//��̒i�̃C���X�^���X����

				if(((2*CreateQuantity+1)/Quantity)==1)
					Direction=FALSE;								//CreateQuantity/(Quantity/2)�̎����ȗ���
			}
			else new SelfDestractEnemy(distance*(CreateQuantity%(Quantity/2))-1.1f,
				1.0f-CreateQuantity*0.0105f,hp,Enemy_Pic,
					Crash_Time-3*CreateQuantity,FALSE);				//���̒i�̃C���X�^���X����
		}
		else if(Time%3==0 && CreateQuantity==Quantity-1){
			new SelfDestractEnemy(distance*(Quantity/2)-1.1f,1.0f-CreateQuantity*0.0105f,
				hp,Enemy_Pic,Crash_Time-3*CreateQuantity,FALSE);	//�Ō�̋@�̂̃C���X�^���X����(�A���S���Y���̓s����ʂɂ��܂���)
			Alive=FALSE;											//�ړI�I�������
		}
		Time++;
	}
};
#endif