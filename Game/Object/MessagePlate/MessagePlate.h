//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   MessagePlate.h
//!
//! @brief  メッセージ板のヘッダファイル
//!
//! @date   2017/04/10
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once
//ヘッダのインクルード＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "..\ObjectBase.h"

//定数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//種類
enum PLATE_TYPE
{
	START,
	NEXT,
	FINISH,
};

//状態
enum PLATE_STATE
{
	MP_NONE,
	MP_MOVE,
};

//クラス＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class MessagePlate : public ObjectBase
{
private:
	int m_time;		//時間
	int m_type;		//種類

public:
	MessagePlate(int type);
	~MessagePlate();
	void Update();

private:
	void SetTexture();		//テクスチャを設定する関数
	void SetInitPos();		//初期位置を設定する関数
};