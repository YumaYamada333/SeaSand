//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Food.cpp
//!
//! @brief  �t�[�h�N���X�̃\�[�X�t�@�C��
//!
//! @date   2017/04/07
//!
//! @author Yuma Yamada
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//�w�b�_�̃C���N���[�h����������������������������������������������������������
#include "..\GameMain.h"
#include "Food.h"

//���O��ԁ���������������������������������������������������������������������
using namespace DirectX;
using namespace DirectX::SimpleMath;

//�萔��������������������������������������������������������������������������

//�H�ނ̃X�s�[�h
//const float N_SPEED = 0.5f;
//const float L_SPEED = 0.2f;
//const float H_SPEED = 1.0f;

//�H�ނ̃T�C�Y
const float F_WIDTH = 128.0f;	//��
const float F_HEIGHT = 64.0f;	//����

//�H�ނ̏c�̊Ԋu
const float F_LINE_HEIGHT = 90.0f;

//�H�ނ̈ړ��p�^�[��
enum FOOD_MOVE_TYPE
{
	FM_1,
	FM_2,
	FM_3,
	FM_4,
	FM_5,
	FM_6,
};

//�H�ނ��ڎw��X���W(5�p�^�[��)
enum FOOD_MOVE_X
{
	LINE_1 = (64),
	LINE_2 = (192),
	LINE_3 = (320),
	LINE_4 = (448),
	LINE_5 = (576),
};

//�֐��̒�`��������������������������������������������������������������������

//----------------------------------------------------------------------
//! @brief �H�ނ̃R���X�g���N�^
//!
//! @param[in] �H�ނ̏��
//----------------------------------------------------------------------
Food::Food(int food_type, int move_type, int food_num, int line_num)
	:m_food_type(food_type)
	,m_move_type(move_type)
	,m_num(food_num)
	,m_time(0)
{
	//�e�N�X�`���̐ݒ�
	SetTexture();

	//�����ʒu�ƃX�s�[�h�̐ݒ�
	SetInitPos(line_num);
	
	//��ԕύX
	m_state = F_MOVE;
}

//----------------------------------------------------------------------
//! @brief �H�ނ̃f�X�g���N�^
//!
//! @param[in] �Ȃ�
//----------------------------------------------------------------------
Food::~Food()
{
	delete m_handle;
}

//----------------------------------------------------------------------
//! @brief �H�ނ̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::Update()
{
	if (m_state == F_MOVE)
	{
		m_time++;
		
		//�s���p�^�[�����Ƃɍs���ύX
		switch (m_move_type)
		{
		case FM_3:
		case FM_4:
			if (m_time == static_cast<int>(WAVE_TIME / (m_turn_num + 1) * 60.0f))
			{
				SetSpeed(m_last_line);
			}
			break;
		case FM_5:
		case FM_6:
			if (m_time == static_cast<int>(WAVE_TIME / (m_turn_num + 1) * 60.0f))
			{
				SetSpeed(GetRand(F_LINE_NUM));
			}
			if (m_time == static_cast<int>(WAVE_TIME / (m_turn_num + 1) * 60.0f * 2))
			{
				SetSpeed(m_last_line);
			}
			break;
		default:
			break;
		}
		int a;
	}
}

//----------------------------------------------------------------------
//! @brief �H�ނ̍��W�X�V
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::Move()
{
	if (m_state == F_MOVE)
	{
		// ���W�X�V
		m_pos += m_spd;
	}
}

//----------------------------------------------------------------------
//! @brief �H�ނ̔��茋��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::Result()
{

}

//----------------------------------------------------------------------
//! @brief �H�ނ̕`��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
//void Food::Render() const
//{
//
//}

//----------------------------------------------------------------------
//! @brief ��ԕύX����֐�
//!
//! @param[in] �ύX��̏��
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::ChangeState(int state)
{
	m_state = state;
}

//----------------------------------------------------------------------
//! @brief �H�ނ̃e�N�X�`����ݒ肷��֐�
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::SetTexture()
{
	//�e�N�X�`���̐ݒ�
	switch (m_food_type)
	{
	case FISH:
		m_handle = new Texture(L"Resources\\Images\\fish.png");
		break;
	case CLAB:
		m_handle = new Texture(L"Resources\\Images\\clab.png");
		break;
	}

	//��_�̐ݒ�
	m_center = Vector2(F_WIDTH / 2, F_HEIGHT / 2);

	//�Z�`�̐ݒ�
	m_grp = { 0, 0, static_cast<LONG>(F_WIDTH), static_cast<LONG>(F_HEIGHT) };
}

//----------------------------------------------------------------------
//! @brief �H�ނ̈ړ��p�^�[�����Ƃɏ����ʒu��ݒ肷��֐�
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::SetInitPos(int line_num)
{
	//�����ʒu�̐ݒ�(���[or�E�[)
	if (m_move_type % 2 == 1)
	{
		m_pos = Vector2(-F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}
	else
	{
		m_pos = Vector2(SCREEN_WIDTH + F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}

	//�ŏI�I�ɂ߂������C���̐ݒ�
	m_last_line = line_num;

	//���x����
	if (m_move_type == FM_1 ||
		m_move_type == FM_2)
	{
		SetSpeed(m_last_line);
	}
	else
	{
		SetSpeed(GetRand(F_LINE_NUM));
	}
}

//----------------------------------------------------------------------
//! @brief �H�ނ̑��x��ݒ肷��֐�
//!
//! @param[in] �߂������C��
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::SetSpeed(int line_num)
{
	//���x����p�ϐ�
	int distance = 0;		//����
	float spdx = 0.0f;		//���x

	//�߂������C���̌���
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

	//�s���p�^�[�����Ƃɏ�����
	switch (m_move_type)
	{
	case FM_1:
		//�����̌v�Z
		distance = m_pos.x - m_line;
		//�^�[���񐔂̐ݒ�
		m_turn_num = 0;
		break;
	case FM_2:
		//�����̌v�Z
		distance = m_line - m_pos.x;
		//�^�[���񐔂̐ݒ�
		m_turn_num = 0;
		break;
	case FM_3:
		//�����̌v�Z
		distance = m_pos.x - m_line;
		//�^�[���񐔂̐ݒ�
		m_turn_num = 1;
		break;
	case FM_4:
		//�����̌v�Z
		distance = m_line - m_pos.x;
		//�^�[���񐔂̐ݒ�
		m_turn_num = 1;
		break;
	case FM_5:
		//�����̌v�Z
		distance = m_pos.x - m_line;
		//�^�[���񐔂̐ݒ�
		m_turn_num = 2;
		break;
	case FM_6:
		//�����̌v�Z
		distance = m_line - m_pos.x;
		//�^�[���񐔂̐ݒ�
		m_turn_num = 2;
		break;
	}
	//�X�s�[�h���v�Z
	spdx = distance / (WAVE_TIME / (m_turn_num + 1)) / 60.0f;
	if (m_move_type % 2 == 0)
	{
		spdx = spdx * -1;
	}
	
	m_spd = Vector2(spdx, 0.0f);
}