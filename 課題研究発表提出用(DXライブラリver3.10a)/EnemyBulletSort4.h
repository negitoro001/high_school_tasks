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
#define MyShipSize 0.0001827149305391596f							//渦巻き設置弾に使用する

class SimpleHomingBullet : public EnemyBullet{						//単純誘導弾
public:
	SimpleHomingBullet(float x,float y,float angle,float speed)
	:	EnemyBullet(x,y,angle,speed,0,0,1)
	{}
	void Move(void){
		ShotAngle=GetMyShipAngle(x,y);
		EnemyBullet::Move();
	}
};
class SimpleHomingShooter : public EnemyBullet{						//単純誘導弾の撃つ
public:
	float Shot_Speed;												//発射速度
	int Interval;													//発射間隔
	int Time;														//タイマー
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
class ConstrainedHomingBullet : public EnemyBullet{					//制約誘導弾
public:
	float MaxAngleRate;												//最大旋回角速度
	ConstrainedHomingBullet(float x,float y,float angle,
			float speed,int interval,float max_angle_rate)
	:	EnemyBullet(x,y,angle,speed,0,0,1),
		MaxAngleRate(max_angle_rate)
	{}
	void Move(void){
		float angle_rate=GetMyShipAngle(x,y)-ShotAngle;				//旋回角速度を求める
		angle_rate-=floor(angle_rate);								//旋回角速度の範囲を0.0～1.0にする
		if(angle_rate<=MaxAngleRate || 1-angle_rate<=MaxAngleRate){	//一定の旋回速度を超えてなければそれを代入
			ShotAngle+=Anglerate;
		}
		else{
			ShotAngle+=(angle_rate<0.5f)?MaxAngleRate:-MaxAngleRate;//一定の旋回速度を超えてたら設定した最大値にする
		}
		ShotAngle-=floor(ShotAngle);
		EnemyBullet::Move();
	}
};
class ConstrainedHomingShooter : public SimpleHomingShooter{		//旋回誘導弾を撃つ
public:
	float MaxAngleRate;												//最大旋回角速度
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
class BulletTrailer : public Enemy{									//軌跡弾
public:
	float Speed;													//敵の速度
	float Angle;
	float MaxAngleRate;												//最大旋回角速度
	int Interval;													//間隔
	int Time;														//タイマー
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
class GapShooter : public EnemyBullet{								//空白弾
public:
	NWayShooter *NWay;												//n-way弾を撃つ
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
class PatternShooter : public EnemyBullet{							//図柄弾
public:
	float Shot_Angle;												//発射角度
	float ShotAngleRange;											//発射角度範囲
	float Shot_Speed;												//発射速度
	int Interval;													//発射間隔
	char *Pattern;													//図柄
	int Width;														//幅
	int Height;														//高さ
	int Time;														//タイマー
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
class PlacedBullet : public EnemyBullet{							//設置弾
public:
	float InitialSpeed;												//初期速度
	int MoveTime;													//移動時間
	int StopTime;													//停止時間
	int Time;														//タイマー
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
class PlacedBulletShooter : public EnemyBullet{						//設置弾を撃つ
public:
	float InitialSpeed;												//初期速度
	int MoveTime;													//移動時間
	int StopTime;													//停止時間
	int Interval;													//発射間隔
	int Time;														//タイマー
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
class SpiralPlacedShooter : public Enemy{							//渦巻き設置弾
public:
	float OrbitAngle;												//軌道上の敵の角度
	float OrbitAngleRate;											//軌道上の敵の角速度
	float OrbitRadius;												//軌道上の半径
	int Shot_Time;													//発射時間
	int Wait_Time;													//待機時間
	int Interval;													//発射間隔
	int Cycle;														//周期
	int Time;														//タイマー
	float BulletSpeed;												//弾の速度
	int GroupCount;													//グループ数
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
		
		new EnemyBullet(x,y,OrbitAngle,BulletSpeed,0,0,1);			//画面外側への方向弾

