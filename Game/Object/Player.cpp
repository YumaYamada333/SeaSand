/*-------------------------------------
プレイヤークラスの定義(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* インクルードファイル */
#include "Player.h"

#include "../../Common.h"

/* 名前空間の使用 */
// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* 静的メンバ変数の定義 */
// TODO:プレイヤー速度はここで調整！
const float Player::SPEED_X = 5.0f;		// 速度Ｘ
const float Player::SPEED_Y = 10.0f;	// 速度Ｙ

const int Player::SCREEN_WIDTH = 640;	// 画像の幅(作業用)

/* メンバ関数の定義 */
/*------------------------------------
Player::Player

summary:コンストラクタ
param  :なし(void)
return :存在しない
------------------------------------*/
Player::Player(Texture * handle, const RECT &grp, const Vector2 pos, Vector2 spd, int state, BREAD_TYPE type)
	:ObjectBase(handle,grp,pos,spd,state),
	 m_type(type),
	 m_is_enter(false),
	 m_is_exit(false)
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
	if (m_is_enter)
	{
		Enter();
	}

	Move();
}

void Player::Render() const
{
	//TODO:画像の幅、高さはここで調整！
	RECT rect = { 0,0,180,180 };		// 画像の幅、高さ
	
	g_spriteBatch->Draw(m_handle->m_pTexture, m_pos, &rect
		, Colors::White, 0.0f, m_center, Vector2(1.0f, 1.0f));
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
	if (!IsSand() && !m_is_exit)
	{
		SetSpd(Vector2(0.0f, 0.0f));
	}
}

/*--------------------------------------------
Player::Sand

summary:はさむ
param  :なし(void)
return :なし(void)
--------------------------------------------*/
void Player::Sand()
{
	switch (m_type)
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
Player::Enter

summary:入場
param  :なし(void)
return :なし(void)
------------------------------------*/
void Player::Enter()
{
	/* スタート位置に修正(マジックナンバーごめんなさい) */
	switch (m_type)
	{
	case UP:
		SetPos(Vector2(m_pos.x, 5.0f));
		break;

	case DOWN:
		SetPos(Vector2(m_pos.x, 360.0f));
		break;
	}

	MoveLeft();

	/* 入場完了 */
	if (IsEnterComplete())
	{
		m_is_enter = false;
		// TODO:残機減らす
	}
}

/*------------------------------------
Player::IsEnter

summary:入場中？
param  :なし(void)
return :入場中(true)、ちがう(false)
------------------------------------*/
bool Player::IsEnter()
{
	return m_is_enter;
}

/*------------------------------------
Player::Exit

summary:退場
param  :なし(void)
return :なし(void)
------------------------------------*/
void Player::Exit()
{
	MoveRight();
	m_is_exit = true;

	/* 退場したらまた入場 */
	if (IsExitComplete())
	{
		m_is_exit  = false;
		m_is_enter = true;
	}

}

/*------------------------------------
Player::IsExit

summary:退場中？
param  :なし(void)
return :退場中(true)、ちがう(false)
------------------------------------*/
bool Player::IsExit()
{
	return m_is_exit;
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

/*------------------------------------
Player::IsEnterComplete

summary:入場完了した？
param  :なし(void)
return :完了(true)、ちがう(false)
------------------------------------*/
bool Player::IsEnterComplete()
{
	if (m_pos.x <= 300.0f)		// スタート位置(マジックナンバーごめんなさい)
	{
		return true;
	}
	return false;
}

/*------------------------------------
Player::IsExitComplete

summary:退場完了した？
param  :なし(void)
return :完了(true)、ちがう(false)
------------------------------------*/
bool Player::IsExitComplete()
{
	/* 画面外に出ているか？ */
	if ((m_pos.x - 100.0f) >= SCREEN_WIDTH)		// 100は入場位置修正
	{
		return true;
	}

	return false;
}