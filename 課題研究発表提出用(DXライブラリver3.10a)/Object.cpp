#include"DxLib.h"
#include"Object.h"
#define PI 3.14159265																		//円周率πを定義

Object::Object(TaskList *List)
:	Task(List)
{}

void Object::Draw(void){																	//描画処理
	int object_x,object_y,x_buffer,y_buffer;
	GetGraphSize(Pic,&x_buffer,&y_buffer);
	object_x=(x+1)*Disp_Height/2-x_buffer/2;
	object_y=(y+1)*Disp_Width/2-y_buffer/2;
	DrawGraph(object_x,object_y,Pic,TRUE);
}
void Object::Alive_Judge(Object *object){													//当たり判定
	int x_buffer,y_buffer,object_circle,bullet_circle;
	int x_object,y_object,bullet_x,bullet_y;												//bullet_x,bullet_yは弾の判定によくつかうだけで、本当は違う時にも使う。
	x_object=(x+1)*Disp_Height/2;
	y_object=(y+1)*Disp_Width/2;
	bullet_x=(object->x+1)*Disp_Height/2;
	bullet_y=(object->y+1)*Disp_Width/2;

	GetGraphSize(Pic,&x_buffer,&y_buffer);													//物体の中心を計算
	object_circle=x_buffer/2*x_buffer/2+y_buffer/2+y_buffer/2;

	GetGraphSize(object->Pic,&x_buffer,&y_buffer);											//弾丸の中心を計算
	bullet_circle=x_buffer/2*x_buffer/2+y_buffer/2+y_buffer/2;

	if((x_object-bullet_x)*(x_object-bullet_x)+
					(y_object-bullet_y)*(y_object-bullet_y)<object_circle+bullet_circle){	//当たり判定
		hp--;
		object->hp--;
	}
}
//この当たり判定は、円を使用しています。