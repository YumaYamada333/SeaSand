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
#include "Food\Food.h"

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
	, m_bread_num(BREAD_NUM)
	, m_wave_clear(true)
{
	ADX2Le::Play(CRI_CUESHEET_0_RESULTBGM, 1.0f, true);
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
		g_init = 1;

		//食材の出現
		FoodAwake();
	}


	m_bread[UP]->MoveReset();
	m_bread[DOWN]->MoveReset();

	/* キー入力 */
	//TODO:関数化候補
	if (!(m_bread[UP]->IsSand()) && !(m_bread[UP]->IsExit()) && !(m_bread[UP]->IsEnter()))
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
			m_bread[UP]->Sand();
			m_bread[DOWN]->Sand();
		}
	}

	m_bread[UP]->Update();
	m_bread[DOWN]->Update();
		
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

	/* パン同士のあたり判定 */
	if (m_bread[UP]->Collision(*(dynamic_cast<ObjectBase*>(m_bread[DOWN]))))
	{
		m_bread[UP]->SetSpd(Vector2(0.0f, 0.0f));
		m_bread[DOWN]->SetSpd(Vector2(0.0f, 0.0f));

		m_bread[UP]->Exit();
		m_bread[DOWN]->Exit();
	}

	//WAVEの更新
	UpdateWave();

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
	m_bread[DOWN]->Render();		// 下のパン

	//食材の描画
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//食材が存在している状態なら
		if (m_food[i] != nullptr)
		{
			m_food[i]->Render();
		}
	}

	m_bread[UP]->Render();			// 上のパン

	wchar_t buf[256];
	swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));
}

//----------------------------------------------------------------------
//! @brief WAVEの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::UpdateWave()
{
	//移動中の魚がいなければクリア
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (m_food[i]->GetState() == F_NONE)
		{
			m_wave_clear = true;
		}
		else
		{
			m_wave_clear = false;
		}
	}
	//クリア時の処理
	if (m_wave_clear)
	{
		//食材の解放
		for (int i = 0; i < FOOD_NUM; i++)
		{
			delete m_food[i];
			m_food[i] = nullptr;
		}
		//パンの枚数を減らす
		m_bread_num--;
		//パンの枚数が残っていたら
		if (m_bread_num > 0)
		{
			//食材の再出現
			FoodAwake();
		}
		else
		{
			//ゲーム終了
			g_NextScene = CLEAR;
		}
	}
}

//----------------------------------------------------------------------
//! @brief 食材を出現させる
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::FoodAwake()
{
	//食材がめざすライン
	int line_num = GetRand(F_LINE_NUM);
	//食材が集まる時間
	int meet_time = GetRand(WAVE_TIME) + 1;
	//食材の出現
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//食材の種類
		int food_type = GetRand(FOOD_TYPE_NUM);
		//出現
		m_food[i] = new Food(food_type, i, line_num, meet_time);
	}
	//waveを開始
	m_wave_clear = false;
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

	const RECT    BREAD_COLLISION_RECT = { 0,0,180,45 };		// 当たり判定の幅、高さ
	const Vector2 BREAD_POS[BREAD_NUM] = { Vector2(300.0f,5.0f),Vector2(300.0f,360.0f) };		// それぞれのスタートライン(上、下)

	/* パン生成 */
	m_bread       = new Player*[BREAD_NUM];	// 配列を動的確保
	m_bread[UP]   = new Player(bread_handle, BREAD_COLLISION_RECT, BREAD_POS[UP], Vector2(0.0f, 0.0f), 0, UP);
	m_bread[DOWN] = new Player(bread_handle, BREAD_COLLISION_RECT, BREAD_POS[DOWN], Vector2(0.0f, 0.0f), 0, DOWN);

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
