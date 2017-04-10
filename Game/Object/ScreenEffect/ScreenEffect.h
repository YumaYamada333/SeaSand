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
		FadeIn,
		FadeOut
	};

private:
	// 設定時間
	int m_setting_time;
	// 計測用の時間
	int m_time;
	// 終了した
	bool m_is_finished;
	// RGBA
	DirectX::SimpleMath::Vector4 m_rgba;

	//// 使用する画面エフェクト
	//void(*m_effect)();

	// タイプ
	Type m_type;

	// 初期化
	ScreenEffect(int time, DirectX::SimpleMath::Vector4 rgba, Type type);

public:
	// 破棄
	~ScreenEffect();

	// エフェクトの生成
	static ScreenEffect* Create(Type type, int time, DirectX::SimpleMath::Vector4 rgba);

	// 判定は行わない
	bool Collision(const ObjectBase& obj) override { return false; };

	// 更新
	void Update() override;

	// 座標更新
	void Move() override;

	// 描画
	void Render() const override;

	// 状態の取得
	bool IsFinished() const;

private:
	// フェードイン
	void FadeInAction();

	// フェードアウト
	void FadeOutAction();

};
