//---定数---//
#define HIGH_SCR_DEF 2500	//ハイスコアの上限
#define CLEAR_HIGH_SCORE 2500	//ゲームクリアした時の最大スコア

//---列挙型---//
//スコア用
enum SCORE
{
	SCR_PL1,
	SCR_HIGH,
	SCR_MAX
};

//---構造体---//

//---プロトタイプ宣言---//
//スコア用
void InitScore(void);	//スコアの初期化用
void AddScore(int num);	//スコア加算用
void DrawTexts(void);	//スコア表示用
void EndGameDrawTexts(void);	//ゲームが終わった際に表示するテキスト表示用