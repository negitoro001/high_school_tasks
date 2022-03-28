#ifndef SHOOTINGGAME_H
#define SHOOTINGGAME_H
#include"DxLib.h"
#include"Task.h"
#include"Object.h"
#include"Enemy.h"
#include"MyShip.h"
#include"Invariable_FPS.h"
#include"Novel_Base_Class.h"

class ShootingGame{
public:
	FPS *fps;													//�錾
	int enemy_book,appear_cnt,count,Back_Music,Back_Picture;	//�錾�i��Ɨp�̊֐��j
	ShootingGame(int TitleNum);									//�R���X�g���N�^
	~ShootingGame(void);										//�f�X�g���N�^

	int Contrast;												//�R���g���X�g����
	int FontHandle,color,TitleNum;								//�t�H���g�n���h���A�F�ϐ��A�^�C�g���ԍ�
	int Side;													//��ʉE�T�C�h�̉摜

	int EnemyDataLoader_appear_cnt(int enemy_csv);				//�G�o�����ԃf�[�^�ǂݍ���
	virtual void Back_Pictures_Move(int count,int Pic);			//�w�i�ǂݍ���(���z�֐�)
	void StageDetail(void);										//�X�e�[�W�ڍו\��
	void GameTask(TaskList *List);								//�^�X�N���X�g�Ǘ���
	void EnemyDataLoader(int enemy_csv);						//�G�f�[�^�ǂݍ���
	virtual void Stage(void);									//�Q�[���{��(���z�֐�)
	bool EndFlag;												//�I���t���O
	bool EndCheck(void);										//�I���`�F�b�N
};
#endif