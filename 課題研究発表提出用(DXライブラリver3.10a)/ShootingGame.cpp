

#include"ShootingGame.h"

ShootingGame::ShootingGame(int TitleNum){																//コンストラクタ
	EndShooting=FALSE;																					//仮設
	Result=0;																							//仮設

	MyShipList=new TaskList(250, 5);																	//自機タスクリスト作成
	EnemyList=new TaskList(500, 50);																	//敵タスクリスト作成
	MyBulletList=new TaskList(250, 30);																	//自機弾タスクリスト作成
	EnemyBulletList=new TaskList(250,5000);																//敵弾タスクリスト作成

	new MyShip(0.f,0.95f,0.025f);																		//自期インスタンス生成

	count=0;EndFlag=FALSE;Contrast=0;
	fps=new FPS();
	switch(TitleNum){
	case EP1_1:

		enemy_book=FileRead_open("EnemyNote/ShootingGame/Stage1-1.csv");
//		enemy_book=FileRead_open("EnemyNote/ShootingGame/Experiment(tmp).csv");//tmp
		//Back_Music=LoadSoundMem("BackMusics/Voice.mp3");
//		Back_Music=LoadSoundMem("使用楽曲(仮)/04 Shake Your Body.mp3");
		Back_Picture=LoadGraph("STG_Back_Pictures/haikei1-1.jpg");
		break;
//	case EP1_2:
//		enemy_book=FileRead_open("EnemyNote/ShootingGame/Stage1-2.csv");
//		Back_Music=LoadSoundMem("BackMusics/Voice.mp3");
//		Back_Picture=LoadGraph("STG_Back_Pictures/haikei1-1.jpg");
//		break;
//	case EP1_3:
//		enemy_book=FileRead_open("EnemyNote/ShootingGame/Stage1-3.csv");
//		Back_Music=LoadSoundMem("BackMusics/Voice.mp3");
//		Back_Picture=LoadGraph("STG_Back_Pictures/haikei1-1.jpg");
	}
	for(int temp_i=0;temp_i<2;temp_i++) while(FileRead_getc(enemy_book)!='\n');							//最初の2行を無視
	appear_cnt=ShootingGame::EnemyDataLoader_appear_cnt(enemy_book);
//	PlaySoundMem(Back_Music,DX_PLAYTYPE_BACK);															//BGM再生
	FontHandle=CreateFontToHandle("ＭＳ ゴシック",13,3,DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	color=GetColor(255,255,255);
	this->TitleNum=TitleNum;
	Side=LoadGraph("OP/side_1.bmp");
}
int ShootingGame :: EnemyDataLoader_appear_cnt(int enemy_csv){											//敵出現時間データ読み込み
	int temp_i,buffer,buffer_i[50];
	char buffer_c[50];

	for(buffer=0;buffer<64;buffer++){
		buffer_i[buffer]=buffer_c[buffer]=FileRead_getc(enemy_csv);
		if(buffer_c[buffer]=='/'){																		//スラッシュがあれば
			while(FileRead_getc(enemy_csv)!='\n');														//改行までループ
			buffer=-1;																					//カウンタを最初に戻して
			continue;
		}
		if(buffer_i[buffer]==','){																		//カンマがきたら
			buffer_c[buffer]='\0';																		//そこまでを文字列とし
			break;
		}
		if(buffer_i[buffer]=='&'){																		//ファイルの終わりなら終了
			temp_i=100;EndFlag=TRUE;
			return 0;
			break;
		}
	}
	return atoi(buffer_c);
}
void ShootingGame :: Back_Pictures_Move(int count,int Pic){												//背景読み込み
	DrawGraph(0,count%700-700,Pic,FALSE);
	DrawGraph(0,count%700,Pic,FALSE);
	DrawGraph(Disp_Height,0,Side,TRUE);
}
void ShootingGame :: GameTask(TaskList *List){															//タスクリスト管理部
	for(TaskIterator i(List);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		object->Move();
		object->Draw();
		if(!object->Alive){
			i.Remove();
			DeleteGraph(object->Pic);																	//3分以上ゲームするとグラフィックハンドル保持数の上限を超えるので解放
		}
	}
}
bool ShootingGame :: EndCheck(void){																	//終了条件
	for(TaskIterator i(EnemyList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		if(object->Alive==TRUE)return FALSE;
	}
	return TRUE;
}
void ShootingGame :: EnemyDataLoader(int enemy_csv){													//敵データ読み込み
	int buffer,buffer_i[50],temp_i;
	char buffer_c[50];
	float temp_x,temp_y,temp_speed;																		//敵情報作業用
	int temp_hp,temp_type,temp_pic_type;																//敵情報作業用

	temp_i=1;

	while(1){
		for(buffer=0;buffer<64;buffer++){
			buffer_i[buffer]=buffer_c[buffer]=FileRead_getc(enemy_csv);
			if(buffer_c[buffer]=='/'){																	//スラッシュがあれば
				while(FileRead_getc(enemy_csv)!='\n');													//改行までループ
				buffer=-1;																				//カウンタを最初に戻して
				continue;
			}
			if(buffer_i[buffer]==','){																	//カンマなら
				buffer_c[buffer]='\0';																	//そこまでを文字列とする
				break;
			}
			if(buffer_i[buffer]=='\n'){																	//終了
				temp_i=6;
				break;
			}
			if(buffer_i[buffer]==EOF)return ;
		}
		switch(temp_i){
		case 1:
			temp_x=(float)atof(buffer_c);
			temp_i++;
			break;
		case 2:
			temp_y=(float)atof(buffer_c);
			temp_i++;
			break;
		case 3:
			temp_speed=(float)atof(buffer_c);
			temp_i++;
			break;
		case 4:
			temp_hp=atoi(buffer_c);
			temp_i++;
			break;
		case 5:
			temp_type=atoi(buffer_c);
			temp_i++;
			break;
		case 6:
			temp_pic_type=atoi(buffer_c);
			new Enemy(temp_x,temp_y,temp_speed,temp_hp,temp_type,temp_pic_type);						//敵機インスタンス生成
			temp_i++;
			break;
		}
	if(temp_i==7)break;
	}
}
void ShootingGame::StageDetail(void){																	//ステージ詳細表示
	switch(TitleNum){
	case EP1_1:
//		DrawFormatStringToHandle(430,390,color,FontHandle,"Shake Your Body");
//		DrawFormatStringToHandle(430,410,color,FontHandle,"Fear,and Loathing");
//		DrawFormatStringToHandle(430,430,color,FontHandle,"in Las Vegas");
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Contrast);
		DrawFormatStringToHandle(10,390,color,FontHandle,"場所 高知県立高知工業高校");
		DrawFormatStringToHandle(10,410,color,FontHandle,"日時 2012年1月31日");
		DrawFormatStringToHandle(10,430,color,FontHandle,"概要 生徒研究発表会発表用デモプレイ");
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	if(count<=255) Contrast++;																			//フェードイン
	if(count>700 && count<=955)Contrast--;																//フェードアウト
}
void ShootingGame::Stage(void){
	while(ProcessMessage()==0 && ClearDrawScreen()==0 && CheckHitKey(KEY_INPUT_ESCAPE)==0){
		fps->measurement();
		Back_Pictures_Move(count,Back_Picture);															//背景描画

		if(appear_cnt!=0 && appear_cnt<=count){															//時間がきたら敵を処理
			ShootingGame::EnemyDataLoader(enemy_book);
			appear_cnt=ShootingGame::EnemyDataLoader_appear_cnt(enemy_book);
		}
		GameTask(MyShipList);																			//自機リスト実行
		GameTask(EnemyList);																			//敵リスト実行
		GameTask(MyBulletList);																			//自機弾リスト実行
		GameTask(EnemyBulletList);																		//敵弾リスト実行
		StageDetail();																					//ステージ詳細表示

		if(count<=255){
			SetDrawBright(count,count,count);
		}
		count++;
		if(EndFlag==TRUE){
			if(EndCheck()==TRUE)break;
			EndShooting=TRUE;																			//仮設
		}
		ScreenFlip();
		fps->Wait();
	}
}
ShootingGame::~ShootingGame(void){
	FileRead_close(enemy_book);																			//ファイルを閉じる
	for(int i=0;i<=255;i+=5){																			//ブラックアウト
		ProcessMessage();
		fps->measurement();
		ClearDrawScreen();
		Back_Pictures_Move(count,Back_Picture);
		SetDrawBright(255-i,255-i,255-i);
		GameTask(MyShipList);																			//自機リスト実行
		GameTask(EnemyList);																			//敵リスト実行
		GameTask(MyBulletList);																			//自機弾リスト実行
		GameTask(EnemyBulletList);																		//敵弾リスト実行
		StageDetail();																					//ステージ詳細表示
		count++;
		ScreenFlip();
		fps->Wait();
	}
	DeleteFontToHandle(FontHandle);
	delete MyShipList;																					//タスクリスト削除
	delete EnemyList;
	delete MyBulletList;
	delete EnemyBulletList;
	InitGraph();																						//画像を全部削除
}