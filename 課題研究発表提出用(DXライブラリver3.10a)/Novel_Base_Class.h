#ifndef NOVEL_BASE_CLASS_H
#define NOVEL_BASE_CLASS_H
#include"Invariable_FPS.h"
#include<stdio.h>
#include<stdlib.h>
//====================================================�V�i���I�̃i���o�����O��`
#define EP0_1 4										//�V�i���I���I�ɁAEP1_1����ɗ���̂ŁA�i���o�����O�̏����ɂ��ꂪ�����Ă���
#define EP0_2 5
#define EP0_3 6
#define EP1_1 1
#define EP1_2 2
#define EP1_3 3
#define EP2_1 7
#define EP2_2 8
#define EP2_3 9
#define EP3_1 10
#define EP3_2 11
#define EP3_3 12
#define EP4_1 13
#define EP4_2 14
#define EP4_3 15
//====================================================
class Novel_Base{
public:
	FPS *fps;										//�錾
	int FontHandle;									//�t�@�C���n���h��
	int x,y;										//���W
	char string_len;								//�ǂݍ��񂾕������𐔂���
	char buffer[5][50];								//�\���p�ɓǂݍ���
	char temp_copy[256];							//txt�t�@�C������ǂݍ���
	int Char_Picture;								//�摜�I��
	int write_len,write_line;						//���݂̓ǂݍ���ł��镶���̏ꏊ
	int TextNote;									//txt��ǂݍ���
	int Box;										//�e�L�X�g�{�b�N�X
	int Registry;									//�ꎞ�ۑ��p(�摜�̊Ǘ��ԍ�)
	bool Novel_Chapter_end;							//�I���t���O
	bool Novel_StopFlag;							//�ꎞ�I�ɓǂݍ��ނ��~�߂鏈��
	bool Ontinuation_PreventFlag;					//�A���I���͖h�~�t���O�i1/60�b�Ń��[�v���Ă��܂����Ƃւ̑Ώ��j
	bool Change_Picture_Flag;						//�ʐ^�ύX���̃t���O�i�ʐ^�̐؂�ւ��t�F�[�h�C���E�A�E�g�Ɏg�p�j
	int Timer;										//�^�C�}�[
	int LineNumber;									//�s���J�E���^

	Novel_Base(void);								//�R���X�g���N�^
	virtual ~Novel_Base(void);						//�f�X�g���N�^
	void Main_String_Method(void);					//��������
	int Char_Loader(void);							//�L�����N�^�[�̉摜��I��
	bool isJapaneseCharacter(unsigned char code);	//���{�ꔻ��
	void Disp_Output(void);							//�����\����
	virtual void Novel_Picture(void)=0;				//�������z�֐��i�摜�\�����j
	virtual void Picture_Fade_In_Out(void)=0;		//�������z�֐��i�摜�̃t�F�[�h�C���E�A�E�g�j
	void Key_Input_Method(void);					//�m�x���p�[�g�ɂ�����L�[���͏���
	virtual void Move(void);						//�{�̏���
};
//==================================================�Z�[�u�f�[�^�Ǘ���
void Method(void);									//���[�h����
void Method(int EpisodeNumber,int Data);			//�Z�[�u����
typedef struct{										//�Z�[�u�f�[�^�\����
	int EpisodeNumber;								//�G�s�\�[�h�ԍ�
	int LineNumber;									//�s��
}SaveData_w;
typedef struct{										//�Z�[�u�f�[�^�\����
	int EpisodeNumber;								//�G�s�\�[�h�ԍ�
	int LineNumber;									//�s��
}SaveData_r;

extern SaveData_r Data_r;							//�O���[�o���ϐ�
extern SaveData_w Data_w;							//�O���[�o���ϐ�
#endif
//���Ȃ݂�virtual �֐�=0;���������z�֐�����
//���������Ƃ��̊��N���X�͒��ۃN���X�Ƃ������ƂɂȂ�
//�������z�֐����ЂƂł�����΁A���ۃN���X�ƂȂ�
//�h���N���X�ł��Ȃ炸�A�������z�֐����`���Ȃ���΂Ȃ�Ȃ��i���Ȃ��ƃG���[�j