#include"DxLib.h"
#include"main_menu.h"
#include"Novel_Base_Class.h"
#include"ShootingGame.h"
#include"Stage1-1_Novel.h"
#include"Game.h"
#pragma warning(disable:4244)
#include<iostream>
#include<map>
#include<vector>
#include<stdio.h>
#include <time.h>
using namespace std;

void Novel_Road_Main(void){																		//�Z�[�u�f�[�^�ǂݏo����
	Method();																					//�Z�[�u�f�[�^�ǂݏo��
	switch(Data_r.EpisodeNumber){																//�Z�[�u�f�[�^�ɂ��؂�ւ���
	case EP1_1:
		if(Data_r.LineNumber!=-1){
			Novel_Base *novel;
			novel=new Stage1_1_Novel(Data_r.LineNumber);
			novel->Move();
			delete novel;
		}
		else{
			ShootingGame *Stage1_1;
			Stage1_1=new ShootingGame(EP1_1);
			Stage1_1->Stage();
			delete Stage1_1;
		}
		break;
	}
}

void Shooting_main(void){																		//����
	InitGraph();
	ShootingGame *Stage1_1;
	Stage1_1=new ShootingGame(EP1_1);
	Stage1_1->Stage();
	delete Stage1_1;
}

void Novel_main(void){																			//����
	Novel_Base *novel;
	novel=new Stage1_1_Novel();
	novel->Move();
	delete novel;
}

void gamemain(void){
	int Selecter;
	Game *game;																					//�錾(�Q�[���{��)
	MainMenu *main_menu;																		//�錾(���C�����j���[)
	main_menu=new MainMenu();																	//�R���X�g���N�^(���C�����j���[)
	Selecter=main_menu->Main_Menu();
	delete main_menu;																			//�f�X�g���N�^(���C�����j���[)
	SetDrawBright(0,0,0);
	switch(Selecter){
	case 0:
		game=new Game(FALSE);																	//�R���X�g���N�^
		game->Play();																			//�{�̏���
		delete game;																			//�f�X�g���N�^
		break;
	case 1:
		game=new Game(TRUE);																	//�R���X�g���N�^
		game->Play();																			//�{�̏���
		delete game;																			//�f�X�g���N�^
		break;
	case 2:
		Novel_main();
		break;
	case 3:
		Novel_Road_Main();																		//��Ɨp
		break;
	case 4:
		break;
	default:
		break;
	}
}

bool message_box(){																				//���b�Z�[�W�{�b�N�X��(�K�v�ɉ����Ďg�p)
	int flag;
	flag=MessageBox(
		NULL ,
		TEXT("�t���X�N���[�����[�h�ŋN�����܂����H(�}�E�X�őI�����Ă�������)"),
		TEXT("�X�N���[���ݒ�"),
		MB_YESNO | MB_ICONQUESTION );
	if(flag==IDNO) return TRUE;
	else return FALSE;
}

//����=========================================================================================================================================
void ResultPut(void){
	int FontHandle=CreateFontToHandle("�l�r �S�V�b�N",18,3,DX_FONTTYPE_ANTIALIASING_EDGE);
	int color=GetColor(0,0,0);
	int EndGraph;
	EndGraph=LoadGraph("Char_Pic/Ep1/�I�����.png");
	for(int i=0;i<255;i+=5){
		ClearDrawScreen();
		SetDrawBright(i,i,i);
		DrawGraph(0,0,EndGraph,TRUE);
		DrawFormatStringToHandle(110,385,color,FontHandle,"%d",Result);
		ScreenFlip();
	}
	WaitKey();
	FILE *fp;
	if ((fp = fopen("Result.txt", "a")) == NULL) {
		printf("file open error!!\n");
		exit(EXIT_FAILURE);																		//�G���[�̏ꍇ�͒ʏ�A�ُ�I������
	}
	time_t now = time(NULL);
    struct tm *pnow = localtime(&now);
	fprintf(fp,"%d:%d:%d�L�^%d\n",pnow->tm_hour,pnow->tm_min,pnow->tm_sec,Result);
	fclose(fp);
}
void StartingGame(void){																		//�N�����̏���
	int Logo1=LoadGraph("OP/���m�������m�H�ƍ����w�Z.png");
	for(int i=0;i<255;i+=5){
		ClearDrawScreen();
		SetDrawBright(i,i,i);
		DrawGraph(0,0,Logo1,TRUE);
		ScreenFlip();
	}
	WaitTimer(3000);
	for(int i=255;i>=0;i-=5){
		ClearDrawScreen();
		SetDrawBright(i,i,i);
		DrawGraph(0,0,Logo1,TRUE);
		ScreenFlip();
	}
	SetDrawBright(255,255,255);
	PlayMovie("OpAnime.AVI",1,DX_MOVIEPLAYTYPE_NORMAL);
}
//=============================================================================================================================================

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
											LPSTR lpCmdLine, int nCmdShow ){					//���C���֐�

	SetMainWindowText("�������Q�[��");															//�^�C�g���̖��O��ύX
//	if(message_box()==TRUE) ChangeWindowMode(TRUE);												//�E�B���h�E���[�h(����)
	ChangeWindowMode(TRUE);																		//�E�B���h�E���[�h�Ŏ��s
	SetWindowSizeChangeEnableFlag(TRUE);														//��ʂ̑傫���̕ύX���\��
	if(DxLib_Init()==-1||SetDrawScreen(DX_SCREEN_BACK)!=0) return -1;							//�������Ɨ���ʉ�

	StartingGame();																				//�N�����̏���
	gamemain();																					//�Q�[���{�̏���
//	ResultPut();																				//����
	DxLib_End();																				//�I��
	return 0;																					//OS�ɐ���I���������Ƃ�ʒm
}