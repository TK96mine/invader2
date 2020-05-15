#include"DxLib.h"
#include"main.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"score.h"

//�ϐ�
int enemyImage[ENEMY_TYPE_MAX][ENEMY_ANI_MAX];	//�G�̉摜�i�[�p
CHARACTER enemy[ENEMY_Y][ENEMY_X];	//�G�̃|�W�V����
MOVE_MODE enemyMoveMode;	//�G�̈ړ����[�h
MOVE_LR enemyMoveX;	//�G�̉����ړ�
ENEMY_TYPE enemyType[ENEMY_Y][ENEMY_X];	//�G�̎��
int enemyCount;	//�G�̐�
int enemyAddSpeed;	//�G�@�̈ړ����x�ɉ����鑬�x
int enemyMoveCnt;	//�G�̈ړ��p�J�E���^�[
int estringCnt;	//�G�p�\�������̓_�ŗp�J�E���^�[
int estringFlag;	//�G�������؂����ۂɕ����\�����邽�߂̃t���O


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

//�G�̈ړ�����
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
			//�ړ�����
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemy[y][x].flag)
					{
						//-----�G�̈ړ�����
						//���ړ�
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

						//�c�ړ�
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
			//�ړ�����
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (enemy[y][x].flag)
					{
						//-----�G�̈ړ�����
						//���ړ�
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

						//�c�ړ�
						if (enemyMoveMode == MOVE_MODE_DOWN)
						{
							enemy[y][x].pos.y += ENEMY_SIZE_Y;
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
			if (enemy[y][x].flag)
			{
				//-----�G�̈ړ�����
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

	//�e�̔���
	for (int x = 0; x < ENEMY_X; x++)
	{
		for (int y = ENEMY_Y - 1; y >= 0; y--)	//1�ԃv���C���[�ɋ߂�(1�ԉ���)�������Ă���G���������G(�G�̏c���̐� - 1)�������琔���Ă���
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
			//�G�Ǝ��@�Ƃ̓����蔻��
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
	//�G�̕\��
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

	//�G�@��������؂������̕\��
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