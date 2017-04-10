//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Food.cpp
//!
//! @brief  フードクラスのソースファイル
//!
//! @date   2017/04/07
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//ヘッダのインクルード＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "..\GameMain.h"
#include "..\Object\Player.h"
#include "Food.h"

//名前空間＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
using namespace DirectX;
using namespace DirectX::SimpleMath;

//定数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//食材のサイズ
const float F_WIDTH = 128.0f;	//幅
const float F_HEIGHT = 64.0f;	//高さ

//食材の縦の間隔
const float F_LINE_HEIGHT = 90.0f;

//食材の向き
enum FOOD_DIRECTION
{
	RIGHT,
	LEFT,
};

//食材が目指すラインの番号
enum FOOD_LINE_NUM
{
	LINE_1,
	LINE_2,
	LINE_3,
	LINE_4,
	LINE_5,
	START_LINE,
};

//食材が目指すX座標(5パターン)
enum FOOD_MOVE_X
{
	POINT_LINE_1 = (64),
	POINT_LINE_2 = (192),
	POINT_LINE_3 = (320),
	POINT_LINE_4 = (448),
	POINT_LINE_5 = (576),
};

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//----------------------------------------------------------------------
//! @brief 食材のコンストラクタ
//!
//! @param[in] 食材の情報
//----------------------------------------------------------------------
Food::Food(int food_type, int food_num, int line_num, int meet_time)
	:m_food_type(food_type)
	,m_num(food_num)
	,m_meet_time(meet_time)
	,m_time(0)
	,m_turn_count(0)
	,m_buck_flag(false)
	,m_buck_time(0)
	/*,m_hit_bread_dis(Vector2(0.0f,0.0f))*/
{
	//初期位置とスピードの設定
	SetInitPos(line_num);
	
	//テクスチャの設定
	SetTexture();

	//状態変更
	m_state = F_MOVE;
}

//----------------------------------------------------------------------
//! @brief 食材のデストラクタ
//!
//! @param[in] なし
//----------------------------------------------------------------------
Food::~Food()
{
	delete m_handle;
}

//----------------------------------------------------------------------
//! @brief 食材の更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Food::Update()
{
	if (m_state == F_MOVE && m_buck_flag ==false)
	{
		m_time++;

		//1秒たっていて、目的地変更回数が規定数に達していなかったら目的地変更
		if (m_time > 60 && m_turn_count <= WAVE_TIME + 1)
		{
			if (m_turn_count == m_meet_time - 1)
			{
				//目的地変更(指定地点)
				SetSpeed(m_last_line);
			}
			else if (m_turn_count == WAVE_TIME)
			{
				//目的地変更(スタート地点)
				SetSpeed(START_LINE);
			}
			else
			{
				//目的地変更(ランダム)
				SetSpeed(GetRand(F_LINE_NUM));
			}

			//目的地変更カウント加算
			m_turn_count++;

			//タイムの初期化
			m_time = 0;
		}
		//目的地変更回数が規定数に達していたら状態を変更
		else if (m_turn_count > WAVE_TIME + 1)
		{
			m_state = F_NONE;
		}

		//テクスチャの再設定
		SetTexture();
	}
	
	if (m_buck_flag)
	{
		m_buck_time++;

		if (m_buck_time > 120)
		{
			m_state = F_NONE;
		}
	}
}

//----------------------------------------------------------------------
//! @brief 食材の座標更新
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Food::Move()
{
	if (m_state == F_MOVE || m_state == F_HIT)
	{
		// 座標更新
		m_pos += m_spd;
	}
}

//----------------------------------------------------------------------
//! @brief 食材の判定結果
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Food::Result()
{

}

//----------------------------------------------------------------------
//! @brief 食材とパンが当たった時の処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Food::HitBread(Player obj)
{
	//状態を変更
	m_state = F_HIT;

	//パンのスピードを取得
	m_spd = obj.GetSpd();
}

//----------------------------------------------------------------------
//! @brief 食材がはける
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Food::Buck()
{
	SetSpeed(START_LINE);
	m_buck_flag = true;
}


//----------------------------------------------------------------------
//! @brief 食材のテクスチャを設定する関数
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Food::SetTexture()
{
	//画像のy座標
	int grpy = 0;
	delete m_handle;

	//テクスチャの設定
	switch (m_food_type)
	{
	case FISH:
		m_handle = new Texture(L"Resources\\Images\\fish.png");
		break;
	case CLAB:
		m_handle = new Texture(L"Resources\\Images\\clab.png");
		break;
	}

	//基準点の設定
	m_center = Vector2(F_WIDTH / 2, F_HEIGHT / 2);

	//短形の設定
	if (m_dir == RIGHT)
	{ grpy = static_cast<int>(F_HEIGHT); }
	else
	{ grpy = 0; }
	m_grp = { 0, grpy, static_cast<LONG>(F_WIDTH), grpy + static_cast<LONG>(F_HEIGHT) };
}

//----------------------------------------------------------------------
//! @brief 初期位置を設定する関数
//!
//! @param[in] 指定秒数でめざすライン(番号)
//!
//! @return なし
//----------------------------------------------------------------------
void Food::SetInitPos(int line_num)
{
	int init_pos = GetRand(2);

	//初期位置の設定(奇数：左端or偶数：右端)
	if (init_pos % 2 == 1)
	{
		m_pos = Vector2(-F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}
	else
	{
		m_pos = Vector2(SCREEN_WIDTH + F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}

	//スタート地点の座標取得
	m_start_line = static_cast<int>(m_pos.x);

	//指定秒数でめざすラインの設定
	m_last_line = line_num;

	//速度決定(5本のラインからランダムの位置へ向かう)
	SetSpeed(GetRand(F_LINE_NUM));
	
}

//----------------------------------------------------------------------
//! @brief 食材の速度を設定する関数
//!
//! @param[in] めざすライン(番号)
//!
//! @return なし
//----------------------------------------------------------------------
void Food::SetSpeed(int line_num)
{
	//速度決定用変数
	int distance = 0;		//距離
	float spdx = 0.0f;		//速度

	//めざすラインの決定
	switch (line_num)
	{
	case LINE_1:
		m_line = POINT_LINE_1;
		break;
	case LINE_2:
		m_line = POINT_LINE_2;
		break;
	case LINE_3:
		m_line = POINT_LINE_3;
		break;
	case LINE_4:
		m_line = POINT_LINE_4;
		break;
	case LINE_5:
		m_line = POINT_LINE_5;
		break;
	case START_LINE:
		m_line = m_start_line;
	}

	//移動距離の計算、向きの設定
	if (m_line > m_pos.x)
	{
		distance = static_cast<int>(m_line - m_pos.x);
		m_dir = RIGHT;
	}
	else
	{	
		distance = static_cast<int>(m_pos.x - m_line);
		m_dir = LEFT;
	}

	//スピードを計算
	spdx = distance / 60.0f;
	if (m_dir == LEFT)
	{
		spdx = spdx * -1;
	}
	
	m_spd = Vector2(spdx, 0.0f);
}