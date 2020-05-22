#include"DxLib.h"
#include"main.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"brast.h"
#include"score.h"

//�ϐ�
int playerImage[PLAYER_STYLE_MAX][PLAYER_ANI_MAX];	//��ڲ԰�̉摜�i�[�p
CHARACTER player;
int hitCnt;
bool hitCheck;
int playerScore;	//�v���C���[�̎c�@��@������̉�����X�R�A�̒l

void PlayerSystemInit(void)
{
	//�v���C���[
	LoadDivGraph("image/serval.png", PLAYER_STYLE_MAX * PLAYER_ANI_MAX, PLAYER_ANI_MAX, PLAYER_STYLE_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage[0]);
}

void PlayerGameInit(void)
{
	player.pos.x = (GAME_SIZE_X - PLAYER_SIZE_X) / 2;
	player.pos.y = (GAME_SIZE_Y - PLAYER_SIZE_Y);
	player.speed = (PLAYER_DEF_SPEED);
	player.flag = true;
	player.life = PLAYER_DEF_LIFE;
	hitCnt = 0;
	hitCheck = false;
	playerScore = 100;

	PlayerBrastGameInit(player.pos);
}

//�v���C���[�̏���
void PlayerControl(void)
{
	player.aniCnt++;

	if (player.flag == true)
	{
		//�E�ړ�
		if (CheckHitKey(KEY_INPUT_NUMPAD6))
		{
			if (player.pos.x >= GAME_SIZE_X - PLAYER_SIZE_X)	//�ړ�����
			{
				player.pos.x = GAME_SIZE_X - PLAYER_SIZE_X;
			}
			else
			{
				player.pos.x += player.speed;
			}
		}
		//���ړ�
		if (CheckHitKey(KEY_INPUT_NUMPAD4))
		{
			if (player.pos.x - player.speed <= 0    /*GAME_OFFSET_X*/)
			{
				player.pos.x = 0;
			}
			else
			{
				player.pos.x -= player.speed;
			}
		}
	}

	//�e�̔���
	PlayerShotControl(player.pos);

}

void PlayerHitEnemy(void)
{
	if (PlayerCheckHitEnemy(player.pos,player.flag) == true)
	{
		if (hitCheck == false)
		{
			player.life--;
			hitCheck = true;
		}

		if (player.life > 0)
		{
			if (player.flag == false)
			{
				ResetEnemyPos();
				player.flag = true;
			}
		}
	}

	Muteki();
}

void PlayerHitEShot(void)
{
	if (PlayerCheckHitEShot(player.pos,player.flag) == true)
	{
		if (hitCheck == false)
		{
			player.life--;
			hitCheck = true;
		}
	}

	Muteki();
}

void Muteki(void)
{
	if (hitCheck == true)
	{
		hitCnt++;
		if (hitCnt > 120)
		{
			hitCheck = false;
			hitCnt = 0;
		}
	}
	else
	{
		hitCnt = 0;
	}
}


// ���@�̐����m�F�p�֐�
bool PlayerDeathProc(void)
{
	if (player.life <= 0)
	{
		return true;
	}

	return false;
}

void PlayerGameDraw(void)
{
	//�c�@����\��
	DrawFormatString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 300, 0xFFFFFF, "PLAYER = %d", player.life);

	//�v���C���[�̈ʒu�\��
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYER = ( %d, %d)", player.pos.x, player.pos.y);

	//�v���C���[�̎c�@�\��
	for (int p = 0; p < player.life; p++)
	{
		DrawGraph((GAME_SIZE_X + 20) + 40 * (p % 3), (SCREEN_SIZE_Y - 80) - PLAYER_SIZE_Y * ((p / 3) + 1), playerImage[PLAYER_STYLE_FRONT][0], true);
	}

	//�v���C���[�̕\��
	if ((hitCnt / 10) % 2 == 0)
	{
		if (player.flag == true)
		{
			if (player.aniCnt % 60 <= 30)
			{
				for (int x = 0; x < PLAYER_ANI_MAX; x++)
				{
					DrawGraph(player.pos.x + GAME_OFFSET_X, (GAME_SIZE_Y + GAME_OFFSET_Y) - PLAYER_SIZE_Y, playerImage[PLAYER_STYLE_BACK][0], true);
				}
			}
			else
			{
				DrawGraph(player.pos.x + GAME_OFFSET_X, (GAME_SIZE_Y + GAME_OFFSET_Y) - PLAYER_SIZE_Y, playerImage[PLAYER_STYLE_BACK][1], true);
			}
		}
	}
}

void PlayerEndScore(void)
{
	EndAddScore(player.life, playerScore);
}

void PlayerCliarDraw(void)
{
	PlayerCliarScoreDraw(player.life, playerScore);
}

void PlayerGameOverDraw(void)
{
	PlayerGameOverScoreDraw(player.life, playerScore);
}

