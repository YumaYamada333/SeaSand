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
	// 座標更新
	m_pos += m_spd;
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

	//めざす座標の設定
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

	//速度の設定
	switch (m_move_type)
	{
	case FM_1:
		m_spd = Vector2(-1.0f, 0.0f);
		break;
	case FM_2:
		m_spd = Vector2(1.0f, 0.0f);
		break;
	case FM_3:
		m_spd = Vector2(-1.0f, 0.0f);
		break;
	}
}
