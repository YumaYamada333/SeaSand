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
#include "Food.h"

//名前空間＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
using namespace DirectX;
using namespace DirectX::SimpleMath;

//定数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//食材のスピード
//const float N_SPEED = 0.5f;
//const float L_SPEED = 0.2f;
//const float H_SPEED = 1.0f;

//食材のサイズ
const float F_WIDTH = 128.0f;	//幅
const float F_HEIGHT = 64.0f;	//高さ

//食材の縦の間隔
const float F_LINE_HEIGHT = 90.0f;

//食材の移動パターン
enum FOOD_MOVE_TYPE
{
	FM_1,
	FM_2,
	FM_3,
	FM_4,
	FM_5,
	FM_6,
};

//食材が目指すX座標(5パターン)
enum FOOD_MOVE_X
{
	LINE_1 = (64),
	LINE_2 = (192),
	LINE_3 = (320),
	LINE_4 = (448),
	LINE_5 = (576),
};

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//----------------------------------------------------------------------
//! @brief 食材のコンストラクタ
//!
//! @param[in] 食材の情報
//----------------------------------------------------------------------
Food::Food(int food_type, int move_type, int food_num, int line_num)
	:m_food_type(food_type)
	,m_move_type(move_type)
	,m_num(food_num)
	,m_time(0)
{
	//テクスチャの設定
	SetTexture();

	//初期位置とスピードの設定
	SetInitPos(line_num);
	
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
	if (m_state == F_MOVE)
	{
		m_time++;
		
		//行動パターンごとに行動変更
		switch (m_move_type)
		{
		case FM_3:
		case FM_4:
			if (m_time == static_cast<int>(WAVE_TIME / (m_turn_num + 1) * 60.0f))
			{
				SetSpeed(m_last_line);
			}
			break;
		case FM_5:
		case FM_6:
			if (m_time == static_cast<int>(WAVE_TIME / (m_turn_num + 1) * 60.0f))
			{
				SetSpeed(GetRand(F_LINE_NUM));
			}
			if (m_time == static_cast<int>(WAVE_TIME / (m_turn_num + 1) * 60.0f * 2))
			{
				SetSpeed(m_last_line);
			}
			break;
		default:
			break;
		}
		int a;
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
	if (m_state == F_MOVE)
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
//! @brief 食材の描画
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
//void Food::Render() const
//{
//
//}

//----------------------------------------------------------------------
//! @brief 状態変更する関数
//!
//! @param[in] 変更後の状態
//!
//! @return なし
//----------------------------------------------------------------------
void Food::ChangeState(int state)
{
	m_state = state;
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
	m_grp = { 0, 0, static_cast<LONG>(F_WIDTH), static_cast<LONG>(F_HEIGHT) };
}

//----------------------------------------------------------------------
//! @brief 食材の移動パターンごとに初期位置を設定する関数
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Food::SetInitPos(int line_num)
{
	//初期位置の設定(左端or右端)
	if (m_move_type % 2 == 1)
	{
		m_pos = Vector2(-F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}
	else
	{
		m_pos = Vector2(SCREEN_WIDTH + F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}

	//最終的にめざすラインの設定
	m_last_line = line_num;

	//速度決定
	if (m_move_type == FM_1 ||
		m_move_type == FM_2)
	{
		SetSpeed(m_last_line);
	}
	else
	{
		SetSpeed(GetRand(F_LINE_NUM));
	}
}

//----------------------------------------------------------------------
//! @brief 食材の速度を設定する関数
//!
//! @param[in] めざすライン
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
	case 1:
		m_line = LINE_1;
		break;
	case 2:
		m_line = LINE_2;
		break;
	case 3:
		m_line = LINE_3;
		break;
	case 4:
		m_line = LINE_4;
		break;
	case 5:
		m_line = LINE_5;
		break;
	}

	//行動パターンごとに情報を代入
	switch (m_move_type)
	{
	case FM_1:
		//距離の計算
		distance = m_pos.x - m_line;
		//ターン回数の設定
		m_turn_num = 0;
		break;
	case FM_2:
		//距離の計算
		distance = m_line - m_pos.x;
		//ターン回数の設定
		m_turn_num = 0;
		break;
	case FM_3:
		//距離の計算
		distance = m_pos.x - m_line;
		//ターン回数の設定
		m_turn_num = 1;
		break;
	case FM_4:
		//距離の計算
		distance = m_line - m_pos.x;
		//ターン回数の設定
		m_turn_num = 1;
		break;
	case FM_5:
		//距離の計算
		distance = m_pos.x - m_line;
		//ターン回数の設定
		m_turn_num = 2;
		break;
	case FM_6:
		//距離の計算
		distance = m_line - m_pos.x;
		//ターン回数の設定
		m_turn_num = 2;
		break;
	}
	//スピードを計算
	spdx = distance / (WAVE_TIME / (m_turn_num + 1)) / 60.0f;
	if (m_move_type % 2 == 0)
	{
		spdx = spdx * -1;
	}
	
	m_spd = Vector2(spdx, 0.0f);
}