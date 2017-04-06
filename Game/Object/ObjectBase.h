//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ObjectBase.h
//!
//! @brief  オブジェクトベースクラスの定義
//!
//! @date   日付　2017年1月30日
//!
//! @author 制作者名	Ryuna Tsuji
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルード防止
#pragma once

// ヘッダーインクルード
#include <d3d11.h>
#include <SimpleMath.h>
#include "..\..\DirectXTK.h"
#include "..\..\Texture.h"

//　クラス定義
class ObjectBase
{
protected:
	// オブジェクト全体の基準点
	static const DirectX::SimpleMath::Vector2 objectPoint;

	// グラフィックハンドル 
	Texture* mHandle;
	// 元画像
	RECT mGrp;
	// 基準点
	DirectX::SimpleMath::Vector2 mCenter;
	// 座標
	DirectX::SimpleMath::Vector2 mPos;
	// 速度
	DirectX::SimpleMath::Vector2 mSpd;
	// 状態
	int mState;		

public:
	// 初期化
	ObjectBase();
	ObjectBase(Texture* handle, const RECT& grp, const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0);

	// 破棄
	virtual ~ObjectBase();

	// ハンドル
	const Texture* SetHandle(Texture* handle);
	const Texture* GetHandle() const;

	// 元画像
	const RECT& SetGrp(const RECT& rect);
	const RECT& ObjectBase::GetGrp() const;

	// 座標
	const DirectX::SimpleMath::Vector2 ObjectBase::SetPos(const DirectX::SimpleMath::Vector2& pos);
	const DirectX::SimpleMath::Vector2 ObjectBase::GetPos() const;

	// 速度
	const DirectX::SimpleMath::Vector2 SetSpd(const DirectX::SimpleMath::Vector2& spd);
	const DirectX::SimpleMath::Vector2 GetSpd() const;

	// 状態
	int SetState(int state);
	int GetState() const;

	// 処理
	virtual void Update();

	// あたり判定
	virtual bool Collision(const ObjectBase& obj);

	// 座標更新
	virtual void Move();

	// 判定結果
	virtual void Result();

	// 描画
	virtual void Render() const;
};
