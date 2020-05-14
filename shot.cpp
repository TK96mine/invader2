#include"DxLib.h"
#include"main.h"
#include"shot.h"




void PlayerShotControl(void)
{
	//プレイヤーの弾の操作
	if (PShotFlag == false)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			PShotFlag = true;
			PShotPosX = PlayerPosX + (PLAYER_SIZE_X - PSHOT_SIZE_X) / 2;
			PShotPosY = PlayerPosY;
		}
	}

	//ﾌﾟﾚｲﾔｰの弾の操作
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
	//敵の弾の操作
	for (int x = 0; x < ENEMY_X; x++)
	{
		for (int y = ENEMY_Y - 1; y >= 0; y--)	//1番プレイヤーに近い(1番下の)生存している敵を除いた敵(敵の縦軸の数 - 1)を下から数えていく
		{
			if (EnemyFlag[y][x] == true)
			{
				//敵機が半分を切った時、発射段数を増やす
				if (EnemyCount < ENEMY_MAX / 2)
				{
					if (GetRand(30) == 1)	//0から30までの数値を乱数で返してその値が1の時に処理する
					{
						//敵の弾の発射
						for (int e = 0; e < ESHOT_MAX; e++)
						{
							if (EShotFlag[e] == false)
							{
								//その列で1番下の生存している敵を見つけた場合の処理
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
					if (GetRand(500) == 1)	//0から500までの数値を乱数で返してその値が1の時に処理する
					{
						//敵の弾の発射
						for (int e = 0; e < ESHOT_MAX; e++)
						{
							if (EShotFlag[e] == false)
							{
								//その列で1番下の生存している敵を見つけた場合の処理
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

	//敵の弾の制御
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (EShotFlag[e] == true)
		{
			EShotPosY[e] += EShotSpeed;		//敵の弾の移動

			if (EShotPosY[e] > GAME_SIZE_Y)		//敵の弾がゲーム画面外に出たとき処理する
			{
				EShotFlag[e] = false;	//敵の弾のフラグをfalseにする
			}
		}
	}
}