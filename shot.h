//定数
//プレイヤー
#define PLAYER_SHOT_MAX 5	//プレイヤーの弾の連射するための所持上限弾数
#define PSHOT_SIZE_X 6		//弾の横ｻｲｽﾞ(自機）
#define PSHOT_SIZE_Y 30		//弾の縦ｻｲｽﾞ(自機）
#define PSHOT_DEF_SPEED	5	//弾のｽﾋﾟｰﾄﾞ(自機）

//敵
#define ESHOT_X 16		//敵の弾のX座標
#define ESHOT_Y 25		//敵の弾のY座標
#define ENEMY_SHOT_MAX 50	//敵の弾の最大数
#define ESHOT_SIZE_X 16		//弾の横ｻｲｽﾞ(敵）
#define ESHOT_SIZE_Y 25		//弾の縦ｻｲｽﾞ(敵）
#define ESHOT_DEF_SPEED 5	//弾のｽﾋﾟｰﾄﾞ(敵）
#define ESHOT_MAX 50	//敵弾の数
#define ENEMY_POINT 200			//敵スコア得点数

//列挙型

//構造体

//プロトタイプ宣言
void ShotSystemInit(void);	//弾の画像ロード用
void ShotGameInit(void);	//弾の変数の初期化用
void PlayerShotControl(XY playerPos);	//プレイヤーの弾移動処理
void EnemySetShot(XY enemyPos, int enemyCount);	//一番下の敵を見つけて弾をセットする
void EnemyShotControl(XY enemyPos, int enemyCount);	//敵の弾の移動処理
bool PlayerCheckHitEShot(XY playerPos, bool playerFlag);	//プレイヤーと敵の弾との当たり判定
bool EnemyCheckHitObj(XY enemyPos, bool enemyFlag);	//敵の当たり判定
void ShotGameDraw(void);	//ゲームシーンでの弾の描画用

