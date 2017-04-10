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

class Food;

//定数
const int FOOD_NUM = 4;		//画面内に1度に出てくる食材の数

//クラス
class Play:public GameBase
{
private:
	Player** m_bread;		// 食パン
	Food* m_food[FOOD_NUM];
	
	void InitBread();		// パン初期化
	void ReleaseBread();	// パン開放

public:
	Play();
	~Play();
	void Update();
	void Render();

	void FoodAwake();

};
