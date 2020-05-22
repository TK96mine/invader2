//---定数---//
#define HIGH_SCR_DEF 2500	//ハイスコアの上限
#define CLEAR_HIGH_SCORE 2500	//ゲームクリアした時の最大スコア

//---列挙型---//
//スコア用
enum SCORE
{
	SCR_PL1,
	SCR_HIGH,
	SCR_PLAYER_NUM,
	SCR_TOTAL,
	SCR_MAX
};

//---構造体---//

//---プロトタイプ宣言---//
//スコア用
void InitScore(void);	//スコアの初期化用
void AddScore(int num);	//スコア加算用
void EndAddScore(int playerLife,int num);	//クリア後にプレイヤーの残機に応じてスコアを追加する
void DrawTexts(void);	//スコア表示用
void EndGameDrawTexts(void);	//ゲームが終わった際に表示するテキスト表示用
void PlayerCliarScoreDraw(int playerLife, int num);	//プレイヤーのクリアしたときのスコア表示用
void PlayerGameOverScoreDraw(int playerLife, int num);	//プレイヤーがゲームオーバーになった時のスコア表示用