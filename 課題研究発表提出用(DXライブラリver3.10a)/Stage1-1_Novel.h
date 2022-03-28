#ifndef STAGE1_1_NOVEL_H
#define STAGE1_1_NOVEL_H
#include"Novel_Base_Class.h"
#include"DxLib.h"

class Stage1_1_Novel : public Novel_Base{
public:
	int Back_Picture;															//背景
	int Char_Pic_1;
	int Char_Pic_2;
	Stage1_1_Novel(void){														//インスタンス生成
		Back_Picture=LoadGraph("STG_Back_Pictures/船内_.png");
		Char_Pic_1=LoadGraph("Char_Pic/Ep1/EP1_RE3004_.png");
		TextNote=FileRead_open("test.txt");
		Box=LoadGraph("box.png");
		Char_Picture=Char_Loader();
		FileRead_gets(temp_copy,256,TextNote);
	}
	Stage1_1_Novel(int LineNumber){												//コンストラクタのオーバーロード
		Back_Picture=LoadGraph("STG_Back_Pictures/船内_.png");
		Char_Pic_1=LoadGraph("sample-1.jpg");
		Char_Pic_2=LoadGraph("sample-2.jpg");
		TextNote=FileRead_open("test.txt");
		Box=LoadGraph("box.png");
		for(int i=0;i<LineNumber;i++) while(FileRead_getc(TextNote)!='\n');		//スキップ処理
		Char_Picture=Char_Loader();
		FileRead_gets(temp_copy,256,TextNote);
	}
	void Novel_Picture(void){													//表示部
		switch(Char_Picture){
		case 1:
			DrawGraph(0,0,Back_Picture,TRUE);
			DrawGraph(350,25,Char_Pic_1,TRUE);
			break;

		case 2:
			DrawGraph(0,0,Back_Picture,FALSE);
			DrawGraph(320,0,Char_Pic_2,TRUE);
			break;
		}
		DrawGraph(0,350,Box,TRUE);
	}
	void Picture_Fade_In_Out(void){												//表示部の改良したものを書き込もう
		for(int i=0;i<=255;i+=5){
			ClearDrawScreen();
			switch(Registry){

			case 1:
				DrawGraph(0,0,Back_Picture,TRUE);
				SetDrawBright(255-i,255-i,255-i);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-i);
				DrawGraph(320,0,Char_Pic_1,TRUE);
				break;
			case 2:
				DrawGraph(0,0,Back_Picture,TRUE);
				SetDrawBright(255-i,255-i,255-i);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-i);
				DrawGraph(320,0,Char_Pic_2,TRUE);
				break;

			}
			SetDrawBright(i,i,i);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,i);
			switch(Char_Picture){
				
			case 1:
				DrawGraph(320,0,Char_Pic_1,TRUE);
				break;
			case 2:
				DrawGraph(320,0,Char_Pic_2,TRUE);
				break;
			}
			SetDrawBright(255,255,255);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			DrawGraph(0,350,Box,TRUE);
			ScreenFlip();
		}
		Change_Picture_Flag=FALSE;
		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
	~Stage1_1_Novel(void){														//デストラクタ
		if(Novel_Chapter_end==TRUE) Method(EP1_1,-1);
		else{
			Method(EP1_1,LineNumber);
			Novel_Base::~Novel_Base();
		}
		for(int i=255;i>=0;i-=5){
			ClearDrawScreen();
			Novel_Picture();
			SetDrawBright(i,i,i);
			ScreenFlip();
		}
	}
};
#endif