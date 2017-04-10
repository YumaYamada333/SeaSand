//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameClear.h
//!
//! @brief  クリアシーンのヘッダファイル
//!
//! @date   2016/12/12
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"

class Clear : public GameBase 
{
private:
	// プレイのスコア(どこかで取得)
	int m_score;
	// 時間
	float m_time;
	// 背景文字
	Texture* m_message_image;
	// 背景画像
	Texture* m_back_image;
	Texture* m_back1_image;
	// 数字
	Texture* m_score_number_image;
public:
	Clear();
	~Clear();
	void Update();
	void Render();
};
