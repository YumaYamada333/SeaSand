//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.h
//!
//! @brief  タイトルシーンのヘッダファイル
//!
//! @date   2016/12/12
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"
#include "Object\ObjectBase.h"
class Title:public GameBase
{
private:
	// 背景画像
	Texture* m_titleback_image;
	//タイトルロゴ
	Texture* m_titlelogo_image;
	Texture* m_titlesteat_image;

	// 画面効果
	ObjectBase* m_screen_effect;

	// 画面遷移用カウンタ
	int m_next_scene_cnt;
public:
	Title();
	~Title();
	void Update();
	void Render();

};



