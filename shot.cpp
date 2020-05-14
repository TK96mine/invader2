#include"DxLib.h"
#include"main.h"
#include"shot.h"




void PlayerShotControl(void)
{
	//�v���C���[�̒e�̑���
	if (PShotFlag == false)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			PShotFlag = true;
			PShotPosX = PlayerPosX + (PLAYER_SIZE_X - PSHOT_SIZE_X) / 2;
			PShotPosY = PlayerPosY;
		}
	}

	//��ڲ԰�̒e�̑���
	if (PShotFlag == true)
	{
		PShotPosY -= PShotSpeed;
		if (PShotPosY < 0)
		{
			PShotFlag = false;
		}
	}
}

void EnemyShotControl(void)
{
	//�G�̒e�̑���
	for (int x = 0; x < ENEMY_X; x++)
	{
		for (int y = ENEMY_Y - 1; y >= 0; y--)	//1�ԃv���C���[�ɋ߂�(1�ԉ���)�������Ă���G���������G(�G�̏c���̐� - 1)�������琔���Ă���
		{
			if (EnemyFlag[y][x] == true)
			{
				//�G�@��������؂������A���˒i���𑝂₷
				if (EnemyCount < ENEMY_MAX / 2)
				{
					if (GetRand(30) == 1)	//0����30�܂ł̐��l�𗐐��ŕԂ��Ă��̒l��1�̎��ɏ�������
					{
						//�G�̒e�̔���
						for (int e = 0; e < ESHOT_MAX; e++)
						{
							if (EShotFlag[e] == false)
							{
								//���̗��1�ԉ��̐������Ă���G���������ꍇ�̏���
								EShotPosX[e] = EnemyPosX[y][x] + (ENEMY_SIZE_X - ESHOT_SIZE_X) / 2;
								EShotPosY[e] = EnemyPosY[y][x];
								EShotFlag[e] = true;
								break;
							}
						}
					}
				}
				else
				{
					if (GetRand(500) == 1)	//0����500�܂ł̐��l�𗐐��ŕԂ��Ă��̒l��1�̎��ɏ�������
					{
						//�G�̒e�̔���
						for (int e = 0; e < ESHOT_MAX; e++)
						{
							if (EShotFlag[e] == false)
							{
								//���̗��1�ԉ��̐������Ă���G���������ꍇ�̏���
								EShotPosX[e] = EnemyPosX[y][x] + (ENEMY_SIZE_X - ESHOT_SIZE_X) / 2;
								EShotPosY[e] = EnemyPosY[y][x];
								EShotFlag[e] = true;
								break;
							}
						}
					}
				}

				break;
			}
		}
	}

	//�G�̒e�̐���
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (EShotFlag[e] == true)
		{
			EShotPosY[e] += EShotSpeed;		//�G�̒e�̈ړ�

			if (EShotPosY[e] > GAME_SIZE_Y)		//�G�̒e���Q�[����ʊO�ɏo���Ƃ���������
			{
				EShotFlag[e] = false;	//�G�̒e�̃t���O��false�ɂ���
			}
		}
	}
}