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
#include "..\Object\Player.h"
#include "Food.h"

//���O��ԁ���������������������������������������������������������������������
using namespace DirectX;
using namespace DirectX::SimpleMath;

//�萔��������������������������������������������������������������������������

//�H�ނ̃T�C�Y
const float F_WIDTH = 128.0f;	//��
const float F_HEIGHT = 64.0f;	//����

//�H�ނ̏c�̊Ԋu
const float F_LINE_HEIGHT = 90.0f;

//�H�ނ̌���
enum FOOD_DIRECTION
{
	RIGHT,
	LEFT,
};

//�H�ނ��ڎw�����C���̔ԍ�
enum FOOD_LINE_NUM
{
	LINE_1,
	LINE_2,
	LINE_3,
	LINE_4,
	LINE_5,
	START_LINE,
};

//�H�ނ��ڎw��X���W(5�p�^�[��)
enum FOOD_MOVE_X
{
	POINT_LINE_1 = (64),
	POINT_LINE_2 = (192),
	POINT_LINE_3 = (320),
	POINT_LINE_4 = (448),
	POINT_LINE_5 = (576),
};

//�֐��̒�`��������������������������������������������������������������������

//----------------------------------------------------------------------
//! @brief �H�ނ̃R���X�g���N�^
//!
//! @param[in] �H�ނ̏��
//----------------------------------------------------------------------
Food::Food(int food_type, int food_num, int line_num, int meet_time)
	:m_food_type(food_type)
	,m_num(food_num)
	,m_meet_time(meet_time)
	,m_time(0)
	,m_turn_count(0)
	,m_buck_flag(false)
	,m_buck_time(0)
	/*,m_hit_bread_dis(Vector2(0.0f,0.0f))*/
{
	//�����ʒu�ƃX�s�[�h�̐ݒ�
	SetInitPos(line_num);
	
	//�e�N�X�`���̐ݒ�
	SetTexture();

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
	if (m_state == F_MOVE && m_buck_flag ==false)
	{
		m_time++;

		//1�b�����Ă��āA�ړI�n�ύX�񐔂��K�萔�ɒB���Ă��Ȃ�������ړI�n�ύX
		if (m_time > 60 && m_turn_count <= WAVE_TIME + 1)
		{
			if (m_turn_count == m_meet_time - 1)
			{
				//�ړI�n�ύX(�w��n�_)
				SetSpeed(m_last_line);
			}
			else if (m_turn_count == WAVE_TIME)
			{
				//�ړI�n�ύX(�X�^�[�g�n�_)
				SetSpeed(START_LINE);
			}
			else
			{
				//�ړI�n�ύX(�����_��)
				SetSpeed(GetRand(F_LINE_NUM));
			}

			//�ړI�n�ύX�J�E���g���Z
			m_turn_count++;

			//�^�C���̏�����
			m_time = 0;
		}
		//�ړI�n�ύX�񐔂��K�萔�ɒB���Ă������Ԃ�ύX
		else if (m_turn_count > WAVE_TIME + 1)
		{
			m_state = F_NONE;
		}

		//�e�N�X�`���̍Đݒ�
		SetTexture();
	}
	
	if (m_buck_flag)
	{
		m_buck_time++;

		if (m_buck_time > 120)
		{
			m_state = F_NONE;
		}
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
	if (m_state == F_MOVE || m_state == F_HIT)
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
//! @brief �H�ނƃp���������������̏���
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::HitBread(Player obj)
{
	//��Ԃ�ύX
	m_state = F_HIT;

	//�p���̃X�s�[�h���擾
	m_spd = obj.GetSpd();
}

//----------------------------------------------------------------------
//! @brief �H�ނ��͂���
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::Buck()
{
	SetSpeed(START_LINE);
	m_buck_flag = true;
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
	//�摜��y���W
	int grpy = 0;
	delete m_handle;

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
	if (m_dir == RIGHT)
	{ grpy = static_cast<int>(F_HEIGHT); }
	else
	{ grpy = 0; }
	m_grp = { 0, grpy, static_cast<LONG>(F_WIDTH), grpy + static_cast<LONG>(F_HEIGHT) };
}

//----------------------------------------------------------------------
//! @brief �����ʒu��ݒ肷��֐�
//!
//! @param[in] �w��b���ł߂������C��(�ԍ�)
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Food::SetInitPos(int line_num)
{
	int init_pos = GetRand(2);

	//�����ʒu�̐ݒ�(��F���[or�����F�E�[)
	if (init_pos % 2 == 1)
	{
		m_pos = Vector2(-F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}
	else
	{
		m_pos = Vector2(SCREEN_WIDTH + F_WIDTH, (m_num + 1) * F_LINE_HEIGHT);
	}

	//�X�^�[�g�n�_�̍��W�擾
	m_start_line = static_cast<int>(m_pos.x);

	//�w��b���ł߂������C���̐ݒ�
	m_last_line = line_num;

	//���x����(5�{�̃��C�����烉���_���̈ʒu�֌�����)
	SetSpeed(GetRand(F_LINE_NUM));
	
}

//----------------------------------------------------------------------
//! @brief �H�ނ̑��x��ݒ肷��֐�
//!
//! @param[in] �߂������C��(�ԍ�)
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
	case LINE_1:
		m_line = POINT_LINE_1;
		break;
	case LINE_2:
		m_line = POINT_LINE_2;
		break;
	case LINE_3:
		m_line = POINT_LINE_3;
		break;
	case LINE_4:
		m_line = POINT_LINE_4;
		break;
	case LINE_5:
		m_line = POINT_LINE_5;
		break;
	case START_LINE:
		m_line = m_start_line;
	}

	//�ړ������̌v�Z�A�����̐ݒ�
	if (m_line > m_pos.x)
	{
		distance = static_cast<int>(m_line - m_pos.x);
		m_dir = RIGHT;
	}
	else
	{	
		distance = static_cast<int>(m_pos.x - m_line);
		m_dir = LEFT;
	}

	//�X�s�[�h���v�Z
	spdx = distance / 60.0f;
	if (m_dir == LEFT)
	{
		spdx = spdx * -1;
	}
	
	m_spd = Vector2(spdx, 0.0f);
}