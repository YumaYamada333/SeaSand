/*-------------------------------------
プレイヤークラス(Player.h)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* 多重インクルード防止 */
#pragma once

/* インクルードファイル */
#include "ObjectBase.h"
#include "../../Common.h"

/* クラスの定義 */
class Player :public ObjectBase
{
public:
	Player(Texture* handle = nullptr, const RECT& grp = RECT(), const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0, BREAD_TYPE type = BREAD_TYPE::UP);	// コンストラクタ
	~Player();		// デストラクタ

	void Update() override;								// 更新
	void Render() const override;

	void MoveLeft();	// 左移動
	void MoveRight();	// 右移動
	void MoveReset();	// 移動リセット

	void Sand();		// はさむ
	bool IsSand();		// はさんでる？(移動のみ。具判定は別)

	void Enter();		// 入場
	bool IsEnter();		// 入場中？
	void Exit();		// 退場
	bool IsExit();		// 退場中？

private:
	/* メンバ関数 */
	void Move() override;		// 移動

	bool IsEnterComplete();		// 入場完了した？
	bool IsExitComplete();		// 退場完了した？(パンが画面外に出た)

	/* メンバ変数 */
	static const float SPEED_X;		// 速度Ｘ
	static const float SPEED_Y;		// 速度Ｙ

	static const int SCREEN_WIDTH;

	BREAD_TYPE m_type;		// パンタイプ

	bool m_is_enter;	// 入場中？
	bool m_is_exit;		// 退場中？

};