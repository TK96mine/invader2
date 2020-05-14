#include"DxLib.h"
#include"main.h"
#include"shot.h"
#include"score.h"

//変数
//プレイヤー
int PShotImage;	//プレイヤーの弾の画像格納用
int PShotPosX;	//プレイヤーの弾の横軸の位置
int PShotPosY;	//プレイヤーの弾の縦軸の位置
int PShotSpeed;	//プレイヤーの弾の移動速度
bool PShotFlag;	//プレイヤーの弾の発射状態

//敵
int EShotImage;	//敵の弾の画像格納用
int EShotPosX[ESHOT_MAX];	//敵の弾の横軸位置
int EShotPosY[ESHOT_MAX];	//敵の弾の縦軸位置
int EShotSpeed;	//敵の弾の速度
bool EShotFlag[ESHOT_MAX];	//敵の弾の状態

void ShotSystemInit(void)
{
	//プレイヤーの弾
	PShotImage = LoadGraph("image/pshot.png");

	//敵の弾
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

void ShotGameDraw(void)
{
	//弾の表示
	//ﾌﾟﾚｲﾔｰの弾の表示
	if (PShotFlag == true)
	{
		DrawGraph(PShotPosX + GAME_OFFSET_X, PShotPosY + GAME_OFFSET_Y, PShotImage, true);
	}
	//敵の弾の表示
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (EShotFlag[e] == true)
		{
			DrawGraph(EShotPosX[e] + GAME_OFFSET_X, EShotPosY[e] + GAME_OFFSET_Y, EShotImage, true);
		}
	}
}