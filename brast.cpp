#include"DxLib.h"

#include"main.h"

#include"brast.h"

//�v���C���[
int playerbakuImage[BAKU_ANI];	//�����摜�i�[�p
XY playerbakuPos;	//�����摜�̈ʒu
int playerbakuAni;	//�����̃A�j���[�V�����p
bool playerbakuFlag;	//�����摜�̏��

//�G
int enemybakuImage[BAKU_ANI];	//�����摜�i�[�p
XY enemybakuPos;	//�����摜�̈ʒu
int enemybakuAni;	//�����̃A�j���[�V�����p
bool enemybakuFlag;	//�����摜�̏��

void BrastSystemInit(void)
{
	LoadDivGraph("image/blast.png", 24, 6, 4, BAKU_SIZE_X, BAKU_SIZE_Y, playerbakuImage);
	LoadDivGraph("image/blast.png", 24, 6, 4, BAKU_SIZE_X, BAKU_SIZE_Y, enemybakuImage);
}

void PlayerBrastGameInit(XY playerPos)
{
	//�v���C���[
	playerbakuPos.x = playerPos.x;
	playerbakuPos.y = playerPos.y;
	playerbakuAni = 0;
	playerbakuFlag = false;
}

void EnemyBrastGameInit(void)
{

}

void BrastControl(void)
{
	/*
		// �����̕\��
		if (bakuFlag == true)
		{
			DrawGraph(bakuPosX, bakuPosY, bakuImage[bakuAni], true);
			bakuAni = bakuAni + 1;
			if (bakuAni >= BAKU_ANI)
			{
				bakuAni = 0;
				bakuFlag = false;
			}
		}

		// �����̕\��
		if (bakuFlag == true)
		{
			bakuAni = bakuAni + 1;
			DrawGraph(bakuPosX, bakuPosY, bakuImage[bakuAni], true);

			if (bakuAni >= BAKU_ANI)
			{
				bakuAni = 0;
				bakuFlag = false;
			}
		}

		if (!bakuFlag)
		{
			bakuAni = 0;
			bakuPosX = PlayerPosX;
			bakuPosY = PlayerPosY;
		}
	*/
}

void BrastGameDraw(void)
{

}