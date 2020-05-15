#include"DxLib.h"
#include"main.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"score.h"

//変数
int enemyImage[ENEMY_TYPE_MAX][ENEMY_ANI_MAX];	//敵の画像格納用
CHARACTER enemy[ENEMY_Y][ENEMY_X];	//敵のポジション
MOVE_MODE enemyMoveMode;	//敵の移動モード
MOVE_LR enemyMoveX;	//敵の横軸移動
ENEMY_TYPE enemyType[ENEMY_Y][ENEMY_X];	//敵の種類
int enemyCount;	//敵の数
int enemyAddSpeed;	//敵機の移動速度に加える速度
int enemyMoveCnt;	//敵の移動用カウンター
int estringCnt;	//敵用表示文字の点滅用カウンター
int estringFlag;	//敵が半数切った際に文字表示するためのフラグ


void EnemySystemInit(void)
{
	LoadDivGraph("image/cellien.png", ENEMY_TYPE_MAX * ENEMY_ANI_MAX, ENEMY_ANI_MAX, ENEMY_TYPE_MAX, ENEMY_SIZE_X, ENEMY_SIZE_Y, enemyImage[0]);
}

void EnemyGameInit(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			enemy[y][x].pos.x = ((ENEMY_SIZE_X * 10) / 7) * x;
			enemy[y][x].pos.y = (ENEMY_SIZE_Y * 9 / 7) * y;
			enemyType[y][x] = (ENEMY_TYPE)((y % (ENEMY_TYPE_MAX - 1)) + 1);
			enemy[y][x].flag = true;
			enemy[y][x].speed = ENEMY_DEF_SPEED;
		}
	}
	enemy[2][3].flag = false;
	enemyAddSpeed = 5;
	enemyMoveMode = MOVE_MODE_LR;
	enemyMoveX = MOVE_LR_RIGHT;
	enemyCount = ENEMY_MAX;
	enemyMoveCnt = 0;
}

//敵の移動処理
void EnemyControl(void)
{
	int enemyPosXMax;
	int enemyPosXMin;

	enemyPosXMin = GAME_SIZE_X;
	enemyPosXMax = 0;

	enemyMoveCnt++;

	if (enemyCount < ENEMY_MAX / 2)
	{
		if (enemyMoveCnt % 30 == 0 || enemyMoveCnt % 30 == 15)
		{
			//移動処理
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemy[y][x].flag)
					{
						//-----敵の移動処理
						//横移動
						if (enemyMoveMode == MOVE_MODE_LR)
						{
							if (enemyMoveX == MOVE_LR_RIGHT)
							{
								enemy[y][x].pos.x += (enemy[y][x].speed + enemyAddSpeed);
							}
							else if (enemyMoveX == MOVE_LR_LEFT)
							{
								enemy[y][x].pos.x -= (enemy[y][x].speed + enemyAddSpeed);
							}
						}

						//縦移動
						if (enemyMoveMode == MOVE_MODE_DOWN)
						{
							enemy[y][x].pos.y += ENEMY_SIZE_Y;
						}

					}
				}
			}
		}
	}
	else
	{
		if (enemyMoveCnt % 60 == 0 || enemyMoveCnt % 60 == 30)
		{
			//移動処理
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemy[y][x].flag)
					{
						//-----敵の移動処理
						//横移動
						if (enemyMoveMode == MOVE_MODE_LR)
						{
							if (enemyMoveX == MOVE_LR_RIGHT)
							{
								enemy[y][x].pos.x += enemy[y][x].speed;
							}
							else if (enemyMoveX == MOVE_LR_LEFT)
							{
								enemy[y][x].pos.x -= enemy[y][x].speed;
							}
						}

						//縦移動
						if (enemyMoveMode == MOVE_MODE_DOWN)
						{
							enemy[y][x].pos.y += ENEMY_SIZE_Y;
						}

					}
				}
			}
		}
	}

	//MinとMaxを計算する
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (enemy[y][x].flag)
			{
				//-----敵の移動制限
				if (enemyPosXMin > enemy[y][x].pos.x)
				{
					enemyPosXMin = enemy[y][x].pos.x;
				}

				if (enemyPosXMax < enemy[y][x].pos.x)
				{
					enemyPosXMax = enemy[y][x].pos.x;
				}
			}
		}
	}

	//移動方向を判断する
	if (enemyMoveMode == MOVE_MODE_DOWN)
	{
		enemyMoveMode = MOVE_MODE_LR;
	}
	else
	{
		if (enemyPosXMax > GAME_SIZE_X - ENEMY_SIZE_X)
		{
			enemyMoveMode = MOVE_MODE_DOWN;
			enemyMoveX = MOVE_LR_LEFT;
		}

		if (enemyPosXMin < 0)
		{
			enemyMoveMode = MOVE_MODE_DOWN;
			enemyMoveX = MOVE_LR_RIGHT;
		}
	}

	//弾の発射
	for (int x = 0; x < ENEMY_X; x++)
	{
		for (int y = ENEMY_Y - 1; y >= 0; y--)	//1番プレイヤーに近い(1番下の)生存している敵を除いた敵(敵の縦軸の数 - 1)を下から数えていく
		{
			EnemyShotControl(enemy[y][x].pos,enemy[y][x].flag,enemyCount);
		}
	}
}

bool PlayerCheckHitEnemy(XY playerPos,bool playerFlag)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//敵と自機との当たり判定
			if (enemy[y][x].flag == true && playerFlag == true)
			{
				if (enemy[y][x].pos.x + ENEMY_SIZE_X >= playerPos.x
					&& enemy[y][x].pos.x <= playerPos.x + PLAYER_SIZE_X
					&& enemy[y][x].pos.y + ENEMY_SIZE_Y >= playerPos.y
					&& enemy[y][x].pos.y <= playerPos.y + PLAYER_SIZE_Y)
				{
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

void EnemyHitObj(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (EnemyCheckHitObj(enemy[y][x].pos,enemy[y][x].flag) == true)
			{
				enemy[y][x].flag = false;
				AddScore(100);
				enemyCount--;

				/*
				if (enemyCount == 0 && player.life > 0)
				{
					systemScene = SCENE_CLEAR;
				}
				*/
			}
		}
	}
}

void ResetEnemyPos(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			enemy[y][x].pos.x = ((ENEMY_SIZE_X * 10) / 7) * x;
			enemy[y][x].pos.y = (ENEMY_SIZE_Y * 9 / 7) * y;
			enemy[y][x].type = (ENEMY_TYPE)((y % (ENEMY_TYPE_MAX - 1)) + 1);
		}
	}
}

void EnemyGameDraw(void)
{
	//敵の表示
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (enemy[y][x].flag == true)
			{
				DrawGraph(enemy[y][x].pos.x + GAME_OFFSET_X, enemy[y][x].pos.y + GAME_OFFSET_Y, enemyImage[enemyType[y][x]][0], true);
			}
		}
	}

	//敵機が半数を切った時の表示
	if (enemyCount < ENEMY_MAX / 2)
	{
		estringCnt ++;

		if (estringCnt > 120)
		{
			estringFlag = false;
		}
		else
		{
			estringFlag = true;
		}

		if (estringFlag == true)
		{
			if (estringCnt != 0 && (estringCnt / 20) % 2 == 0)
			{
				DrawString((SCREEN_SIZE_X / 2) - 120, (SCREEN_SIZE_Y / 2) - 20, "W  A  R  N  I  N  G", 0xFF0000);
			}
		}
	}
}