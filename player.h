//定数
#define PLAYER_SIZE_X 48	//ﾌﾟﾚｲﾔｰの横ｻｲｽﾞ
#define PLAYER_SIZE_Y 48	//ﾌﾟﾚｲﾔｰの縦ｻｲｽﾞ
#define PLAYER_DEF_SPEED 2	//ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
#define PLAYER_DEF_LIFE 5	//プレイヤーのデフォルトのライフ
#define PLAYER_ANI_MAX 2	//プレイヤーのアニメーションする画像数

//列挙型
//プレイヤーの向き
enum PLAYER_STYLE
{
	PLAYER_STYLE_BACK,
	PLAYER_STYLE_FRONT,
	PLAYER_STYLE_MAX
};

//構造体



//プロトタイプ宣言
//プレイヤーの画像読み込み専用
void PlayerSystemInit(void);	

//プレイヤーの変数の初期化用
void PlayerGameInit(void);	

//プレイヤーの移動等の処理用
void PlayerControl(void);	

//プレイヤーが敵に当たった時の処理
void PlayerHitEnemy(void);

//プレイヤーが敵の弾に当たった時の処理
void PlayerHitEShot(void);

//プレイヤーを無敵にするための関数
void Muteki(void);

//プレイヤーのゲームオーバー用
bool PlayerDeathProc(void);

//プレイヤーのゲーム終了時のスコア
void PlayerEndScore(void);

//プレイヤーの描画用
void PlayerGameDraw(void);	//ゲーム中
void PlayerCliarDraw(void);	//ゲームクリア
void PlayerGameOverDraw(void);	//ゲームオーバー



