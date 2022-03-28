#ifndef INVARIABLE_FPS_H
#define INVARIABLE_FPS_H

class Invariable_FPS{
	int StartTime;				//����J�n����
	int Count;					//�J�E���^
	float Fps;					//fps
	static const int COUNT=60;	//���ς����T���v����
	static const int FPS=60;	//�ݒ肵��FPS
public:
	Invariable_FPS(void);		//�R���X�g���N�^
	bool measurement(void);		//�v��
	void Wait(void);			//�ҋ@
};

typedef Invariable_FPS FPS;		//�uInvariable_FPS�v���uFPS�v�ɗ���

#endif