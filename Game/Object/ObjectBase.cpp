//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.cpp
//!
//! @brief  オブジェクトベースクラスのメンバ定義
//!
//! @date   日付　2017年1月30日
//!
//! @author 制作者名	Ryuna Tsuji
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダーインクルード
#include "ObjectBase.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 基準点(左上0.0f ～ 1.0f右上)
const Vector2 ObjectBase::m_anchor_point = Vector2(0.5f, 0.5f);

//----------------------------------------------------------------------
//! @brief オブジェクトの初期化
//!
//! @param[in] オブジェクトの情報
//----------------------------------------------------------------------
ObjectBase::ObjectBase()
{
}

ObjectBase::ObjectBase(Texture* handle, const RECT& grp, const DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 spd, int state)
	: m_handle(handle)
	, m_grp(grp)
	, m_center(Vector2(static_cast<float>(grp.right - grp.left), static_cast<float>(grp.bottom - grp.top)) * m_anchor_point)
	, m_pos(pos)
	, m_spd(spd)
	, m_state(state)
{
}

//----------------------------------------------------------------------
//! @brief オブジェクトの破棄
//----------------------------------------------------------------------
ObjectBase::~ObjectBase()
{

}

//----------------------------------------------------------------------
//! @brief テクスチャのセット
//!
//! @param[in] テクスチャ
//!
//! @return 現在のテクスチャ
//----------------------------------------------------------------------
const Texture* ObjectBase::SetHandle(Texture* handle)
{
	return 	m_handle = handle;
}

//----------------------------------------------------------------------
//! @brief テクスチャの取得
//!
//! @param[in] なし
//!
//! @return 現在のテクスチャ
//----------------------------------------------------------------------
const Texture* ObjectBase::GetHandle() const
{
	return m_handle;
}

//----------------------------------------------------------------------
//! @brief 矩形のセット
//!
//! @param[in] 矩形(RECT)
//!
//! @return 現在の矩形
//----------------------------------------------------------------------
const RECT& ObjectBase::SetGrp(const RECT& rect)
{
	return m_grp = rect;
}

//----------------------------------------------------------------------
//! @brief 矩形の取得
//!
//! @param[in] なし
//!
//! @return 現在の矩形
//----------------------------------------------------------------------
const RECT& ObjectBase::GetGrp() const
{
	return m_grp;
}

//----------------------------------------------------------------------
//! @brief 座標のセット
//!
//! @param[in] 座標
//!
//! @return 現在の座標
//----------------------------------------------------------------------
const Vector2 ObjectBase::SetPos(const Vector2& pos)
{
	return m_pos = pos;
}

//----------------------------------------------------------------------
//! @brief 座標の取得
//!
//! @param[in] なし
//!
//! @return 現在の座標
//----------------------------------------------------------------------
const Vector2 ObjectBase::GetPos() const
{
	return m_pos;
}

//----------------------------------------------------------------------
//! @brief 速度のセット
//!
//! @param[in] 速度
//!
//! @return 現在の速度
//----------------------------------------------------------------------
const Vector2 ObjectBase::SetSpd(const Vector2& spd)
{
	return m_spd = spd;
}

//----------------------------------------------------------------------
//! @brief 速度の取得
//!
//! @param[in] 速度
//!
//! @return 現在の速度
//----------------------------------------------------------------------
const Vector2 ObjectBase::GetSpd() const
{
	return m_spd;
}

//----------------------------------------------------------------------
//! @brief 状態のセット
//!
//! @param[in] 状態
//!
//! @return 現在の状態
//----------------------------------------------------------------------
int ObjectBase::SetState(int state)
{
	return m_state = state;
}

//----------------------------------------------------------------------
//! @brief 状態の取得
//!
//! @param[in] なし
//!
//! @return 状態の取得
//----------------------------------------------------------------------
int ObjectBase::GetState() const
{
	return m_state;
}

//----------------------------------------------------------------------
//! @brief 処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ObjectBase::Update()
{
	
}

//----------------------------------------------------------------------
//! @brief 更新
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ObjectBase::Move()
{
	// 座標更新
	m_pos += m_spd;
}

//----------------------------------------------------------------------
//! @brief 判定結果
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ObjectBase::Result()
{
}

//----------------------------------------------------------------------
//! @brief あたり判定
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
bool ObjectBase::Collision(const ObjectBase& obj)
{
	int width = (m_grp.right - m_grp.left) / 2;
	int height = (m_grp.bottom - m_grp.top) / 2;
	RECT collisionBox = 
	{
		static_cast<LONG>(m_pos.x - width),
		static_cast<LONG>(m_pos.y - height),
		static_cast<LONG>(m_pos.x + width),
		static_cast<LONG>(m_pos.y + height)
	};

	width = (obj.m_grp.right - obj.m_grp.left) / 2;
	height = (obj.m_grp.bottom - obj.m_grp.top) / 2;
	RECT collisionObj =
	{
		static_cast<LONG>(obj.m_pos.x - width),
		static_cast<LONG>(obj.m_pos.y - height),
		static_cast<LONG>(obj.m_pos.x + width),
		static_cast<LONG>(obj.m_pos.y + height)
	};


	if (collisionBox.left < collisionObj.right &&
		collisionBox.top < collisionObj.bottom &&
		collisionBox.right > collisionObj.left &&
		collisionBox.bottom > collisionObj.top)
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
//! @brief 描画
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ObjectBase::Render() const
{
	g_spriteBatch->Draw(m_handle->m_pTexture, m_pos, &m_grp
		, Colors::White, 0.0f, m_center, Vector2(1.0f, 1.0f));
}
