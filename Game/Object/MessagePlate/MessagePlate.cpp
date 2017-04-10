//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   MessagePlate.cpp
//!
//! @brief  ���b�Z�[�W�̃\�[�X�t�@�C��
//!
//! @date   2017/04/10
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//�w�b�_�̃C���N���[�h����������������������������������������������������������
#include "..\..\GameMain.h"
#include "MessagePlate.h"

//���O��ԁ���������������������������������������������������������������������
using namespace DirectX;
using namespace DirectX::SimpleMath;

//�萔��������������������������������������������������������������������������
//�X�s�[�h
const float MP_SPEED = -640.0f / 60.0f;

//�ړ����䎞��
const int MOVE_TIME = 60;
const int WATE_TIME = 30;

//�֐��̒�`��������������������������������������������������������������������

//----------------------------------------------------------------------
//! @brief ���b�Z�[�W�̃R���X�g���N�^
//!
//! @param[in] �H�ނ̏��
//----------------------------------------------------------------------
MessagePlate::MessagePlate(int type)
	:m_time(0)
	,m_type(type)
{
	//��ނ�ݒ�
	m_state = MP_MOVE;
	//�e�N�X�`����ݒ�
	SetTexture();
	//�����ʒu�ƃX�s�[�h��ݒ�
	SetInitPos();
}

//----------------------------------------------------------------------
//! @brief ���b�Z�[�W�̃f�X�g���N�^
//!
//! @param[in] �Ȃ�
//----------------------------------------------------------------------
MessagePlate::~MessagePlate()
{
	delete m_handle;
}

//----------------------------------------------------------------------
//! @brief ���b�Z�[�W�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MessagePlate::Update()
{
	m_time++;

	//�ړ���ԂȂ�ړ�
	if (m_state == MP_MOVE)
	{
		//�ړ�
		if (m_time < MOVE_TIME)
		{
			m_spd = Vector2(MP_SPEED, 0.0f);
		}
		//�ҋ@
		if (m_time >= MOVE_TIME && m_time < MOVE_TIME + WATE_TIME)
		{
			m_spd = Vector2(0.0f, 0.0f);
		}
		//�ړ�
		if (m_time >= MOVE_TIME + WATE_TIME)
		{
			m_spd = Vector2(MP_SPEED, 0.0f);
		}
	}

	//���[�܂ōs�����������
	if (m_pos.x < -SCREEN_WIDTH)
	{
		m_state = MP_NONE;
	}
}

//----------------------------------------------------------------------
//! @brief ���b�Z�[�W�̃e�N�X�`����ݒ肷��֐�
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MessagePlate::SetTexture()
{
	//�e�N�X�`���̐ݒ�
	switch (m_type)
	{
	case START:
		m_handle = new Texture(L"Resources\\Images\\start.png");
		break;
	case NEXT:
		m_handle = new Texture(L"Resources\\Images\\next.png");
		break;
	case FINISH:
		m_handle = new Texture(L"Resources\\Images\\finish.png");
		break;
	}

	//��_�̐ݒ�
	m_center = Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//�Z�`�̐ݒ�
	m_grp = { 0, 0, static_cast<LONG>(SCREEN_WIDTH), static_cast<LONG>(SCREEN_HEIGHT) };
}

//----------------------------------------------------------------------
//! @brief �����ʒu��ݒ肷��֐�
//!
//! @param[in] �w��b���ł߂������C��(�ԍ�)
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MessagePlate::SetInitPos()
{
	m_pos = Vector2(static_cast<float>(SCREEN_WIDTH + SCREEN_WIDTH / 2), static_cast<float>(SCREEN_HEIGHT / 2));
	m_spd = Vector2(MP_SPEED, 0.0f);
}