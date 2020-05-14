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

//����
int playerbakuImage[BAKU_ANI];	//�����摜�i�[�p
int playerbakuPosX;	//�����摜�̉����ʒu
int playerbakuPosY;	//�����摜�̏c���ʒu
int playerbakuAni;	//�����̃A�j���[�V�����p
bool playerbakuFlag;	//�����摜�̏��

void PlayerSystemInit(void)
{
	//�v���C���[
	LoadDivGraph("image/serval.png", PLAYER_STYLE_MAX * PLAYER_ANI_MAX, PLAYER_ANI_MAX, PLAYER_STYLE_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage[0]);
	LoadDivGraph("image/blast.png", 24, 6, 4, BAKU_SIZE_X, BAKU_SIZE_Y, playerbakuImage);
}

void PlayerGameInit(void)
{
	playerPosX = (GAME_SIZE_X - PLAYER_SIZE_X) / 2;
	playerPosY = (GAME_SIZE_Y - PLAYER_SIZE_Y);
	playerSpeed = (PLAYER_DEF_SPEED);
	playerFlag = true;
	playerLife = PLAYER_DEF_LIFE;

	//����
	playerbakuPosX = playerPosX;
	playerbakuPosY = playerPosY;
	playerbakuAni = 0;
	playerbakuFlag = false;
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