/*-------------------------------------
�v���C���[�N���X�̒�`(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* �C���N���[�h�t�@�C�� */
#include "Player.h"

/* ���O��Ԃ̎g�p */
using namespace DirectX::SimpleMath;

/* �����o�֐��̒�` */
/*------------------------------------
Player::Player

summary:�R���X�g���N�^
param  :�Ȃ�(void)
return :���݂��Ȃ�
------------------------------------*/
Player::Player(Texture * handle, const RECT &grp, const Vector2 pos, Vector2 spd, int state)
	:ObjectBase(handle,grp,pos,spd,state)
{}

Player::~Player()
{
}
