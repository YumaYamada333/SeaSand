//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScreenEffect.cpp
//!
//! @brief  画面効果クラスのメンバ定義
//!
//! @date   2017/04/07
//!
//! @author 辻流己
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================

#include "ScreenEffect.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//グローバル変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－
//----------------------------------------------------------------------
//! @brief 画面効果生成
//!
//! @param[in] なし
//----------------------------------------------------------------------
ScreenEffect::ScreenEffect(int time, Vector4 rgba, Type type)
	: m_setting_time(time)
	, m_time(0)
	, m_rgba(rgba)
	, m_type(type)
	, m_is_finished(false)
{
	m_grp = { 0,0,640,480 };
	m_handle = new Texture(L"Resources\\Images\\BlackImage.png");
}

//----------------------------------------------------------------------
//! @brief 画面効果破棄
//----------------------------------------------------------------------
ScreenEffect::~ScreenEffect()
{

}

//----------------------------------------------------------------------
//! @brief 生成
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
ScreenEffect* ScreenEffect::Create(Type type, int time, Vector4 rgba)
{
	ScreenEffect* effect = nullptr;

	effect = new ScreenEffect(time, rgba, type);

	return effect;
}

//----------------------------------------------------------------------
//! @brief 処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ScreenEffect::Update()
{
	// エフェクトごとに処理
	switch (m_type)
	{
	case ScreenEffect::FadeIn:
		if (m_rgba.w > 0.0f)
		{
			m_rgba.w -= static_cast<float>(m_time) / m_setting_time;
		}
		else m_is_finished = true;
		break;
	case ScreenEffect::FadeOut:
		if (m_rgba.w < 1.0f)
		{
			m_rgba.w += static_cast<float>(m_time) / m_setting_time;
		}

		break;
	default:
		break;
	}

	m_time++;
}

//----------------------------------------------------------------------
//! @brief 座標更新
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ScreenEffect::Move()
{
	ObjectBase::Move();
}

//----------------------------------------------------------------------
//! @brief 画面効果描画
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ScreenEffect::Render() const
{
	g_spriteBatch->Draw(m_handle->m_pTexture, m_pos, &m_grp
		, m_rgba, 0.0f, m_center, Vector2(1.0f, 1.0f));

}

//----------------------------------------------------------------------
//! @brief 状態の取得
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
bool ScreenEffect::IsFinished() const
{
	return m_is_finished;
}

//----------------------------------------------------------------------
//! @brief フェードイン
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ScreenEffect::FadeInAction()
{
	m_rgba.z -= static_cast<float>(m_time) / m_setting_time;
}

//----------------------------------------------------------------------
//! @brief フェードアウト
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ScreenEffect::FadeOutAction()
{
	m_rgba.z += static_cast<float>(m_time) / m_setting_time;
}
