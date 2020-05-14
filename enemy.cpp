#include"DxLib.h"
#include"main.h"
#include"enemy.h"
#include"score.h"

//�ϐ�
int enemyImage[ENEMY_TYPE_MAX][ENEMY_ANI_MAX];	//�G�̉摜�i�[�p
int enemyPosX[ENEMY_Y][ENEMY_X];	//�G�̉����̃|�W�V����
int enemyPosY[ENEMY_Y][ENEMY_X];	//�G�̏c���̃|�W�V����
int enemySpeed;	//�G�̈ړ����x
bool enemyFlag[ENEMY_Y][ENEMY_X];	//�G�̐����m�F�p�ϐ�
MOVE_MODE enemyMoveMode;	//�G�̈ړ����[�h
MOVE_LR enemyMoveX;	//�G�̉����ړ�
ENEMY_TYPE enemyType[ENEMY_Y][ENEMY_X];	//�G�̎��
int enemyCount;	//�G�̐�
int enemyAddSpeed;	//�G�@�̈ړ����x�ɉ����鑬�x
int enemyMoveCnt;	//�G�̈ړ��p�J�E���^�[

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

//�G�̈ړ�����
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
			//�ړ�����
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemyFlag[y][x])
					{
						//-----�G�̈ړ�����
						//���ړ�
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

						//�c�ړ�
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
			//�ړ�����
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemyFlag[y][x])
					{
						//-----�G�̈ړ�����
						//���ړ�
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

						//�c�ړ�
						if (enemyMoveMode == MOVE_MODE_DOWN)
						{
							enemyPosY[y][x] += ENEMY_SIZE_Y;
						}

					}
				}
			}
		}
	}

	//Min��Max���v�Z����
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (enemyFlag[y][x])
			{
				//-----�G�̈ړ�����
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

	//�ړ������𔻒f����
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

//���@�̒e�ƓG�̓����蔻��
bool EnemyCheckHitObj(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//���@�̒e�ƓG�̓����蔻��
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
	//�G�̕\��
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

	//�G�@��������؂������̕\��
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