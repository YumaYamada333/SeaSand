/*-------------------------------------
�v���C���[�N���X�̒�`(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* �C���N���[�h�t�@�C�� */
#include "Player.h"

/* ���O��Ԃ̎g�p */
using namespace DirectX::SimpleMath;

/* �ÓI�����o�ϐ��̒�` */
const float Player::SPEED_X = 10.0f;		// ���x�w

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

/*------------------------------------
Player::Player

summary:�R���X�g���N�^
param  :�Ȃ�(void)
return :���݂��Ȃ�
------------------------------------*/
Player::~Player()
{}

void Player::Update()
{
	Move();
}

void Player::Move()
{
	m_pos += m_spd;
}

void Player::MoveLeft()
{
	SetSpd(Vector2(-SPEED_X, 0.0f));
}

void Player::MoveRight()
{
	SetSpd(Vector2(SPEED_X, 0.0f));
}

void Player::MoveReset()
{
	SetSpd(Vector2(0.0f, 0.0f));
}
