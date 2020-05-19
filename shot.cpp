#include"DxLib.h"
#include"main.h"
#include"player.h"
#include"shot.h"
#include"score.h"

//�ϐ�
//�v���C���[
int pShotImage;	//�v���C���[�̒e�̉摜�i�[�p
CHARACTER pShot;	//�v���C���[�̒e

//�G
int eShotImage;	//�G�̒e�̉摜�i�[�p
CHARACTER eShot[ESHOT_MAX];	//�G�̒e�̉����ʒu

void ShotSystemInit(void)
{
	//�v���C���[�̒e
	pShotImage = LoadGraph("image/pshot.png");

	//�G�̒e
	eShotImage = LoadGraph("image/eshot.png");
}

void ShotGameInit(void)
{
	pShot.pos.y = 0;
	pShot.pos.x = 0;
	pShot.speed = PSHOT_DEF_SPEED;
	pShot.flag = false;

	for (int e = 0; e < ESHOT_MAX; e++)
	{
		eShot[e].pos.x = 0;
		eShot[e].pos.y = 0;
		eShot[e].speed = ESHOT_DEF_SPEED;
		eShot[e].flag = false;
	}
}

void PlayerShotControl(XY playerPos)
{
	//�v���C���[�̒e�̑���
	if (pShot.flag == false)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			pShot.flag = true;
			pShot.pos.x = playerPos.x + (PLAYER_SIZE_X - PSHOT_SIZE_X) / 2;
			pShot.pos.y = playerPos.y;
		}
	}

	//��ڲ԰�̒e�̑���
	if (pShot.flag == true)
	{
		pShot.pos.y -= pShot.speed;
		if (pShot.pos.y < 0)
		{
			pShot.flag = false;
		}
	}
}

void EnemySetShot(XY enemyPos, int enemyCount)
{
	//�G�̒e�̔���
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == false)
		{
			//���̗��1�ԉ��̐������Ă���G���������ꍇ�̏���
			eShot[e].pos.x = enemyPos.x + (ENEMY_SIZE_X - ESHOT_SIZE_X) / 2;
			eShot[e].pos.y = enemyPos.y;
			eShot[e].flag = true;
			break;
		}
	}
}

void EnemyShotControl(XY enemyPos, int enemyCount)
{
	int rand = GetRand(100);	//0�`100�܂ł̗������m�ۂ��A�����ϐ��Ɋi�[

	//�G�̒e�̑���
	//�G�@��������؂������A���˒i���𑝂₷
	if (enemyCount < ENEMY_MAX / 2)
	{
		if (rand <= 5)	
		{
			EnemySetShot(enemyPos,enemyCount);
		}
	}
	else
	{
		if (rand == 1)
		{
			//�G�̒e�̔���
			for (int e = 0; e < ESHOT_MAX; e++)
			{
				EnemySetShot(enemyPos, enemyCount);
			}
		}
	}

	//�G�̒e�̐���
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == true)
		{
			eShot[e].pos.y +=  eShot[e].speed;		//�G�̒e�̈ړ�

			if (eShot[e].pos.y > GAME_SIZE_Y)		//�G�̒e���Q�[����ʊO�ɏo���Ƃ���������
			{
				eShot[e].flag = false;	//�G�̒e�̃t���O��false�ɂ���
			}
		}
	}
}

//�v���C���[�ƓG�̒e�̓����蔻��
bool PlayerCheckHitEShot(XY playerPos,bool playerFlag)
{
	//�G�̒e�Ǝ��@�Ƃ̓����蔻��
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == true && playerFlag == true)
		{
			if (eShot[e].pos.x + ESHOT_SIZE_X >= playerPos.x
				&& eShot[e].pos.x <= playerPos.x + PLAYER_SIZE_X
				&& eShot[e].pos.y + ESHOT_SIZE_Y >= playerPos.y
				&& eShot[e].pos.y <= playerPos.y + PLAYER_SIZE_Y)
			{
				eShot[e].flag = false;

				return true;
			}
		}
	}

	return false;
}

//���@�̒e�ƓG�̓����蔻��
bool EnemyCheckHitObj(XY enemyPos,bool enemyFlag)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//���@�̒e�ƓG�̓����蔻��
			if (pShot.flag == true)
			{
				if (enemyPos.x + ENEMY_SIZE_X >= pShot.pos.x
					&& enemyPos.x <= pShot.pos.x + PSHOT_SIZE_X
					&& enemyPos.y + ENEMY_SIZE_Y >= pShot.pos.y
					&& enemyPos.y <= pShot.pos.y + PSHOT_SIZE_Y
					&& enemyFlag == true)
				{
					pShot.flag = false;

					return true;
				}
			}
		}
	}

	return false;
}

void ShotGameDraw(void)
{
	//�e�̕\��
	//��ڲ԰�̒e�̕\��
	if (pShot.flag == true)
	{
		DrawGraph(pShot.pos.x + GAME_OFFSET_X, pShot.pos.y + GAME_OFFSET_Y, pShotImage, true);
	}
	//�G�̒e�̕\��
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == true)
		{
			DrawGraph(eShot[e].pos.x + GAME_OFFSET_X, eShot[e].pos.y + GAME_OFFSET_Y, eShotImage, true);
		}
	}
}