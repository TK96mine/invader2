#include"DxLib.h"
#include"main.h"
#include"enemy.h"
#include"score.h"

//•Ï”
int enemyImage[ENEMY_TYPE_MAX][ENEMY_ANI_MAX];	//“G‚Ì‰æ‘œŠi”[—p
int enemyPosX[ENEMY_Y][ENEMY_X];	//“G‚Ì‰¡²‚Ìƒ|ƒWƒVƒ‡ƒ“
int enemyPosY[ENEMY_Y][ENEMY_X];	//“G‚Ìc²‚Ìƒ|ƒWƒVƒ‡ƒ“
int enemySpeed;	//“G‚ÌˆÚ“®‘¬“x
bool enemyFlag[ENEMY_Y][ENEMY_X];	//“G‚Ì¶‘¶Šm”F—p•Ï”
MOVE_MODE enemyMoveMode;	//“G‚ÌˆÚ“®ƒ‚[ƒh
MOVE_LR enemyMoveX;	//“G‚Ì‰¡²ˆÚ“®
ENEMY_TYPE enemyType[ENEMY_Y][ENEMY_X];	//“G‚Ìí—Ş
int enemyCount;	//“G‚Ì”
int enemyAddSpeed;	//“G‹@‚ÌˆÚ“®‘¬“x‚É‰Á‚¦‚é‘¬“x
int enemyMoveCnt;	//“G‚ÌˆÚ“®—pƒJƒEƒ“ƒ^[

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

//“G‚ÌˆÚ“®ˆ—
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
			//ˆÚ“®ˆ—
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemyFlag[y][x])
					{
						//-----“G‚ÌˆÚ“®ˆ—
						//‰¡ˆÚ“®
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

						//cˆÚ“®
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
			//ˆÚ“®ˆ—
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemyFlag[y][x])
					{
						//-----“G‚ÌˆÚ“®ˆ—
						//‰¡ˆÚ“®
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

						//cˆÚ“®
						if (enemyMoveMode == MOVE_MODE_DOWN)
						{
							enemyPosY[y][x] += ENEMY_SIZE_Y;
						}

					}
				}
			}
		}
	}

	//Min‚ÆMax‚ğŒvZ‚·‚é
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (enemyFlag[y][x])
			{
				//-----“G‚ÌˆÚ“®§ŒÀ
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

	//ˆÚ“®•ûŒü‚ğ”»’f‚·‚é
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

//©‹@‚Ì’e‚Æ“G‚Ì“–‚½‚è”»’è
bool EnemyCheckHitObj(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//©‹@‚Ì’e‚Æ“G‚Ì“–‚½‚è”»’è
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
	//“G‚Ì•\¦
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

	//“G‹@‚ª”¼”‚ğØ‚Á‚½‚Ì•\¦
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