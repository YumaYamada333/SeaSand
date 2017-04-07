/*-------------------------------------
プレイヤークラスの定義(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* インクルードファイル */
#include "Player.h"

#include "../../Common.h"

/* 名前空間の使用 */
using namespace DirectX::SimpleMath;

/* 静的メンバ変数の定義 */
// TODO:プレイヤー速度はここで調整！
const float Player::SPEED_X = 5.0f;		// 速度Ｘ
const float Player::SPEED_Y = 10.0f;		// 速度Ｙ

/* メンバ関数の定義 */
/*------------------------------------
Player::Player

summary:コンストラクタ
param  :なし(void)
return :存在しない
------------------------------------*/
Player::Player(Texture * handle, const RECT &grp, const Vector2 pos, Vector2 spd, int state)
	:ObjectBase(handle,grp,pos,spd,state)
{}

/*------------------------------------
Player::~Player

summary:デストラクタ
param  :存在しない
return :存在しない
------------------------------------*/
Player::~Player()
{}

/*------------------------------------
Player::Update

summary:更新
param  :なし(void)
return :なし(void)
------------------------------------*/
void Player::Update()
{
	Move();
}

/*------------------------------------
Player::MoveLeft

summary:左移動
param  :なし(void)
return :なし(void)
------------------------------------*/
void Player::MoveLeft()
{
	SetSpd(Vector2(-SPEED_X, 0.0f));
}

/*------------------------------------
Player::MoveRight

summary:右移動
param  :なし(void)
return :なし(void)
------------------------------------*/
void Player::MoveRight()
{
	SetSpd(Vector2(SPEED_X, 0.0f));
}

/*------------------------------------
Player::MoveReset

summary:移動リセット
param  :なし(void)
return :なし(void)
------------------------------------*/
void Player::MoveReset()
{
	if (!IsSand())
		SetSpd(Vector2(0.0f, 0.0f));
}

/*--------------------------------------------
Player::Sand

summary:はさむ
param  :食パンタイプ(BREAD_TYPE)
return :なし(void)
--------------------------------------------*/
void Player::Sand(BREAD_TYPE type)
{
	switch (type)
	{
	case UP:
		SetSpd(Vector2(0.0f, SPEED_Y));
		break;

	case DOWN:
		SetSpd(Vector2(0.0f, -SPEED_Y));
		break;
	}
}

/*--------------------------------------------
Player::IsSand

summary:はさんでる？
param  :なし(void)
return :はさんでる(true)、はさんでない(false)
--------------------------------------------*/
bool Player::IsSand()
{
	return m_spd.y != 0.0f ? true : false;
}

/*------------------------------------
Player::Move

summary:移動
param  :なし(void)
return :なし(void)
------------------------------------*/
void Player::Move()
{
	m_pos += m_spd;
}