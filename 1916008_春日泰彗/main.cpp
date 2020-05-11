#include"Dxlib.h"

#include"main.h"

// �ϐ��̒�`
int gameCounter;	//�Q�[���p�J�E���^�[
int titleImage;		//���ق̉摜�i�[�p
int gameoverImage; //�ްуI�[�o�̲Ұ�ފi�[�p
bool gameScene;	//�Q�[���V�[���̏��(?)
int titlePosX;	//�^�C�g���摜�̉����̈ʒu
int titlePosY;	//�^�C�g���摜�̏c���̈ʒu
int gameoverPosX;	//�Q�[���I�[�o�[�摜�̉����̈ʒu
int gameoverPosY;	//�Q�[���I�[�o�[�摜�̏c���̈ʒu
int systemScene;	//�V�[���̏�Ԋi�[�p
int score[SCR_MAX];	//�X�R�A�ۑ��p

//��ڲ԰�̕ϐ�
int PlayerImage[PLAYER_STYLE_MAX][PLAYER_ANI_MAX];	//��ڲ԰�̉摜�i�[�p
int PlayerPosX;		//��ڲ԰��X���W
int PlayerPosY;		//��ڲ԰��Y���W
int PlayerSpeed;	//��ڲ԰�̽�߰��
bool PlayerFlag;		//��ڲ԰���׸�
int PlayerLife;		//�c�@

//�G�̕ϐ�
int EnemyImage[ENEMY_TYPE_MAX][ENEMY_ANI_MAX];	//�G�̉摜�i�[�p
int EnemyPosX[ENEMY_Y][ENEMY_X];	//�G�̉����̃|�W�V����
int EnemyPosY[ENEMY_Y][ENEMY_X];	//�G�̏c���̃|�W�V����
int EnemySpeed;	//�G�̈ړ����x
bool EnemyFlag[ENEMY_Y][ENEMY_X];	//�G�̐����m�F�p�ϐ�
MOVE_MODE EnemyMoveMode;	//�G�̈ړ����[�h
MOVE_LR EnemyMoveX;	//�G�̉����ړ�
ENEMY_TYPE enemyType[ENEMY_Y][ENEMY_X];	//�G�̎��
int EnemyCount;	//�G�̐�
int enemyAddSpeed;	//�G�@�̈ړ����x�ɉ����鑬�x

//�e�̕ϐ�
//��ڲ԰
int PShotImage;	//�v���C���[�̒e�̉摜�i�[�p
int PShotPosX;	//�v���C���[�̒e�̉����̈ʒu
int PShotPosY;	//�v���C���[�̒e�̏c���̈ʒu
int PShotSpeed;	//�v���C���[�̒e�̈ړ����x
bool PShotFlag;	//�v���C���[�̒e�̔��ˏ��
//�G
int EShotImage;	//�G�̒e�̉摜�i�[�p
int EShotPosX[ESHOT_MAX];	//�G�̒e�̉����ʒu
int EShotPosY[ESHOT_MAX];	//�G�̒e�̏c���ʒu
int EShotSpeed;	//�G�̒e�̑��x
bool EShotFlag[ESHOT_MAX];	//�G�̒e�̏��

//����
int playerbakuImage[BAKU_ANI];	//�����摜�i�[�p
int playerbakuPosX;	//�����摜�̉����ʒu
int playerbakuPosY;	//�����摜�̏c���ʒu
int playerbakuAni;	//�����̃A�j���[�V�����p
bool playerbakuFlag;	//�����摜�̏��
int enemybakuImage[BAKU_ANI];	//�����摜�i�[�p
int enemybakuPosX;	//�����摜�̉����ʒu
int enemybakuPosY;	//�����摜�̏c���ʒu
int enemybakuAni;	//�����̃A�j���[�V�����p
bool enemybakuFlag;	//�����摜�̏��

//�L�[�o�b�t�@
int spaceKeyOld;	//1�t���[���O�̃X�y�[�X�L�[�̏��
int spaceKeyNew;	//���݂̃X�y�[�X�L�[�̏��

