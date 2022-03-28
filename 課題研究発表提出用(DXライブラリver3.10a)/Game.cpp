#include"Game.h"
Game::Game(bool ContinueMode){
	if(ContinueMode==FALSE){
		novel=new Stage1_1_Novel();
		ShootingMode=FALSE;
		EpisodeNum=1;
	}
	else{
		Method();
		if(Data_r.LineNumber==-1){
			shooting=new ShootingGame(Data_r.EpisodeNumber);
			ShootingMode=TRUE;
			EpisodeNum=Data_r.EpisodeNumber;
		}
		else{
			switch(Data_r.EpisodeNumber){
			case EP1_1:
				novel=new Stage1_1_Novel(Data_r.LineNumber);
				break;
				//ここを増やす
			}
			ShootingMode=FALSE;
			EpisodeNum=Data_r.EpisodeNumber;
		}
	}
	Change=FALSE;
	compulsion_shut_down=FALSE;
}
void Game::Play(void){
	while(compulsion_shut_down==FALSE){
		if(Change==TRUE){
			if(ShootingMode==TRUE){
				EpisodeNum++;
//				switch(EpisodeNum){
					//処理を書き込む
//				}
				ShootingMode=FALSE;
			}
			else{
				shooting=new ShootingGame(EpisodeNum);
				ShootingMode=TRUE;
			}
			Change=FALSE;
		}
		if(ShootingMode==TRUE){
			shooting->Stage();
//			if(CheckHitKey(KEY_INPUT_ESCAPE)==TRUE)compulsion_shut_down=TRUE;
//			else delete shooting;
			//仮設プログラム(課題研究発表用)
			compulsion_shut_down=TRUE;
			Change=TRUE;
		}
		else{
			novel->Move();
			if(CheckHitKey(KEY_INPUT_ESCAPE)==TRUE)compulsion_shut_down=TRUE;
			else delete novel;
			Change=TRUE;
		}
	}
}
Game::~Game(void){
	if(compulsion_shut_down==TRUE){
		if(ShootingMode==TRUE) delete shooting;
		else delete novel;
	}
}