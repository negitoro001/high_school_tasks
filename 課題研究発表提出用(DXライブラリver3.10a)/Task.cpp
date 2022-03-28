#include"Task.h"
#include<stdio.h>
#include<assert.h>
#include"DxLib.h"

//�^�X�N���X�g
Task *TaskList::GetTask(size_t i){									//���̃^�X�N�Q��
	return (Task *)(Buffer+TaskSize*i);
}

TaskList::TaskList(size_t size,size_t count)						//�^�X�N���X�g�̃R���X�g���N�^
:	TaskSize(size),TaskCount(count)
{
	Buffer=new char[TaskSize*(TaskCount+2)];						//�_�~�[�^�X�N���m�ۂ��邽��

	//�A�N�e�B�u�^�X�N������
	ActiveTask=GetTask(0);											//�ŏ��̓_�~�[�^�X�N
	ActiveTask->Prev=ActiveTask->Next=ActiveTask;

	//�t���[�^�X�N������
	FreeTask=GetTask(1);											//������Ԃł͂��ׂẴ^�X�N���t���[�^�X�N���X�g�ɘA��
	for(size_t i=1;i<TaskCount+2;i++){
		GetTask(i)->Prev=NULL;
		GetTask(i)->Next=GetTask(i+1);
	}
	GetTask(TaskCount+1)->Next=FreeTask;
}
TaskList::~TaskList(void){
	delete [] Buffer;
}

void *TaskList::New(size_t size){
	assert(size<=TaskSize);											//�^�X�N�̍ő�T�C�Y�𒴂����Ƃ��̓G���[���o���i���i������Ƃ��ɂ͖��������j
	if(FreeTask->Next==FreeTask)return NULL;						//�t���[�^�X�N��1���Ȃ��Ƃ���NULL��Ԃ�

	Task *task=FreeTask->Next;										//�t���[�^�X�N���X�g����^�X�N��1�Ƃ肾��
	FreeTask->Next=task->Next;
	return task;
}

void TaskList::Delete(void *p){
	Task *task=(Task*)p;
	assert(task->Prev!=NULL);

	task->Prev=NULL;
	task->Next=FreeTask->Next;
	FreeTask->Next=task;
}
//�^�X�N
Task::Task(TaskList *List){											//�R���X�g���N�^
	Prev=List->ActiveTask->Prev;
	Next=List->ActiveTask;
	Prev->Next=Next->Prev=this;
}

Task::~Task(void){
	Prev->Next=Next;
	Next->Prev=Prev;
}

//�^�X�N�C�e���[�^
TaskIterator::TaskIterator(TaskList *List)
:	List(List),task(List->ActiveTask)
{}

bool TaskIterator::HasNext(void){
	return task->Next!=List->ActiveTask;
}

Task* TaskIterator::Next(void){
	return task=task->Next;
}

void TaskIterator::Remove(void){
	task=task->Prev;
	delete task->Next;
}
//�^�X�N�C�e���[�^�̂݁utask�v�Ƃ������̂��g�p���Ă���B�Ⴂ�ɒ��ӂ��K�v

TaskList* MyShipList;
TaskList* EnemyList;
TaskList* MyBulletList;
TaskList* EnemyBulletList;
int Result;															//����
bool EndShooting;													//����