//�J�E���^�[�p
int massageCnt;	//���b�Z�[�W�p�J�E���^�[
int enemyMoveCnt;	//�G�̈ړ��p�J�E���^�[
int playerAniCnt;	//�v���C���[�̃A�j���[�V�����p�J�E���^�[
int stringCnt;	//�����\���̓_�ŗp�J�E���^�[

//�Q�[���N���A�p
int clearImage;	//�Q�[���N���A�̉摜�i�[�p
int crearPosX;		//�Q�[���N���A�摜�̉����ʒu
int clearPosY;		//�Q�[���N���A�摜�̏c���ʒu

//�w�i�p
int bgImage;
int gameoverBgImage;

//�����\���p
bool stringFlag;


//winmain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	//����������
	if (!SystemInit())
	{
		return -1;
	}

	SystemInit();

	//�ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�X�y�[�X�L�[�̏�Ԋm�F
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

		ScreenFlip();//��ʓ���ւ�
	}

	DxLib_End();
	return 0;
}

bool SystemInit(void)
{
	bool retFlag = true; //�֐��̖߂�l

	//���я���
	SetWindowText("1916008_�t���לa");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == 1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	// ���̨���̓o�^
	//�G�̒e
	EShotImage = LoadGraph("image/eshot.png");
	if (LoadGraph("image/eshot.png") == -1)
	{
		AST();
		retFlag = false;
	}
	//�v���C���[
	LoadDivGraph("image/serval.png", PLAYER_STYLE_MAX * PLAYER_ANI_MAX, PLAYER_ANI_MAX, PLAYER_STYLE_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, PlayerImage[0]);
	if (LoadDivGraph("image/serval.png", PLAYER_STYLE_MAX * PLAYER_ANI_MAX, PLAYER_ANI_MAX, PLAYER_STYLE_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, PlayerImage[0]) == -1)
	{
		AST();
		retFlag = false;
	}
	//�w�i
	bgImage = LoadGraph("image/bgimage.jpg");
	if (LoadGraph("image/bgimage.jpg") == -1)
	{
		AST();
		retFlag = false;
	}

	//����
	LoadDivGraph("image/blast.png", 24, 6, 4, BAKU_SIZE_X, BAKU_SIZE_Y, playerbakuImage);
	if (LoadDivGraph("image/blast.png", 24, 6, 4, BAKU_SIZE_X, BAKU_SIZE_Y, playerbakuImage) == -1)
	{
		AST();
		retFlag = false;
	}
	//�G
	LoadDivGraph("image/cellien.png", ENEMY_TYPE_MAX * ENEMY_ANI_MAX, ENEMY_ANI_MAX, ENEMY_TYPE_MAX, ENEMY_SIZE_X, ENEMY_SIZE_Y, EnemyImage[0]);
	if (LoadDivGraph("image/cellien.png", ENEMY_TYPE_MAX * ENEMY_ANI_MAX, ENEMY_ANI_MAX, ENEMY_TYPE_MAX, ENEMY_SIZE_X, ENEMY_SIZE_Y, EnemyImage[0])== -1)
	{
		AST();
		retFlag = false;
	}
	//�v���C���[�̒e
	PShotImage = LoadGraph("image/pshot.png");
	if (LoadGraph("image/pshot.png") == -1)
	{
		AST();
		retFlag = false;
	}
	//�^�C�g��
	 titleImage = LoadGraph("image/TitleLogo2.png");
	 if (LoadGraph("image/TitleLogo2.png") == -1)
	 {
		 AST();
		 retFlag = false;
	 }
	 //�Q�[���N���A
	 clearImage = LoadGraph("image/gameclear.png");
	 if (LoadGraph("image/gameclear.png") == -1)
	 {
		 AST();
		 retFlag = false;
	 }

	 //�Q�[���I�[�o�[
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
	// �ϐ��̏�����
	score[SCR_PL1] = 0;

	//��ڲ԰
	PlayerPosX = (GAME_SIZE_X - PLAYER_SIZE_X) / 2;
	PlayerPosY = (GAME_SIZE_Y - PLAYER_SIZE_Y);
	PlayerSpeed = (PLAYER_DEF_SPEED);
	PlayerFlag = true;
	PlayerLife = PLAYER_DEF_LIFE;

	//�G
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

	//�e
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

	//����
	playerbakuPosX = PlayerPosX;
	playerbakuPosY = PlayerPosY;
	playerbakuAni = 0;
	playerbakuFlag = false;

	//�J�E���g�p
	massageCnt = 0;
	enemyMoveCnt = 0;
	stringCnt = 0;

	//�����\���p
	stringFlag = false;

	systemScene = SCENE_TITLE;
}




