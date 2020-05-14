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
			if (EnemyFlag[y][x] == true && PlayerFlag == true)
			{
				if (EnemyPosX[y][x] + ENEMY_SIZE_X >= PlayerPosX
					&& EnemyPosX[y][x] <= PlayerPosX + PLAYER_SIZE_X
					&& EnemyPosY[y][x] + ENEMY_SIZE_Y >= PlayerPosY
					&& EnemyPosY[y][x] <= PlayerPosY + PLAYER_SIZE_Y)
				{
					PlayerFlag = false;
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
		if (EShotFlag[e] == true && PlayerFlag == true)
		{

			if (EShotPosX[e] + ESHOT_SIZE_X >= PlayerPosX
				&& EShotPosX[e] <= PlayerPosX + PLAYER_SIZE_X
				&& EShotPosY[e] + ESHOT_SIZE_Y >= PlayerPosY
				&& EShotPosY[e] <= PlayerPosY + PLAYER_SIZE_Y)
			{
				EShotFlag[e] = false;
				PlayerFlag = false;
				PlayerFlag = true;
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
	PlayerLife--;

	if (PlayerLife > 0)
	{
		if (PlayerFlag == false)
		{

			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					EnemyPosX[y][x] = ((ENEMY_SIZE_X * 10) / 7) * x;
					EnemyPosY[y][x] = (ENEMY_SIZE_Y * 9 / 7) * y;
					enemyType[y][x] = (ENEMY_TYPE)((y % (ENEMY_TYPE_MAX - 1)) + 1);
				}
			}
			PlayerFlag = true;
		}
	}

	if (PlayerLife <= 0)
	{
		systemScene = SCENE_GAMEOVER;		// 残機がない場合、ｹﾞｰﾑｵｰﾊﾞｰにする
	}
}

void PlayerGameDraw(void)
{
	//残機数を表示
	DrawFormatString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 300, 0xFFFFFF, "PLAYER = %d", PlayerLife);

	//プレイヤーの位置表示
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYER = ( %d, %d)", PlayerPosX, PlayerPosY);

	//プレイヤーの残機表示
	for (int p = 0; p < PlayerLife; p++)
	{
		DrawGraph((GAME_SIZE_X + 20) + 40 * (p % 3), (SCREEN_SIZE_Y - 80) - PLAYER_SIZE_Y * ((p / 3) + 1), PlayerImage[PLAYER_STYLE_FRONT][0], true);
	}

	//プレイヤーの表示
	if (PlayerFlag == true)
	{
		if (playerAniCnt % 60 <= 30)
		{
			for (int x = 0; x < PLAYER_ANI_MAX; x++)
			{
				DrawGraph(PlayerPosX + GAME_OFFSET_X, (GAME_SIZE_Y + GAME_OFFSET_Y) - PLAYER_SIZE_Y, PlayerImage[PLAYER_STYLE_BACK][0], true);
			}
		}
		else
		{
			DrawGraph(PlayerPosX + GAME_OFFSET_X, (GAME_SIZE_Y + GAME_OFFSET_Y) - PLAYER_SIZE_Y, PlayerImage[PLAYER_STYLE_BACK][1], true);
		}
	}
}


