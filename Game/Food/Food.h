//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Food.h
//!
//! @brief  フードクラスのヘッダファイル
//!
//! @date   2017/04/07
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

//ヘッダのインクルード＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "..\Object\ObjectBase.h"

class Player;

//定数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

//食材の種類の数
const int FOOD_TYPE_NUM = 2;

//めざすラインの数
const int F_LINE_NUM = 5;

//1WAVEの時間
const int WAVE_TIME = 6;

//食材の種類
enum FOOD_TYPE
{
	FISH,
	CLAB,
};

//食材の状態
enum FOOD_STATE
{
	F_NONE,		//存在しない
	F_MOVE,		//動いている
	F_HIT,		//パンに当たっている
};

//クラス＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class Food : public ObjectBase
{
private:
	int m_dir;				//向き
	int m_food_type;		//食材の種類
	int m_num;				//何個目の食材か
	int m_line;				//食材が目指すライン(x座標)
	int m_last_line;		//食材が指定秒数で目指すライン(番号)
	int m_start_line;		//食材のスタート地点(x座標)
	int m_meet_time;		//食材が集まるタイミング
	int m_time;				//食材の移動時間制御用
	int m_turn_count;		//目的ライン変更回数
	DirectX::SimpleMath::Vector2 m_hit_bread_dis;	//当たったパンと自分との距離

public:
	Food(int food_type, int food_num, int m_line, int meet_time);	// コンストラクタ
	~Food();				// デストラクタ
	void Update();			// 更新処理
	void Move();			// 座標更新
	void Result();			// 判定結果
	void HitBread(Player obj);		//パンと当たった時の処理

private:
	void SetTexture();		//テクスチャを設定する関数
	void SetInitPos(int line_num);		//初期位置を設定する関数
	void SetSpeed(int line);			//速度を設定する関数
};