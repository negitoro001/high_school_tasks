#include"Novel_Base_Class.h"
#include"DxLib.h"
#include<stdio.h>

Novel_Base::Novel_Base(void){												//コンストラクタ
	Novel_Chapter_end=FALSE;
	write_line=0;
	write_len=0;
	string_len=0;
	Novel_StopFlag=FALSE;
	Ontinuation_PreventFlag=FALSE;
	Change_Picture_Flag=FALSE;
	FontHandle=CreateFontToHandle("ＭＳ ゴシック",
		18,3,DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	fps=new FPS();
	LineNumber=0;
	Timer=0;

}

bool Novel_Base::isJapaneseCharacter(unsigned char code){					//日本語判定
	if( (code >= 0x81 && code <= 0x9F) || (code >= 0xE0 && code <= 0xFC) ) {
		return TRUE;
	}
	return FALSE;
}
void Novel_Base::Disp_Output(void){											//文字表示部
	int disp_len,disp_line,z;
	int color=GetColor(255,255,255);
	disp_line=0;disp_len=0;
	for(z=0;z<string_len;z++){
		if(isJapaneseCharacter(buffer[disp_line][disp_len])==TRUE){
			DrawFormatStringToHandle(10+disp_len*10,390+disp_line*20,color,FontHandle,
				"%c%c",buffer[disp_line][disp_len],buffer[disp_line][disp_len+1]);

			disp_len+=2;z++;
		}
		else{
			DrawFormatStringToHandle(10+disp_len*10,390+disp_line*20,
				color,FontHandle,"%c",buffer[disp_line][disp_len]);

			disp_len++;
		}
		if(disp_len>=49){
			disp_line++;
			disp_len=0;
		}
	}
}
int Novel_Base::Char_Loader(void){											//キャラクターを読み込む
	int i;
	char Select_Picture[10];
	i=0;
	while(1){
		Select_Picture[i]=FileRead_getc(TextNote);
		if(Select_Picture[i]=='.')break;
		i++;
	}
	return atoi(Select_Picture);
}
void Novel_Base::Main_String_Method(void){									//文字を読み込む
	if(isJapaneseCharacter(temp_copy[string_len])==TRUE){
		buffer[write_line][write_len]=temp_copy[string_len];
		string_len++;
		write_len++;
		buffer[write_line][write_len]=temp_copy[string_len];
		string_len++;
		write_len++;
	}
	else if(temp_copy[string_len]==0){
		Novel_StopFlag=TRUE;
	}
	else if(temp_copy[string_len]=='/'){
		Novel_Chapter_end=TRUE;
	}
	else{
		buffer[write_line][write_len]=temp_copy[string_len];
		string_len++;
		write_len++;
	}

	if(write_len>=49){
		write_line++;
		write_len=0;
	}
}
void Novel_Base::Key_Input_Method(void){									//キー入力処理
	if(Novel_StopFlag==FALSE && Ontinuation_PreventFlag==FALSE &&
		(CheckHitKey(KEY_INPUT_RETURN)==1 || CheckHitKey(KEY_INPUT_SPACE)==1)){

		Ontinuation_PreventFlag=TRUE;
		while(Novel_StopFlag!=TRUE && Novel_Chapter_end!=TRUE){
			Main_String_Method();
		}
	}
	if(Novel_StopFlag==TRUE && Ontinuation_PreventFlag==TRUE && 
		(CheckHitKey(KEY_INPUT_RETURN)==0 && CheckHitKey(KEY_INPUT_SPACE)==0)){

		Ontinuation_PreventFlag=FALSE;
	}
	if(Novel_StopFlag==TRUE && Ontinuation_PreventFlag==FALSE &&
		(CheckHitKey(KEY_INPUT_RETURN)==1 || CheckHitKey(KEY_INPUT_SPACE)==1)){

		Novel_StopFlag=FALSE;
		Ontinuation_PreventFlag=TRUE;
		Registry=Char_Picture;
		Char_Picture=Char_Loader();
		FileRead_gets(temp_copy,256,TextNote);
		write_line=0;
		write_len=0;
		string_len=0;
		LineNumber++;
		if(Registry!=Char_Picture)Change_Picture_Flag=TRUE;					//写真変更処理実行
	}
	if(Novel_StopFlag==FALSE && Ontinuation_PreventFlag==TRUE && 
		(CheckHitKey(KEY_INPUT_RETURN)==0 && CheckHitKey(KEY_INPUT_SPACE)==0)){

		Ontinuation_PreventFlag=FALSE;
	}
}
Novel_Base::~Novel_Base(void){												//デストラクタ
	DeleteFontToHandle(FontHandle);
	InitGraph();															//画像を全部削除
}
void Novel_Base::Move(void){
	while(ProcessMessage()==0 && ClearDrawScreen()==0 &&
		CheckHitKey(KEY_INPUT_ESCAPE)==0){

		fps->measurement();
		if(Novel_StopFlag==FALSE && Timer%15==0){
			Main_String_Method();
		}
		Key_Input_Method();
		if(Change_Picture_Flag==TRUE) Picture_Fade_In_Out();
		Novel_Picture();
		Disp_Output();
		Timer++;
		if(Timer<=255) SetDrawBright(Timer,Timer,Timer);
		ScreenFlip();
		fps->Wait();
		if(Novel_Chapter_end==TRUE){
			WaitKey();
			break;
		}
	}
}
//==========================================================================セーブデータ管理部
void Method(void){
	FILE *fp=fopen("セーブデータ.dat","rb");								//バイナリファイルを開く
	fread( &Data_r, sizeof(Data_r), 1, fp );								//SaveData構造体の中身を入力
	fclose(fp);																//ファイルを閉じる
}
void Method(int EpisodeNumber,int Data){
	SaveData_w Data_w={EpisodeNumber,Data};
	FILE *fp=fopen("セーブデータ.dat","wb");								//バイナリファイルを開く
	fwrite( &Data_w, sizeof(Data_w), 1, fp );								//SaveData構造体の中身を出力
	fclose(fp);																//ファイルを閉じる
}
//グローバル変数
SaveData_r Data_r;
SaveData_w Data_w;