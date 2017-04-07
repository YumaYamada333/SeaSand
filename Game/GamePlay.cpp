//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  ゲームプレイ処理のソースファイル
//!
//! @date   2016/11/04		
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GamePlay.h"
#include "Food\Food.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//グローバル変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－
int g_count;

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－
//----------------------------------------------------------------------
//! @brief プレイコンストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Play::Play()
{
	
}

//----------------------------------------------------------------------
//! @brief プレイデストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Play::~Play()
{
	//食材の破棄
	for (int i = 0; i < FOOD_NUM; i++)
	{
		delete m_food[i];
	}
}

//----------------------------------------------------------------------
//! @brief ゲームプレイ処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::Update()
{
	//シーンの最初に一回だけ行う初期化処理
	if (g_init == 0)
	{
		//めざすライン
		int line_num = GetRand(F_LINE_NUM);
		//食材の出現
		for (int i = 0; i < FOOD_NUM; i++)
		{
			//食材の種類
			int food_type = GetRand(FOOD_TYPE_NUM);
			//食材の行動パターン
			int move_type = GetRand(F_MOVE_TYPE_NUM);
			m_food[i] = new Food(food_type, move_type, i, line_num);
		}

		g_init = 1;
	}	
	//食材の更新
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i]->Update();
	}

	//食材の移動
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i]->Move();
	}
	/*if (g_mouse.leftButton)
	{
		g_NextScene = CLEAR;
	}*/
}

//----------------------------------------------------------------------
//! @brief ゲームプレイ描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::Render()
{
	wchar_t buf[256];

	swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));

	//食材の描画
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i]->Render();
	}
}
