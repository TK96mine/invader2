//定数
#define ENEMY_DEF_SCORE 100	//敵一体につき加えるスコアのデフォルトの値

//列挙型
//敵の左右の移動用
enum MOVE_LR
{
	MOVE_LR_LEFT,
	MOVE_LR_RIGHT,
	MOVE_LR_MAX
};

//敵の上下の移動用
enum MOVE_MODE
{
	MOVE_MODE_LR,
	MOVE_MODE_DOWN,
	MOVE_MODE_MAX
};

//敵の種類
enum ENEMY_TYPE
{
	ENEMY_TYPE_NON,
	ENEMY_TYPE_RED,
	ENEMY_TYPE_BLUE,
	ENEMY_TYPE_GREEN,
	ENEMY_TYPE_ORANGE,
	ENEMY_TYPE_MAX
};


//構造体



//プロトタイプ宣言
void EnemySystemInit(void);	//敵の画像ロード用
void EnemyGameInit(void);	//敵の変数初期化用
void EnemyControl(void);	//敵の移動等の処理用
bool PlayerCheckHitEnemy(XY playerPos, bool playerFlag);	//プレイヤーと敵の当たり判定
void EnemyHitObj(void);		//敵と自機の弾が当たった時の処理
void ResetEnemyPos(void);	//プレイヤーと敵が当たった際に敵の位置を初期化する
bool PlayerClearCheck(void);	//プレイヤーがクリアしたか判定するための関数
int LoseEnemyNum(void);	//敵の倒した機体数を返り値として返す関数
int PlayerAtackEnemyScore(void);	//プレイヤーが倒した敵の数に応じたスコアの表示(返り値としてスコアの合計を返す(loseEnemyNum * score))
void EnemyGameDraw(void);	//敵のゲームシーンでの描画用
