/*-------------------------------------
プレイヤークラスの定義(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* インクルードファイル */
#include "Player.h"

/* 名前空間の使用 */
using namespace DirectX::SimpleMath;

/* 静的メンバ変数の定義 */
const float Player::SPEED_X = 10.0f;		// 速度Ｘ

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
Player::Player

summary:コンストラクタ
param  :なし(void)
return :存在しない
------------------------------------*/
Player::~Player()
{}

void Player::Update()
{
	Move();
}

void Player::Move()
{
	m_pos += m_spd;
}

void Player::MoveLeft()
{
	SetSpd(Vector2(-SPEED_X, 0.0f));
}

void Player::MoveRight()
{
	SetSpd(Vector2(SPEED_X, 0.0f));
}

void Player::MoveReset()
{
	SetSpd(Vector2(0.0f, 0.0f));
}
