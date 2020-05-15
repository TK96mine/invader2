//定数

//列挙型

//構造体

//プロトタイプ宣言
void ShotSystemInit(void);	//弾の画像ロード用
void ShotGameInit(void);	//弾の変数の初期化用
void PlayerShotControl(XY playerPos);	//プレイヤーの弾移動処理
void EnemyShotControl(XY enemyPos, bool enemyFlag, int enemyCount);	//敵の弾の移動処理
bool PlayerCheckHitEShot(XY playerPos, bool playerFlag);	//プレイヤーと敵の弾との当たり判定
bool EnemyCheckHitObj(XY enemyPos, bool enemyFlag);	//敵の当たり判定
void ShotGameDraw(void);	//ゲームシーンでの弾の描画用

