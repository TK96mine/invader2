#include"DxLib.h"

#include"main.h"

#include"player.h"

//変数
int playerImage[PLAYER_STYLE_MAX][PLAYER_ANI_MAX];	//ﾌﾟﾚｲﾔｰの画像格納用
int playerPosX;		//ﾌﾟﾚｲﾔｰのX座標
int playerPosY;		//ﾌﾟﾚｲﾔｰのY座標
int playerSpeed;	//ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
bool playerFlag;		//ﾌﾟﾚｲﾔｰのﾌﾗｸﾞ
int playerLife;		//残機
int playerAniCnt;	//プレイヤーのアニメーション用カウンター

void PlayerSystemInit(void)
{
	//プレイヤー
	LoadDivGraph("image/serval.png", PLAYER_STYLE_MAX * PLAYER_ANI_MAX, PLAYER_ANI_MAX, PLAYER_STYLE_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage[0]);
}

void PlayerGameInit(void)
{
	playerPosX = (GAME_SIZE_X - PLAYER_SIZE_X) / 2;
	playerPosY = (GAME_SIZE_Y - PLAYER_SIZE_Y);
	playerSpeed = (PLAYER_DEF_SPEED);
	playerFlag = true;
	playerLife = PLAYER_DEF_LIFE;
}

//プレイヤーの処理
void PlayerControl(void)
{
	if (playerFlag == true)
	{
		//右移動
		if (CheckHitKey(KEY_INPUT_NUMPAD6))
		{
			if (playerPosX >= GAME_SIZE_X - PLAYER_SIZE_X)	//移動制限
			{
				playerPosX = GAME_SIZE_X - PLAYER_SIZE_X;
			}
			else
			{
				playerPosX += playerSpeed;
			}
		}
		//左移動
		if (CheckHitKey(KEY_INPUT_NUMPAD4))
		{
			if (playerPosX - playerSpeed <= 0    /*GAME_OFFSET_X*/)
			{
				playerPosX = 0;
			}
			else
			{
				playerPosX -= playerSpeed;
			}
		}
	}
}

bool PlayerCheckHitEnemy(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//敵と自機との当たり判定
			if (enemyFlag[y][x] == true && playerFlag == true)
			{
				if (enemyPosX[y][x] + ENEMY_SIZE_X >= playerPosX
					&& enemyPosX[y][x] <= playerPosX + PLAYER_SIZE_X
					&& enemyPosY[y][x] + ENEMY_SIZE_Y >= playerPosY
					&& enemyPosY[y][x] <= playerPosY + PLAYER_SIZE_Y)
				{
					playerFlag = false;
					PlayerDeathProc();

					if (playerLife > 0)
					{
						if (playerFlag == false)
						{

							for (int y = 0; y < ENEMY_Y; y++)
							{
								for (int x = 0; x < ENEMY_X; x++)
								{
									enemyPosX[y][x] = ((ENEMY_SIZE_X * 10) / 7) * x;
									enemyPosY[y][x] = (ENEMY_SIZE_Y * 9 / 7) * y;
									enemyType[y][x] = (ENEMY_TYPE)((y % (ENEMY_TYPE_MAX - 1)) + 1);
								}
							}
							playerFlag = true;
						}
					}

					return true;

					/*else if (PlayerLife == 0)
					{
						systemScene = SCENE_GAMEOVER;
					}*/
				}
			}
		}
	}

	return false;
}

//プレイヤーと敵の弾の当たり判定
bool PlayerCheckHitEShot(void)
{
	//敵の弾と自機との当たり判定
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShotFlag[e] == true && playerFlag == true)
		{

			if (eShotPosX[e] + ESHOT_SIZE_X >= elayerPosX
				&& eShotPosX[e] <= playerPosX + PLAYER_SIZE_X
				&& eShotPosY[e] + ESHOT_SIZE_Y >= playerPosY
				&& eShotPosY[e] <= playerPosY + PLAYER_SIZE_Y)
			{
				eShotFlag[e] = false;
				playerFlag = false;
				playerFlag = true;
				PlayerDeathProc();

				return true;
			}
		}
	}

	return false;
}

// 自機の減算処理
void PlayerDeathProc(void)
{
	playerLife--;

	if (playerLife <= 0)
	{
		systemScene = SCENE_GAMEOVER;		// 残機がない場合、ｹﾞｰﾑｵｰﾊﾞｰにする
	}
}

void PlayerGameDraw(void)
{
	//残機数を表示
	DrawFormatString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 300, 0xFFFFFF, "PLAYER = %d", playerLife);

	//プレイヤーの位置表示
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYER = ( %d, %d)", playerPosX, playerPosY);

	//プレイヤーの残機表示
	for (int p = 0; p < playerLife; p++)
	{
		DrawGraph((GAME_SIZE_X + 20) + 40 * (p % 3), (SCREEN_SIZE_Y - 80) - PLAYER_SIZE_Y * ((p / 3) + 1), playerImage[PLAYER_STYLE_FRONT][0], true);
	}

	//プレイヤーの表示
	if (playerFlag == true)
	{
		if (playerAniCnt % 60 <= 30)
		{
			for (int x = 0; x < PLAYER_ANI_MAX; x++)
			{
				DrawGraph(playerPosX + GAME_OFFSET_X, (GAME_SIZE_Y + GAME_OFFSET_Y) - PLAYER_SIZE_Y, playerImage[PLAYER_STYLE_BACK][0], true);
			}
		}
		else
		{
			DrawGraph(playerPosX + GAME_OFFSET_X, (GAME_SIZE_Y + GAME_OFFSET_Y) - PLAYER_SIZE_Y, playerImage[PLAYER_STYLE_BACK][1], true);
		}
	}
}