//�^�C�g��
void TitleScene(void)
{
	DrawGraph(GAME_OFFSET_X, GAME_OFFSET_Y, bgImage, true);
	DrawGraph(((GAME_SIZE_X - GAMETITLE_SIZE_X) + 50 ) / 2, ((SCREEN_SIZE_Y / 2) - GAMETITLE_SIZE_Y), titleImage, true);
	DrawString((GAME_SIZE_X - 130) / 2, 310, "PLEASE PUSH SPACE KEY", 0xFFFFFF);

	if (massageCnt % 60 <= 40)
	{
		DrawString((GAME_SIZE_X - 180) / 2, 350, "�X�y�[�X�L�[�������Ă�������", 0xFFFFFF);
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyNew != spaceKeyOld)
	{
  		systemScene = SCENE_GAME;
	}

	DrawTexts();
}

//�v���C���[�̏���
void playerControl(void)
{

	if (PlayerFlag == true)
	{
		//�E�ړ�
		if (CheckHitKey(KEY_INPUT_NUMPAD6))
		{
			if (PlayerPosX  >= GAME_SIZE_X - PLAYER_SIZE_X)	//�ړ�����
			{
				PlayerPosX = GAME_SIZE_X - PLAYER_SIZE_X;
			}
			else
			{
				PlayerPosX += PlayerSpeed;
			}
		}
		//���ړ�
		if (CheckHitKey(KEY_INPUT_NUMPAD4))
		{
			if (PlayerPosX - PlayerSpeed <= 0    /*GAME_OFFSET_X*/)
			{
				PlayerPosX = 0;
			}
			else
			{
				PlayerPosX -= PlayerSpeed;
			}
		}
	}
}

