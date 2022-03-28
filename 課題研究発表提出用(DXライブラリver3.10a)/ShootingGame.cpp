

#include"ShootingGame.h"

ShootingGame::ShootingGame(int TitleNum){																//�R���X�g���N�^
	EndShooting=FALSE;																					//����
	Result=0;																							//����

	MyShipList=new TaskList(250, 5);																	//���@�^�X�N���X�g�쐬
	EnemyList=new TaskList(500, 50);																	//�G�^�X�N���X�g�쐬
	MyBulletList=new TaskList(250, 30);																	//���@�e�^�X�N���X�g�쐬
	EnemyBulletList=new TaskList(250,5000);																//�G�e�^�X�N���X�g�쐬

	new MyShip(0.f,0.95f,0.025f);																		//�����C���X�^���X����

	count=0;EndFlag=FALSE;Contrast=0;
	fps=new FPS();
	switch(TitleNum){
	case EP1_1:

		enemy_book=FileRead_open("EnemyNote/ShootingGame/Stage1-1.csv");
//		enemy_book=FileRead_open("EnemyNote/ShootingGame/Experiment(tmp).csv");//tmp
		//Back_Music=LoadSoundMem("BackMusics/Voice.mp3");
//		Back_Music=LoadSoundMem("�g�p�y��(��)/04 Shake Your Body.mp3");
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
	for(int temp_i=0;temp_i<2;temp_i++) while(FileRead_getc(enemy_book)!='\n');							//�ŏ���2�s�𖳎�
	appear_cnt=ShootingGame::EnemyDataLoader_appear_cnt(enemy_book);
//	PlaySoundMem(Back_Music,DX_PLAYTYPE_BACK);															//BGM�Đ�
	FontHandle=CreateFontToHandle("�l�r �S�V�b�N",13,3,DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	color=GetColor(255,255,255);
	this->TitleNum=TitleNum;
	Side=LoadGraph("OP/side_1.bmp");
}
int ShootingGame :: EnemyDataLoader_appear_cnt(int enemy_csv){											//�G�o�����ԃf�[�^�ǂݍ���
	int temp_i,buffer,buffer_i[50];
	char buffer_c[50];

	for(buffer=0;buffer<64;buffer++){
		buffer_i[buffer]=buffer_c[buffer]=FileRead_getc(enemy_csv);
		if(buffer_c[buffer]=='/'){																		//�X���b�V���������
			while(FileRead_getc(enemy_csv)!='\n');														//���s�܂Ń��[�v
			buffer=-1;																					//�J�E���^���ŏ��ɖ߂���
			continue;
		}
		if(buffer_i[buffer]==','){																		//�J���}��������
			buffer_c[buffer]='\0';																		//�����܂ł𕶎���Ƃ�
			break;
		}
		if(buffer_i[buffer]=='&'){																		//�t�@�C���̏I���Ȃ�I��
			temp_i=100;EndFlag=TRUE;
			return 0;
			break;
		}
	}
	return atoi(buffer_c);
}
void ShootingGame :: Back_Pictures_Move(int count,int Pic){												//�w�i�ǂݍ���
	DrawGraph(0,count%700-700,Pic,FALSE);
	DrawGraph(0,count%700,Pic,FALSE);
	DrawGraph(Disp_Height,0,Side,TRUE);
}
void ShootingGame :: GameTask(TaskList *List){															//�^�X�N���X�g�Ǘ���
	for(TaskIterator i(List);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		object->Move();
		object->Draw();
		if(!object->Alive){
			i.Remove();
			DeleteGraph(object->Pic);																	//3���ȏ�Q�[������ƃO���t�B�b�N�n���h���ێ����̏���𒴂���̂ŉ��
		}
	}
}
bool ShootingGame :: EndCheck(void){																	//�I������
	for(TaskIterator i(EnemyList);i.HasNext();){
		Object *object=static_cast<Object*>(i.Next());
		if(object->Alive==TRUE)return FALSE;
	}
	return TRUE;
}
void ShootingGame :: EnemyDataLoader(int enemy_csv){													//�G�f�[�^�ǂݍ���
	int buffer,buffer_i[50],temp_i;
	char buffer_c[50];
	float temp_x,temp_y,temp_speed;																		//�G����Ɨp
	int temp_hp,temp_type,temp_pic_type;																//�G����Ɨp

	temp_i=1;

	while(1){
		for(buffer=0;buffer<64;buffer++){
			buffer_i[buffer]=buffer_c[buffer]=FileRead_getc(enemy_csv);
			if(buffer_c[buffer]=='/'){																	//�X���b�V���������
				while(FileRead_getc(enemy_csv)!='\n');													//���s�܂Ń��[�v
				buffer=-1;																				//�J�E���^���ŏ��ɖ߂���
				continue;
			}
			if(buffer_i[buffer]==','){																	//�J���}�Ȃ�
				buffer_c[buffer]='\0';																	//�����܂ł𕶎���Ƃ���
				break;
			}
			if(buffer_i[buffer]=='\n'){																	//�I��
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
			new Enemy(temp_x,temp_y,temp_speed,temp_hp,temp_type,temp_pic_type);						//�G�@�C���X�^���X����
			temp_i++;
			break;
		}
	if(temp_i==7)break;
	}
}
void ShootingGame::StageDetail(void){																	//�X�e�[�W�ڍו\��
	switch(TitleNum){
	case EP1_1:
//		DrawFormatStringToHandle(430,390,color,FontHandle,"Shake Your Body");
//		DrawFormatStringToHandle(430,410,color,FontHandle,"Fear,and Loathing");
//		DrawFormatStringToHandle(430,430,color,FontHandle,"in Las Vegas");
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Contrast);
		DrawFormatStringToHandle(10,390,color,FontHandle,"�ꏊ ���m�������m�H�ƍ��Z");
		DrawFormatStringToHandle(10,410,color,FontHandle,"���� 2012�N1��31��");
		DrawFormatStringToHandle(10,430,color,FontHandle,"�T�v ���k�������\��\�p�f���v���C");
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	if(count<=255) Contrast++;																			//�t�F�[�h�C��
	if(count>700 && count<=955)Contrast--;																//�t�F�[�h�A�E�g
}
void ShootingGame::Stage(void){
	while(ProcessMessage()==0 && ClearDrawScreen()==0 && CheckHitKey(KEY_INPUT_ESCAPE)==0){
		fps->measurement();
		Back_Pictures_Move(count,Back_Picture);															//�w�i�`��

		if(appear_cnt!=0 && appear_cnt<=count){															//���Ԃ�������G������
			ShootingGame::EnemyDataLoader(enemy_book);
			appear_cnt=ShootingGame::EnemyDataLoader_appear_cnt(enemy_book);
		}
		GameTask(MyShipList);																			//���@���X�g���s
		GameTask(EnemyList);																			//�G���X�g���s
		GameTask(MyBulletList);																			//���@�e���X�g���s
		GameTask(EnemyBulletList);																		//�G�e���X�g���s
		StageDetail();																					//�X�e�[�W�ڍו\��

		if(count<=255){
			SetDrawBright(count,count,count);
		}
		count++;
		if(EndFlag==TRUE){
			if(EndCheck()==TRUE)break;
			EndShooting=TRUE;																			//����
		}
		ScreenFlip();
		fps->Wait();
	}
}
ShootingGame::~ShootingGame(void){
	FileRead_close(enemy_book);																			//�t�@�C�������
	for(int i=0;i<=255;i+=5){																			//�u���b�N�A�E�g
		ProcessMessage();
		fps->measurement();
		ClearDrawScreen();
		Back_Pictures_Move(count,Back_Picture);
		SetDrawBright(255-i,255-i,255-i);
		GameTask(MyShipList);																			//���@���X�g���s
		GameTask(EnemyList);																			//�G���X�g���s
		GameTask(MyBulletList);																			//���@�e���X�g���s
		GameTask(EnemyBulletList);																		//�G�e���X�g���s
		StageDetail();																					//�X�e�[�W�ڍו\��
		count++;
		ScreenFlip();
		fps->Wait();
	}
	DeleteFontToHandle(FontHandle);
	delete MyShipList;																					//�^�X�N���X�g�폜
	delete EnemyList;
	delete MyBulletList;
	delete EnemyBulletList;
	InitGraph();																						//�摜��S���폜
}