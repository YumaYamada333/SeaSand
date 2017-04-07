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
#include <cassert>		// assert

#include "../Common.h"

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
	:m_bread(nullptr)
{
	InitBread();
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
	ReleaseBread();
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
		g_init = 1;
	}

	m_bread[UP]->MoveReset();
	m_bread[DOWN]->MoveReset();

	/* キー入力 */
	// TODO:関数化候補
	if (!(m_bread[UP]->IsSand()))
	{
		if (g_key.Left)					// 左移動
		{
			m_bread[UP]->MoveLeft();
			m_bread[DOWN]->MoveLeft();
		}
		else if (g_key.Right)			// 右移動
		{
			m_bread[UP]->MoveRight();
			m_bread[DOWN]->MoveRight();
		}
		else if (g_key.Space)			// はさむ
		{
			m_bread[UP]->Sand(UP);
			m_bread[DOWN]->Sand(DOWN);
		}
	}

	m_bread[UP]->Update();
	m_bread[DOWN]->Update();

	/* パン同士のあたり判定 */
	if (m_bread[UP]->Collision(*(dynamic_cast<ObjectBase*>(m_bread[DOWN]))))
	{
		m_bread[UP]->SetSpd(Vector2(0.0f, 0.0f));
		m_bread[DOWN]->SetSpd(Vector2(0.0f, 0.0f));
	}

	//if (g_mouse.leftButton)
	//{
	//	g_NextScene = CLEAR;
	//}
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
	m_bread[UP]->Render();
	m_bread[DOWN]->Render();

	wchar_t buf[256];
	swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));
}

/*------------------------------------
Play::InitPlayer

summary:パン初期化
param  :なし(void)
return :なし(void)
------------------------------------*/
void Play::InitBread()
{
	// TODO:パンの各パラメーターはここで変更！
	const int BREAD_NUM = 2;			// パンの数
	Texture* bread_handle = new Texture(L"Resources/Images/bread.png");
	assert(bread_handle != nullptr);

	const RECT    BREAD_RECT           = { 0,0,100,20 };
	const Vector2 BREAD_POS[BREAD_NUM] = { Vector2(100.0f,100.0f),Vector2(100.0f,400.0f) };

	/* パン生成 */
	m_bread = new Player*[BREAD_NUM];	// 動的配列確保
	m_bread[UP]   = new Player(bread_handle, BREAD_RECT, BREAD_POS[UP]);
	m_bread[DOWN] = new Player(bread_handle, BREAD_RECT, BREAD_POS[DOWN]);

}

/*------------------------------------
Play::ReleaseBread

summary:パン解放
param  :なし(void)
return :なし(void)
------------------------------------*/
void Play::ReleaseBread()
{
	DeleteMemory(m_bread[UP]);
	DeleteMemory(m_bread[DOWN]);
	DeleteArrayMemory(m_bread);
}
