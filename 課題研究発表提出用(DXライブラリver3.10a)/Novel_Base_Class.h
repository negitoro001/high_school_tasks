#ifndef NOVEL_BASE_CLASS_H
#define NOVEL_BASE_CLASS_H
#include"Invariable_FPS.h"
#include<stdio.h>
#include<stdlib.h>
//====================================================シナリオのナンバリング定義
#define EP0_1 4										//シナリオ順的に、EP1_1が先に来るので、ナンバリングの順序にずれが生じている
#define EP0_2 5
#define EP0_3 6
#define EP1_1 1
#define EP1_2 2
#define EP1_3 3
#define EP2_1 7
#define EP2_2 8
#define EP2_3 9
#define EP3_1 10
#define EP3_2 11
#define EP3_3 12
#define EP4_1 13
#define EP4_2 14
#define EP4_3 15
//====================================================
class Novel_Base{
public:
	FPS *fps;										//宣言
	int FontHandle;									//ファイルハンドル
	int x,y;										//座標
	char string_len;								//読み込んだ文字数を数える
	char buffer[5][50];								//表示用に読み込む
	char temp_copy[256];							//txtファイルから読み込む
	int Char_Picture;								//画像選択
	int write_len,write_line;						//現在の読み込んでいる文字の場所
	int TextNote;									//txtを読み込む
	int Box;										//テキストボックス
	int Registry;									//一時保存用(画像の管理番号)
	bool Novel_Chapter_end;							//終了フラグ
	bool Novel_StopFlag;							//一時的に読み込むを止める処理
	bool Ontinuation_PreventFlag;					//連続的入力防止フラグ（1/60秒でループしてしまうことへの対処）
	bool Change_Picture_Flag;						//写真変更時のフラグ（写真の切り替えフェードイン・アウトに使用）
	int Timer;										//タイマー
	int LineNumber;									//行数カウンタ

	Novel_Base(void);								//コンストラクタ
	virtual ~Novel_Base(void);						//デストラクタ
	void Main_String_Method(void);					//文字処理
	int Char_Loader(void);							//キャラクターの画像を選択
	bool isJapaneseCharacter(unsigned char code);	//日本語判定
	void Disp_Output(void);							//文字表示部
	virtual void Novel_Picture(void)=0;				//純粋仮想関数（画像表示部）
	virtual void Picture_Fade_In_Out(void)=0;		//純粋仮想関数（画像のフェードイン・アウト）
	void Key_Input_Method(void);					//ノベルパートにおけるキー入力処理
	virtual void Move(void);						//本体処理
};
//==================================================セーブデータ管理部
void Method(void);									//ロード処理
void Method(int EpisodeNumber,int Data);			//セーブ処理
typedef struct{										//セーブデータ構造体
	int EpisodeNumber;								//エピソード番号
	int LineNumber;									//行数
}SaveData_w;
typedef struct{										//セーブデータ構造体
	int EpisodeNumber;								//エピソード番号
	int LineNumber;									//行数
}SaveData_r;

extern SaveData_r Data_r;							//グローバル変数
extern SaveData_w Data_w;							//グローバル変数
#endif
//ちなみにvirtual 関数=0;が純粋仮想関数だが
//これをするとこの基底クラスは抽象クラスということになる
//純粋仮想関数がひとつでもあれば、抽象クラスとなる
//派生クラスでかならず、純粋仮想関数を定義しなければならない（しないとエラー）