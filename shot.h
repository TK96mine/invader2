//�萔
//�v���C���[
#define PLAYER_SHOT_MAX 5	//�v���C���[�̒e�̘A�˂��邽�߂̏�������e��
#define PSHOT_SIZE_X 6		//�e�̉�����(���@�j
#define PSHOT_SIZE_Y 30		//�e�̏c����(���@�j
#define PSHOT_DEF_SPEED	5	//�e�̽�߰��(���@�j

//�G
#define ESHOT_X 16		//�G�̒e��X���W
#define ESHOT_Y 25		//�G�̒e��Y���W
#define ENEMY_SHOT_MAX 50	//�G�̒e�̍ő吔
#define ESHOT_SIZE_X 16		//�e�̉�����(�G�j
#define ESHOT_SIZE_Y 25		//�e�̏c����(�G�j
#define ESHOT_DEF_SPEED 5	//�e�̽�߰��(�G�j
#define ESHOT_MAX 50	//�G�e�̐�
#define ENEMY_POINT 200			//�G�X�R�A���_��

//�񋓌^

//�\����

//�v���g�^�C�v�錾
void ShotSystemInit(void);	//�e�̉摜���[�h�p
void ShotGameInit(void);	//�e�̕ϐ��̏������p
void PlayerShotControl(XY playerPos);	//�v���C���[�̒e�ړ�����
void EnemySetShot(XY enemyPos, int enemyCount);	//��ԉ��̓G�������Ēe���Z�b�g����
void EnemyShotControl(XY enemyPos, int enemyCount);	//�G�̒e�̈ړ�����
bool PlayerCheckHitEShot(XY playerPos, bool playerFlag);	//�v���C���[�ƓG�̒e�Ƃ̓����蔻��
bool EnemyCheckHitObj(XY enemyPos, bool enemyFlag);	//�G�̓����蔻��
void ShotGameDraw(void);	//�Q�[���V�[���ł̒e�̕`��p

