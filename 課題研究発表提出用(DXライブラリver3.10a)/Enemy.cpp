#include"DxLib.h"
#include"Enemy.h"
#include"Object.h"
#include"EnemyCrash.h"
#include"Fokker_D_VII_BOSS.h"
#include"EnemyBulletSort1.h"
#include"EnemyBulletSort2.h"
#include"EnemyBulletSort3.h"
#include"EnemyBulletSort4.h"

Enemy::Enemy(float x,float y,float speed,
				int hp,int type,int pic_type)						//�R���X�g���N�^
:	Object(EnemyList)
{
	cnt=0;
	this->x=x;
	this->y=y;
	Alive=TRUE;
	this->speed=speed;
	this->hp=hp;
	this->type=type;
	ShootFlag=FALSE;
//Stage1-1
	switch(type){
	case 10:														//���i
		Angle=0.25f;												//�G�̊p�x�̐ݒ�
		Angle_a=0;
		IntervalFlag=FALSE;
		FireInterval=150;
		break;
	case 11:														//�E��(��)
		Angle=0.27f;
		Angle_a=0;
		FireInterval=120;
		IntervalFlag=FALSE;
		break;
	case 12:														//����(��)
		Angle=-0.77f;
		Angle_a=0;
		FireInterval=120;
		IntervalFlag=FALSE;
		break;
	case 13:														//�E��(��)
		Angle=0.33f;
		Angle_a=0;
		IntervalFlag=FALSE;
		FireInterval=150;
		break;
	case 14:														//����(��)
		Angle=-0.83f;
		Angle_a=0;
		IntervalFlag=FALSE;
		FireInterval=150;
		break;
	case 15:														//�E��(��)
		Angle=0.35f;
		Angle_a=0;
		break;
	case 16:														//����(��)
		Angle=-0.9f;
		Angle_a=0;
		break;
//Stage1-2
	case 30:
        Angle=0.6f;													//����
        Angle_a=0.00001f;
        break;
	case 31:
        Angle=-0.1f;												//�E��
        Angle_a=0.00001f;
        break;
	case 37:														//case30�̒e����
        Angle=0.6f;													//����
        Angle_a=0.00001f;
        IntervalFlag=FALSE;
		FireInterval=100;
		break;
	case 38:														//case31�̒e����
        Angle=-0.1f;												//�E��
        Angle_a=0.00001f;
		IntervalFlag=FALSE;
		FireInterval=100;
        break;

	case 32:
		Angle=0.25f;												//��
		Angle_a=0;
		IntervalFlag=FALSE;
		FireInterval=180;
		break;
	case 41:
		Angle=0.25f;
		Angle_a=0;
		break;

	case 33:
		Angle=-0.85f;												//�E��
		Angle_a=0.00001f;
		break;
	case 34:
		Angle=0.35f;												//����
		Angle_a=0.00001f;
		break;
	case 35:														//case33�̒e����
		Angle=-0.85f;												//�E��
		Angle_a=0.00001f;
		IntervalFlag=FALSE;
		FireInterval=240;
		break;
	case 36:														//case34�̒e����
		Angle=0.35f;												//����
		Angle_a=0.00001f;
		IntervalFlag=FALSE;
		FireInterval=240;
		break;

	case 39:
		Angle=0.23f;
		Angle_a=0.25f;
		IntervalFlag=FALSE;
		FireInterval=210;
		break;
	case 40:
		Angle=0.27f;
		Angle_a=0.25f;
		IntervalFlag=FALSE;
		FireInterval=210;
		break;

//
	case 60:
		Angle=0.25f;
		Angle_a=0;
		IntervalFlag=FALSE;
		FireInterval=150;
		break;
	case 61:
		Angle=0.25f;
		Angle_a=0;
		IntervalFlag=FALSE;
		FireInterval=150;
		break;
	case 62:
		Angle=0.25f;												//�G�̊p�x�̐ݒ�
		Angle_a=0;
		IntervalFlag=FALSE;
		FireInterval=30;
		break;
	}
	switch(pic_type){
	case 1:															//�G��1
		AnimeLoopNum=18;
		LoadDivGraph("Enemy_Picutures/enemy_1.bmp",18,9,2,80,80,Anime);
//		Pic=LoadGraph("FD..BF.png");
		break;
	}
}
void Enemy::Move(void){
	cnt++;															//�����J�E���^�[����
	if(hp>0){
		switch(type){
		case 1:
			if(cnt<30)y+=speed;										//�^���Ɉړ�
			else if(cnt<70);
			else y-=speed;
			if(cnt==300)Alive=FALSE;
			break;
		case 2:
			if(cnt<50)y+=speed;
			else if(cnt==50){
				if(ShootFlag==FALSE){
//				new SpiralShooter(x,y,0,0.01f,0.02f);
//				new IntervalMultipleSpiralShooter(x,y,0,0.01f,0.02f,4,5);
//				new BiDirectionalSpiralShooter(x,y,0,0.01f,0.02f,-0.02f,4,5);
//				new BentSpiralShooter(x,y,0,0.02f,0.005f,1,10,-0.003f,0.0002f);
//				new CombinedSpiralShooter(x,y);
//				new WasherSpiralShooter(x,y);
//				new HardWasherSpiralShooter(x,y);
//				new NWayShooter(x,y,0.25f,0.2f,0.02f,7,5,0,0);
//				new CircleShooter(x,y,0.25f,0.02f,8,5,0,0);
//				new AimingNWayShooter(x,y,0.25f,0.02f,9,10);
//				new IntermittentAimingNWayShooter(x,y,0.25f,0.04f,9,2,60,20);
//				new RandamNWayShooter(x,y,0.25f,0.2f,0.02f,1,1);
//				new RandamCircleShooter(x,y,0.02f,3,1);
//				new RollingNWayShooter(x,y,0.25f,0.2f,0.01f,0.02f,5,1,5);
//				new WavingNWayShooter(x,y,0.25f,0.2f,0.05f,0.02f,5,5,120);
//				new WavingCircleShooter(x,y,0.25f,0.1f,0.02f,8,1,120);
//				new AimingShooter(x,y,0.02,10);
//				new LineShooter(x,y,0.25f,0.01f,20,30,15);
//				new AimingLineShooter(x,y,0.02f,2,20,10);
//				new SpreadingShooter(x,y,0.2f,0.01f,9,240,0.005f,4);
				new RandamSpreadingShooter(x,y,0.2f,0.02f,0.02f,30,240);
//				new OvertakingShooter(x,y,0.2f,0.01f,7,240,0.002f,0,10,4);
//				new SimpleHomingShooter(x,y,0.02f,20);
//				new ConstrainedHomingShooter(x,y,0.02f,20,0.0005f);	//�Ō�̈����ɒ��ӂ��K�v
//				new GapShooter(x,y,0.95f,0.003f,200,100);
//				Pattern1(x,y);
//				new PlacedBulletShooter(x,y,0.01f,60,120,20);
//				new StarPlacedShooter(x,y,0.25f,0.3f,100,30,2,250,0.01f,0.4f);
//				new ReStarPlacedShooter(x,y,0,0.3f,100,30,2,400,0.01f,0.4f);
					ShootFlag=TRUE;
				}
			}
			break;

//
		case 10:													//�_���e(���ړ�)
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			Angle+=Angle_a;
			Angle-=floor(Angle);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			break;


		case 11:													//3�_�o�[�X�g(���ړ�)
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			Angle+=Angle_a;
			Angle-=floor(Angle);
			if(cnt%5==0 && IntervalFlag==FALSE){
				new Directionalshooter(x,y,0.25f,0.03f,1);
				if(cnt%15==0) IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			break;
		case 12:
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			Angle+=Angle_a;
			Angle-=floor(Angle);
			if(cnt%5==0 && IntervalFlag==FALSE){
				new Directionalshooter(x,y,0.25f,0.03f,1);
				if(cnt%15==0) IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			break;

		case 13:													//�_���e(�΂�)
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			Angle+=Angle_a;
			Angle-=floor(Angle);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			break;
		case 14:
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;

		case 15:
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;
		case 16:
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;
//                
        case 30:
            rad=Angle*DX_PI_F*2;
            x+=speed*cosf(rad);
            y+=speed*sinf(rad);
            Angle+=Angle_a;
            Angle-=floor(Angle);
            break;
        case 31:
            rad=Angle*DX_PI_F*2;
            x+=speed*cosf(rad);
            y+=speed*sinf(rad);
            Angle+=Angle_a;
            Angle-=floor(Angle);
            break;

		case 32:													//�_���e
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;

		case 33:
			rad=Angle*DX_PI_F*2;
            x+=speed*cosf(rad);
            y+=speed*sinf(rad);
            Angle+=Angle_a;
            Angle-=floor(Angle);
			break;
		case 34:
			rad=Angle*DX_PI_F*2;
            x+=speed*cosf(rad);
            y+=speed*sinf(rad);
            Angle+=Angle_a;
            Angle-=floor(Angle);
			break;
		case 35:													//case33�̑_���e			
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;
		case 36:													//case34�̑_���e
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;

		case 37:													//case30��3�_�o�[�X�g			
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			Angle+=Angle_a;
			Angle-=floor(Angle);
			if(cnt%5==0 && IntervalFlag==FALSE){
				new Directionalshooter(x,y,0.25f,0.03f,1);
				if(cnt%15==0) IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			break;
		case 38:													//case31�̑_���e			
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;

			case 39:												//�_���e			
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.05f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;
			case 40:												//�_���e			
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.05f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			Angle+=Angle_a;
			Angle-=floor(Angle);
			break;

		case 41:
			rad=Angle*DX_PI_F*2;
            x+=speed*cosf(rad);
            y+=speed*sinf(rad);
            Angle+=Angle_a;
            Angle-=floor(Angle);
			break;
//
		case 60:
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(y>=-0.3333f) Angle=0;
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			break;
		case 61:
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(y>=-0.3333f) Angle=0.5f;
			if(IntervalFlag==FALSE){
				new Directionalshooter(x,y,GetMyShipAngle(x,y),0.03f,1);
				IntervalFlag=TRUE;
			}
			if(cnt%FireInterval==0)IntervalFlag=FALSE;
			break;
		case 62:
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
			if(cnt==90){
				init_genrand((unsigned long)timeGetTime());
				Angle=genrand_real2()/2;
				Angle-=floor(Angle);
			}
			break;
//
		case 300:													//��
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,300);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;

		case 301:													//��(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,301);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;
		case 302:													//��
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,302);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
            break;
		case 303:													//��(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,303);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
            break;
		case 304:													//��
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,304);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
            break;
		case 305:													//��(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,305);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;
		case 306:													//�E
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,306);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;
		case 307:													//�E(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,307);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;
		case 308:													//����(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,308);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;	
		case 309:													//�E��(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,309);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;
		case 310:													//����(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,310);
				Alive=FALSE;
				ShootFlag=TRUE;
			}
			break;
		case 311:													//�E��(�~�T�C���Ȃ�)
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,311);
				Alive=FALSE;
				ShootFlag=TRUE;
				break;
		case 312://
			if(ShootFlag==FALSE){
				new Fokker_D_VII_BOSS(x,y,speed,hp,312);
				Alive=FALSE;
				ShootFlag=TRUE;
				break;
			}
		}
		case 1000:													//����(�E�H�[���I�u�f�X)
			if(ShootFlag==FALSE){
				new Wall_Of_Death(speed,hp,20,1,284);
																	//��O�����̕ύX�ŁA�Z�x�����\�B
																	//����ȊO�̈����͓��ɂ�����K�v�͂Ȃ��B���́A�������͈Ӗ����Ȃ��B
				ShootFlag=TRUE;
				Alive=FALSE;
			}
			break;

		}
		for(TaskIterator i(MyBulletList);i.HasNext();){
			Object *object=static_cast<Object*>(i.Next());
			Alive_Judge(object);
			break;
		}
//=====================================================================================
	}
	else {
		new EnemyCrash(x,y,Anime[0]);
		Alive=FALSE;
	}
	if(cnt==600)Alive=FALSE;										//10�b��A����
}

void *Enemy::operator new(size_t n){
	return EnemyList->New(n);
}
void Enemy::operator delete(void *p){
	EnemyList->Delete(p);
}
void Pattern1(float x,float y){										//�}���̃p�^�[��1
	static char Pattern1[]=
		"					"
		"					"
		"					"
		"###################";
	new PatternShooter(x,y,0.25f,0.3f,0.005f,10,Pattern1,19,8);
}
void Enemy::Draw(void){												//�Ƃ肠�����A�I�[�o���C�h(����)
	int	object_x,object_y;
	object_x=(x+1)*Disp_Height/2;
	object_y=(y+1)*Disp_Width/2;
	DrawRotaGraph(object_x,object_y,1,DX_PI_F+
			(Angle-0.25f)*DX_PI_F,Anime[cnt%AnimeLoopNum],TRUE);		//0.74f memo
}