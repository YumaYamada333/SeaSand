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
#include "Object\MessagePlate\MessagePlate.h"

#include "../Common.h"

#include "Object\ScreenEffect\ScreenEffect.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//グローバル変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝−
int g_count;

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝−
//----------------------------------------------------------------------
//! @brief プレイコンストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Play::Play()
	
	:m_bread(nullptr)
	,m_bread_num(BREAD_NUM)
	,m_wave_clear(false)
	,m_time(0)
	,m_plate(nullptr)
{
	// 画像読み込み
	m_backplay_image = new Texture(L"Resources\\Images\\PlayBackImage.png");

	//ポインタの初期化
	for (int i = 0; i < FOOD_NUM; i++)
	{
		m_food[i] = nullptr;
	}
	InitBread();

	// screenエフェクト
	m_screen_effect = ScreenEffect::Create(ScreenEffect::Type::FadeIn, 1.5f * 60, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	// プレイbgmの再生
	ADX2Le::Play(CRI_CUESHEET_0_PLAYBGM, 1.0f, true);
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

	if (m_screen_effect)
	{
		delete m_screen_effect;
	}
	//メッセージ板の破棄
	delete m_plate;

	// プレイ再生BGM停止
	ADX2Le::Stop();
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
		g_score = 0;
		//m_time++;
		//プレートの出現
		if (m_plate == nullptr)
		{
			m_plate = new MessagePlate(START);
		}
		
		//プレートが消えたら
		if (m_plate->GetState() == MP_NONE)
		{
			//プレートの破棄
			delete m_plate;
			m_plate = nullptr;

			//食材の出現
			FoodAwake();

			/* パン登場 */
			m_bread[UP]->SetEnter();
			m_bread[DOWN]->SetEnter();

			g_init = 1;
		}
	}

	// screen効果の更新
	if (m_screen_effect)
	{
		m_screen_effect->Update();
		if (dynamic_cast<ScreenEffect*>(m_screen_effect)->IsFinished())
		{
			delete m_screen_effect;
			m_screen_effect = nullptr;
		}
		return;
	}

	if (!(m_bread[UP]->IsEnter()))
	{
		m_bread[UP]->MoveReset();
		m_bread[DOWN]->MoveReset();
	}

	/* キー入力 */
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
		else if (g_keyTracker->pressed.Space)			// はさむ
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
		//食材が存在している状態なら
		if (m_food[i] != nullptr)
		{
			m_food[i]->Update();
		}
	}
	//メッセージ板の更新
	if (m_plate != nullptr)
	{
		m_plate->Update();
	}
	
	//食材の移動
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//食材が存在している状態なら
		if (m_food[i] != nullptr)
		{
			m_food[i]->Move();
		}
	}
	//メッセージの移動
	if (m_plate != nullptr)
	{
		m_plate->Move();
	}

	//パンと食材が当たったら
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//食材が存在している状態なら
		if (m_food[i] != nullptr)
		{
			if (m_bread[UP]->Collision(*(dynamic_cast<ObjectBase*>(m_food[i]))) &&
				m_bread[UP]->IsSand())
			{
				m_food[i]->HitBread(*m_bread[UP]);
			}
			if (m_bread[DOWN]->Collision(*(dynamic_cast<ObjectBase*>(m_food[i]))) &&
				m_bread[DOWN]->IsSand())
			{
				m_food[i]->HitBread(*m_bread[DOWN]);
			}
		}
	}

	/* パンと具のあたり判定 */
	for (int i = 0; i < FOOD_NUM; ++i)
	{
		//食材が存在している状態なら
		if (m_food[i] != nullptr)
		{
			if (m_bread[UP]->IsSand())			// はさむ処理をしてるときだけ判定
			{
				/* 上のパン */
				if (m_bread[UP]->Collision(*(dynamic_cast<ObjectBase*>(m_food[i]))))
				{
					m_food[i]->SetState(F_HIT);
					m_food[i]->SetSpd(Vector2(0.0f, Player::SPEED_Y));

					/* 下のパンとくっついたら、パンと一緒に移動 */
					if (m_food[i]->Collision(*(dynamic_cast<ObjectBase*>(m_bread[DOWN]))))
					{
						m_food[i]->SetSpd(Vector2(Player::SPEED_EXIT_X, 0.0f));
					}
				}

				/* 下のパン */
				if (m_bread[DOWN]->Collision(*(dynamic_cast<ObjectBase*>(m_food[i]))))
				{
					m_food[i]->SetState(F_HIT);
					m_food[i]->SetSpd(Vector2(0.0f, -Player::SPEED_Y));

					/* 上のパンとくっついたら、パンと一緒に移動 */
					if (m_food[i]->Collision(*(dynamic_cast<ObjectBase*>(m_bread[UP]))))
					{
						m_food[i]->SetSpd(Vector2(Player::SPEED_EXIT_X, 0.0f));
					}
				}
			}

			/* 具も場外に行ったら */
			if ((m_bread[UP]->IsExitComplete()))
			{
				if((m_food[i]->GetState() == F_HIT))
				{
					m_food[i]->SetState(F_NONE);
					// TODO:スコア加算？
					g_score++;
				}
				else if (m_food[i]->GetState() == F_MOVE)
				{
					//m_food[i]->SetSpeed(5);
					m_food[i]->Buck();
				}
			}
		}
	}

	const int BREAD_LIMIT_TIME_MS = 360;		// パンの寿命(6 * 60 = 360ms)

	/* 一定時間経ったらパンふにゃふにゃ(退場) */
	if (m_time_ms >= BREAD_LIMIT_TIME_MS)
	{
		m_bread[UP]->SetSpd(Vector2(0.0f, 0.0f));
		m_bread[DOWN]->SetSpd(Vector2(0.0f, 0.0f));

		m_bread[UP]->Exit();
		m_bread[DOWN]->Exit();
	}

	/* パン同士のあたり判定 */
	if (m_bread[UP]->Collision(*(dynamic_cast<ObjectBase*>(m_bread[DOWN]))))
	{
		if (m_bread[UP]->GetSpd().y != 0.0f || m_bread[DOWN]->GetSpd().y != 0.0f)
		{
			m_bread[UP]->SetSpd(Vector2(0.0f, 0.0f));
			m_bread[DOWN]->SetSpd(Vector2(0.0f, 0.0f));
			// 挟んだ音
			ADX2Le::Play(CRI_CUESHEET_0_HASAMU2);
		}

		m_bread[UP]->Exit();
		m_bread[DOWN]->Exit();
	}

	// screen効果の座標変更
	if (m_screen_effect) 
	{
		m_screen_effect->Move();
	}

	//WAVEの更新
	UpdateWave();

	/* 時間更新 */
	++m_time_ms;
	if (m_bread[UP]->IsEnter())
	{
		m_time_ms = 0;
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
	//背景
	DrawRectTexture(0.0f, 0.0f, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, m_backplay_image);

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

	//メッセージ板の描画
	if (m_plate != nullptr)
	{
		m_plate->Render();
	}

	/*wchar_t buf[256];
	swprintf_s(buf, 256, L"PLAY");*/
	// screenエフェクトの描画
	if (m_screen_effect)
	{
		m_screen_effect->Render();
	}
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
	int cnt = 0;

	//移動中の魚がいなければクリア
	for (int i = 0; i < FOOD_NUM; i++)
	{
		//食材が存在している状態なら
		if (m_food[i] != nullptr)
		{
			if (m_food[i]->GetState() == F_NONE)
			{
				++cnt;
			}
		}
	}
	//クリア時の処理
	//if (m_wave_clear)
	if(cnt==FOOD_NUM)
	{
		//プレートの出現
		if (m_plate == nullptr)
		{
			if (m_bread_num > 1)
			{
				m_plate = new MessagePlate(NEXT);
			}
			else
			{
				m_plate = new MessagePlate(FINISH);
			}
		}

		//プレートが消えたらWAVE切り替え
		if (m_plate->GetState() == MP_NONE)
		{
			//プレートの破棄
			delete m_plate;
			m_plate = nullptr;

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
				// TODO:パン登場
				/* パン登場 */
				m_bread[UP]->SetEnter();
				m_bread[DOWN]->SetEnter();

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

	const RECT    BREAD_COLLISION_RECT = { 0,0,100,45 };		// 当たり判定の幅、高さ
	const Vector2 BREAD_POS[BREAD_NUM] = { Vector2(640.0f + 100.0f,5.0f),Vector2(640.0f + 100.0f,360.0f) };	// それぞれのスタートライン(上、下)

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
