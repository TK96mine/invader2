#include"DxLib.h"
#include"main.h"
#include"shot.h"
#include"score.h"

//�ϐ�
//�v���C���[
int PShotImage;	//�v���C���[�̒e�̉摜�i�[�p
int PShotPosX;	//�v���C���[�̒e�̉����̈ʒu
int PShotPosY;	//�v���C���[�̒e�̏c���̈ʒu
int PShotSpeed;	//�v���C���[�̒e�̈ړ����x
bool PShotFlag;	//�v���C���[�̒e�̔��ˏ��

//�G
int EShotImage;	//�G�̒e�̉摜�i�[�p
int EShotPosX[ESHOT_MAX];	//�G�̒e�̉����ʒu
int EShotPosY[ESHOT_MAX];	//�G�̒e�̏c���ʒu
int EShotSpeed;	//�G�̒e�̑��x
bool EShotFlag[ESHOT_MAX];	//�G�̒e�̏��

void ShotSystemInit(void)
{
	//�v���C���[�̒e
	PShotImage = LoadGraph("image/pshot.png");

	//�G�̒e
	EShotImage = LoadGraph("image/eshot.png");
}

void ShotGameInit(void)
{
	PShotPosY = 0;
	PShotPosX = 0;
	PShotSpeed = (PSHOT_DEF_SPEED);
	EShotSpeed = (ESHOT_DEF_SPEED);
	for (int x = 0; x < ENEMY_X; x++)
	{
		EShotPosX[x] = 0;
		EShotPosY[x] = 0;

		EShotFlag[x] = false;
	}
	PShotFlag = false;
}

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

void ShotGameDraw(void)
{
	//�e�̕\��
	//��ڲ԰�̒e�̕\��
	if (PShotFlag == true)
	{
		DrawGraph(PShotPosX + GAME_OFFSET_X, PShotPosY + GAME_OFFSET_Y, PShotImage, true);
	}
	//�G�̒e�̕\��
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (EShotFlag[e] == true)
		{
			DrawGraph(EShotPosX[e] + GAME_OFFSET_X, EShotPosY[e] + GAME_OFFSET_Y, EShotImage, true);
		}
	}
}