#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include"Invariable_FPS.h"

class Menu{
public:
	int Font;								//�t�H���g�f�[�^
	int CurrentFont;						//�I�����ꂽ���[�h�̃t�H���g
	char *string;							//������
	int White;								//�F�i���j
	int x,y,pic;							//���W�ۑ��ϐ�
	Menu(int lenth,char *string);			//�R���X�g���N�^
	void PutMenu(bool Flag);				//�\����
	~Menu(void);							//�f�X�g���N�^
};
class MainMenu{
public:
	Menu* maindisp[5];						//�錾
	FPS *fps;								//�錾
	MainMenu(void);							//�R���X�g���N�^
	bool mainmenu_flag;						//���C�����j���[�t���O
	bool stopflag;							//��~�t���O
	int back_pic;							//�w�i
	int y;									//���W
	int White;								//�F�i���j
	int selecter;							//�ǂ��I��ł��邩
	int Timer;								//�^�C�}�[

	int Main_Menu(void);					//����
	void MainMenu_Input_Key(void);			//�L�[�{�[�h���͏���
	~MainMenu(void);						//�f�X�g���N�^
};
#endif