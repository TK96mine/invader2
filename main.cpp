#include"Dxlib.h"
#include"main.h"
#include"player.h"
#include"enemy.h"
#include"shot.h"
#include"brast.h"
#include"score.h"

// �ϐ��̒�`
int gameCounter;	//�Q�[���p�J�E���^�[
int titleImage;		//���ق̉摜�i�[�p
int gameoverImage; //�ްуI�[�o�̲Ұ�ފi�[�p
bool gameScene;	//�Q�[���V�[���̏��(?)
XY titlePos;	//�^�C�g���摜�̈ʒu
XY gameoverPos;	//�Q�[���I�[�o�[�摜�̈ʒu
int systemScene;	//�V�[���̏�Ԋi�[�p

//�L�[�o�b�t�@
int spaceKeyOld;	//1�t���[���O�̃X�y�[�X�L�[�̏��
int spaceKeyNew;	//���݂̃X�y�[�X�L�[�̏��

//�J�E���^�[�p
int massageCnt;	//���b�Z�[�W�p�J�E���^�[
int stringCnt;	//�����\���̓_�ŗp�J�E���^�[

//�Q�[���N���A�p
int clearImage;	//�Q�[���N���A�̉摜�i�[�p
XY crearPos;		//�Q�[���N���A�摜�ʒu

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
	PlayerSystemInit();
	EnemySystemInit();
	ShotSystemInit();
	BrastSystemInit();

	//�w�i
	bgImage = LoadGraph("image/bgimage.jpg");
	//�^�C�g��
	 titleImage = LoadGraph("image/TitleLogo2.png");
	 //�Q�[���N���A
	 clearImage = LoadGraph("image/gameclear.png");
	 //�Q�[���I�[�o�[
	 gameoverImage = LoadGraph("image/GameOver.png");
	 gameoverBgImage = LoadGraph("image/gameoverbg2.jpg");

	return retFlag;
}

void InitScene(void)
{
	// �ϐ��̏�����
	//��ڲ԰
	PlayerGameInit();
	//�G
	EnemyGameInit();
	//�e
	ShotGameInit();

	titlePos.x = 40;
	titlePos.y = 40;
	gameoverPos.x = 50;
	gameoverPos.y = 50;
	gameScene = true;

	//�J�E���g�p
	massageCnt = 0;
	stringCnt = 0;

	//�X�R�A�p
	InitScore();

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

void Gamescene(void)
{
	//�v���C���[
	PlayerControl();
	PlayerHitEnemy();
	PlayerHitEShot();

	//�G
	EnemyControl();
	EnemyHitObj();

	if (PlayerClearCheck() == true)
	{
		systemScene = SCENE_CLEAR;
	}

	if (PlayerDeathProc() == true)
	{
		systemScene = SCENE_GAMEOVER;		// �c�@���Ȃ��ꍇ�A�ްѵ��ް�ɂ���
	}

	gameDraw();
}


void GameClear(void)
{
	DrawGraph(0, 0, clearImage, true);

	DrawString((SCREEN_SIZE_X - 140) / 2, SCREEN_SIZE_Y - 60, "PLEASE PUSH SPACEKEY", 0x0000FF);

	if (massageCnt % 45 <= 25)
	{
		DrawString((SCREEN_SIZE_X - 240) / 2, SCREEN_SIZE_Y - 40, "�X�y�[�X�L�[�������ă^�C�g���ɖ߂�", 0x000000);
	}

	EndGameDrawTexts();

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

	//�Q�[���J�E���g�̕\��
	DrawFormatString(0, 16, 0xFFFFFF, "GAME COUNT = %d", gameCounter);

	//�����̕\��
	DrawString((SCREEN_SIZE_X - 190) / 2, 350, "Thank You for Playing! ", 0xFFFF00);
	DrawString((SCREEN_SIZE_X - 180) / 2, 440, "PLEASE PUSH SPACE KEY ", 0xFFFFFF);

	if (massageCnt % 60 <= 40)
	{
		DrawString((SCREEN_SIZE_X - 225) / 2, 480, "�X�y�[�X�L�[�������Ă������� ", 0xFFFFFF);
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

	//�Q�[���J�E���g�̕\��
	DrawFormatString(GAME_OFFSET_X + 20, GAME_OFFSET_Y + 16, 0xFFFFFF, "GAME COUNT = %d", gameCounter);

	ShotGameDraw();
	PlayerGameDraw();
	EnemyGameDraw();
	DrawTexts();

	/*
	//�X�y�[�X�L�[�̏��
	DrawFormatString(0, 16, GetColor(0, 220, 250), "SPACE NEW = %d", spaceKeyNew);
	DrawFormatString(0, 32, GetColor(0, 220, 250), "SPACE OLD = %d",spaceKeyOld);
	*/
}


