//�A�T�[�g�̒�`
#ifdef _DEBUG
#define AST() {\
	CHAR ast_msg[256];\
	wsprintf(ast_msg, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_msg, "�A�T�[�g�\��", MB_OK);\
	}
#else
#define AST()
#endif

//�萔
#define SCREEN_SIZE_X 800	//��ʂ̉�����
#define SCREEN_SIZE_Y 600	//��ʂ̏c����

#define GAMETITLE_SIZE_X 423	//�Q�[���̃^�C�g���̉��T�C�Y
#define GAMETITLE_SIZE_Y 198	//�Q�[���̃^�C�g���̏c�T�C�Y

#define GAME_SIZE_X 640	//�Q�[����ʂ̉��T�C�Y
#define GAME_SIZE_Y 480	//�Q�[����ʂ̏c�T�C�Y
#define GAME_SCREEN_X 20	//�Q�[����ʂ̕`��I�t�Z�b�g
#define GAME_SCREEN_Y 50	//�Q�[����ʂ̕`��I�t�Z�b�g
#define GAME_SCREEN_SIZE_X 600	//�Q�[����ʂ̉��T�C�Y
#define GAME_SCREEN_SIZE_Y 500	//�Q�[����ʂ̏c�T�C�Y
#define GAME_OFFSET_X 20	//�Q�[����ʂ̉��I�t�Z�b�g
#define GAME_OFFSET_Y 20	//�Q�[����ʂ̏c�I�t�Z�b�g

#define GAMEOVER_SIZE_X 452	//�Q�[���I�[�o�[�̉��T�C�Y
#define GAMEOVER_SIZE_Y 123	//�Q�[���I�[�o�[�̏c�T�C�Y
#define GAMEOVER_BGSIZE_X 640	//�Q�[���I�[�o�[�w�i�̉��T�C�Y
#define GAMEOVER_BGSIZE_Y 320	//�Q�[���I�[�o�[�w�i�̏c�T�C�Y


//�񋓌^�̒�`
//�Q�[���V�[���p
enum SCENE		
{
	SCENE_INIT,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_CLEAR,
	SCENE_GAMEOVER,
	SCENE_MAX
};

//�\����
struct XY
{
	int x;
	int y;
};

struct CHARACTER
{
	XY pos;	//�ʒu���i�[�p
	int speed;	//�ړ��ʊi�[�p
	bool flag;	//�����m�F�p
	int life;	//�c��@�̐�
	int aniCnt;	//�A�j���[�V�����p�J�E���^�[
	int type;	//���
};

//�v���g�^�C�v�錾
//������
bool SystemInit(void);	//�ϐ�
void InitScene(void);	//�V�[��

//�V�[���p
void TitleScene(void);	//�^�C�g��
void Gamescene(void);	//�Q�[��
void GameOverScene(void);	//�Q�[���I�[�o�[
void GameClear(void);	//�Q�[���N���A

//�摜�̕`��p
void gameDraw(void);	//�摜�̕`��

//���ʂ̉�ʃ��C�A�E�g
void gameDraw(void);	//�摜�̕`��

/*
//�v���C���[�̎��S�p
void playerDeathProc(void);
*/

