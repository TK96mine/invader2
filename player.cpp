#include"DxLib.h"

#include"main.h"

#include"player.h"

//変数
int playerImage[PLAYER_STYLE_MAX][PLAYER_ANI_MAX];	//ﾌﾟﾚｲﾔｰの画像格納用
int playerPosX;		//ﾌﾟﾚｲﾔｰのX座標
int playerPosY;		//ﾌﾟﾚｲﾔｰのY座標
int playerSpeed;	//ﾌﾟﾚｲﾔｰのｽﾋﾟｰﾄﾞ
bool playerFlag;		//ﾌﾟﾚｲﾔｰのﾌﾗｸﾞ
int playerLife;		//残機

//爆発
int playerbakuImage[BAKU_ANI];	//爆発画像格納用
int playerbakuPosX;	//爆発画像の横軸位置
int playerbakuPosY;	//爆発画像の縦軸位置
int playerbakuAni;	//爆発のアニメーション用
bool playerbakuFlag;	//爆発画像の状態

void PlayerSystemInit(void)
{
	//プレイヤー
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

	//爆発
	playerbakuPosX = playerPosX;
	playerbakuPosY = playerPosY;
	playerbakuAni = 0;
	playerbakuFlag = false;
}

//プレイヤーの処理
void PlayerControl(void)
{

	if (playerFlag == true)
	{
		//右移動
		if (CheckHitKey(KEY_INPUT_NUMPAD6))
		{
			if (playerPosX >= GAME_SIZE_X - PLAYER_SIZE_X)	//移動制限
			{
				playerPosX = GAME_SIZE_X - PLAYER_SIZE_X;
			}
			else
			{
				playerPosX += playerSpeed;
			}
		}
		//左移動
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