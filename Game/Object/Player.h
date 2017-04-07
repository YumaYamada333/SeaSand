/*-------------------------------------
プレイヤークラス(Player.h)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* 多重インクルード防止 */
#pragma once

/* インクルードファイル */
#include "ObjectBase.h"

/* 使用する型 */
enum  BREAD_TYPE;

/* クラスの定義 */
class Player :public ObjectBase
{
public:
	Player(Texture* handle = nullptr, const RECT& grp = RECT(), const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0);	// コンストラクタ
	~Player();		// デストラクタ

	void Update() override;		// 更新

	void MoveLeft();	// 左移動
	void MoveRight();	// 右移動
	void MoveReset();	// 移動リセット

	void Sand(BREAD_TYPE type);	// はさむ
	bool IsSand();				// はさんでる？(移動のみ。具判定は別)

private:
	/* メンバ関数 */
	void Move()   override;		// 移動
	
	/* メンバ変数 */
	static const float SPEED_X;		// 速度Ｘ
	static const float SPEED_Y;		// 速度Ｙ
};