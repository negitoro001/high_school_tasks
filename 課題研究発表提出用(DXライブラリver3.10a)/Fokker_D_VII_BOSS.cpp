#include"Fokker_D_VII_BOSS.h"
#include"DxLib.h"
#include"EnemyCrash.h"
#include"EnemyBulletSort4.h"

Fokker_D_VII_BOSS::Fokker_D_VII_BOSS(float x,
	float y,float speed,int hp,int type)					//コンストラクタ
:	Enemy(x,y,speed,hp,type,0)
{
	LoadDivGraph("Enemy_Picutures/Fokker_D_VII_Ordinary.bmp",
		18,9,2,80,80,Anime);
	ShootFlag=FALSE;
	Alive=TRUE;
	Angle=0.25f;
	Angle_a=0.004f;
	AnimeLoopNum=18;
	this->type=type;
	switch(type){
	case 302:
		Angle=0.75f;										//上
		Angle_a=0;
		break;
	case 303:
		Angle=0.75f;										//上(ミサイルなし)
		Angle_a=0;
		break;
	case 304:
		Angle=0.5f;											//左
		Angle_a=0;
		break;
	case 305:
		Angle=0.5f;											//左(ミサイルなし)
		Angle_a=0;
		break;
	case 306:
		Angle=0;											//右
		Angle_a=0;
		break;
	case 307:
		Angle=0;											//右(ミサイルなし)
		Angle_a=0;
		break;
	case 308:
		Angle=0.17f;										//左下(ミサイルなし)
		Angle_a=0.1f;
		break;
	case 309:
		Angle=0.33f;										//右下(ミサイルなし)
		Angle_a=0.1f;
		break;
	case 310:
		Angle=0.66f;										//左上(ミサイルなし)
		Angle_a=0.1f;
		break;
	case 311:
		Angle=0.83f;										//右上(ミサイルなし)
		Angle_a=0.1f;
		break;
	case 312:												//中ボス用
		Angle=0.25f;
		Angle_a=0;
		break;
	}
}

void Fokker_D_VII_BOSS::Move(void){
	switch(type){
//
	case 300:
		y+=speed;
		if(cnt==60 && ShootFlag==FALSE){
			//new Cluster_Missile(x,y,
//			GetMyShipAngle(x,y),0.012f,60,7);				//追尾型クラスターミサイル（自作ww)
			new ReStarPlacedShooter(x,y,0,0.3f,
				100,30,2,400,0.01f,0.4f);

			ShootFlag=TRUE;
			speed=0;										//停止
		}
		break;

	case 301:
			ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
//
	case 302:
            if(ShootFlag==FALSE){
                new Cluster_Missile(x,y,GetMyShipAngle(x,y),
					0.012f,60,7);							//追尾型クラスターミサイル

                ShootFlag=TRUE;
            }
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
    case 303:
			ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
//
    case 304:
            if(ShootFlag==FALSE){
                new Cluster_Missile(x,y,GetMyShipAngle(x,y),
					0.012f,60,7);							//追尾型クラスターミサイル

                ShootFlag=TRUE;
            }
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
    case 305:
			ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
//
    case 306:
            if(ShootFlag==FALSE){
                new Cluster_Missile(x,y,GetMyShipAngle(x,y),
					0.012f,60,7);							//追尾型クラスターミサイル

                ShootFlag=TRUE;
            }
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
    case 307:
            ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
//
    case 308:
            ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
    case 309:
            ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
//
    case 310:
            ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
    case 311:
            ShootFlag=TRUE;
			rad=Angle*DX_PI_F*2;
			x+=speed*cosf(rad);
			y+=speed*sinf(rad);
		break;
	case 312:
		y+=speed;
		if(cnt==60 && ShootFlag==FALSE){
			//new Cluster_Missile(x,y,GetMyShipAngle(x,y),
//			0.012f,60,7);									//追尾型クラスターミサイル（自作ww)

			new ReStarPlacedShooter(x,y,0,0.3f,100,
				30,2,400,0.01f,0.4f);

			ShootFlag=TRUE;
			speed=0;										//停止
		}
		break;
//
	}
	for(TaskIterator i(MyBulletList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		Alive_Judge(object);
		break;
	}
	if(hp<=0) {
		for(int i=0;i<AnimeLoopNum;i++) DeleteGraph(Anime[i]);
		new EnemyCrash(x,y,Anime[0]);
		Alive=FALSE;
	}
	cnt++;
}