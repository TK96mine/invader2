//�萔
#define PLAYER_SIZE_X 48	//��ڲ԰�̉�����
#define PLAYER_SIZE_Y 48	//��ڲ԰�̏c����
#define PLAYER_DEF_SPEED 2	//��ڲ԰�̽�߰��
#define PLAYER_DEF_LIFE 5	//�v���C���[�̃f�t�H���g�̃��C�t
#define PLAYER_ANI_MAX 2	//�v���C���[�̃A�j���[�V��������摜��

//�񋓌^
//�v���C���[�̌���
enum PLAYER_STYLE
{
	PLAYER_STYLE_BACK,
	PLAYER_STYLE_FRONT,
	PLAYER_STYLE_MAX
};

//�\����

//�v���g�^�C�v�錾
void PlayerSystemInit(void);	//�v���C���[�̉摜�ǂݍ��ݐ�p
void PlayerGameInit(void);	//�v���C���[�̕ϐ��̏������p
void PlayerControl(void);	//�v���C���[�̈ړ����̏����p
