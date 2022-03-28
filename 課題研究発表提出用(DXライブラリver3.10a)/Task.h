#ifndef TASK_H							//�C���N���[�h�K�[�h
#define TASK_H

//���̕����͈ꕔ�֐���ς��������ŁA�Q�l���̃p�N���ł��B���͎͂����ł��܂���

//�^�X�N�{��================================================================================================
class Task{
friend class TaskList;					//friend�͂ǂ�ȃN���X�ł�(private�ł�)���R�ɃA�N�Z�X�ł���Ƃ�������
friend class TaskIterator;
private:
	Task *Prev,*Next;
	void *operator new(size_t n){}		//new���Z�q�̃I�[�o�[���[�h�B�f�t�H���g��new�̖�����
	void operator delete(void *p){}		//delete���Z�q�̃I�[�o�[���[�h�B�f�t�H���g��delete�̖�����
public:
	Task(TaskList *List);				//�R���X�g���N�^
	virtual ~Task(void);				//�f�X�g���N�^
};

//�^�X�N���X�g�i�^�X�N�̊Ǘ����j=============================================================================
class TaskList{
friend class Task;
friend class TaskIterator;
private:
	char *Buffer;
	Task *ActiveTask,*FreeTask;
	size_t TaskSize,TaskCount;

	Task *GetTask(size_t i);			//�^�X�N�Q��

public:
	TaskList(size_t size,size_t count);//�R���X�g���N�^
	~TaskList(void);					//�f�X�g���N�^

	void *New(size_t size);				//new���I�[�o�[���C�h
	void Delete(void *p);				//delete���I�[�o�[���C�h
};

//�^�X�N�C�e���[�^�i���X�g�̊Ǘ����j=========================================================================
class TaskIterator{
friend class Task;
friend class TaskList;
private:
	TaskList *List;
	Task *task;
public:
	TaskIterator(TaskList *List);		//�R���X�g���N�^
	bool HasNext(void);					//���̃��X�g�ɔ��
	Task *Next(void);					//���̃��X�g
	void Remove(void);					//�폜

};
//�O���[�o���֐�=============================================================================================
extern TaskList* MyShipList;
extern TaskList* EnemyList;
extern TaskList* MyBulletList;
extern TaskList* EnemyBulletList;
extern int Result;						//����
extern bool EndShooting;				//����
#endif