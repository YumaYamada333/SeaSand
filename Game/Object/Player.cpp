/*-------------------------------------
プレイヤークラスの定義(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* インクルードファイル */
#include "Player.h"

/* 名前空間の使用 */
using namespace DirectX::SimpleMath;

/* メンバ関数の定義 */
/*------------------------------------
Player::Player

summary:コンストラクタ
param  :なし(void)
return :存在しない
------------------------------------*/
Player::Player(Texture * handle, const RECT &grp, const Vector2 pos, Vector2 spd, int state)
	:ObjectBase(handle,grp,pos,spd,state)
{}

Player::~Player()
{
}
