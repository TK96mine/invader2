#include"Dxlib.h"

#include"main.h"

#include"score.h"

//�ϐ��̐ݒ�
int score[SCR_MAX];	//�X�R�A�ۑ��p
int drawTextsCnt;	//�\������e�L�X�g�_�ŗp�J�E���^�[


//�X�R�A������������
void InitScore(void)
{
	//�n�C�X�R�A�̍X�V
	if (score[SCR_PL1] > score[SCR_HIGH])
	{
		score[SCR_HIGH] = score[SCR_PL1];
	}

	//�ϐ��̏�����
	score[SCR_PL1] = 0;
	drawTextsCnt = 0;
}

//�X�R�A�̉��Z����
void AddScore(int num)
{
	//�X�R�A����
	score[SCR_PL1] += num;
}

//�X�R�A�\���p
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

	DrawFormatString((SCREEN_SIZE_X / 2) - 70, SCREEN_SIZE_Y / 2, 0xFF00FF, "HIGH SCORE = %d", score[SCR_HIGH]);

	if (drawTextsCnt % 40 >= 20)
	{
		DrawFormatString((SCREEN_SIZE_X / 2) - 50, (SCREEN_SIZE_Y / 2) + 20, 0xFF00FF, "SCORE = %d", score[SCR_PL1]);
	}

	if (score[SCR_PL1] >= score[SCR_HIGH] && score[SCR_PL1] != 0)
	{
		if (drawTextsCnt % 60 <= 20)
		{
			DrawString((SCREEN_SIZE_X - 100) / 2, (SCREEN_SIZE_Y / 2) + 80, "'New Record' ", 0x00FFFF);
		}
	}
}