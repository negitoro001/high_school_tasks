#ifndef GAME_H										//�C���N���[�h�K�[�h
#define GAME_H										//�C���N���[�h�K�[�h
#include"ShootingGame.h"
#include"Stage1-1_Novel.h"
#include"Invariable_FPS.h"
class Game{
public:
	bool compulsion_shut_down;						//�����I��
	bool Change;									//�`�F���W�t���O
	int EpisodeNum;									//EP�ԍ�
	bool ShootingMode;								//�V���[�e�B���O���[�h
	ShootingGame *shooting;							//�錾(�V���[�e�B���O)
	Novel_Base *novel;								//�錾(�m�x��)
	Game(bool ContinueMode);						//�R���X�g���N�^
	void Play(void);								//���s����
	~Game(void);									//�f�X�g���N�^
};
#endif												//�C���N���[�h�K�[�h