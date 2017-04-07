/*-------------------------------------
プレイヤークラス(Player.h)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* 多重インクルード防止 */
#pragma once

/* インクルードファイル */
#include "ObjectBase.h"

/* クラスの定義 */
class Player :public ObjectBase
{
public:
	Player(Texture* handle, const RECT& grp, const DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2 spd = DirectX::SimpleMath::Vector2(0.0f, 0.0f), int state = 0);	// コンストラクタ
	~Player();		// デストラクタ

};