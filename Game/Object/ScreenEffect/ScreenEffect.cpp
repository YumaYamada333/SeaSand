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

//グローバル変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝−

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝−
//----------------------------------------------------------------------
//! @brief 画面効果生成
//!
//! @param[in] なし
//----------------------------------------------------------------------
ScreenEffect::ScreenEffect()
	: m_setting_time(0)
	, m_time(0)
{

}

//----------------------------------------------------------------------
//! @brief 画面効果破棄
//----------------------------------------------------------------------
ScreenEffect::~ScreenEffect()
{

}

//----------------------------------------------------------------------
//! @brief 処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
const ScreenEffect& ScreenEffect::Create(Type type)
{
	switch (type)
	{
	default:
		break;
	}
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
	float a = 
	g_spriteBatch->Draw(m_handle->m_pTexture, m_pos, &m_grp
		, Vector4(1.0f, 1.0f,1.0f, a), 0.0f, m_center, Vector2(1.0f, 1.0f));

}