//�G�̏���
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
			//�ړ�����
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (EnemyFlag[y][x])
					{
						//-----�G�̈ړ�����
						//���ړ�
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

						//�c�ړ�
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
			//�ړ�����
			for (int y = 0; y < ENEMY_Y; y++)
			{
				for (int x = 0; x < ENEMY_X; x++)
				{
					if (EnemyFlag[y][x])
					{
						//-----�G�̈ړ�����
						//���ړ�
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

						//�c�ړ�
						if (EnemyMoveMode == MOVE_MODE_DOWN)
						{
							EnemyPosY[y][x] += ENEMY_SIZE_Y;
						}

					}
				}
			}
		}
	}


	//Min��Max���v�Z����
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			if (EnemyFlag[y][x])
			{
				//-----�G�̈ړ�����
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

	//�ړ������𔻒f����
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
	//�v���C���[�̒e�̑���
	if (PShotFlag == false)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			PShotFlag = true;
			PShotPosX = PlayerPosX + (PLAYER_SIZE_X - PSHOT_SIZE_X) / 2;
			PShotPosY = PlayerPosY;
		}
	}

	//��ڲ԰�̒e�̑���
	if (PShotFlag == true)
	{
		PShotPosY -= PShotSpeed;
		if (PShotPosY < 0)
		{
			PShotFlag = false;
		}
	}

	//�G�̒e�̑���
	for (int x = 0; x < ENEMY_X; x++)
	{
		for (int y = ENEMY_Y - 1; y >= 0; y--)	//1�ԃv���C���[�ɋ߂�(1�ԉ���)�������Ă���G���������G(�G�̏c���̐� - 1)�������琔���Ă���
		{
			if (EnemyFlag[y][x] == true)
			{
				//�G�@��������؂������A���˒i���𑝂₷
				if (EnemyCount < ENEMY_MAX / 2)
				{
					if (GetRand(30) == 1)	//0����30�܂ł̐��l�𗐐��ŕԂ��Ă��̒l��1�̎��ɏ�������
					{
						//�G�̒e�̔���
						for (int e = 0; e < ESHOT_MAX; e++)
						{
							if (EShotFlag[e] == false)
							{
								//���̗��1�ԉ��̐������Ă���G���������ꍇ�̏���
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
					if (GetRand(500) == 1)	//0����500�܂ł̐��l�𗐐��ŕԂ��Ă��̒l��1�̎��ɏ�������
					{
						//�G�̒e�̔���
						for (int e = 0; e < ESHOT_MAX; e++)
						{
							if (EShotFlag[e] == false)
							{
								//���̗��1�ԉ��̐������Ă���G���������ꍇ�̏���
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

	//�G�̒e�̐���
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (EShotFlag[e] == true)
		{
			EShotPosY[e] += EShotSpeed;		//�G�̒e�̈ړ�

			if (EShotPosY[e] > GAME_SIZE_Y)		//�G�̒e���Q�[����ʊO�ɏo���Ƃ���������
			{
				EShotFlag[e] = false;	//�G�̒e�̃t���O��false�ɂ���
			}
		}
	}
}


//�����蔻��
void CheckHitObj(void)
{
	for (int y = 0; y < ENEMY_Y; y++)
	{
		for (int x = 0; x < ENEMY_X; x++)
		{
			//���@�̒e�ƓG�̓����蔻��
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

			//�G�Ǝ��@�Ƃ̓����蔻��
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

				//�G�̒e�Ǝ��@�Ƃ̓����蔻��
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
				*/

				/*
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
	DrawFormatString((SCREEN_SIZE_X / 2) - 70, SCREEN_SIZE_Y / 2, 0xFF00FF, "HIGH SCORE = %d", score[SCR_HIGH]);
	if (massageCnt % 40 >= 20)
	{
		DrawFormatString((SCREEN_SIZE_X / 2) - 50, (SCREEN_SIZE_Y / 2) + 20, 0xFF00FF, "SCORE = %d", score[SCR_PL1]);
	}

	if (score[SCR_PL1] >= score[SCR_HIGH] && score[SCR_PL1] != 0)
	{
		DrawString((SCREEN_SIZE_X - 100) / 2, (SCREEN_SIZE_Y / 2) + 40, "'New Record' ", 0xFFD700);
	}

	DrawString((SCREEN_SIZE_X - 140) / 2, SCREEN_SIZE_Y - 60, "PLEASE PUSH SPACEKEY", 0x0000FF);

	if (massageCnt % 45 <= 25)
	{
		DrawString((SCREEN_SIZE_X - 240) / 2, SCREEN_SIZE_Y - 40, "�X�y�[�X�L�[�������ă^�C�g���ɖ߂�", 0x000000);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyNew != spaceKeyOld)
	{
		systemScene = SCENE_INIT;
	}
}


//�Q�[���I�[�o�[
void GameOverScene(void)
{
	//�Q�[���I�[�o�[�V�[��
	DrawExtendGraph(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, gameoverBgImage, true);
	DrawGraph((SCREEN_SIZE_X - GAMEOVER_SIZE_X) / 2, (SCREEN_SIZE_Y - (GAMEOVER_SIZE_Y * 2)) / 2, gameoverImage, true);

	//�v���C���[�̈ʒu�\��
	DrawFormatString(0, 0, 0xFFFFFF, "PLAYER = ( %d, %d)", PlayerPosX, PlayerPosY);
	//�Q�[���J�E���g�̕\��
	DrawFormatString(0, 16, 0xFFFFFF, "GAME COUNT = %d", gameCounter);

	//�����̕\��
	DrawString((SCREEN_SIZE_X - 190) / 2, 350, "Thank You for Playing! ", 0xFFFF00);
	DrawString((SCREEN_SIZE_X - 180) / 2, 440, "PLEASE PUSH SPACE KEY ", 0xFFFFFF);

	if (score[SCR_PL1] >= score[SCR_HIGH] && score[SCR_PL1] != 0)
	{
		if (massageCnt % 60 <= 20)
		{
			DrawString((SCREEN_SIZE_X - 100) / 2, (SCREEN_SIZE_Y / 2) + 80, "'New Record' ", 0x00FFFF);
		}
	}

	if (massageCnt % 60 <= 40)
	{
		DrawString((SCREEN_SIZE_X - 225) / 2, 480, "�X�y�[�X�L�[�������Ă������� ", 0xFFFFFF);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && spaceKeyNew != spaceKeyOld)
	{
		systemScene = SCENE_INIT;
	}


	DrawTexts();

}

void gameDraw(void)
{
	DrawGraph(GAME_OFFSET_X, GAME_OFFSET_Y, bgImage, true);

	//�c�@����\��
	DrawFormatString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 300, 0xFFFFFF, "PLAYER = %d", PlayerLife);

	//�v���C���[�̈ʒu�\��
	DrawFormatString(GAME_OFFSET_X + 20, GAME_OFFSET_Y, 0xFFFFFF, "PLAYER = ( %d, %d)", PlayerPosX, PlayerPosY);

	//�Q�[���J�E���g�̕\��
	DrawFormatString(GAME_OFFSET_X + 20, GAME_OFFSET_Y + 16, 0xFFFFFF, "GAME COUNT = %d", gameCounter);

	/*
	//�X�y�[�X�L�[�̏��
	DrawFormatString(0, 16, GetColor(0, 220, 250), "SPACE NEW = %d", spaceKeyNew);
	DrawFormatString(0, 32, GetColor(0, 220, 250), "SPACE OLD = %d",spaceKeyOld);
	*/

	//�v���C���[�̎c�@�\��
	for (int p = 0; p < PlayerLife; p++)
	{
		DrawGraph((GAME_SIZE_X + 20) + 40 * (p % 3), (SCREEN_SIZE_Y - 80) - PLAYER_SIZE_Y * ((p / 3) + 1), PlayerImage[PLAYER_STYLE_FRONT][0], true);
	}

	//�G�̕\��
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

	//�G�@��������؂������̕\��
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

	//�e�̕\��
	//��ڲ԰�̒e�̕\��
	if (PShotFlag == true)
	{
		DrawGraph(PShotPosX + GAME_OFFSET_X, PShotPosY + GAME_OFFSET_Y, PShotImage, true);
	}
	//�G�̒e�̕\��
	for (int e = 0; e < ESHOT_MAX; e++)
	{
		if (EShotFlag[e] == true)
		{
			DrawGraph(EShotPosX[e] + GAME_OFFSET_X, EShotPosY[e] + GAME_OFFSET_Y, EShotImage, true);
		}
	}

	//�v���C���[�̕\��
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

void DrawTexts(void)
{
	int drawScore;
	int drawLengh;
	int textColor = 0xFFFFFF;

	//�n�C�X�R�A
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X )+ 50, 70, "HIGH", textColor);
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 77, 90, "SCORE", textColor);

	drawScore = (score[SCR_HIGH] >= 100000 ? 99999 : score[SCR_HIGH]);
	drawLengh = GetDrawFormatStringWidth("%d", drawScore);
	DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 100 - drawLengh, 120, textColor, "%d", drawScore);

	//PL1
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 170, "SCORE", textColor);

	drawScore = (score[SCR_PL1] >= 100000 ? 99999 : score[SCR_PL1]);
	drawLengh = GetDrawFormatStringWidth("%d", drawScore);
	DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 100 - drawLengh, 200, textColor, "%d", drawScore);

}


//�X�R�A�̉��Z����
void AddScore(int num)
{
	//�X�R�A����
	score[SCR_PL1] += num;

	//�X�R�A�̍X�V
	if (score[SCR_PL1] > score[SCR_HIGH])
	{
		score[SCR_HIGH] = score[SCR_PL1];
	}
}

// ���@�̌��Z����
void PlayerDeathProc(void)
{
	PlayerLife--;
	if (PlayerLife <= 0)
	{
		systemScene = SCENE_GAMEOVER;		// �c�@���Ȃ��ꍇ�A�ްѵ��ް�ɂ���
	}
}

