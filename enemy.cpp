#include"DxLib.h"
#include"main.h"
#include"enemy.h"
#include"score.h"

//変数
int enemyImage[ENEMY_TYPE_MAX][ENEMY_ANI_MAX];	//敵の画像格納用
int enemyPosX[ENEMY_Y][ENEMY_X];	//敵の横軸のポジション
int enemyPosY[ENEMY_Y][ENEMY_X];	//敵の縦軸のポジション
int enemySpeed;	//敵の移動速度
bool enemyFlag[ENEMY_Y][ENEMY_X];	//敵の生存確認用変数
MOVE_MODE enemyMoveMode;	//敵の移動モード
MOVE_LR enemyMoveX;	//敵の横軸移動
ENEMY_TYPE enemyType[ENEMY_Y][ENEMY_X];	//敵の種類
int enemyCount;	//敵の数
int enemyAddSpeed;	//敵機の移動速度に加える速度
int enemyMoveCnt;	//敵の移動用カウンター

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
			enemyPosX[y][x] = ((ENEMY_SIZE_X * 10) / 7) * x;
			enemyPosY[y][x] = (ENEMY_SIZE_Y * 9 / 7) * y;
			enemyType[y][x] = (ENEMY_TYPE)((y % (ENEMY_TYPE_MAX - 1)) + 1);
			enemyFlag[y][x] = true;
		}
	}

	enemyFlag[2][3] = false;
	enemySpeed = ENEMY_DEF_SPEED;
	enemyAddSpeed = 5;
	enemyMoveMode == MOVE_MODE_LR;
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

	if (enemyCount < ENEMY_MAX / 2)
	{
		if (enemyMoveCnt % 30 == 0 || enemyMoveCnt % 30 == 15)
		{
			//移動処理
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemyFlag[y][x])
					{
						//-----敵の移動処理
						//横移動
						if (enemyMoveMode == MOVE_MODE_LR)
						{
							if (enemyMoveX == MOVE_LR_RIGHT)
							{
								enemyPosX[y][x] += (enemySpeed + enemyAddSpeed);
							}
							else if (enemyMoveX == MOVE_LR_LEFT)
							{
								enemyPosX[y][x] -= (enemySpeed + enemyAddSpeed);
							}
						}

						//縦移動
						if (enemyMoveMode == MOVE_MODE_DOWN)
						{
							enemyPosY[y][x] += ENEMY_SIZE_Y;
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
					if (enemyFlag[y][x])
					{
						//-----敵の移動処理
						//横移動
						if (enemyMoveMode == MOVE_MODE_LR)
						{
							if (enemyMoveX == MOVE_LR_RIGHT)
							{
								enemyPosX[y][x] += enemySpeed;
							}
							else if (enemyMoveX == MOVE_LR_LEFT)
							{
								enemyPosX[y][x] -= enemySpeed;
							}
						}

						//縦移動
						if (enemyMoveMode == MOVE_MODE_DOWN)
						{
							enemyPosY[y][x] += ENEMY_SIZE_Y;
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
			if (enemyFlag[y][x])
			{
				//-----敵の移動制限
				if (enemyPosXMin > enemyPosX[y][x])
				{
					enemyPosXMin = enemyPosX[y][x];
				}

				if (enemyPosXMax < enemyPosX[y][x])
				{
					enemyPosXMax = enemyPosX[y][x];
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
}

//自機の弾と敵の当たり判定
bool EnemyCheckHitObj(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//自機の弾と敵の当たり判定
			if (PShotFlag == true)
			{
				if (enemyPosX[y][x] + ENEMY_SIZE_X >= PShotPosX
					&& enemyPosX[y][x] <= PShotPosX + PSHOT_SIZE_X
					&& enemyPosY[y][x] + ENEMY_SIZE_Y >= PShotPosY
					&& enemyPosY[y][x] <= PShotPosY + PSHOT_SIZE_Y
					&& enemyFlag[y][x] == true)
				{
					enemyFlag[y][x] = false;
					PShotFlag = false;
					AddScore(100);
					enemyCount--;
					return true;

					if (enemyCount == 0 && PlayerLife > 0)
					{
						SystemScene = SCENE_CLEAR;
					}
				}
			}
		}
	}

	return false;
}

void EnemyGameDraw(void)
{
	//敵の表示
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (enemyFlag[y][x] == true)
			{
				DrawGraph(enemyPosX[y][x] + GAME_OFFSET_X, enemyPosY[y][x] + GAME_OFFSET_Y, enemyImage[enemyType[y][x]][0], true);
			}
		}
	}

	//敵機が半数を切った時の表示
	if (enemyCount < ENEMY_MAX / 2)
	{
		stringCnt += 1;

		if (stringCnt > 120)
		{
			stringFlag = false;
		}
		else
		{
			stringFlag = true;
		}

		if (stringFlag == true)
		{
			if (stringCnt != 0 && (stringCnt / 20) % 2 == 0)
			{
				DrawString((SCREEN_SIZE_X / 2) - 120, (SCREEN_SIZE_Y / 2) - 20, "W  A  R  N  I  N  G", 0xFF0000);
			}
		}
	}
}