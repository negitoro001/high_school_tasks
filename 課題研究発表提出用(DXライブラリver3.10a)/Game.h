#ifndef GAME_H										//インクルードガード
#define GAME_H										//インクルードガード
#include"ShootingGame.h"
#include"Stage1-1_Novel.h"
#include"Invariable_FPS.h"
class Game{
public:
	bool compulsion_shut_down;						//強制終了
	bool Change;									//チェンジフラグ
	int EpisodeNum;									//EP番号
	bool ShootingMode;								//シューティングモード
	ShootingGame *shooting;							//宣言(シューティング)
	Novel_Base *novel;								//宣言(ノベル)
	Game(bool ContinueMode);						//コンストラクタ
	void Play(void);								//実行処理
	~Game(void);									//デストラクタ
};
#endif												//インクルードガード