//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  プレイシーンのヘッダファイル
//!
//! @date   2016/12/12
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"
#include "Object\Player.h"

//クラス
class Play:public GameBase
{
private:
	static enum		// パン区別
	{
		UP,		// 上のパン
		DOWN,	// 下のパン
	};

	Player** m_bread;		// 食パン
	
	void InitBread();		// パン初期化
	void ReleaseBread();	// パン開放

public:
	Play();
	~Play();
	void Update();
	void Render();
};
