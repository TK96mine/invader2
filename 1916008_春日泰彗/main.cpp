#include"Dxlib.h"

#include"main.h"

#include"score.h"

#include"player.h"

// 変数の定義
int gameCounter;	//ゲーム用カウンター
int titleImage;		//ﾀｲﾄﾙの画像格納用
int gameoverImage; //ｹﾞｰﾑオーバのｲﾒｰｼﾞ格納用
bool gameScene;	//ゲームシーンの状態(?)
int titlePosX;	//タイトル画像の横軸の位置
int titlePosY;	//タイトル画像の縦軸の位置
int gameoverPosX;	//ゲームオーバー画像の横軸の位置
int gameoverPosY;	//ゲームオーバー画像の縦軸の位置
int systemScene;	//シーンの状態格納用

//敵の変数
int EnemyImage[ENEMY_TYPE_MAX][ENEMY_ANI_MAX];	//敵の画像格納用
int EnemyPosX[ENEMY_Y][ENEMY_X];	//敵の横軸のポジション
int EnemyPosY[ENEMY_Y][ENEMY_X];	//敵の縦軸のポジション
int EnemySpeed;	//敵の移動速度
bool EnemyFlag[ENEMY_Y][ENEMY_X];	//敵の生存確認用変数
MOVE_MODE EnemyMoveMode;	//敵の移動モード
MOVE_LR EnemyMoveX;	//敵の横軸移動
ENEMY_TYPE enemyType[ENEMY_Y][ENEMY_X];	//敵の種類
int EnemyCount;	//敵の数
int enemyAddSpeed;	//敵機の移動速度に加える速度

//弾の変数
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

//爆発
int enemybakuImage[BAKU_ANI];	//爆発画像格納用
int enemybakuPosX;	//爆発画像の横軸位置
int enemybakuPosY;	//爆発画像の縦軸位置
int enemybakuAni;	//爆発のアニメーション用
bool enemybakuFlag;	//爆発画像の状態

//キーバッファ
int spaceKeyOld;	//1フレーム前のスペースキーの状態
int spaceKeyNew;	//現在のスペースキーの状態

//カウンター用
int massageCnt;	//メッセージ用カウンター
int enemyMoveCnt;	//敵の移動用カウンター
int playerAniCnt;	//プレイヤーのアニメーション用カウンター
int stringCnt;	//文字表示の点滅用カウンター

//ゲームクリア用
int clearImage;	//ゲームクリアの画像格納用
int crearPosX;		//ゲームクリア画像の横軸位置
int clearPosY;		//ゲームクリア画像の縦軸位置

//背景用
int bgImage;
int gameoverBgImage;

//文字表示用
bool stringFlag;


//winmain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	//初期化処理
	if (!SystemInit())
	{
		return -1;
	}

	SystemInit();

	//ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//スペースキーの状態確認
		spaceKeyOld = spaceKeyNew;
		spaceKeyNew = CheckHitKey(KEY_INPUT_SPACE);

		ClsDrawScreen();

		gameCounter++;
		if (gameCounter >= 99999)
		{
			gameCounter = 0;
		}

		massageCnt++;
		if (massageCnt > 99999)
		{
			massageCnt = 0;
		}

		enemyMoveCnt++;
		if (enemyMoveCnt > 99999)
		{
			enemyMoveCnt = 0;
		}

		playerAniCnt++;
		if (playerAniCnt > 99999)
		{
			playerAniCnt = 0;
		}

		switch (systemScene)
		{
			case SCENE_INIT:
				InitScene();
			break;

			case SCENE_TITLE:
				TitleScene();
			break;

			case SCENE_GAME:
				Gamescene();
			break;

			case SCENE_CLEAR:
				GameClear();
			break;

			case SCENE_GAMEOVER:
				GameOverScene();
			break;

			default:
				return -1;
			break;

		}

		ScreenFlip();//画面入れ替え
	}

	DxLib_End();
	return 0;
}

