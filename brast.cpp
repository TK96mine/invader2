#include"DxLib.h"

#include"main.h"

#include"brast.h"

//プレイヤー
int playerbakuImage[BAKU_ANI];	//爆発画像格納用
int playerbakuPosX;	//爆発画像の横軸位置
int playerbakuPosY;	//爆発画像の縦軸位置
int playerbakuAni;	//爆発のアニメーション用
bool playerbakuFlag;	//爆発画像の状態

//敵
int enemybakuImage[BAKU_ANI];	//爆発画像格納用
int enemybakuPosX;	//爆発画像の横軸位置
int enemybakuPosY;	//爆発画像の縦軸位置
int enemybakuAni;	//爆発のアニメーション用
bool enemybakuFlag;	//爆発画像の状態

void BrastSystemInit(void)
{
	LoadDivGraph("image/blast.png", 24, 6, 4, BAKU_SIZE_X, BAKU_SIZE_Y, playerbakuImage);
	LoadDivGraph("image/blast.png", 24, 6, 4, BAKU_SIZE_X, BAKU_SIZE_Y, enemybakuImage);
}

void BrastGameInit(void)
{
	//プレイヤー
	playerbakuPosX = playerPosX;
	playerbakuPosY = playerPosY;
	playerbakuAni = 0;
	playerbakuFlag = false;
}

void BrastControl(void)
{
	/*
		// 爆発の表示
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

		// 爆発の表示
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