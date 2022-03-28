#include"DxLib.h"
#include"Object.h"
#define PI 3.14159265																		//�~�����΂��`

Object::Object(TaskList *List)
:	Task(List)
{}

void Object::Draw(void){																	//�`�揈��
	int object_x,object_y,x_buffer,y_buffer;
	GetGraphSize(Pic,&x_buffer,&y_buffer);
	object_x=(x+1)*Disp_Height/2-x_buffer/2;
	object_y=(y+1)*Disp_Width/2-y_buffer/2;
	DrawGraph(object_x,object_y,Pic,TRUE);
}
void Object::Alive_Judge(Object *object){													//�����蔻��
	int x_buffer,y_buffer,object_circle,bullet_circle;
	int x_object,y_object,bullet_x,bullet_y;												//bullet_x,bullet_y�͒e�̔���ɂ悭���������ŁA�{���͈Ⴄ���ɂ��g���B
	x_object=(x+1)*Disp_Height/2;
	y_object=(y+1)*Disp_Width/2;
	bullet_x=(object->x+1)*Disp_Height/2;
	bullet_y=(object->y+1)*Disp_Width/2;

	GetGraphSize(Pic,&x_buffer,&y_buffer);													//���̂̒��S���v�Z
	object_circle=x_buffer/2*x_buffer/2+y_buffer/2+y_buffer/2;

	GetGraphSize(object->Pic,&x_buffer,&y_buffer);											//�e�ۂ̒��S���v�Z
	bullet_circle=x_buffer/2*x_buffer/2+y_buffer/2+y_buffer/2;

	if((x_object-bullet_x)*(x_object-bullet_x)+
					(y_object-bullet_y)*(y_object-bullet_y)<object_circle+bullet_circle){	//�����蔻��
		hp--;
		object->hp--;
	}
}
//���̓����蔻��́A�~���g�p���Ă��܂��B