bool SystemInit(void)
{
	bool retFlag = true; //関数の戻り値

	//ｼｽﾃﾑ処理
	SetWindowText("1916008_春日泰彗");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == 1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	// ｸﾞﾗﾌｨｯｸの登録
	PlayerSystemInit();

	//敵の弾
	EShotImage = LoadGraph("image/eshot.png");
	if (LoadGraph("image/eshot.png") == -1)
	{
		AST();
		retFlag = false;
	}

	//背景
	bgImage = LoadGraph("image/bgimage.jpg");
	if (LoadGraph("image/bgimage.jpg") == -1)
	{
		AST();
		retFlag = false;
	}

	//爆発
	//敵
	LoadDivGraph("image/cellien.png", ENEMY_TYPE_MAX * ENEMY_ANI_MAX, ENEMY_ANI_MAX, ENEMY_TYPE_MAX, ENEMY_SIZE_X, ENEMY_SIZE_Y, EnemyImage[0]);
	if (LoadDivGraph("image/cellien.png", ENEMY_TYPE_MAX * ENEMY_ANI_MAX, ENEMY_ANI_MAX, ENEMY_TYPE_MAX, ENEMY_SIZE_X, ENEMY_SIZE_Y, EnemyImage[0])== -1)
	{
		AST();
		retFlag = false;
	}
	//プレイヤーの弾
	PShotImage = LoadGraph("image/pshot.png");
	if (LoadGraph("image/pshot.png") == -1)
	{
		AST();
		retFlag = false;
	}
	//タイトル
	 titleImage = LoadGraph("image/TitleLogo2.png");
	 if (LoadGraph("image/TitleLogo2.png") == -1)
	 {
		 AST();
		 retFlag = false;
	 }
	 //ゲームクリア
	 clearImage = LoadGraph("image/gameclear.png");
	 if (LoadGraph("image/gameclear.png") == -1)
	 {
		 AST();
		 retFlag = false;
	 }

	 //ゲームオーバー
	 gameoverImage = LoadGraph("image/GameOver.png");
	 if (LoadGraph("image/GameOver.png") == -1)
	 {
		 AST();
		 retFlag = false;
	 }

	 gameoverBgImage = LoadGraph("image/gameoverbg2.jpg");
	 if (LoadGraph("image/gameoverbg2.jpg") == -1)
	 {
		 AST();
		 retFlag = false;
	 }

	return retFlag;
}

void InitScene(void)
{
	// 変数の初期化
	//ﾌﾟﾚｲﾔｰ
	PlayerGameInit();

	//敵
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			EnemyPosX[y][x] = ((ENEMY_SIZE_X  * 10) / 7) * x;
			EnemyPosY[y][x] = (ENEMY_SIZE_Y * 9 / 7) * y;
			enemyType[y][x] = (ENEMY_TYPE)((y % (ENEMY_TYPE_MAX - 1)) + 1 );
			EnemyFlag[y][x] = true;
		}
	}

	EnemyFlag[2][3] = false;
	EnemySpeed = ENEMY_DEF_SPEED;
	enemyAddSpeed = 5;
	EnemyMoveMode == MOVE_MODE_LR;
	EnemyMoveX = MOVE_LR_RIGHT;
	EnemyCount = ENEMY_MAX;

	//弾
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
	titlePosX = 40;
	titlePosY = 40;
	gameoverPosX = 50;
	gameoverPosY = 50;
	gameScene = true;

	//カウント用
	massageCnt = 0;
	enemyMoveCnt = 0;
	stringCnt = 0;

	//スコア用
	InitScore();

	//文字表示用
	stringFlag = false;

	systemScene = SCENE_TITLE;
}




//タイトル
void TitleScene(void)
{
	DrawGraph(GAME_OFFSET_X, GAME_OFFSET_Y, bgImage, true);
	DrawGraph(((GAME_SIZE_X - GAMETITLE_SIZE_X) + 50 ) / 2, ((SCREEN_SIZE_Y / 2) - GAMETITLE_SIZE_Y), titleImage, true);
	DrawString((GAME_SIZE_X - 130) / 2, 310, "PLEASE PUSH SPACE KEY", 0xFFFFFF);

	if (massageCnt % 60 <= 40)
	{
		DrawString((GAME_SIZE_X - 180) / 2, 350, "スペースキーを押してください", 0xFFFFFF);
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyNew != spaceKeyOld)
	{
  		systemScene = SCENE_GAME;
	}

	DrawTexts();
}

