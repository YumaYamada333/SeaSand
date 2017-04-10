//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   MessagePlate.cpp
//!
//! @brief  メッセージ板のソースファイル
//!
//! @date   2017/04/10
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//ヘッダのインクルード＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "..\..\GameMain.h"
#include "MessagePlate.h"

//名前空間＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
using namespace DirectX;
using namespace DirectX::SimpleMath;

//定数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//スピード
const float MP_SPEED = -640.0f / 60.0f;

//移動制御時間
const int MOVE_TIME = 60;
const int WATE_TIME = 30;

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//----------------------------------------------------------------------
//! @brief メッセージ板のコンストラクタ
//!
//! @param[in] 食材の情報
//----------------------------------------------------------------------
MessagePlate::MessagePlate(int type)
	:m_time(0)
	,m_type(type)
{
	//種類を設定
	m_state = MP_MOVE;
	//テクスチャを設定
	SetTexture();
	//初期位置とスピードを設定
	SetInitPos();
}

//----------------------------------------------------------------------
//! @brief メッセージ板のデストラクタ
//!
//! @param[in] なし
//----------------------------------------------------------------------
MessagePlate::~MessagePlate()
{
	delete m_handle;
}

//----------------------------------------------------------------------
//! @brief メッセージ板の更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void MessagePlate::Update()
{
	m_time++;

	//移動状態なら移動
	if (m_state == MP_MOVE)
	{
		//移動
		if (m_time < MOVE_TIME)
		{
			m_spd = Vector2(MP_SPEED, 0.0f);
		}
		//待機
		if (m_time >= MOVE_TIME && m_time < MOVE_TIME + WATE_TIME)
		{
			m_spd = Vector2(0.0f, 0.0f);
		}
		//移動
		if (m_time >= MOVE_TIME + WATE_TIME)
		{
			m_spd = Vector2(MP_SPEED, 0.0f);
		}
	}

	//左端まで行ったら消える
	if (m_pos.x < -SCREEN_WIDTH)
	{
		m_state = MP_NONE;
	}
}

//----------------------------------------------------------------------
//! @brief メッセージ板のテクスチャを設定する関数
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void MessagePlate::SetTexture()
{
	//テクスチャの設定
	switch (m_type)
	{
	case START:
		m_handle = new Texture(L"Resources\\Images\\start.png");
		break;
	case NEXT:
		m_handle = new Texture(L"Resources\\Images\\next.png");
		break;
	case FINISH:
		m_handle = new Texture(L"Resources\\Images\\finish.png");
		break;
	}

	//基準点の設定
	m_center = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//短形の設定
	m_grp = { 0, 0, static_cast<LONG>(SCREEN_WIDTH), static_cast<LONG>(SCREEN_HEIGHT) };
}

//----------------------------------------------------------------------
//! @brief 初期位置を設定する関数
//!
//! @param[in] 指定秒数でめざすライン(番号)
//!
//! @return なし
//----------------------------------------------------------------------
void MessagePlate::SetInitPos()
{
	m_pos = Vector2(static_cast<float>(SCREEN_WIDTH + SCREEN_WIDTH / 2), static_cast<float>(SCREEN_HEIGHT / 2));
	m_spd = Vector2(MP_SPEED, 0.0f);
}