		//設置弾
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
class StarPlacedShooter : public EnemyBullet{						//星型設置弾
public:
	float X,Y;														//座標
	float StarAngle;												//星の角度
	float StarSize;													//星のサイズ
	int Shot_Time;													//発射時間
	int Wait_Time;													//待機時間
	int Interval;													//発射間隔
	int Cycle;														//周期
	int Time;														//タイマー
	float BulletSpeed;												//弾の速度
	float BulletAngle;												//弾の角度
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
class PlacedTwiceBullet : public EnemyBullet{						//星型再設置弾
public:
	float PlacedAngle[2];											//角度
	float PlacedSpeed[2];											//速度
	int PlacedTime[3];												//時間
	int Time;														//タイマー
	PlacedTwiceBullet(float x,float y,float angle,float angle0,
		float angle1,float speed0,float speed1,int time0,
			int time1,int time2,int pic)
	:	EnemyBullet(x,y,angle,0,0,0,1),
		Time(0)
	{
		//角度
		PlacedAngle[0]=angle0;
		PlacedAngle[1]=angle1;
		//速度
		PlacedSpeed[0]=speed0;
		PlacedSpeed[1]=speed1;
		//時間
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
class ReStarPlacedShooter : public EnemyBullet{						//再設置星型設置弾
public:
	float X,Y;														//座標
	float StarAngle;												//星の角度
	float StarSize;													//星のサイズ
	int Shot_Time;													//発射時間
	int Wait_Time;													//待機時間
	int Interval;													//発射間隔
	int Cycle;														//周期
	int Time;														//タイマー
	float BulletSpeed;												//弾の速度
	float BulletAngle;												//弾の角度
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
//佐竹自作====================================================
class CrashBulletTrailer : public EnemyBullet{						//自作軌跡弾の弾
public:
	float Shot_Speed;												//発射速度
	int CrashTime;													//爆破時間
	int Shot_Count;													//射出回数計測
	int Pic;														//写真選択
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
class CrashBulletTrailerEnemy : public Enemy{						//自作軌跡弾の撃つ敵
public:
	float Speed;													//敵の速度
	float Angle;
	float MaxAngleRate;												//最大旋回角速度
	int Interval;													//間隔
	int Time;														//タイマー
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
//========================================================（かなりデキが悪い）
class Cluster_Missile : public Enemy{								//クラスター爆弾というか、ヘッジホッグのようなモノ（自作）
public:
	int Time;														//カウンター
	int Crash_Time;													//時限
	float Angle;													//角度
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
//第一、第二、第三引数は変更しないでください。
//=======================================================
//ウォールオブデス!!!(自作)
class SelfDestractEnemy : public Enemy{								//自爆型敵(ウォールオブデスに使用)
public:
	int Time;														//タイマー
	int Crash_Time;													//爆破タイム
	bool Direction;													//方向(下向きを真、上向きを偽とする)
	SelfDestractEnemy(float x,float y,int hp,int enemy_pic,
			int crash_time,bool direction)							//コンストラクタ
	:	Enemy(x,y,speed,hp,0,enemy_pic),
		Crash_Time(crash_time),
		Direction(direction),
		Time(0)
	{}
	void Move(void){
		if(Direction==TRUE) y+=0.0035f;
		else y-=0.0035f;
		if(Crash_Time==Time){
			hp=0;													//即死
		}
		Enemy::Move();
		Time++;
	}
};
class Wall_Of_Death : public Enemy{									//スターター
public:
	int Time;														//タイマー
	int Crash_Time;													//爆破タイム
	int Quantity;													//敵の量
	int CreateQuantity;												//生成量
	float distance;													//間隔
	bool Direction;													//方向(下向きを真、上向きを偽とする)
	int Enemy_Pic;													//写真
	Wall_Of_Death(float speed,int hp,int quantity,int enemy_pic,int crash_time)
	:	Enemy(2,2,speed,hp,0,0),
		Quantity(quantity),
		Crash_Time(crash_time),
		CreateQuantity(0),
		Direction(TRUE),
		Enemy_Pic(enemy_pic),
		Time(0)
	{
		distance=(float)4/Quantity;									//計算式2/(Quantity/2)を簡略化
	}
	void Move(void){
		if(Time%3==0 && CreateQuantity<Quantity-1){					//生成処理(一気に生成すると処理落ちするので回避)
			CreateQuantity++;
			if(Direction==TRUE) {
				new SelfDestractEnemy((float)distance*CreateQuantity-1.1f,
					-1.0f+CreateQuantity*0.0105f,hp,Enemy_Pic,
						Crash_Time-3*CreateQuantity,TRUE);			//上の段のインスタンス生成

				if(((2*CreateQuantity+1)/Quantity)==1)
					Direction=FALSE;								//CreateQuantity/(Quantity/2)の式を簡略化
			}
			else new SelfDestractEnemy(distance*(CreateQuantity%(Quantity/2))-1.1f,
				1.0f-CreateQuantity*0.0105f,hp,Enemy_Pic,
					Crash_Time-3*CreateQuantity,FALSE);				//下の段のインスタンス生成
		}
		else if(Time%3==0 && CreateQuantity==Quantity-1){
			new SelfDestractEnemy(distance*(Quantity/2)-1.1f,1.0f-CreateQuantity*0.0105f,
				hp,Enemy_Pic,Crash_Time-3*CreateQuantity,FALSE);	//最後の機体のインスタンス生成(アルゴリズムの都合上別にしますた)
			Alive=FALSE;											//目的終了後消滅
		}
		Time++;
	}
};
#endif