//敵の処理
void EnemyControl(void)
{
	int EnemyPosXMax;
	int EnemyPosXMin;

	EnemyPosXMin = GAME_SIZE_X;
	EnemyPosXMax = 0;

	if (EnemyCount < ENEMY_MAX / 2)
	{
		if (enemyMoveCnt % 30 == 0 || enemyMoveCnt % 30 == 15)
		{
			//移動処理
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (EnemyFlag[y][x])
					{
						//-----敵の移動処理
						//横移動
						if (EnemyMoveMode == MOVE_MODE_LR)
						{
							if (EnemyMoveX == MOVE_LR_RIGHT)
							{
								EnemyPosX[y][x] += (EnemySpeed + enemyAddSpeed);
							}
							else if (EnemyMoveX == MOVE_LR_LEFT)
							{
								EnemyPosX[y][x] -= (EnemySpeed + enemyAddSpeed);
							}
						}

						//縦移動
						if (EnemyMoveMode == MOVE_MODE_DOWN)
						{
							EnemyPosY[y][x] += ENEMY_SIZE_Y;
						}

					}
				}
			}
		}
	}
	else
	{
		if (enemyMoveCnt % 60 == 0 || enemyMoveCnt % 60 == 30)
		{
			//移動処理
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (EnemyFlag[y][x])
					{
						//-----敵の移動処理
						//横移動
						if (EnemyMoveMode == MOVE_MODE_LR)
						{
							if (EnemyMoveX == MOVE_LR_RIGHT)
							{
								EnemyPosX[y][x] += EnemySpeed;
							}
							else if (EnemyMoveX == MOVE_LR_LEFT)
							{
								EnemyPosX[y][x] -= EnemySpeed;
							}
						}

						//縦移動
						if (EnemyMoveMode == MOVE_MODE_DOWN)
						{
							EnemyPosY[y][x] += ENEMY_SIZE_Y;
						}

					}
				}
			}
		}
	}


	//MinとMaxを計算する
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (EnemyFlag[y][x])
			{
				//-----敵の移動制限
				if (EnemyPosXMin > EnemyPosX[y][x])
				{
					EnemyPosXMin = EnemyPosX[y][x];
				}

				if (EnemyPosXMax < EnemyPosX[y][x])
				{
					EnemyPosXMax = EnemyPosX[y][x];
				}
			}
		}
	}

	//移動方向を判断する
	if (EnemyMoveMode == MOVE_MODE_DOWN)
	{
		EnemyMoveMode = MOVE_MODE_LR;
	}
	else
	{
		if (EnemyPosXMax > GAME_SIZE_X - ENEMY_SIZE_X)
		{
			EnemyMoveMode = MOVE_MODE_DOWN;
			EnemyMoveX = MOVE_LR_LEFT;
		}

		if (EnemyPosXMin < 0)
		{
			EnemyMoveMode = MOVE_MODE_DOWN;
			EnemyMoveX = MOVE_LR_RIGHT;
		}
	}
}

void shotControl(void)
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


