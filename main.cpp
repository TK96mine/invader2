#include"Dxlib.h"
#include"main.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"brast.h"
#include"score.h"

// 変数の定義
int gameCounter;	//ゲーム用カウンター
int titleImage;		//ﾀｲﾄﾙの画像格納用
int gameoverImage; //ｹﾞｰﾑオーバのｲﾒｰｼﾞ格納用
bool gameScene;	//ゲームシーンの状態(?)
XY titlePos;	//タイトル画像の位置
XY gameoverPos;	//ゲームオーバー画像の位置
int systemScene;	//シーンの状態格納用

//キーバッファ
int spaceKeyOld;	//1フレーム前のスペースキーの状態
int spaceKeyNew;	//現在のスペースキーの状態

//カウンター用
int massageCnt;	//メッセージ用カウンター
int stringCnt;	//文字表示の点滅用カウンター

//ゲームクリア用
int clearImage;	//ゲームクリアの画像格納用
XY crearPos;		//ゲームクリア画像位置

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
	EnemySystemInit();
	ShotSystemInit();
	BrastSystemInit();

	//背景
	bgImage = LoadGraph("image/bgimage.jpg");
	//タイトル
	 titleImage = LoadGraph("image/TitleLogo2.png");
	 //ゲームクリア
	 clearImage = LoadGraph("image/gameclear.png");
	 //ゲームオーバー
	 gameoverImage = LoadGraph("image/GameOver.png");
	 gameoverBgImage = LoadGraph("image/gameoverbg2.jpg");

	return retFlag;
}

void InitScene(void)
{
	// 変数の初期化
	//ﾌﾟﾚｲﾔｰ
	PlayerGameInit();
	//敵
	EnemyGameInit();
	//弾
	ShotGameInit();

	titlePos.x = 40;
	titlePos.y = 40;
	gameoverPos.x = 50;
	gameoverPos.y = 50;
	gameScene = true;

	//カウント用
	massageCnt = 0;
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

void Gamescene(void)
{
	//プレイヤー
	PlayerControl();
	PlayerHitEnemy();
	PlayerHitEShot();

	//敵
	EnemyControl();
	EnemyHitObj();

	if (PlayerClearCheck() == true)
	{
		systemScene = SCENE_CLEAR;
	}

	if (PlayerDeathProc() == true)
	{
		systemScene = SCENE_GAMEOVER;		// 残機がない場合、ｹﾞｰﾑｵｰﾊﾞｰにする
	}

	gameDraw();
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

	//ゲームカウントの表示
	DrawFormatString(GAME_OFFSET_X + 20, GAME_OFFSET_Y + 16, 0xFFFFFF, "GAME COUNT = %d", gameCounter);

	ShotGameDraw();
	PlayerGameDraw();
	EnemyGameDraw();
	DrawTexts();

	/*
	//スペースキーの状態
	DrawFormatString(0, 16, GetColor(0, 220, 250), "SPACE NEW = %d", spaceKeyNew);
	DrawFormatString(0, 32, GetColor(0, 220, 250), "SPACE OLD = %d",spaceKeyOld);
	*/
}


