//�萔

//�񋓌^

//�\����

//�v���g�^�C�v�錾
void ShotSystemInit(void);	//�e�̉摜���[�h�p
void ShotGameInit(void);	//�e�̕ϐ��̏������p
void PlayerShotControl(XY playerPos);	//�v���C���[�̒e�ړ�����
void EnemyShotControl(XY enemyPos, bool enemyFlag, int enemyCount);	//�G�̒e�̈ړ�����
bool PlayerCheckHitEShot(XY playerPos, bool playerFlag);	//�v���C���[�ƓG�̒e�Ƃ̓����蔻��
bool EnemyCheckHitObj(XY enemyPos, bool enemyFlag);	//�G�̓����蔻��
void ShotGameDraw(void);	//�Q�[���V�[���ł̒e�̕`��p

