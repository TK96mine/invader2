#include"DxLib.h"

#include"main.h"

#include"player.h"

//�ϐ�
int playerImage[PLAYER_STYLE_MAX][PLAYER_ANI_MAX];	//��ڲ԰�̉摜�i�[�p
int playerPosX;		//��ڲ԰��X���W
int playerPosY;		//��ڲ԰��Y���W
int playerSpeed;	//��ڲ԰�̽�߰��
bool playerFlag;		//��ڲ԰���׸�
int playerLife;		//�c�@
int playerAniCnt;	//�v���C���[�̃A�j���[�V�����p�J�E���^�[

void PlayerSystemInit(void)
{
	//�v���C���[
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

//�v���C���[�̏���
void PlayerControl(void)
{
	if (playerFlag == true)
	{
		//�E�ړ�
		if (CheckHitKey(KEY_INPUT_NUMPAD6))
		{
			if (playerPosX >= GAME_SIZE_X - PLAYER_SIZE_X)	//�ړ�����
			{
				playerPosX = GAME_SIZE_X - PLAYER_SIZE_X;
			}
			else
			{
				playerPosX += playerSpeed;
			}
		}
		//���ړ�
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
			//�G�Ǝ��@�Ƃ̓����蔻��
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

//�v���C���[�ƓG�̒e�̓����蔻��
bool PlayerCheckHitEShot(void)
{
	//�G�̒e�Ǝ��@�Ƃ̓����蔻��
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

// ���@�̌��Z����
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
		systemScene = SCENE_GAMEOVER;		// �c�@���Ȃ��ꍇ�A�ްѵ��ް�ɂ���
	}
}

void PlayerGameDraw(void)
{
	//�c�@����\��
	DrawFormatString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 300, 0xFFFFFF, "PLAYER = %d", PlayerLife);

	//�v���C���[�̈ʒu�\��
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYER = ( %d, %d)", PlayerPosX, PlayerPosY);

	//�v���C���[�̎c�@�\��
	for (int p = 0; p < PlayerLife; p++)
	{
		DrawGraph((GAME_SIZE_X + 20) + 40 * (p % 3), (SCREEN_SIZE_Y - 80) - PLAYER_SIZE_Y * ((p / 3) + 1), PlayerImage[PLAYER_STYLE_FRONT][0], true);
	}

	//�v���C���[�̕\��
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


