#include"DxLib.h"
#include"main.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"brast.h"

//変数
int playerImage[PLAYER_STYLE_MAX][PLAYER_ANI_MAX];	//ﾌﾟﾚｲﾔｰの画像格納用
CHARACTER player;

void PlayerSystemInit(void)
{
	//プレイヤー
	LoadDivGraph("image/serval.png", PLAYER_STYLE_MAX * PLAYER_ANI_MAX, PLAYER_ANI_MAX, PLAYER_STYLE_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage[0]);
}

void PlayerGameInit(void)
{
	player.pos.x = (GAME_SIZE_X - PLAYER_SIZE_X) / 2;
	player.pos.y = (GAME_SIZE_Y - PLAYER_SIZE_Y);
	player.speed = (PLAYER_DEF_SPEED);
	player.flag = true;
	player.life = PLAYER_DEF_LIFE;

	PlayerBrastGameInit(player.pos);
}

//プレイヤーの処理
void PlayerControl(void)
{
	player.aniCnt++;

	if (player.flag == true)
	{
		//右移動
		if (CheckHitKey(KEY_INPUT_NUMPAD6))
		{
			if (player.pos.x >= GAME_SIZE_X - PLAYER_SIZE_X)	//移動制限
			{
				player.pos.x = GAME_SIZE_X - PLAYER_SIZE_X;
			}
			else
			{
				player.pos.x += player.speed;
			}
		}
		//左移動
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

	//弾の発射
	PlayerShotControl(player.pos);

}

void PlayerHitEnemy(void)
{
	if (PlayerCheckHitEShot(player.pos, player.flag) == true)
	{
		player.flag = false;
		PlayerDeathProc();

		if (player.life > 0)
		{
			if (player.flag == false)
			{
				player.flag = true;
			}
		}
	}

	if (PlayerCheckHitEnemy(player.pos,player.flag) == true)
	{
		player.flag = false;
		PlayerDeathProc();

		if (player.life > 0)
		{
			if (player.flag == false)
			{
				ResetEnemyPos();
				player.flag = true;
			}
		}
	}
}

void PlayerHitEShot(void)
{
	if (PlayerCheckHitEShot(player.pos,player.flag) == true)
	{
		player.flag = false;
		player.flag = true;
		PlayerDeathProc();
	}
}


// 自機の減算処理
bool PlayerDeathProc(void)
{
	player.life--;

	if (player.life <= 0)
	{
		return true;
	}

	return false;
}

void PlayerGameDraw(void)
{
	//残機数を表示
	DrawFormatString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 300, 0xFFFFFF, "PLAYER = %d", player.life);

	//プレイヤーの位置表示
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYER = ( %d, %d)", player.pos.x, player.pos.y);

	//プレイヤーの残機表示
	for (int p = 0; p < player.life; p++)
	{
		DrawGraph((GAME_SIZE_X + 20) + 40 * (p % 3), (SCREEN_SIZE_Y - 80) - PLAYER_SIZE_Y * ((p / 3) + 1), playerImage[PLAYER_STYLE_FRONT][0], true);
	}

	//プレイヤーの表示
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


