//---�萔---//
#define HIGH_SCR_DEF 2500	//�n�C�X�R�A�̏��
#define CLEAR_HIGH_SCORE 2500	//�Q�[���N���A�������̍ő�X�R�A

//---�񋓌^---//
//�X�R�A�p
enum SCORE
{
	SCR_PL1,
	SCR_HIGH,
	SCR_MAX
};

//---�\����---//

//---�v���g�^�C�v�錾---//
//�X�R�A�p
void InitScore(void);	//�X�R�A�̏������p
void AddScore(int num);	//�X�R�A���Z�p
void DrawTexts(void);	//�X�R�A�\���p
void EndGameDrawTexts(void);	//�Q�[�����I������ۂɕ\������e�L�X�g�\���p