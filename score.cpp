#include"Dxlib.h"

#include"main.h"

#include"player.h"

#include"enemy.h"

#include"score.h"

//�ϐ��̐ݒ�
int score[SCR_MAX];	//�X�R�A�ۑ��p
int drawTextsCnt;	//�\������e�L�X�g�_�ŗp�J�E���^�[
bool addScr;	//�v���C���[�̎c�@�ɉ������X�R�A�̉��Z���s�����߂̃t���O


//�X�R�A������������
void InitScore(void)
{
	//�n�C�X�R�A�̍X�V
	if (score[SCR_TOTAL] > score[SCR_HIGH])
	{
		score[SCR_HIGH] = score[SCR_TOTAL];
	}

	//�ϐ��̏�����
	score[SCR_TOTAL] = 0;
	score[SCR_PL1] = 0;
	drawTextsCnt = 0;
	addScr = false;
}

//�X�R�A�̉��Z����
void AddScore(int num)
{
	//�X�R�A����
	score[SCR_PL1] += num;
}

void EndAddScore(int playerLife,int num)
{
	if (addScr == false)
	{
		score[SCR_PLAYER_NUM] += playerLife * num;
		score[SCR_TOTAL] = score[SCR_PLAYER_NUM] + score[SCR_PL1];
		addScr = true;
	}
	else
	{

	}
}

void DrawTexts(void)
{
	//�v���C���̃X�R�A�i�[�p
	int drawScore;	
	//�\�����镶����̒����i�[�p
	int drawLengh;	
	//�����̐F(16�i��)�i�[�p
	int textColor = 0xFFFFFF;	

	//--�n�C�X�R�A--//
	//"HIGH SCORE"�ƕ\������
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 70, "HIGH", textColor);
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 77, 90, "SCORE", textColor);

	//�n�C�X�R�A�̏����ݒ�
	drawScore = (score[SCR_HIGH] >= 100000 ? 99999 : score[SCR_HIGH]);

	//�\������X�R�A�̕�����̒����𒲂ׂ�
	drawLengh = GetDrawFormatStringWidth("%d", drawScore);

	//�v���C���̃X�R�A��\������
	DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 100 - drawLengh, 120, textColor, "%d", score[SCR_HIGH]);

	//--�X�R�A--//
	//"SCORE"�ƕ\������
	DrawString((GAME_SCREEN_X + GAME_SCREEN_SIZE_X) + 50, 170, "SCORE", textColor);

	//�X�R�A�̏����ݒ�
	drawScore = (score[SCR_PL1] >= 100000 ? 99999 : score[SCR_PL1]);

	//�\������X�R�A�̕�����̒����𒲂ׂ�
	drawLengh = GetDrawFormatStringWidth("%d", drawScore);

	//�X�R�A��\������
	DrawFormatString(GAME_SCREEN_X + GAME_SCREEN_SIZE_X + 100 - drawLengh, 200, textColor, "%d", drawScore);
}


//�Q�[�����I������ۂɕ\������X�R�A���̕\���p
void EndGameDrawTexts(void)
{
	//�e�L�X�g�p�J�E���^�[�̃J�E���g������
	drawTextsCnt++;

	DrawFormatString((SCREEN_SIZE_X / 2) - 70, (SCREEN_SIZE_Y / 2) + 20, 0xFF00FF, "HIGH SCORE = %d", score[SCR_HIGH]);

	if (drawTextsCnt % 40 >= 20)
	{
		DrawFormatString((SCREEN_SIZE_X / 2) - 50, (SCREEN_SIZE_Y / 2) + 40, 0xFF00FF, "SCORE = %d", score[SCR_TOTAL]);
	}

	if (score[SCR_PL1] >= score[SCR_HIGH] && score[SCR_PL1] != 0)
	{
		if (drawTextsCnt % 60 <= 20)
		{
			DrawString((SCREEN_SIZE_X - 100) / 2, (SCREEN_SIZE_Y / 2) + 80, "'New Record' ", 0x00FFFF);
		}
	}
}

void PlayerCliarScoreDraw(int playerLife, int num)
{
	int e = LoseEnemyNum();
	int pCliarScore = PlayerAtackEnemyScore();

	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 40, 0x00FF00, "�|�����@�̐� : %d �~ score : %d = %d", e, num, pCliarScore);
	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 20, 0x00FF00, "playerlife : %d �~ score : %d = %d", playerLife, num, score[SCR_PLAYER_NUM]);
	DrawFormatString((SCREEN_SIZE_X / 2) - 250, SCREEN_SIZE_Y / 2, 0x00FF00, "Score : %d + �v���C���[�̎c�胉�C�t���̃X�R�A : %d = %d", score[SCR_PL1], score[SCR_PLAYER_NUM], score[SCR_TOTAL]);
}

void PlayerGameOverScoreDraw(int playerLife, int num)
{
	int e = LoseEnemyNum();
	int pLoseScore = PlayerAtackEnemyScore();

	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 40, 0x00FF00, "�|�����@�̐� : %d �~ score : %d = %d", e, num, pLoseScore);
	DrawFormatString((SCREEN_SIZE_X / 2) - 200, (SCREEN_SIZE_Y / 2) - 20, 0x00FF00, "playerlife : %d �~ score : %d = %d", playerLife, num, score[SCR_PLAYER_NUM]);
	DrawFormatString((SCREEN_SIZE_X / 2) - 150, SCREEN_SIZE_Y / 2, 0x00FF00, "Score : %d + �v���C���[�̎c�胉�C�t���̃X�R�A : %d = %d", score[SCR_PL1], score[SCR_PLAYER_NUM], score[SCR_TOTAL]);
}

void PlayerAtackEnemyScore(int enemyCount)
{

}