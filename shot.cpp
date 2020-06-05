#include"DxLib.h"
#include"math.h"
#include"main.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"score.h"

//•Ï”
//ƒvƒŒƒCƒ„[
int pShotImage;	//ƒvƒŒƒCƒ„[‚Ì’e‚Ì‰æ‘œŠi”[—p
CHARACTER pShot[PLAYER_SHOT_MAX];	//ƒvƒŒƒCƒ„[‚Ì’e

//“G
int eShotImage;	//“G‚Ì’e‚Ì‰æ‘œŠi”[—p
CHARACTER eShot[ESHOT_MAX];	//“G‚Ì’e‚Ì‰¡²ˆÊ’u

void ShotSystemInit(void)
{
	//ƒvƒŒƒCƒ„[‚Ì’e
	pShotImage = LoadGraph("image/pshot.png");

	//“G‚Ì’e
	eShotImage = LoadGraph("image/eshot.png");
}

void ShotGameInit(void)
{
	for (int s = 0; s < PLAYER_SHOT_MAX; s++)
	{
		pShot[s].pos.y = 0;
		pShot[s].pos.x = 0;
		pShot[s].speed = PSHOT_DEF_SPEED;
		pShot[s].flag = false;
	}


	for (int e = 0; e < ESHOT_MAX; e++)
	{
		eShot[e].pos.x = 0;
		eShot[e].pos.y = 0;
		eShot[e].speed = ESHOT_DEF_SPEED;
		eShot[e].flag = false;
	}
}

void PlayerShotControl(XY playerPos)
{
	//ƒvƒŒƒCƒ„[‚Ì’e‚Ì‘€ì
	for (int s = 0; s < PLAYER_SHOT_MAX; s++)
	{
		if (pShot[s].flag == false)
		{
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				pShot[s].flag = true;
				pShot[s].pos.x = playerPos.x + (PLAYER_SIZE_X - PSHOT_SIZE_X) / 2;
				pShot[s].pos.y = playerPos.y;
			}
		}

		if (pShot[s].flag == true)
		{
			pShot[s].pos.y -= pShot[s].speed;
			if (pShot[s].pos.y < 0)
			{
				pShot[s].flag = false;
			}
		}
	}
}

void EnemySetShot(XY enemyPos, int enemyCount)
{
	//“G‚Ì’e‚Ì”­Ë
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == false)
		{
			//‚»‚Ì—ñ‚Å1”Ô‰º‚Ì¶‘¶‚µ‚Ä‚¢‚é“G‚ğŒ©‚Â‚¯‚½ê‡‚Ìˆ—
			eShot[e].pos.x = enemyPos.x + (ENEMY_SIZE_X - ESHOT_SIZE_X) / 2;
			eShot[e].pos.y = enemyPos.y;
			eShot[e].flag = true;
			break;
		}
	}
}

void EnemyShotControl(XY enemyPos, int enemyCount)
{
	int rand = GetRand(100);	//0`100‚Ü‚Å‚Ì—”‚ğŠm•Û‚µA‚»‚ê‚ğ•Ï”‚ÉŠi”[

	//“G‚Ì’e‚Ì‘€ì
	//“G‹@‚ª”¼•ª‚ğØ‚Á‚½A”­Ë’i”‚ğ‘‚â‚·
	if (enemyCount < ENEMY_MAX / 2)
	{
		if (rand <= 5)	
		{
			EnemySetShot(enemyPos,enemyCount);
		}
	}
	else
	{
		if (rand == 1)
		{
			//“G‚Ì’e‚Ì”­Ë
			for (int e = 0; e < ESHOT_MAX; e++)
			{
				EnemySetShot(enemyPos, enemyCount);
			}
		}
	}

	//“G‚Ì’e‚Ì§Œä
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == true)
		{
			eShot[e].pos.y +=  eShot[e].speed;		//“G‚Ì’e‚ÌˆÚ“®

			if (eShot[e].pos.y > GAME_SIZE_Y)		//“G‚Ì’e‚ªƒQ[ƒ€‰æ–ÊŠO‚Éo‚½‚Æ‚«ˆ—‚·‚é
			{
				eShot[e].flag = false;	//“G‚Ì’e‚Ìƒtƒ‰ƒO‚ğfalse‚É‚·‚é
			}
		}
	}
}

//ƒvƒŒƒCƒ„[‚Æ“G‚Ì’e‚Ì“–‚½‚è”»’è
bool PlayerCheckHitEShot(XY playerPos,bool playerFlag)
{
	//“G‚Ì’e‚Æ©‹@‚Æ‚Ì“–‚½‚è”»’è
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

//©‹@‚Ì’e‚Æ“G‚Ì“–‚½‚è”»’è
bool EnemyCheckHitObj(XY enemyPos,bool enemyFlag)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			for (int s = 0; s < PLAYER_SHOT_MAX; s++)
			{
				//©‹@‚Ì’e‚Æ“G‚Ì“–‚½‚è”»’è
				if (pShot[s].flag == true)
				{
					if (enemyPos.x + ENEMY_SIZE_X >= pShot[s].pos.x
						&& enemyPos.x <= pShot[s].pos.x + PSHOT_SIZE_X
						&& enemyPos.y + ENEMY_SIZE_Y >= pShot[s].pos.y
						&& enemyPos.y <= pShot[s].pos.y + PSHOT_SIZE_Y
						&& enemyFlag == true)
					{
						pShot[s].flag = false;

						return true;
					}
				}
			}
		}
	}

	return false;
}

void ShotGameDraw(void)
{
	//’e‚Ì•\¦
	//ÌßÚ²Ô°‚Ì’e‚Ì•\¦
	for (int s = 0; s < PLAYER_SHOT_MAX; s++)
	{
		if (pShot[s].flag == true)
		{
			DrawGraph(pShot[s].pos.x + GAME_OFFSET_X, pShot[s].pos.y + GAME_OFFSET_Y, pShotImage, true);
		}
	}
	//“G‚Ì’e‚Ì•\¦
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (eShot[e].flag == true)
		{
			DrawGraph(eShot[e].pos.x + GAME_OFFSET_X, eShot[e].pos.y + GAME_OFFSET_Y, eShotImage, true);
		}
	}
}