#ifndef OBJECT_H
#define OBJECT_H
#include"Task.h"
#define Disp_Width 480
#define Disp_Height 387							//�p�����[�^�����\
class Object : public Task{
public:
	Object(TaskList *List);						//�R���X�g���N�^
	float x,y,speed;							//���W�A�X�s�[�h�ϐ�
	bool Alive;									//�����t���O
	int Pic,hp;									//Pic�͈ꖇ�C���X�g�p�A�̗͕ϐ�

	virtual void Move(void)=0;					//�ړ��֐�(�������z�֐��j
	virtual void Draw(void);					//�`��֐�(���z�֐��j
	virtual void Alive_Judge(Object *object);	//�����蔻��
};
#endif
//�������z�֐��Ƃ́A���N���X�ł͐錾�݂̂ŁA��`����Ă��Ȃ��֐��̂���