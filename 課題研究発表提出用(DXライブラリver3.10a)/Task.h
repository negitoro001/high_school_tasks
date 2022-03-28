#ifndef TASK_H							//インクルードガード
#define TASK_H

//この部分は一部関数を変えただけで、参考書のパクリです。入力は自分でやりました

//タスク本体================================================================================================
class Task{
friend class TaskList;					//friendはどんなクラスでも(privateでも)自由にアクセスできるというもの
friend class TaskIterator;
private:
	Task *Prev,*Next;
	void *operator new(size_t n){}		//new演算子のオーバーロード。デフォルトのnewの無効化
	void operator delete(void *p){}		//delete演算子のオーバーロード。デフォルトのdeleteの無効化
public:
	Task(TaskList *List);				//コンストラクタ
	virtual ~Task(void);				//デストラクタ
};

//タスクリスト（タスクの管理部）=============================================================================
class TaskList{
friend class Task;
friend class TaskIterator;
private:
	char *Buffer;
	Task *ActiveTask,*FreeTask;
	size_t TaskSize,TaskCount;

	Task *GetTask(size_t i);			//タスク参照

public:
	TaskList(size_t size,size_t count);//コンストラクタ
	~TaskList(void);					//デストラクタ

	void *New(size_t size);				//newをオーバーライド
	void Delete(void *p);				//deleteをオーバーライド
};

//タスクイテレータ（リストの管理部）=========================================================================
class TaskIterator{
friend class Task;
friend class TaskList;
private:
	TaskList *List;
	Task *task;
public:
	TaskIterator(TaskList *List);		//コンストラクタ
	bool HasNext(void);					//次のリストに飛ぶ
	Task *Next(void);					//次のリスト
	void Remove(void);					//削除

};
//グローバル関数=============================================================================================
extern TaskList* MyShipList;
extern TaskList* EnemyList;
extern TaskList* MyBulletList;
extern TaskList* EnemyBulletList;
extern int Result;						//仮設
extern bool EndShooting;				//仮設
#endif