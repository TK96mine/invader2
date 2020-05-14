//アサートの定義
#ifdef _DEBUG
#define AST() {\
	CHAR ast_msg[256];\
	wsprintf(ast_msg, "%s %d行目\0", __FILE__, __LINE__);\
	MessageBox(0, ast_msg, "アサート表示", MB_OK);\
	}
#else
#define AST()
#endif

//定数
#define SCREEN_SIZE_X 800	//画面の横ｻｲｽﾞ
#define SCREEN_SIZE_Y 600	//画面の縦ｻｲｽﾞ

#define GAME_SIZE_X 640	//ゲーム画面の横サイズ
#define GAME_SIZE_Y 480	//ゲーム画面の縦サイズ

#define GAME_OFFSET_X 20	//ゲーム画面の横オフセット
#define GAME_OFFSET_Y 20	//ゲーム画面の縦オフセット

#define ESHOT_X 16		//敵の弾のX座標
#define ESHOT_Y 25		//敵の弾のY座標

#define ENEMY_SIZE_X 48		//敵の横ｻｲｽﾞ
#define ENEMY_SIZE_Y 32		//敵の縦ｻｲｽﾞ
#define ENEMY_DEF_SPEED 5	//敵のｽﾋﾟｰﾄﾞ

#define PSHOT_SIZE_X 6		//弾の横ｻｲｽﾞ(自機）
#define PSHOT_SIZE_Y 30		//弾の縦ｻｲｽﾞ(自機）
#define PSHOT_DEF_SPEED	5	//弾のｽﾋﾟｰﾄﾞ(自機）

#define ENEMY_SHOT_MAX 50	//敵弾の数
#define ESHOT_SIZE_X 16		//弾の横ｻｲｽﾞ(敵）
#define ESHOT_SIZE_Y 25		//弾の縦ｻｲｽﾞ(敵）
#define ESHOT_DEF_SPEED 5	//弾のｽﾋﾟｰﾄﾞ(敵）
#define ESHOT_MAX 50	//敵弾の数
#define ENEMY_POINT 200			//敵スコア得点数

#define ENEMY_X 5			//敵の横の数
#define ENEMY_Y 5			//敵の縦の数
#define ENEMY_MAX  24	//敵の最大数

#define BAKU_SIZE_X 96	//爆発の横サイズ
#define BAKU_SIZE_Y 96	//爆発の縦サイズ
#define BAKU_ANI 24	//爆発のアニメーション数

#define GAMEOVER_SIZE_X 452	//ゲームオーバーの横サイズ
#define GAMEOVER_SIZE_Y 123	//ゲームオーバーの縦サイズ
#define GAMEOVER_BGSIZE_X 640	//ゲームオーバー背景の横サイズ
#define GAMEOVER_BGSIZE_Y 320	//ゲームオーバー背景の縦サイズ


#define GAMETITLE_SIZE_X 423	//ゲームのタイトルの横サイズ
#define GAMETITLE_SIZE_Y 198	//ゲームのタイトルの縦サイズ

#define ENEMY_SHOT_MAX 50	//敵の弾の最大数
#define ENEMY_ANI_MAX	2	//敵のアニメーションする画像数

#define GAME_SCREEN_X 20	//ゲーム画面の描画オフセット
#define GAME_SCREEN_Y 50	//ゲーム画面の描画オフセット
#define GAME_SCREEN_SIZE_X 600	//ゲーム画面の横サイズ
#define GAME_SCREEN_SIZE_Y 500	//ゲーム画面の縦サイズ


//列挙型の定義
//ゲームシーン用
enum SCENE		
{
	SCENE_INIT,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_CLEAR,
	SCENE_GAMEOVER,
	SCENE_MAX
};

//構造体
struct XY
{
	int x;
	int y;
};


//プロトタイプ宣言

//初期化
bool SystemInit(void);	//変数
void InitScene(void);	//シーン

//シーン用
void TitleScene(void);	//タイトル
void Gamescene(void);	//ゲーム
void GameOverScene(void);	//ゲームオーバー
void GameClear(void);	//ゲームクリア

//当たり判定
void HitObj(void);	//当たり判定

//画像の描画用
void gameDraw(void);	//画像の描画

//共通の画面レイアウト
void gameDraw(void);	//画像の描画

/*
//プレイヤーの死亡用
void playerDeathProc(void);
*/

