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
const Vector2 ObjectBase::objectPoint = Vector2(0.5f, 0.5f);

//----------------------------------------------------------------------
//! @brief オブジェクトの初期化
//!
//! @param[in] オブジェクトの情報
//----------------------------------------------------------------------
ObjectBase::ObjectBase()
{
}

ObjectBase::ObjectBase(Texture* handle, const RECT& grp, const DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 spd, int state)
	: mHandle(handle)
	, mGrp(grp)
	, mCenter(Vector2(static_cast<float>(grp.right - grp.left), static_cast<float>(grp.bottom - grp.top)) * objectPoint)
	, mPos(pos)
	, mSpd(spd)
	, mState(state)
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
	return 	mHandle = handle;
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
	return mHandle;
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
	return mGrp = rect;
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
	return mGrp;
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
	return mPos = pos;
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
	return mPos;
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
	return mSpd = spd;
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
	return mSpd;
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
	return mState = state;
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
	return mState;
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
	mPos += mSpd;
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
	int width = (mGrp.right - mGrp.left) / 2;
	int height = (mGrp.bottom - mGrp.top) / 2;
	RECT collisionBox = 
	{
		static_cast<LONG>(mPos.x - width),
		static_cast<LONG>(mPos.y - height),
		static_cast<LONG>(mPos.x + width),
		static_cast<LONG>(mPos.y + height)
	};

	width = (obj.mGrp.right - obj.mGrp.left) / 2;
	height = (obj.mGrp.bottom - obj.mGrp.top) / 2;
	RECT collisionObj =
	{
		static_cast<LONG>(obj.mPos.x - width),
		static_cast<LONG>(obj.mPos.y - height),
		static_cast<LONG>(obj.mPos.x + width),
		static_cast<LONG>(obj.mPos.y + height)
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
	g_spriteBatch->Draw(mHandle->m_pTexture, mPos, &mGrp
		, Colors::White, 0.0f, mCenter, Vector2(1.0f, 1.0f));
}
