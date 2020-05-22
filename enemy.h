//�萔
#define ENEMY_DEF_SCORE 100	//�G��̂ɂ�������X�R�A�̃f�t�H���g�̒l

//�񋓌^
//�G�̍��E�̈ړ��p
enum MOVE_LR
{
	MOVE_LR_LEFT,
	MOVE_LR_RIGHT,
	MOVE_LR_MAX
};

//�G�̏㉺�̈ړ��p
enum MOVE_MODE
{
	MOVE_MODE_LR,
	MOVE_MODE_DOWN,
	MOVE_MODE_MAX
};

//�G�̎��
enum ENEMY_TYPE
{
	ENEMY_TYPE_NON,
	ENEMY_TYPE_RED,
	ENEMY_TYPE_BLUE,
	ENEMY_TYPE_GREEN,
	ENEMY_TYPE_ORANGE,
	ENEMY_TYPE_MAX
};


//�\����



//�v���g�^�C�v�錾
void EnemySystemInit(void);	//�G�̉摜���[�h�p
void EnemyGameInit(void);	//�G�̕ϐ��������p
void EnemyControl(void);	//�G�̈ړ����̏����p
bool PlayerCheckHitEnemy(XY playerPos, bool playerFlag);	//�v���C���[�ƓG�̓����蔻��
void EnemyHitObj(void);		//�G�Ǝ��@�̒e�������������̏���
void ResetEnemyPos(void);	//�v���C���[�ƓG�����������ۂɓG�̈ʒu������������
bool PlayerClearCheck(void);	//�v���C���[���N���A���������肷�邽�߂̊֐�
int LoseEnemyNum(void);	//�G�̓|�����@�̐���Ԃ�l�Ƃ��ĕԂ��֐�
int PlayerAtackEnemyScore(void);	//�v���C���[���|�����G�̐��ɉ������X�R�A�̕\��(�Ԃ�l�Ƃ��ăX�R�A�̍��v��Ԃ�(loseEnemyNum * score))
void EnemyGameDraw(void);	//�G�̃Q�[���V�[���ł̕`��p
