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

class Title:public GameBase
{
private:
	// 背景画像
	Texture* m_titleback_image;
	//タイトルロゴ
	Texture* m_titlelogo_image;
	Texture* m_titlesteat_image;

public:
	Title();
	~Title();
	void Update();
	void Render();

};



