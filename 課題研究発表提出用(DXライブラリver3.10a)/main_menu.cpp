#include"main_menu.h"
#include"DxLib.h"

Menu::Menu(int lenth,char *string){								//インスタンス生成
	x=170;
	y=100+lenth;
	Font=CreateFontToHandle("ＭＳ ゴシック",40,8,DX_FONTTYPE_ANTIALIASING_8X8);
	CurrentFont=CreateFontToHandle("ＭＳ 明朝",50,8,DX_FONTTYPE_ANTIALIASING_8X8);
	White=GetColor(0,150,255);
	this->string=string;
}

void Menu::PutMenu(bool Flag){									//描画処理
	if(Flag==TRUE)DrawStringToHandle(x,y,string,White,Font);
	else DrawStringToHandle(x,y,string,White,CurrentFont);

}

MainMenu::MainMenu(void){										//コンストラクタ
	maindisp[0]=new Menu(0,"START");							//START
	maindisp[1]=new Menu(50,"CONTINUE(1)");						//CONTINUE(1)
	maindisp[2]=new Menu(100,"CONTINNUE(2)");					//CONTINUE(2)
	maindisp[3]=new Menu(150,"OPTION");							//OPTION
	maindisp[4]=new Menu(200,"EXIT");							//EXIT
	back_pic=LoadGraph("logo.bmp");
	mainmenu_flag=FALSE;stopflag=FALSE;
	White=GetColor(0,0,255);y=100;
	fps=new FPS();
	SetDrawBright(0,0,0);
	Timer=0;
}

Menu::~Menu(void){											//デストラクタ
	InitFontToHandle();

}
int MainMenu::Main_Menu(void){
	while(ProcessMessage()==0 && ClearDrawScreen()==0 &&
			CheckHitKey(KEY_INPUT_ESCAPE)==0){
		fps->measurement();
		DrawGraph(0,0,back_pic,FALSE);							//背景
		MainMenu::MainMenu_Input_Key();							//入力処理
		for(int i=0;i<5;i++){
			if(y/50-2==i) maindisp[i]->PutMenu(FALSE);
			else maindisp[i]->PutMenu(TRUE);					//表示（パーツ）
		}
		if(mainmenu_flag==TRUE){								//選択した後、作ったMENUを削除し、メモリを解放
			selecter=y/50-2;									//どれに選択したか
		}
		Timer+=5;
		if(mainmenu_flag==TRUE)break;
		ScreenFlip();
		fps->Wait();
		if(Timer<=255) SetDrawBright(Timer,Timer,Timer);
	}
	return selecter;
}

void MainMenu::MainMenu_Input_Key(void){						//入力処理
	if(CheckHitKey(KEY_INPUT_RETURN)==1 ||
		CheckHitKey(KEY_INPUT_SPACE)==1) mainmenu_flag=TRUE;

	if(stopflag==FALSE){
		if(CheckHitKey(KEY_INPUT_UP)==1) y-=50;
		if(CheckHitKey(KEY_INPUT_DOWN)==1) y+=50;
	}
	if(CheckHitKey(KEY_INPUT_UP)==1 ||
		CheckHitKey(KEY_INPUT_DOWN)==1) stopflag=TRUE;

	if(CheckHitKey(KEY_INPUT_UP)==0 &&
		CheckHitKey(KEY_INPUT_DOWN)==0) stopflag=FALSE;
	if(y>300) y=100;
	if(y<100) y=300;
}
MainMenu::~MainMenu(void){
	for(int i=0;i<255;i+=5){									//画面をフェードアウト
		SetDrawBright(255-i,255-i,255-i);
		for(int a=0;a<5;a++) maindisp[a]->PutMenu(TRUE);
		DrawGraph(0,0,back_pic,TRUE);
		ScreenFlip();
	}
	for(int a=0;a<5;a++) delete maindisp[a];
}