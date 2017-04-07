//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScreenEffect.h
//!
//! @brief  画面効果クラスの定義
//!
//! @date   2017/04/07
//!
//! @author 辻流己
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include "..\ObjectBase.h"

class ScreenEffect : public ObjectBase
{
public:
	// 生成タイプ
	enum Type
	{
		Fade
	};
private:
	// 設定時間
	int m_setting_time;
	// 計測用の時間
	int m_time;

	// 初期化
	ScreenEffect();
public:
	// 破棄
	~ScreenEffect();

	// エフェクトの生成
	const ScreenEffect& Create(Type type);

	// あたり判定は行わない
	bool Collision(const ObjectBase& obj) override { return false; };

	// 更新
	void Update() override;

	// 座標更新
	void Move() override;

	// 描画
	void Render() const override;

};
