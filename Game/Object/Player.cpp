/*-------------------------------------
�v���C���[�N���X�̒�`(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* �C���N���[�h�t�@�C�� */
#include "Player.h"

#include "../../Common.h"

/* ���O��Ԃ̎g�p */
using namespace DirectX::SimpleMath;

/* �ÓI�����o�ϐ��̒�` */
// TODO:�v���C���[���x�͂����Œ����I
const float Player::SPEED_X = 5.0f;		// ���x�w
const float Player::SPEED_Y = 10.0f;		// ���x�x

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
Player::~Player

summary:�f�X�g���N�^
param  :���݂��Ȃ�
return :���݂��Ȃ�
------------------------------------*/
Player::~Player()
{}

/*------------------------------------
Player::Update

summary:�X�V
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Player::Update()
{
	Move();
}

/*------------------------------------
Player::MoveLeft

summary:���ړ�
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Player::MoveLeft()
{
	SetSpd(Vector2(-SPEED_X, 0.0f));
}

/*------------------------------------
Player::MoveRight

summary:�E�ړ�
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Player::MoveRight()
{
	SetSpd(Vector2(SPEED_X, 0.0f));
}

/*------------------------------------
Player::MoveReset

summary:�ړ����Z�b�g
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Player::MoveReset()
{
	if (!IsSand())
		SetSpd(Vector2(0.0f, 0.0f));
}

/*--------------------------------------------
Player::Sand

summary:�͂���
param  :�H�p���^�C�v(BREAD_TYPE)
return :�Ȃ�(void)
--------------------------------------------*/
void Player::Sand(BREAD_TYPE type)
{
	switch (type)
	{
	case UP:
		SetSpd(Vector2(0.0f, SPEED_Y));
		break;

	case DOWN:
		SetSpd(Vector2(0.0f, -SPEED_Y));
		break;
	}
}

/*--------------------------------------------
Player::IsSand

summary:�͂���ł�H
param  :�Ȃ�(void)
return :�͂���ł�(true)�A�͂���łȂ�(false)
--------------------------------------------*/
bool Player::IsSand()
{
	return m_spd.y != 0.0f ? true : false;
}

/*------------------------------------
Player::Move

summary:�ړ�
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Player::Move()
{
	m_pos += m_spd;
}