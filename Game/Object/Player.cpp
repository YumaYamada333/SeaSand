/*-------------------------------------
�v���C���[�N���X�̒�`(Player.cpp)

date  :2017.04.07
Author:Miyu Hara
-------------------------------------*/
/* �C���N���[�h�t�@�C�� */
#include "Player.h"

#include "../../Common.h"

/* ���O��Ԃ̎g�p */
// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;

/* �ÓI�����o�ϐ��̒�` */
// TODO:�v���C���[���x�͂����Œ����I
const float Player::SPEED_X = 5.0f;		// ���x�w
const float Player::SPEED_Y = 10.0f;	// ���x�x

const int Player::SCREEN_WIDTH = 640;	// �摜�̕�(��Ɨp)

/* �����o�֐��̒�` */
/*------------------------------------
Player::Player

summary:�R���X�g���N�^
param  :�Ȃ�(void)
return :���݂��Ȃ�
------------------------------------*/
Player::Player(Texture * handle, const RECT &grp, const Vector2 pos, Vector2 spd, int state, BREAD_TYPE type)
	:ObjectBase(handle,grp,pos,spd,state),
	 m_type(type),
	 m_is_enter(false),
	 m_is_exit(false)
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
	if (m_is_enter)
	{
		Enter();
	}

	Move();
}

void Player::Render() const
{
	//TODO:�摜�̕��A�����͂����Œ����I
	RECT rect = { 0,0,180,180 };		// �摜�̕��A����
	
	g_spriteBatch->Draw(m_handle->m_pTexture, m_pos, &rect
		, Colors::White, 0.0f, m_center, Vector2(1.0f, 1.0f));
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
	if (!IsSand() && !m_is_exit)
	{
		SetSpd(Vector2(0.0f, 0.0f));
	}
}

/*--------------------------------------------
Player::Sand

summary:�͂���
param  :�Ȃ�(void)
return :�Ȃ�(void)
--------------------------------------------*/
void Player::Sand()
{
	switch (m_type)
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
Player::Enter

summary:����
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Player::Enter()
{
	/* �X�^�[�g�ʒu�ɏC��(�}�W�b�N�i���o�[���߂�Ȃ���) */
	switch (m_type)
	{
	case UP:
		SetPos(Vector2(m_pos.x, 5.0f));
		break;

	case DOWN:
		SetPos(Vector2(m_pos.x, 360.0f));
		break;
	}

	MoveLeft();

	/* ���ꊮ�� */
	if (IsEnterComplete())
	{
		m_is_enter = false;
		// TODO:�c�@���炷
	}
}

/*------------------------------------
Player::IsEnter

summary:���ꒆ�H
param  :�Ȃ�(void)
return :���ꒆ(true)�A������(false)
------------------------------------*/
bool Player::IsEnter()
{
	return m_is_enter;
}

/*------------------------------------
Player::Exit

summary:�ޏ�
param  :�Ȃ�(void)
return :�Ȃ�(void)
------------------------------------*/
void Player::Exit()
{
	MoveRight();
	m_is_exit = true;

	/* �ޏꂵ����܂����� */
	if (IsExitComplete())
	{
		m_is_exit  = false;
		m_is_enter = true;
	}

}

/*------------------------------------
Player::IsExit

summary:�ޏꒆ�H
param  :�Ȃ�(void)
return :�ޏꒆ(true)�A������(false)
------------------------------------*/
bool Player::IsExit()
{
	return m_is_exit;
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

/*------------------------------------
Player::IsEnterComplete

summary:���ꊮ�������H
param  :�Ȃ�(void)
return :����(true)�A������(false)
------------------------------------*/
bool Player::IsEnterComplete()
{
	if (m_pos.x <= 300.0f)		// �X�^�[�g�ʒu(�}�W�b�N�i���o�[���߂�Ȃ���)
	{
		return true;
	}
	return false;
}

/*------------------------------------
Player::IsExitComplete

summary:�ޏꊮ�������H
param  :�Ȃ�(void)
return :����(true)�A������(false)
------------------------------------*/
bool Player::IsExitComplete()
{
	/* ��ʊO�ɏo�Ă��邩�H */
	if ((m_pos.x - 100.0f) >= SCREEN_WIDTH)		// 100�͓���ʒu�C��
	{
		return true;
	}

	return false;
}