//当たり判定
void CheckHitObj(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//自機の弾と敵の当たり判定
			if (PShotFlag == true)
			{
				if (EnemyPosX[y][x] + ENEMY_SIZE_X >= PShotPosX
					&& EnemyPosX[y][x] <= PShotPosX + PSHOT_SIZE_X
					&& EnemyPosY[y][x] + ENEMY_SIZE_Y >= PShotPosY
					&& EnemyPosY[y][x] <= PShotPosY + PSHOT_SIZE_Y
					&& EnemyFlag[y][x] == true)
				{
					EnemyFlag[y][x] = false;
					PShotFlag = false;
					AddScore(100);
					EnemyCount--;

					if (EnemyCount == 0 && PlayerLife > 0)
					{
						systemScene = SCENE_CLEAR;
					}
				}
			}

			//敵と自機との当たり判定
			if (EnemyFlag[y][x] == true && PlayerFlag == true)
			{
				if (EnemyPosX[y][x] + ENEMY_SIZE_X >= PlayerPosX
					&& EnemyPosX[y][x] <= PlayerPosX + PLAYER_SIZE_X
					&& EnemyPosY[y][x] + ENEMY_SIZE_Y >= PlayerPosY
					&& EnemyPosY[y][x] <= PlayerPosY + PLAYER_SIZE_Y)
				{
					PlayerFlag = false;
					PlayerDeathProc();
					
					
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
					/*else if (PlayerLife == 0)
					{
						systemScene = SCENE_GAMEOVER;
					}*/
				}

				//敵の弾と自機との当たり判定
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
						}
					}
				}
			}
				


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
				*/

				/*
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
	}
}


void Gamescene(void)
{
	gameDraw();

	shotControl();
	playerControl();
	EnemyControl();
	CheckHitObj();

}


void GameClear(void)
{
	DrawGraph(0, 0, clearImage, true);

	DrawString((SCREEN_SIZE_X - 140) / 2, SCREEN_SIZE_Y - 60, "PLEASE PUSH SPACEKEY", 0x0000FF);

	if (massageCnt % 45 <= 25)
	{
		DrawString((SCREEN_SIZE_X - 240) / 2, SCREEN_SIZE_Y - 40, "スペースキーを押してタイトルに戻る", 0x000000);
	}

	EndGameDrawTexts();

	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyNew != spaceKeyOld)
	{
		systemScene = SCENE_INIT;
	}
}


//ゲームオーバー
void GameOverScene(void)
{
	//ゲームオーバーシーン
	DrawExtendGraph(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, gameoverBgImage, true);
	DrawGraph((SCREEN_SIZE_X - GAMEOVER_SIZE_X) / 2, (SCREEN_SIZE_Y - (GAMEOVER_SIZE_Y * 2)) / 2, gameoverImage, true);

	//プレイヤーの位置表示
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYER = ( %d, %d)", PlayerPosX, PlayerPosY);
	//ゲームカウントの表示
	DrawFormatString(0, 16, 0xFFFFFF, "GAME COUNT = %d", gameCounter);

	//文字の表示
	DrawString((SCREEN_SIZE_X - 190) / 2, 350, "Thank You for Playing! ", 0xFFFF00);
	DrawString((SCREEN_SIZE_X - 180) / 2, 440, "PLEASE PUSH SPACE KEY ", 0xFFFFFF);

	if (massageCnt % 60 <= 40)
	{
		DrawString((SCREEN_SIZE_X - 225) / 2, 480, "スペースキーを押してください ", 0xFFFFFF);
	}

	EndGameDrawTexts();

	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyNew != spaceKeyOld)
	{
		systemScene = SCENE_INIT;
	}
}

void gameDraw(void)
{
	DrawGraph(GAME_OFFSET_X, GAME_OFFSET_Y, bgImage, true);

	//残機数を表示
	DrawFormatString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 300, 0xFFFFFF, "PLAYER = %d", PlayerLife);

	//プレイヤーの位置表示
	DrawFormatString(GAME_OFFSET_X + 20, GAME_OFFSET_Y, 0xFFFFFF, "PLAYER = ( %d, %d)", PlayerPosX, PlayerPosY);

	//ゲームカウントの表示
	DrawFormatString(GAME_OFFSET_X + 20, GAME_OFFSET_Y + 16, 0xFFFFFF, "GAME COUNT = %d", gameCounter);

	/*
	//スペースキーの状態
	DrawFormatString(0, 16, GetColor(0, 220, 250), "SPACE NEW = %d", spaceKeyNew);
	DrawFormatString(0, 32, GetColor(0, 220, 250), "SPACE OLD = %d",spaceKeyOld);
	*/

	//プレイヤーの残機表示
	for (int p = 0; p < PlayerLife; p++)
	{
		DrawGraph((GAME_SIZE_X + 20) + 40 * (p % 3), (SCREEN_SIZE_Y - 80) - PLAYER_SIZE_Y * ((p / 3) + 1), PlayerImage[PLAYER_STYLE_FRONT][0], true);
	}

	//敵の表示
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (EnemyFlag[y][x] == true)
			{
				DrawGraph(EnemyPosX[y][x] + GAME_OFFSET_X, EnemyPosY[y][x] + GAME_OFFSET_Y, EnemyImage[enemyType[y][x]][0], true);
			}
		}
	}

	//敵機が半数を切った時の表示
	if (EnemyCount < ENEMY_MAX / 2)
	{		
		stringCnt += 1;

		if (stringCnt > 120)
		{
			stringFlag = false;
		}
		else
		{
			stringFlag = true;
		}

		if (stringFlag == true)
		{
			if (stringCnt != 0 && (stringCnt / 20) % 2 == 0)
			{
				DrawString((SCREEN_SIZE_X / 2) - 120, (SCREEN_SIZE_Y / 2) - 20, "W  A  R  N  I  N  G", 0xFF0000);
			}
		}
	}

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

	//プレイヤーの表示
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
	DrawTexts();
}

// 自機の減算処理
void PlayerDeathProc(void)
{
	PlayerLife--;
	if (PlayerLife <= 0)
	{
		systemScene = SCENE_GAMEOVER;		// 残機がない場合、ｹﾞｰﾑｵｰﾊﾞｰにする
	}
}

