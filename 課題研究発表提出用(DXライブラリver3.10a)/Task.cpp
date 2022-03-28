#include"Task.h"
#include<stdio.h>
#include<assert.h>
#include"DxLib.h"

//タスクリスト
Task *TaskList::GetTask(size_t i){									//次のタスク参照
	return (Task *)(Buffer+TaskSize*i);
}

TaskList::TaskList(size_t size,size_t count)						//タスクリストのコンストラクタ
:	TaskSize(size),TaskCount(count)
{
	Buffer=new char[TaskSize*(TaskCount+2)];						//ダミータスクを確保するため

	//アクティブタスク初期化
	ActiveTask=GetTask(0);											//最初はダミータスク
	ActiveTask->Prev=ActiveTask->Next=ActiveTask;

	//フリータスク初期化
	FreeTask=GetTask(1);											//初期状態ではすべてのタスクがフリータスクリストに連結
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
	assert(size<=TaskSize);											//タスクの最大サイズを超えたときはエラーを出す（製品化するときには無視される）
	if(FreeTask->Next==FreeTask)return NULL;						//フリータスクが1個もないときはNULLを返す

	Task *task=FreeTask->Next;										//フリータスクリストからタスクを1個とりだす
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
//タスク
Task::Task(TaskList *List){											//コンストラクタ
	Prev=List->ActiveTask->Prev;
	Next=List->ActiveTask;
	Prev->Next=Next->Prev=this;
}

Task::~Task(void){
	Prev->Next=Next;
	Next->Prev=Prev;
}

//タスクイテレータ
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
//タスクイテレータのみ「task」というものを使用している。違いに注意が必要

TaskList* MyShipList;
TaskList* EnemyList;
TaskList* MyBulletList;
TaskList* EnemyBulletList;
int Result;															//仮設
bool EndShooting;													//仮設