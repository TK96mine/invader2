#include"DxLib.h"
#include"main.h"
#include"player.h"
#include"shot.h"
#include"score.h"

//変数
//プレイヤー
int pShotImage;	//プレイヤーの弾の画像格納用
CHARACTER pShot;	//プレイヤーの弾

//敵
int eShotImage;	//敵の弾の画像格納用
CHARACTER eShot[ESHOT_MAX];	//敵の弾の横軸位置

void ShotSystemInit(void)
{
	//プレイヤーの弾
	pShotImage = LoadGraph("image/pshot.png");

	//敵の弾
	eShotImage = LoadGraph("image/eshot.png");
}

void ShotGameInit(void)
{
	pShot.pos.y = 0;
	pShot.pos.x = 0;
	pShot.speed = (PSHOT_DEF_SPEED);

	for (int x = 0; x < ENEMY_X; x++)
	{
		eShot[x].pos.x = 0;
		eShot[x].pos.y = 0;
		eShot[x].speed = (ESHOT_DEF_SPEED);
		eShot[x].flag = false;
	}
	pShot.flag = false;
}

void PlayerShotControl(XY playerPos)
{
	//プレイヤーの弾の操作
	if (pShot.flag == false)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			pShot.flag = true;
			pShot.pos.x = playerPos.x + (PLAYER_SIZE_X - PSHOT_SIZE_X) / 2;
			pShot.pos.y = playerPos.y;
		}
	}

	//ﾌﾟﾚｲﾔｰの弾の操作
	if (pShot.flag == true)
	{
		pShot.pos.y -= pShot.speed;
		if (pShot.pos.y < 0)
		{
			pShot.flag = false;
		}
	}
}

void EnemyShotControl(XY enemyPos, bool enemyFlag, int enemyCount)
{
	//敵の弾の操作
	if (enemyFlag == true)
	{
		//敵機が半分を切った時、発射段数を増やす
		if (enemyCount < ENEMY_MAX / 2)
		{
			if (GetRand(30) == 1)	//0から30までの数値を乱数で返してその値が1の時に処理する
			{
				//敵の弾の発射
				for (int e = 0; e < ESHOT_MAX; e++)
				{
					if (eShot[e].flag == false)
					{
						//その列で1番下の生存している敵を見つけた場合の処理
						eShot[e].pos.x = enemyPos.x + (ENEMY_SIZE_X - ESHOT_SIZE_X) / 2;
						eShot[e].pos.y = enemyPos.y;
						eShot[e].flag = true;
						break;
					}
				}
			}
		}
		else
		{
			if (GetRand(500) == 1)	//0から500までの数値を乱数で返してその値が1の時に処理する
			{
				//敵の弾の発射
				for (int e = 0; e < ESHOT_MAX; e++)
				{
					if (eShot[e].flag == false)
					{
						//その列で1番下の生存している敵を見つけた場合の処理
						eShot[e].pos.x = enemyPos.x + (ENEMY_SIZE_X - ESHOT_SIZE_X) / 2;
						eShot[e].pos.y = enemyPos.y;
						eShot[e].flag = true;
						break;
					}
				}
			}
		}

		//break;
	}

	//敵の弾の制御
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == true)
		{
			eShot[e].pos.y += eShot[e].speed;		//敵の弾の移動

			if (eShot[e].pos.y > GAME_SIZE_Y)		//敵の弾がゲーム画面外に出たとき処理する
			{
				eShot[e].flag = false;	//敵の弾のフラグをfalseにする
			}
		}
	}
}

//プレイヤーと敵の弾の当たり判定
bool PlayerCheckHitEShot(XY playerPos,bool playerFlag)
{
	//敵の弾と自機との当たり判定
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

//自機の弾と敵の当たり判定
bool EnemyCheckHitObj(XY enemyPos,bool enemyFlag)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//自機の弾と敵の当たり判定
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
	//弾の表示
	//ﾌﾟﾚｲﾔｰの弾の表示
	if (pShot.flag == true)
	{
		DrawGraph(pShot.pos.x + GAME_OFFSET_X, pShot.pos.y + GAME_OFFSET_Y, pShotImage, true);
	}
	//敵の弾の表示
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == true)
		{
			DrawGraph(eShot[e].pos.x + GAME_OFFSET_X, eShot[e].pos.y + GAME_OFFSET_Y, eShotImage, true);
		}
	}
}