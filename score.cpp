#include"Dxlib.h"

#include"main.h"

#include"player.h"

#include"enemy.h"

#include"score.h"

//変数の設定
int score[SCR_MAX];	//スコア保存用
int drawTextsCnt;	//表示するテキスト点滅用カウンター
bool addScr;	//プレイヤーの残機に応じたスコアの加算を行うためのフラグ


//スコアを初期化する
void InitScore(void)
{
	//ハイスコアの更新
	if (score[SCR_TOTAL] > score[SCR_HIGH])
	{
		score[SCR_HIGH] = score[SCR_TOTAL];
	}

	//変数の初期化
	score[SCR_TOTAL] = 0;
	score[SCR_PL1] = 0;
	drawTextsCnt = 0;
	addScr = false;
}

//スコアの加算処理
void AddScore(int num)
{
	//スコア処理
	score[SCR_PL1] += num;
}

void EndAddScore(int playerLife,int num)
{
	if (addScr == false)
	{
		score[SCR_PLAYER_NUM] += playerLife * num;
		score[SCR_TOTAL] = score[SCR_PLAYER_NUM] + score[SCR_PL1];
		addScr = true;
	}
	else
	{

	}
}

void DrawTexts(void)
{
	//プレイ中のスコア格納用
	int drawScore;	
	//表示する文字列の長さ格納用
	int drawLengh;	
	//文字の色(16進数)格納用
	int textColor = 0xFFFFFF;	

	//--ハイスコア--//
	//"HIGH SCORE"と表示する
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 70, "HIGH", textColor);
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 77, 90, "SCORE", textColor);

	//ハイスコアの上限を設定
	drawScore = (score[SCR_HIGH] >= 100000 ? 99999 : score[SCR_HIGH]);

	//表示するスコアの文字列の長さを調べる
	drawLengh = GetDrawFormatStringWidth("%d", drawScore);

	//プレイ中のスコアを表示する
	DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 100 - drawLengh, 120, textColor, "%d", score[SCR_HIGH]);

	//--スコア--//
	//"SCORE"と表示する
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 170, "SCORE", textColor);

	//スコアの上限を設定
	drawScore = (score[SCR_PL1] >= 100000 ? 99999 : score[SCR_PL1]);

	//表示するスコアの文字列の長さを調べる
	drawLengh = GetDrawFormatStringWidth("%d", drawScore);

	//スコアを表示する
	DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 100 - drawLengh, 200, textColor, "%d", drawScore);
}


//ゲームが終わった際に表示するスコア等の表示用
void EndGameDrawTexts(void)
{
	//テキスト用カウンターのカウントをする
	drawTextsCnt++;

	DrawFormatString((SCREEN_SIZE_X / 2) - 70, (SCREEN_SIZE_Y / 2) + 20, 0xFF00FF, "HIGH SCORE = %d", score[SCR_HIGH]);

	if (drawTextsCnt % 40 >= 20)
	{
		DrawFormatString((SCREEN_SIZE_X / 2) - 50, (SCREEN_SIZE_Y / 2) + 40, 0xFF00FF, "SCORE = %d", score[SCR_TOTAL]);
	}

	if (score[SCR_PL1] >= score[SCR_HIGH] && score[SCR_PL1] != 0)
	{
		if (drawTextsCnt % 60 <= 20)
		{
			DrawString((SCREEN_SIZE_X - 100) / 2, (SCREEN_SIZE_Y / 2) + 80, "'New Record' ", 0x00FFFF);
		}
	}
}

void PlayerCliarScoreDraw(int playerLife, int num)
{
	int e = LoseEnemyNum();
	int pCliarScore = PlayerAtackEnemyScore();

	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 40, 0x00FF00, "倒した機体数 : %d × score : %d = %d", e, num, pCliarScore);
	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 20, 0x00FF00, "playerlife : %d × score : %d = %d", playerLife, num, score[SCR_PLAYER_NUM]);
	DrawFormatString((SCREEN_SIZE_X / 2) - 250, SCREEN_SIZE_Y / 2, 0x00FF00, "Score : %d + プレイヤーの残りライフ分のスコア : %d = %d", score[SCR_PL1], score[SCR_PLAYER_NUM], score[SCR_TOTAL]);
}

void PlayerGameOverScoreDraw(int playerLife, int num)
{
	int e = LoseEnemyNum();
	int pLoseScore = PlayerAtackEnemyScore();

	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 40, 0x00FF00, "倒した機体数 : %d × score : %d = %d", e, num, pLoseScore);
	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 20, 0x00FF00, "playerlife : %d × score : %d = %d", playerLife, num, score[SCR_PLAYER_NUM]);
	DrawFormatString((SCREEN_SIZE_X / 2) - 150, SCREEN_SIZE_Y / 2, 0x00FF00, "Score : %d + プレイヤーの残りライフ分のスコア : %d = %d", score[SCR_PL1], score[SCR_PLAYER_NUM], score[SCR_TOTAL]);
}

void PlayerAtackEnemyScore(int enemyCount)
{

}