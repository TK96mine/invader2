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

#define GAMETITLE_SIZE_X 423	//ゲームのタイトルの横サイズ
#define GAMETITLE_SIZE_Y 198	//ゲームのタイトルの縦サイズ

#define GAME_SIZE_X 640	//ゲーム画面の横サイズ
#define GAME_SIZE_Y 480	//ゲーム画面の縦サイズ
#define GAME_SCREEN_X 20	//ゲーム画面の描画オフセット
#define GAME_SCREEN_Y 50	//ゲーム画面の描画オフセット
#define GAME_SCREEN_SIZE_X 600	//ゲーム画面の横サイズ
#define GAME_SCREEN_SIZE_Y 500	//ゲーム画面の縦サイズ
#define GAME_OFFSET_X 20	//ゲーム画面の横オフセット
#define GAME_OFFSET_Y 20	//ゲーム画面の縦オフセット

#define GAMEOVER_SIZE_X 452	//ゲームオーバーの横サイズ
#define GAMEOVER_SIZE_Y 123	//ゲームオーバーの縦サイズ
#define GAMEOVER_BGSIZE_X 640	//ゲームオーバー背景の横サイズ
#define GAMEOVER_BGSIZE_Y 320	//ゲームオーバー背景の縦サイズ


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

struct CHARACTER
{
	XY pos;	//位置情報格納用
	int speed;	//移動量格納用
	bool flag;	//生存確認用
	int life;	//残り機体数
	int aniCnt;	//アニメーション用カウンター
	int type;	//種類
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

//画像の描画用
void gameDraw(void);	//画像の描画

//共通の画面レイアウト
void gameDraw(void);	//画像の描画

/*
//プレイヤーの死亡用
void playerDeathProc(void);
*/

