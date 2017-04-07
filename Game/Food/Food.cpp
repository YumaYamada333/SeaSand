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
	// ���W�X�V
	m_pos += m_spd;
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

	//�߂������W�̐ݒ�
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

	//���x�̐ݒ�
	switch (m_move_type)
	{
	case FM_1:
		m_spd = Vector2(-1.0f, 0.0f);
		break;
	case FM_2:
		m_spd = Vector2(1.0f, 0.0f);
		break;
	case FM_3:
		m_spd = Vector2(-1.0f, 0.0f);
		break;
	}
}
